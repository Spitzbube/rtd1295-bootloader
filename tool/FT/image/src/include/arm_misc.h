#ifndef __20130417_MISC_H__
#define __20130417_MISC_H__

#define switch_to_secure_state() asm("smc #1")
extern void switch_to_user_mode();
extern void switch_to_privileged_mode();

void set_entry_scpu(unsigned int id, unsigned int* main_scpu1);
extern void send_sgi();
extern void wake_up_core1();
extern init_nonsecure();
extern disable_i_cache();
extern memcpy32(void* dst, const void *src, unsigned wdcount);
extern enable_d_cache();
extern clean_dcache_range(unsigned int *start, unsigned int *end);
extern disable_interrupts();

#endif
