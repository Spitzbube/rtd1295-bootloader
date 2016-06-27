#ifndef _MARS_reg_H_
#define _MARS_reg_H_

#define REG_PCI	0xb8017000
/* DVR Registers 200MHz 0xb8017000~0xb801707C 128bytes */
#define DVR_GNR_MODE				(REG_PCI+0x0000)		/* PCI Slave on/off */
#define DVR_GNR_EN					(REG_PCI+0x0004)		/* sbus,dbus,rbus endian convert */
#define DVR_GNR_INT					(REG_PCI+0x0008)		/* Slave-DMA,PCI,CFG,MIO,DMA interrupt Status */
#define DVR_CFG_CT					(REG_PCI+0x000c)		/* CFG GO */
#define DVR_CFG_EN					(REG_PCI+0x0010)		/* CFG enable */
#define DVR_CFG_ST					(REG_PCI+0x0014)		/* CFG Status error or R/W done ->polling */
#define DVR_CFG_ADDR				(REG_PCI+0x0018)		/* CFG format */
#define DVR_CFG_WDATA				(REG_PCI+0x001c)		/* CFG data to be write */
#define DVR_CFG_RDATA				(REG_PCI+0x0020)		/* CFG data read back */
#define DVR_MIO_CT					(REG_PCI+0x0024)		/* MIO GO */
#define DVR_MIO_ST					(REG_PCI+0x0028)		/* MIO Status R/W done or error ->polling */
#define DVR_MIO_EN					(REG_PCI+0x002c)		/* Enable IO or MM Command */
#define DVR_MIO_ADDR				(REG_PCI+0x0030)		/* MIO destination address */
#define DVR_MIO_WDATA				(REG_PCI+0x0034)		/* MIO data to be write */
#define DVR_MIO_RDATA				(REG_PCI+0x0038)		/* MIO data read back */
#define DVR_DMA_CT					(REG_PCI+0x003C)		/* DMA GO */
#define DVR_DMA_ST					(REG_PCI+0x0040)		/* DMA condition */
#define DVR_DMA_EN					(REG_PCI+0x0044)		/* DMA Enable (choose descripotr base or not) */
#define DVR_DMA_PCI					(REG_PCI+0x0048)		/* PCI address,non descriptor base*/
#define DVR_DMA_DDR					(REG_PCI+0x004C)		/* DDR address,non descriptor base */
#define DVR_DMA_CNT					(REG_PCI+0x0050)		/* DMA byte size transfer,max 16MB */
#define DVR_DMA_DES0				(REG_PCI+0x0054)		/* DMA base address,initial size */
#define DVR_DMA_DES1				(REG_PCI+0x0058)		/* DMA limit address,max size */
#define DVR_DMA_DES2				(REG_PCI+0x005C)		/* DMA write pointer address */
#define DVR_DMA_DES3				(REG_PCI+0x0060)		/* DMA read pointer address */
#define DVR_SOFT_RST				(REG_PCI+0x0064)
#define DVR_CLK_ST					(REG_PCI+0x0068)		/*busy or clk status*/
#define DVR_SPC_CT					(REG_PCI+0x006C)		
#define DVR_SPC_ST					(REG_PCI+0x0070)		/* Clk_run & INTA status */
#define DVR_DBG					(REG_PCI+0x0074)		/* Debug enable */
#define DVR_DIR_ST					(REG_PCI+0x0078)		/* Direct R/W error */
#define DVR_DIR_EN					(REG_PCI+0x007C)		/* Direct MIO en_interrupt */
#define DVR_DEV_ST					(REG_PCI+0x0080)		/*  */
#define DVR_DEV_CT					(REG_PCI+0x0084)		/*  */
#define DVR_DEV_DDR					(REG_PCI+0x0088)		/* ddr Slave dma start address */
#define DVR_DEV_PCI					(REG_PCI+0x008c)		/* pci Slave dma start address */
#define DVR_DEV_CNT					(REG_PCI+0x0090)		/* burst count */
#define DVR_TMP0_REG				(REG_PCI+0x0094)		/* Dummy test register*/
#define DVR_TMP1_REG				(REG_PCI+0x00A0)		/* delay chain debug port*/
#define DVR_SCTCH					(REG_PCI+0x00AC)		/* Dummy register value 10*/

