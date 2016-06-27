#include <uart/utility.h>
#include <uart/UART.h>
#include <uart/Phoenix_reg.h>

UINT8    CharMap[16] = {'0', '1', '2', '3', '4', '5', '6', '7', \
                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void UART_Init(){
	UINT8 tmp;
	// set DLAB=1 to set DLL and DLH for baud rate
	Wreg32(UART1_LCR,Rreg32(UART1_LCR)|0x80);		//DLAB=1  

	Wreg32(UART1_DLL,0xe);	// baut rate, 0x12 for FPGA 33MHz, 0xe for ASIC 27MHz       
	Wreg32(UART1_DLH,0x0);
	
	// set DLAB=0 to access RBR and IER	
	Wreg32(UART1_LCR,0x03);		// DLAB=0, no parity, 8 bit, 1 stop bit
	Wreg32(UART1_IER,0x0);		//disable all interrupt
 	Wreg32(UART1_FCR,0xaf);		//clear FIFO,DMA enable 
	while ((Rreg32(UART1_LSR) & LSR_DR) == LSR_DR){
		tmp = (UINT8)Rreg32(UART1_RBR);     // dummy read to clear RBR/FIFO
		}
 	//tx_NewLine();
 	//tx_CHAR("Free Start Address = 0x");
	//tx_UINT32(_app_heap_start); tx_NewLine();
}

void tx_UINT8(UINT8 data){
	
	while ((Rreg32(UART1_LSR) & LSR_THRE) != LSR_THRE); // wait for THRE==1 (TX FIFO empty)			
	Wreg32(UART1_THR, (UINT32)data);
}

void tx_UINT32(UINT32 data){
   tx_UINT8(CharMap[(data & 0xf0000000) >> 28]);
   tx_UINT8(CharMap[(data & 0x0f000000) >> 24]);
   tx_UINT8(CharMap[(data & 0x00f00000) >> 20]);
   tx_UINT8(CharMap[(data & 0x000f0000) >> 16]);
   tx_UINT8(CharMap[(data & 0x0000f000) >> 12]);
   tx_UINT8(CharMap[(data & 0x00000f00) >> 8]);
   tx_UINT8(CharMap[(data & 0x000000f0) >> 4]);
   tx_UINT8(CharMap[(data & 0x0000000f) >> 0]);
}

void tx_CHAR(UINT8 *string){
	
	while(0 != Rreg8(string)){
	Wreg32(UART1_THR,*string);
	string++;
	while ((Rreg32(UART1_LSR) & LSR_THRE) != LSR_THRE);// wait for THRE==1 (TX FIFO empty)
   }
}

void tx_NewLine(void){
   tx_UINT8(0x0d);
   tx_UINT8(0x0a);//next line
}
  
void prints(UINT8 *string){
	tx_CHAR(string);
	//tx_NewLine();
}

int vsprintf(char *buf, const char *fmt, const int *dp)
{
	char *p, *s;

	s = buf;
	for ( ; *fmt != '\0'; ++fmt) {
		if (*fmt != '%') {
			buf ? *s++ = *fmt : putchar(*fmt);
			continue;
		}
		if (*++fmt == 's') {
			for (p = (char *)*dp++; *p != '\0'; p++)
				buf ? *s++ = *p : putchar(*p);
		}
		else {	/* Length of item is bounded */
			char tmp[20], *q = tmp;
			int alt = 0;
			int shift = 28;
			if (*fmt == '#') {
				alt = 1;
				fmt++;
			}
			if (*fmt == 'h') {
				shift = 12;
				fmt++;
			}
			if (*fmt == 'h') {
				shift = 4;
				fmt++;
			}
			/*
			 * Before each format q points to tmp buffer
			 * After each format q points past end of item
			 */
			if ((*fmt | 0x20) == 'x') {
				/* With x86 gcc, sizeof(long) == sizeof(int) */
				const long *lp = (const long *)dp;
				long h = *lp++;
				int ncase = (*fmt & 0x20);
				dp = (const int *)lp;
				if (alt) {
					*q++ = '0';
					*q++ = 'X' | ncase;
				}
				for ( ; shift >= 0; shift -= 4)
					*q++ = "0123456789ABCDEF"[(h >> shift) & 0xF] | ncase;
			}
			else if (*fmt == 'd') {
				int i = *dp++;
				char *r;
				if (i < 0) {
					*q++ = '-';
					i = -i;
				}
				p = q;		/* save beginning of digits */
				do {
					*q++ = '0' + (i % 10);
					i /= 10;
				} while (i);
				/* reverse digits, stop in middle */
				r = q;		/* don't alter q */
				while (--r > p) {
					i = *r;
					*r = *p;
					*p++ = i;
				}
			}
			else if (*fmt == '@') {
				unsigned char *r;
				union {
					long		l;
					unsigned char	c[4];
				} u;
				const long *lp = (const long *)dp;
				u.l = *lp++;
				dp = (const int *)lp;
				for (r = &u.c[0]; r < &u.c[4]; ++r)
					q += SprintF(q, "%d.", *r);
				--q;
			}
			else if (*fmt == '!') {
				char *r;
				p = (char *)*dp++;
				for (r = p + ETH_ALEN; p < r; ++p)
					q += SprintF(q, "%hhX:", *p);
				--q;
			}
			else if (*fmt == 'c')
				*q++ = *dp++;
			else
				*q++ = *fmt;
			/* now output the saved string */
			for (p = tmp; p < q; ++p)
				buf ? *s++ = *p : putchar(*p);
		}
	}
	if (buf)
		*s = '\0';
	return (s - buf);
}



void serial_outc(char c)
{

	while (1) {
//		i++;
	//	if (i >=3210)
		//	break;
		//if 	(rtd_inl(UART0_BASE + UART_LSR) & 0x60)
		//if 	(Rreg32(UART1_LSR) & 0x60)
		//	break;	
		if     (Rreg32(UART1_TFL)<31)
                        break;      
	}

	//for(i=0; i<0xff00;i++);
 	Wreg32(UART1_THR, c);  
	if (c == 0x0a)
		Wreg32(UART1_THR, 0x0d);  
}

int SprintF(char *buf, const char *fmt, ...)
{
	return vsprintf(buf, fmt, ((const int *)&fmt)+1);
}

void printk(const char *fmt, ...)
{
	(void)vsprintf(0, fmt, ((const int *)&fmt)+1);
}

// ref:flash_writer_u
#define UARTINFO_TEMT_MASK                  0x40
#define UARTINFO_THRE_MASK                  0x20
#define UARTINFO_TRANSMITTER_READY_MASK     (UARTINFO_TEMT_MASK | UARTINFO_THRE_MASK)

void serial_write(unsigned char  *p_param)
{
	while((Rreg32(UART1_LSR) & UARTINFO_TRANSMITTER_READY_MASK) != UARTINFO_TRANSMITTER_READY_MASK);
	
	Wreg32(UART1_RBR, *p_param);
	
}

void print_val(UINT32 val, UINT32 len)
{
	unsigned char ch;
	
	len--;
	do {
		ch = (val >> (len << 2)) & 0xf;
		ch += (ch < 0xa ? 0x30 : 0x37);
		serial_write(&ch);
	} while(len--);

}