#ifndef __SATA_H__
#define __SATA_H__

int init_sata(int dev);
int scan_sata(int dev);
lbaint_t sata_read(int dev, lbaint_t blknr, lbaint_t blkcnt, void *buffer);
lbaint_t sata_write(int dev, lbaint_t blknr, lbaint_t blkcnt, const void *buffer);
lbaint_t rtk_sata_read(lbaint_t blknr, lbaint_t blkcnt, void *buffer);
lbaint_t rtk_sata_write(lbaint_t blknr, lbaint_t blkcnt, const void *buffer);

int sata_initialize(void);
int __sata_initialize(void);

#endif
