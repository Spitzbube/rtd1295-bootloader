#ifndef _UART_H_
#define _UART_H_

#include "utility.h"

#define putchar(x)	serial_outc(x)
#define sprintf	SprintF
#define ETH_ALEN			6

extern void UART_Init();

extern void prints(UINT8 *);
extern void tx_CHAR(UINT8 *);
extern void tx_NewLine();
extern void tx_UINT32(UINT32 );
extern void tx_UINT8(UINT8 );
extern int vsprintf(char * , const char* , const int *);
extern int SprintF(char *buf, const char *fmt, ...);
extern void printk(const char *, ...);

extern void serial_outc (char );

#endif   // _UART_H_
