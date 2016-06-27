#!/usr/bin/perl
#+FHDR--------------------------------------------------------------------------
#  Copyright (c) 2012, Realtek Semiconductor Corporation
#  Realtek's Proprietary/Confidential
#
#  All rights reserved. No part of this design may be reproduced or stored
#  in a retrieval system, or transmitted, in any form or by any means,
#  electronic, mechanical, photocopying, recording, or otherwise,
#  without prior written permission of the Realtek Semiconductor Corporation.
#  Unauthorized reproduction, duplication, use, or disclosure of this
#  design will be deemed as infringement.
#-------------------------------------------------------------------------------
#  Author :  Rex Lin (x5741)
#  Keywords : ARM MMU Page Table
#  Version : 1.1
#  Description:
#     Simple ARM page table generator
#-FHDR--------------------------------------------------------------------------
#
# Mode   | VA                    | PA                    |TYPE     | bus   |inner  | outer
#=======+=======================+=======================+=========+=======+=======+========
# USER   | [0000_0000,1800_0000) | [0000_0000,1800_0000) | mem     | dbus  | -     | -
# USER   | [1800_0000,2000_0000) | [1800_0000,2000_0000) | device  | rbus  | -     | -
# USER   | [2000_0000,8000_0000) | [2000_0000,8000_0000) | mem     | dbus  | WB/WA | WB/WA
# USER   | [8000_0000,9800_0000) | [0000_0000,1800_0000) | mem     | dbus  | WB/WA | WB/WA
# USER   | [9800_0000,a000_0000) | [1800_0000,2000_0000) | device  | rbus  | -     | -
# USER   | [a000_0000,b800_0000) | [0000_0000,1800_0000) | mem     | dbus  | -     | -
# USER   | [b800_0000,c000_0000) | [1800_0000,2000_0000) | device  | rbus  | -     | -
# USER   | [c000_0000,ffff_ffff) | [c000_0000,ffff_ffff) | mem     | dbus  | -     | -
# ========================================================================================
# Memory    TEX   C B  Code | Description
# Type                      |
# ========================================================================================
# Strongly  000   0 0  0000 | Strongly Ordered
# Ordered                   |
# Device    000   0 1  0004 | Shared Device
# Normal    000   1 0  0008 | Outer and Inner WT, no WA
# Normal    000   1 1  000c | Outer and Inner WB, no WA
# Normal    001   0 0  1000 | Outer and Inner non-cacheable
# Device    010   0 0  2000 | Non-shared Device
# Normal    001   1 1  100c | Outer and Inner WB, WA
#                           |
# Normal    1BB   A A       | BB = Outer and AA = Inner Policy
# Normal    101   1 0  5008 | Outer WT no WA, Inner WB WA
# 
# 0 0 uncache
# 0 1 WB WA
# 1 0 WT no WA
# 1 1 WB no WA
#
# /*****************************************************************
#  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 
#  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
# +-----------------------+---+-+-+-+-----+---+-+-------+-+-+-+---+
# | Section Base Address  |0 0|n|S|A|T E X|A P|P|Domain |x|C|B|1 0|  
# |                       |   |G| |P|     |   | |       |n| | |   |
# |                       |   | | |X|     |   | |       | | | |   |
# +-----------------------+---+-+-+-+-----+---+-+-------+-+-+-+---+
# 
# [17]    (nG)    :
# [16]    (S)     : sharable
# [15]    (APX)   :
# [14:12] (TEX)   :
# [11:10] (AP)    : access permission : Privileged + User
# [9]     (P)     : 
# [8:5]   (domain):
# [4]     (xn)    :
# [3]     (C)     : cacheable
# [2]     (B)     : bufferable

use Getopt::Long;

# &help if (@ARGV == 0);

Getopt::Long::config("default","pass_through");
$Getopt::Long::autoabbrev = 0;
$result = Getopt::Long::GetOptions (
    "help",
    "output=s",
    "debug"
);

my $debug = 0;
my $outfile = "page_table.inc";

if (defined $opt_debug) {
    $debug = 1;
}

if (defined $opt_help) {
    &help;
}

if (defined $opt_output) {
   $outfile = $opt_output;
}

print "Output file: $outfile\n";
open (OFILE, "> $outfile") or die "Cannot open output file $outfile\n";

my $shareable = 1 << 16;
my $section = 0x2;

my $ap_kernel = 0xc00;
my $ap_user   = 0xc00;

my $tex_cache    = 0x100c;
my $tex_uncache  = 0x1000;
my $tex_device   = 0x0004;

my $page_attr;


print OFILE ".section \".boot.data\", \"aw\"\n";
print OFILE ".global MMU_PageTable\n";
print OFILE ".align 14\n";
print OFILE "MMU_PageTable:";

for ($idx=0; $idx < 0x1000; $idx=$idx+1) {
    # Default page attribute: falut (illegal, access will cause fault exception)
    # Put address to dont care filed for debug purpose
    $page_attr = $idx *0x00100000;

# Mode   | VA                    | PA                    |TYPE     | bus   |inner  | outer
#=======+=======================+=======================+=========+=======+=======+========
# USER   | [0000_0000,1800_0000) | [0000_0000,1800_0000) | mem     | dbus  | - 	   | -
# USER   | [1800_0000,2000_0000) | [1800_0000,2000_0000) | device  | rbus  | -     | -
# USER   | [2000_0000,8000_0000) | [2000_0000,8000_0000) | mem     | dbus  | WB/WA | WB/WA
# USER   | [8000_0000,9800_0000) | [0000_0000,1800_0000) | mem     | dbus  | WB/WA | WB/WA
# USER   | [9800_0000,a000_0000) | [1800_0000,2000_0000) | device  | rbus  | -     | -
# USER   | [a000_0000,b800_0000) | [0000_0000,1800_0000) | mem     | dbus  | -     | -
# USER   | [b800_0000,c000_0000) | [1800_0000,2000_0000) | device  | rbus  | -     | -
# USER   | [c000_0000,ffff_ffff) | [c000_0000,ffff_ffff) | mem     | dbus  | -     | -
    if (($idx >=0x000) && ($idx < 0x180))  { $page_attr = $idx*0x00100000 + $shareable | $section | $ap_kernel | $tex_uncache; }
    if (($idx >=0x180) && ($idx < 0x800))  { $page_attr = $idx*0x00100000 + $shareable | $section | $ap_kernel | $tex_device; }
    if (($idx >=0x800) && ($idx < 0x980))  { $page_attr = ($idx-0x800)*0x00100000 + $shareable | $section | $ap_kernel | $tex_cache; }
    if (($idx >=0x980) && ($idx < 0xa00))  { $page_attr = ($idx-0x800)*0x00100000 + $shareable | $section | $ap_kernel | $tex_device; }
    if (($idx >=0xa00) && ($idx < 0xb80))  { $page_attr = ($idx-0xa00)*0x00100000 + $shareable | $section | $ap_kernel | $tex_uncache; }
    if (($idx >=0xb80) && ($idx < 0xc00))  { $page_attr = ($idx-0xa00)*0x00100000 + $shareable | $section | $ap_kernel | $tex_device; }
    if (($idx >=0xc00) && ($idx < 0x1000)) { $page_attr = $idx*0x00100000 + $shareable + $section + $ap_kernel + $tex_uncache; }

#    printf "addr: %08x, page attr: %08x\n", $idx*0x00100000, $page_attr;
    if (($idx % 4) == 0) {
        printf OFILE "\n    .word 0x%08x", $page_attr;
    }
    else {
        printf OFILE ", 0x%08x", $page_attr;
    }
}
