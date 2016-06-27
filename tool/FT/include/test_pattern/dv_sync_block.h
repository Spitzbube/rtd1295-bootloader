#ifndef DV_SYNC_BLOCK_H__20131206_
#define DV_SYNC_BLOCK_H__20131206_

#define DV_SYNC_BLOCK_MAGIC_NUMBER (0xbabebabe)

struct DV_SYNC_BLOCK
{
    unsigned int magic;
    unsigned int go;
    unsigned int return_addr;
    unsigned int result;
    unsigned int counter;
    unsigned int hif_status;
};
extern struct DV_SYNC_BLOCK;
enum dv_hif_status  { dv_hif_disable, dv_hif_wait_init, dv_hif_wait_case, dv_hif_done_case, dv_hif_done_init};
#endif