/* PCI Bridge Registers 33MHz 0xb8017080~0xb80170BF 64bytes */
#define PCI_SCTCH					(REG_PCI+0x0100)		/* Dummy register */
#define PCI_GNR_EN1					(REG_PCI+0x0104)		/* Retry counter */
#define PCI_GNR_EN2					(REG_PCI+0x0108)		/* Enable interrupt and translation address */
#define PCI_GNR_ST					(REG_PCI+0x010C)		/* Error cause slave or master */
#define PCI_GNR_INT					(REG_PCI+0x0110)		/* Interrupt status */
#define PCI_MASK0					(REG_PCI+0x0114)		/* Rbus address mask */
#define PCI_TRANSL0					(REG_PCI+0x0118)		/* Rbus translation address */
#define PCI_MASK1					(REG_PCI+0x011C)		/* Dbus address mask */
#define PCI_TRANSL1					(REG_PCI+0x0120)		/* Dbus translation address */
#define PCI_MASK2					(REG_PCI+0x0124)		/* Sbus address mask */
#define PCI_TRANSL2					(REG_PCI+0x0128)		/* Sbus translation address */

/* PCI Configuration Space Registers 0xb80170C0~0xb80170FF 64bytes */
#define CFG_00H					(REG_PCI+0x0200)		/* Device and Vender ID */
#define CFG_04H					(REG_PCI+0x0204)		/* Status and Command */
#define CFG_08H					(REG_PCI+0x0208)		/* Class Code and Rev. ID*/
#define CFG_0CH					(REG_PCI+0x020C)		/* BAR0 latency_timer and cacheline_zie 128bytes*/
#define CFG_10H					(REG_PCI+0x0210)		/* BAR1 reg */
#define CFG_14H					(REG_PCI+0x0214)		/* BAR2 rbus */
#define CFG_18H					(REG_PCI+0x0218)		/* BAR3 dbus */
#define CFG_1CH					(REG_PCI+0x021C)		/* BAR4 sbus */
#define CFG_2CH					(REG_PCI+0x022C)		/* sub ID and sub vender ID*/
#define CFG_3CH					(REG_PCI+0x023C)		/* Interrupt pin INTA*/
#define EN_PCI_DEBUG				(REG_PCI+0x1100)		/*debug port d for PCI*/



/* ===========   ETN   =====================*/
/*========================================================*/
#if 1
#define REG_ETN	0xb8016000
#define IDR0						(REG_ETN+0x0000)		/*ID register*/
#define IDR1						(REG_ETN+0x0001)		/*ID register*/
#define IDR2						(REG_ETN+0x0002)		/*ID register*/
#define IDR3						(REG_ETN+0x0003)		/*ID register*/
#define IDR4						(REG_ETN+0x0004)		/*ID register*/
#define IDR5						(REG_ETN+0x0005)		/*ID register*/
#define MAR0						(REG_ETN+0x0008)		/*ID register*/
#define MAR1						(REG_ETN+0x0009)		/*ID register*/
#define MAR2						(REG_ETN+0x000A)		/*ID register*/
#define MAR3						(REG_ETN+0x000B)		/*ID register*/
#define MAR4						(REG_ETN+0x000C)		/*ID register*/
#define MAR5						(REG_ETN+0x000D)		/*ID register*/
#define MAR6						(REG_ETN+0x000E)		/*ID register*/
#define MAR7						(REG_ETN+0x000F)		/*ID register*/
#define TXOKCNT					(REG_ETN+0x0014)		/*Tx OK counter*/
#define RXOKCNT					(REG_ETN+0x0016)		/*Rx OK counter*/
#define TXERR						(REG_ETN+0x0014)		/*Tx errors counter*/
#define RXERR						(REG_ETN+0x0016)		/*Rx errors counter*/
#define MISSPKT					(REG_ETN+0x0018)		/*Missed packets resulting from FIFO full*/
#define FAE						(REG_ETN+0x001A)		/*Frame Alignment Error packets*/
#define TX1COL						(REG_ETN+0x001C)		/*TX collision=1 packets counter*/
#define TXMCOL						(REG_ETN+0x001E)		/*TX 16 >collision >1 packets counter*/
#define RXOKPHY					(REG_ETN+0x0020)		/*Rx physical address OK packets*/
#define RXOKBRD					(REG_ETN+0x0022)		/*Rx broadcast OK packets*/
#define RXOKMUL					(REG_ETN+0x0024)		/*Rx multicast OK packets*/
#define TXABT						(REG_ETN+0x0026)		/*Tx abort packets*/
#define TXUNDRN					(REG_ETN+0x0028)		/*Tx underrun and discared packets*/
#define TRSR						(REG_ETN+0x0034)		/*Tx Rx Status */
#define CMD					(REG_ETN+0x003B)		/*Command Register */
#define IMR						(REG_ETN+0x003C)		/*Interrupt Mask Register */
#define ISR						(REG_ETN+0x003E)		/*Interrupt Status Register*/
#define TCR						(REG_ETN+0x0040)		/*Tx Configuration Register */
#define RCR						(REG_ETN+0x0044)		/*Rx Configuration Register */
#define MSR						(REG_ETN+0x0058)		/*Media Status Register */
#define MIIAR						(REG_ETN+0x005C)		/*MII Access Register */

