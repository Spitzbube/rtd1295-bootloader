/************************************************************************
 *
 *  md.h
 *
 *  Public header file for MD module
 *
 ************************************************************************/

#ifndef MD_H
#define MD_H

/************************************************************************
 *  Definition
 ************************************************************************/

/************************************************************************
 *  Public functions
 ************************************************************************/
int md_memcpy(void *dst, void *src, unsigned int len);
//void md_flash2mem(void *dst, void *src, UINT32 len);

#endif /* #ifndef MD_H */
