/* Realtek dwc3 phy driver*/

#include <asm/arch/usb.h>
#include <dwc3-uboot.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>

#include "linux-compat.h"
#include "core.h"

static int xhci_usb_utmi_wait_register(u32 reg, u32 mask, u32 result)
{
	uint timeout = 10;
	while (((__raw_readl((volatile u32*)reg) & mask) != result) && timeout--) {
		udelay(100);
		if (timeout <= 0) {
			printf("%s: \033[0:32:31m Can't program USB phy\033[m\n",__func__);
			return -1;
		}
	}
	return 0;
}

#define REG_MDIO_CTL 0x10//0x18013210

static int rtk_usb_phy3_wait_vbusy(struct phy_data dwc3)
{
	return xhci_usb_utmi_wait_register(dwc3.wrap_addr + REG_MDIO_CTL, (1<<7), 0);
}

static u32 rtk_xhci_usb3_phy_read(struct phy_data dwc3, char addr)
{
	volatile unsigned int regVal;

	regVal = (addr << 8);
	__raw_writel(regVal, (volatile u32*)(dwc3.wrap_addr + REG_MDIO_CTL));

	rtk_usb_phy3_wait_vbusy(dwc3);

	return __raw_readl((volatile u32*)(dwc3.wrap_addr + REG_MDIO_CTL));
}

static int rtk_xhci_usb3_phy_write(struct phy_data dwc3, char addr, u16 data)
{
	volatile unsigned int regVal;

	regVal = (1 << 0) |
			(addr << 8) |
			(data <<16);
	__raw_writel(regVal, (volatile u32*)(dwc3.wrap_addr + REG_MDIO_CTL));

	rtk_usb_phy3_wait_vbusy(dwc3);
	mdelay(10);
	return 0;
}

void rtk_dwc3_usb3_phy_setting(struct dwc3 *dwc)
{
	int i;
	struct phy_data dwc3 = dwc->phy_data;
	struct usb3phy u3phy = dwc3.u3phy;

	debug("RTK USB3 phy init\n");
	for (i = 0; i < u3phy.size; ++i) {
		rtk_xhci_usb3_phy_write(dwc3, u3phy.addr[i], u3phy.data[i]);
		debug("%s addr = %02x, value = %08x\n", __func__, u3phy.addr[i], u3phy.data[i]);
	}
#if	1//def SHOW_USBPHY_PARA
	{
		int i=0;
		for (i=0; i<0x30; i++)
			debug("\033[0;36m [%02x] %08x \033[m\n", i, rtk_xhci_usb3_phy_read(dwc3, i));
	}
#endif
	return 0;

}

#define REG_USB3BASE				0x8100
#define REG_WRAP_VUSB2StatusOut2	0x14//(0x18013214)
#define REG_GUSB2PHYACC0			0x180 + REG_USB3BASE//(0x18028280)

#define USB_ST_BUSY	(1<<17)

static char rtk_xhci_usb2_phy_read(struct phy_data dwc3, char addr)
{
	volatile unsigned int regVal;

	xhci_usb_utmi_wait_register(dwc3.dwc3_addr + REG_GUSB2PHYACC0, USB_ST_BUSY, 0);

	// VCtrl = low nibble of addr, VLoadM = 1
	regVal = (1 << 25) |
			 ((addr & 0x0f) << 8);

	__raw_writel(regVal, (volatile u32*)(dwc3.dwc3_addr + REG_GUSB2PHYACC0));
	xhci_usb_utmi_wait_register(dwc3.dwc3_addr + REG_GUSB2PHYACC0, USB_ST_BUSY, 0);

	// VCtrl = low nibble of addr, VLoadM = 0
	regVal = (1 << 25) |
			 ((addr & 0xf0) << 4);

	__raw_writel(regVal, (volatile u32*)(dwc3.dwc3_addr + REG_GUSB2PHYACC0));
	xhci_usb_utmi_wait_register(dwc3.dwc3_addr + REG_GUSB2PHYACC0, USB_ST_BUSY, 0);

	regVal = __raw_readl((volatile u32*)(dwc3.dwc3_addr + REG_GUSB2PHYACC0));
	return (char) (regVal & 0xff);
}