#define TxFDP1						(REG_ETN+0x0100)		/*Tx First Descriptor Pointer*/                         
#define TxCDO1						(REG_ETN+0x0104)		/*Tx Current Descriptor Offset*/                        
#define TxCPO1						(REG_ETN+0x0108)		/*Tx Current Page Offset*/                              
#define TxFDP2						(REG_ETN+0x0180)		/*Tx First Descriptor Pointer low priority*/
#define TxCDO2						(REG_ETN+0x0184)		/*Tx Current Descriptor Offset low priority*/
#define TxCPO2						(REG_ETN+0x018C)		/*Tx Current Page Offset low priority*/    
#define RxFDP						(REG_ETN+0x01f0)		/*Rx First Descriptor Pointer*/
#define RxCDO						(REG_ETN+0x01f4)		/*Rx Current Descriptor Offset*/
#define RxRingSize					(REG_ETN+0x01f6)		/*Rx ring size*/
#define RxCPO						(REG_ETN+0x01f8)		/*Rx Current Page Offset*/
#define EthrntRxCPU_Des_Num			(REG_ETN+0x0230)		/*CPU has finished descriptor, driver update*/
#define EthrntRxCPU_Des_Wrap			(REG_ETN+0x0231)		/*driver update this when pasting EOR*/
#define Rx_Pse_Des_Thres				(REG_ETN+0x0232)		/*diff between CPU and RxCDO*/
#define ETHER_IO_CMD				(REG_ETN+0x0234)		/*Rx and Tx Enable*/
#define ETHER_dbg					(REG_ETN+0x0244)		/*Rx and Tx Enable*/

#endif
/*========================================================*/

/* CRT Registers about PCI */
#define REG_CRT	0xb8000000
#define PCI_CKSEL				(REG_CRT+0x0038)	//PLL from HD or Audio
#define PCICK_IO				(REG_CRT+0x0338)	//Host/Device mode, w/wo delay chain
#define PCICK_DELAY				(REG_CRT+0x033C)	//delay chain value
#define pfunc_pci5				(REG_CRT+0x03AC)	//PCI CLK driving strength BIT22


/* ISO Registers*/
#define REG_ISO	0xb801bd00
#define ISO_CTRL				(REG_CRT+0x0030)	//ISO control register
#define ISO_CELL				(REG_CRT+0x0038)	//ISO cell enable/disable
#define ISO_GPDIR				(REG_CRT+0x0070)	//ISO GPIO Input/Output
#define ISO_GPDATO				(REG_CRT+0x0074)	//ISO GPIO 
#define ISO_GPIO_MUX			(REG_CRT+0x00d8)	//ISO GPIO mux pad



/* SB2 Registers */
#define REG_SB2	0xb801a000
#define SB2_rbus_timeout					(REG_SB2+0x0010)
#define SB2_PCI_BASE0					(REG_SB2+0x0030)
#define SB2_PCI_BASE1					(REG_SB2+0x0034)
#define SB2_PCI_MASK0					(REG_SB2+0x0040)
#define SB2_PCI_MASK1					(REG_SB2+0x0044)
#define SB2_PCI_TRAN0					(REG_SB2+0x0050)
#define SB2_PCI_TRAN1					(REG_SB2+0x0054)
#define SB2_PCI_CTRL					(REG_SB2+0x0060)

