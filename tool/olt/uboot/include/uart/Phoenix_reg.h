#ifndef _Phoenix_reg_H_
#define _Phoenix_reg_H_


/* CRT Registers about PCI */
#define REG_CRT	0x18000000
#define PCI_CKSEL				(REG_CRT+0x0038)	//PLL from HD or Audio


/* SB2 Registers */
#define REG_SB2	0x1801a000
#define SB2_rbus_timeout			(REG_SB2+0x0010)
#define SB2_PCI_BASE0					(REG_SB2+0x0030)
#define SB2_PCI_BASE1					(REG_SB2+0x0034)
#define SB2_PCI_MASK0					(REG_SB2+0x0040)
#define SB2_PCI_MASK1					(REG_SB2+0x0044)
#define SB2_PCI_TRAN0					(REG_SB2+0x0050)
#define SB2_PCI_TRAN1					(REG_SB2+0x0054)
#define SB2_PCI_CTRL					(REG_SB2+0x0060)

/* Timer Registers */
#define TimerBase				(0x1801b500)
#define MIS_TC0_CV				(TimerBase + 0x0c)	//Timer0 current value
#define MIS_TC0_Ctrl			(TimerBase + 0x18)	//Timer0 control

/* UART Registers */
#define UART1Base    (0x18007800)
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

#define UART1_TFL    (UART1Base + 0x80) // Tx fifo level

#define UART2Base    (0x1801b220)
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
#define MDREG		0x1800b000
#define MD_CTL			(MDREG+0x00)	
#define MD_INT_ST		(MDREG+0x04)	
#define MD_INT_EN		(MDREG+0x08)	
#define MD_BASE		(MDREG+0x0c)	//Desc base address
#define MD_LIMIT		(MDREG+0x10)	//Desc limit address
#define MD_Rdptr		(MDREG+0x14)	//Read pointer
#define MD_Wrptr		(MDREG+0x18)	//write pointer
#define MD_fifo		(MDREG+0x1c)	//fifo queue for SCPU instructions (debug)
#define MD_INSCNT		(MDREG+0x20)	//instruction counter



#endif   // _Phoenix_reg_H_