static int rtk_xhci_usb2_phy_write(struct phy_data dwc3, char addr, char data)
{
	volatile unsigned int regVal;

	__raw_writeb(data, (volatile u32*)(dwc3.wrap_addr + REG_WRAP_VUSB2StatusOut2));
	xhci_usb_utmi_wait_register(dwc3.dwc3_addr + REG_GUSB2PHYACC0, USB_ST_BUSY, 0);

	// VCtrl = low nibble of addr, VLoadM = 1
	regVal = (1 << 25) | 
			 ((addr & 0x0f) << 8);	

	__raw_writel(regVal, (volatile u32*)(dwc3.dwc3_addr + REG_GUSB2PHYACC0));
	xhci_usb_utmi_wait_register(dwc3.dwc3_addr + REG_GUSB2PHYACC0, USB_ST_BUSY, 0);

	// VCtrl = low nibble of addr, VLoadM = 0
	regVal = (1 << 25) | 
			 ((addr & 0xf0) << 4);	

	__raw_writel(regVal, (volatile u32*)(dwc3.dwc3_addr + REG_GUSB2PHYACC0));
	xhci_usb_utmi_wait_register(dwc3.dwc3_addr + REG_GUSB2PHYACC0, USB_ST_BUSY, 0);

	return 0;
}

void rtk_dwc3_usb2_phy_setting(struct dwc3 *dwc)
{
	int i;
	struct phy_data dwc3 = dwc->phy_data;
	struct usb2phy u2phy = dwc3.u2phy;
	for (i = 0; i < u2phy.size; ++i) {
		if (rtk_xhci_usb2_phy_write(dwc3, u2phy.addr[i], u2phy.data[i])) {
			printf("[%s:%d], Error : addr = 0x%x, value = 0x%x\n",
				__FUNCTION__, __LINE__,
				u2phy.addr[i],
				u2phy.data[i]);
			return -1;
		} else {
			debug("[%s:%d], Good : addr = 0x%x, value = 0x%x, verify =0x%x\n",
				__FUNCTION__, __LINE__,
				u2phy.addr[i],
				u2phy.data[i], rtk_xhci_usb2_phy_read(dwc3, u2phy.addr[i]));
		}
		mdelay(10);
	}
}

int rtk_dwc3_get_phy_data(struct dwc3 *dwc) {
	struct phy_data *data = &dwc->phy_data;
	int index = 0;
	data->dwc3_addr = realtek_get_base_usb_xhci(index);
	data->wrap_addr = realtek_get_base_usb_xhci_phy(index);
	data->u2phy.size = realtek_get_dwc3_u2phy_size(index)[0];
	data->u2phy.addr = realtek_get_dwc3_u2phy_addr(index);
	data->u2phy.data = realtek_get_dwc3_u2phy_data(index);
	data->u3phy.size = realtek_get_dwc3_u3phy_size(index)[0];
	data->u3phy.addr = realtek_get_dwc3_u3phy_addr(index);
	data->u3phy.data = realtek_get_dwc3_u3phy_data(index);
}

static struct dwc3_device dwc3_device_data = {
	.maximum_speed = USB_SPEED_SUPER,
	.base = 0x98020000,
	.dr_mode = USB_DR_MODE_PERIPHERAL,
	.index = 0,
};

int usb_gadget_handle_interrupts(int index)
{
	dwc3_uboot_handle_interrupt(0);
	return 0;
}

// CRT_SOFT_RESET1 usb part
#define rstn_usb_phy1 		(0x1 << 9)
#define rstn_usb_phy0 		(0x1 << 8)
#define rstn_usb 			(0x1 << 6)
#define rstn_usb3_p0_mdio 	(0x1 << 4)
#define rstn_usb3_phy0_pow 	(0x1 << 2)
// CRT_SOFT_RESET2 usb part
#define rstn_usb3_p1_mdio 	(0x1 << 5)
#define rstn_usb3_phy1_pow 	(0x1 << 4)
#define rstn_usb_phy2 		(0x1 << 3)
#define rstn_usb_phy3 		(0x1 << 2)
// CRT_CLOCK_ENABLE1 usb part
#define clk_en_usb 			(0x1 << 4)

