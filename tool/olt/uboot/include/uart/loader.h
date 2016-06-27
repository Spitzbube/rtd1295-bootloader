#ifndef _loader_h_
#define _loader_h_

extern UINT32 _isr_cause_reg;
extern UINT32 _app_heap_start;
extern UINT32 _app_heap_end;
extern void ISR_entry(void);

#endif   // _loader_h_
