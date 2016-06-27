/*
 *
 */

#ifndef __PRINT64_H__
#define __PRINT64_H__

#include <config.h>

/* decalre */
void print64_s(const char *ch);
void print64_hex_val(unsigned long long val, unsigned int digitlen);
void print64_hex32(unsigned long long value);
void print64_hex64(unsigned long long value);
void print64_dec(unsigned long long value);

/* macro */




#endif // __PRINT64_H__
