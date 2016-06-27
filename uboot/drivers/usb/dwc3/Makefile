include $(TOPDIR)/config.mk

LIB	:= $(obj)libusb_dwc3.o

COBJS-$(CONFIG_USB_DWC3) += core.o gadget.o ep0.o

COBJS-$(CONFIG_USB_DWC3_OMAP) += dwc3-omap.o
COBJS-$(CONFIG_USB_DWC3_PHY_OMAP) += ti_usb_phy.o
COBJS-$(CONFIG_USB_DWC3_PHY_SAMSUNG) += samsung_usb_phy.o
COBJS-$(CONFIG_USB_RTK_DWC3_GADGET) += rtk_usb_phy.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(call cmd_link_o_target, $(OBJS))

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#