static int usb_clk_enable(void) {
	static int enabled = 0;
	void *reset1 = RTD1295_CRT_BASE + 0x0;
	void *reset2 = RTD1295_CRT_BASE + 0x4;
	void *clk_en1 = RTD1295_CRT_BASE + 0xC;

	int reset1_pll_flag = rstn_usb_phy1 | rstn_usb_phy0 | rstn_usb3_phy0_pow;
	int reset2_pll_flag = rstn_usb_phy2;// | rstn_usb_phy3 | rstn_usb3_phy1_pow;
	int reset1_usb_flag = rstn_usb3_p0_mdio | rstn_usb;
	int reset2_usb_flag = 0;// rstn_usb3_p1_mdio;

	__raw_writel(~(reset1_pll_flag | reset1_usb_flag) & __raw_readl((volatile u32*)reset1), (volatile u32*) reset1);
	__raw_writel(~(reset2_pll_flag | reset2_usb_flag) & __raw_readl((volatile u32*)reset2), (volatile u32*) reset2);
	__raw_writel(~clk_en_usb & __raw_readl((volatile u32*)clk_en1), (volatile u32*) clk_en1);

	if (get_cpu_id() == RTK1296_CPU_ID) {
		debug("Realtek-usb 1296 u3host clock\n");
		reset2_pll_flag = rstn_usb_phy2 | rstn_usb_phy3 | rstn_usb3_phy1_pow;
		reset2_usb_flag = rstn_usb3_p1_mdio;
	}

	debug("Realtek-usb Start ....\n");
	debug("Realtek-usb init start soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(__raw_readl((volatile u32*)reset1)),
		(uint32_t)(__raw_readl((volatile u32*)reset2)),
		(uint32_t)(__raw_readl((volatile u32*)clk_en1)));

	//Enable PLL
	__raw_writel(reset1_pll_flag | __raw_readl((volatile u32*)reset1), (volatile u32*) reset1);
	__raw_writel(reset2_pll_flag | __raw_readl((volatile u32*)reset2), (volatile u32*) reset2);

	mdelay(200);
	debug("Realtek-usb: Enable PLL soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(__raw_readl((volatile u32*)reset1)),
		(uint32_t)(__raw_readl((volatile u32*)reset2)),
		(uint32_t)(__raw_readl((volatile u32*)clk_en1)));

	//Reset USB
	//__raw_writel(0x354 | __raw_readl((volatile u32*)reset1), (volatile u32*) reset1);
	//mdelay(10);

	//Turn on USB clk
	__raw_writel(clk_en_usb | __raw_readl((volatile u32*)clk_en1), (volatile u32*) clk_en1);
	__raw_writel(~clk_en_usb & __raw_readl((volatile u32*)clk_en1), (volatile u32*) clk_en1);
	mdelay(10);

	debug("Realtek-usb: trigger bit4 CLK_EN_USB soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(__raw_readl((volatile u32*)reset1)),
		(uint32_t)(__raw_readl((volatile u32*)reset2)),
		(uint32_t)(__raw_readl((volatile u32*)clk_en1)));

	__raw_writel(reset1_usb_flag | __raw_readl((volatile u32*)reset1), (volatile u32*) reset1);
	__raw_writel(reset2_usb_flag | __raw_readl((volatile u32*)reset2), (volatile u32*) reset2);
	mdelay(10);
	debug("Realtek-usn: Turn on all RSTN_USB soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(__raw_readl((volatile u32*)reset1)),
		(uint32_t)(__raw_readl((volatile u32*)reset2)),
		(uint32_t)(__raw_readl((volatile u32*)clk_en1)));

	__raw_writel(clk_en_usb | __raw_readl((volatile u32*)clk_en1), (volatile u32*) clk_en1);
	mdelay(10);
	debug("Realtek-usb: Turn on CLK_EN_USB soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(__raw_readl((volatile u32*)reset1)),
		(uint32_t)(__raw_readl((volatile u32*)reset2)),
		(uint32_t)(__raw_readl((volatile u32*)clk_en1)));

	return 0;
}


int rtk_dwc3_device_init(void) {
	usb_clk_enable();

	__raw_writel(0x2, 0x98013200);

	debug("Realtek-usb: disable usb wraper multi-request (%x)\n", __raw_readl(0x98013200));

	dwc3_uboot_init(&dwc3_device_data);
}