/* Timer Registers */
#define TimerBase				(0xb801b500)
#define MIS_TC0_CV				(TimerBase + 0x0c)	//Timer0 current value
#define MIS_TC0_Ctrl			(TimerBase + 0x18)	//Timer0 control


/* UART Registers */
#define UART1Base    (0xb8007800)
#define UART1_RBR    (UART1Base + 0x00) // Receive Buffer Register (when DLAB=0)
#define UART1_THR    (UART1Base + 0x00) // Transmit Holding Register (when DLAB=0)
#define UART1_DLL    (UART1Base + 0x00) // Divisor Latch Low (when DLAB=1)
#define UART1_IER    (UART1Base + 0x04) // Interrupt Enable Register (when DLAB=0)
#define UART1_DLH    (UART1Base + 0x04) // Divisor Latch High (when DLAB=1)
#define UART1_IIR    (UART1Base + 0x08) // Interrupt Identify Register (read only)
#define UART1_FCR    (UART1Base + 0x08) // FIFO Control Register (write only)
#define UART1_LCR    (UART1Base + 0x0C) // Line Control Register
#define UART1_MCR    (UART1Base + 0x10) // Modem Control Register
#define UART1_LSR    (UART1Base + 0x14) // Line Status Register
#define UART1_MSR    (UART1Base + 0x18) // Modem Status Register
#define UART1_SCR    (UART1Base + 0x1C) // Scratch Register

#define UART2Base    (0xb801b200)
#define UART2_RBR    (UART2Base + 0x00) // Receive Buffer Register (when DLAB=0)
#define UART2_THR    (UART2Base + 0x00) // Transmit Holding Register (when DLAB=0)
#define UART2_DLL    (UART2Base + 0x00) // Divisor Latch Low (when DLAB=1)
#define UART2_IER    (UART2Base + 0x04) // Interrupt Enable Register (when DLAB=0)
#define UART2_DLH    (UART2Base + 0x04) // Divisor Latch High (when DLAB=1)
#define UART2_IIR    (UART2Base + 0x08) // Interrupt Identify Register (read only)
#define UART2_FCR    (UART2Base + 0x08) // FIFO Control Register (write only)
#define UART2_LCR    (UART2Base + 0x0C) // Line Control Register
#define UART2_MCR    (UART2Base + 0x10) // Modem Control Register
#define UART2_LSR    (UART2Base + 0x14) // Line Status Register
#define UART2_MSR    (UART2Base + 0x18) // Modem Status Register
#define UART2_SCR    (UART2Base + 0x1C) // Scratch Register

#define LSR_DR    (0x01 << 0)  // LSR_0, Data Ready
#define LSR_OE    (0x01 << 1) // LSR_1, Overrun Error
#define LSR_PE    (0x01 << 2) // LSR_2, Parity Error
#define LSR_FE    (0x01 << 3) // LSR_3, Frame Error
#define LSR_BI    (0x01 << 4) // LSR_4, Break Interrupt
#define LSR_THRE  (0x01 << 5) // LSR_5, THR empty


/* MD Registers move data*/
#define MDREG		0xb800b000
#define MD_CTL			(MDREG+0x00)	
#define MD_INT_ST		(MDREG+0x04)	
#define MD_INT_EN		(MDREG+0x08)	
#define MD_BASE		(MDREG+0x0c)	//Desc base address
#define MD_LIMIT		(MDREG+0x10)	//Desc limit address
#define MD_Rdptr		(MDREG+0x14)	//Read pointer
#define MD_Wrptr		(MDREG+0x18)	//write pointer
#define MD_fifo		(MDREG+0x1c)	//fifo queue for SCPU instructions (debug)
#define MD_INSCNT		(MDREG+0x20)	//instruction counter

/* ETN Registers */
#define ETNREG		0xb8016000



#define ETN_MIIAR		(ETNREG+0x5c)

#endif   // _MARS_reg_H_
