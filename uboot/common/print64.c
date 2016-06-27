/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <asm/byteorder.h>
#include <asm/unaligned.h>

DECLARE_GLOBAL_DATA_PTR;

void print64_s(const char *ch)
{
    unsigned char ch8;
    unsigned char tmpBuf[1024]={0};

    memset(tmpBuf, 0x00, sizeof(tmpBuf));


    while (*ch != '\0') {
        ch8 = *ch;
        if (*ch++ == '\n') {
            ch8 = 0x0d;
            putc(ch8);
            ch8 = 0x0a;
        }
        putc(ch8);
    }
}

void print64_hex_val(unsigned long long val, unsigned int digitlen)
{
    unsigned char ch8;

    if( !digitlen ) {
        return;
    }

    print64_s("0x");
    digitlen--;
    do {
            ch8 = (val >> (digitlen << 2)) & 0xf;
            ch8 += (ch8 < 0xa ? 0x30 : 0x37);
            putc(ch8);
    } while(digitlen--);
}

void print64_hex32(unsigned long long value)
{
    print64_hex_val(value, 8);
}

void print64_hex64(unsigned long long value)
{
    print64_hex_val(value, 16);
}

void print64_dec(unsigned long long value)
{
    // 0x7FFFFFFF              = 134217727
    // 0x7FFFFFFFFFFFFFFF      = 9223372036854775807
    unsigned long long divider = 1000000000000000000;
    unsigned long long multiler;
    unsigned int pass_zero;

    pass_zero = 1;

    if( value >= 0x7FFFFFFFFFFFFFFFUL ) {
        print64_s("Input value is too large\n");
        return;
    }

    while( divider >= 10 ) {
        multiler = value / divider;

        if( multiler == 0 && pass_zero ) {

        }
        else {
            putc(('0' + multiler));
            pass_zero = 0;
        }

        value -= (multiler*divider);
        divider = divider/10;
    }
    putc(('0' + value));
}
