//#ifndef DDR_CTRL_H
#include "DW_common.h"
//#define DDR_CTRL_H
#define DDR_BASE 0xbb100000
#define TRAINING_RESULT_BASE 0xb002ff80
#define LOG_ADDR     0xb002ff00
//typedef unsigned int uint32_t;

struct rxi310_dramc_portmap {
  volatile uint32_t pctl_ccr;        /* 8'h00 */ 
  volatile uint32_t pctl_dcr;        /* 8'h04 */
  volatile uint32_t pctl_iocr;       /* 8'h08 */
  volatile uint32_t pctl_csr;        /* 8'h0c */
  volatile uint32_t pctl_drr;        /* 8'h10 */
  volatile uint32_t pctl_tpr0;       /* 8'h14 */
  volatile uint32_t pctl_tpr1;       /* 8'h18 */
  volatile uint32_t pctl_tpr2;       /* 8'h1c */
  volatile uint32_t pctl_mr;         /* 8'h20 */
  volatile uint32_t pctl_emr1;       /* 8'h24 */
  volatile uint32_t pctl_emr2;       /* 8'h28 */
  volatile uint32_t pctl_emr3;       /* 8'h2c */
  volatile uint32_t pctl_csr2;       /* 8'h30 */       
  volatile uint32_t pctl_srst;       /* 8'h34 */       

  volatile uint32_t pctl_dtr2;       /* 8'h38 */       
  volatile uint32_t pctl_dtr3;       /* 8'h3c */       

  volatile uint32_t pctl_gdllcr;     /* 8'h40 */ 
  volatile uint32_t pctl_dllcr0;     /* 8'h44 */
  volatile uint32_t pctl_dllcr1;     /* 8'h48 */
  volatile uint32_t pctl_dllcr2;     /* 8'h4c */
  volatile uint32_t pctl_dllcr3;     /* 8'h50 */
  volatile uint32_t pctl_dllcr4;     /* 8'h54 */
  volatile uint32_t pctl_dllcr5;     /* 8'h58 */
  volatile uint32_t pctl_dllcr6;     /* 8'h5c */
  volatile uint32_t pctl_dllcr7;     /* 8'h60 */
  volatile uint32_t pctl_dllcr8;     /* 8'h64 */
  volatile uint32_t pctl_dqtr0;      /* 8'h68 */
  volatile uint32_t pctl_dqtr1;      /* 8'h6c */
  volatile uint32_t pctl_dqtr2;      /* 8'h70 */
  volatile uint32_t pctl_dqtr3;      /* 8'h74 */
  volatile uint32_t pctl_dqtr4;      /* 8'h78 */
  volatile uint32_t pctl_dqtr5;      /* 8'h7c */
  volatile uint32_t pctl_dqtr6;      /* 8'h80 */
  volatile uint32_t pctl_dqtr7;      /* 8'h84 */
  volatile uint32_t pctl_dqstr;      /* 8'h88 */
  volatile uint32_t pctl_dqsbtr;     /* 8'h8c */
  volatile uint32_t pctl_odtcr;      /* 8'h90 */
  volatile uint32_t pctl_dtr0;       /* 8'h94 */
  volatile uint32_t pctl_dtr1;       /* 8'h98 */
  volatile uint32_t pctl_dtar;       /* 8'h9c */
  volatile uint32_t pctl_zqcr0;      /* 8'ha0 */

  volatile uint32_t pctl_zqcr1;      /* 8'ha4 */
  volatile uint32_t pctl_zqsr;       /* 8'ha8 */
  volatile uint32_t pctl_rslr0;      /* 8'hac */
  volatile uint32_t pctl_rslr1;      /* 8'hb0 */
  volatile uint32_t pctl_rslr2;      /* 8'hb4 */
  volatile uint32_t pctl_rslr3;      /* 8'hb8 */
  volatile uint32_t pctl_rdgr0;      /* 8'hbc */
  volatile uint32_t pctl_rdgr1;      /* 8'hc0 */
  volatile uint32_t pctl_rdgr2;      /* 8'hc4 */
  volatile uint32_t pctl_rdgr3;      /* 8'hc8 */
  volatile uint32_t pctl_mxsl;       /* 8'hcc */      

  volatile uint32_t pctl_bcr;        /* 8'hd0 */ 
  volatile uint32_t pctl_balr0;      /* 8'hd4 */
  volatile uint32_t pctl_balr1;      /* 8'hd8 */
  volatile uint32_t pctl_bdr0;       /* 8'hdc */
  volatile uint32_t pctl_bdr1;       /* 8'he0 */
  volatile uint32_t pctl_bbr;        /* 8'he4 */
  volatile uint32_t pctl_bsr;        /* 8'he8 */
  volatile uint32_t pctl_byr;        /* 8'hec */
  volatile uint32_t pctl_bfa;        /* 8'hf0 */

  volatile uint32_t reserv_2[12];    /* 8'hf4 - 12'h120 */       

  volatile uint32_t sch_scr;         /* 12'h224 */
  volatile uint32_t sch_qcr;         /* 12'h230 */ 
  volatile uint32_t sch_pcr;         /* 12'h234 */
  volatile uint32_t sch_qtr0;        /* 12'h240 */
  volatile uint32_t sch_qtr1;        /* 12'h244 */
  volatile uint32_t sch_qtr2;        /* 12'h248 */
  volatile uint32_t sch_qtr3;        /* 12'h24c */
  volatile uint32_t sch_qtr4;        /* 12'h250 */
  volatile uint32_t sch_qtr5;        /* 12'h254 */
  volatile uint32_t sch_qtr6;        /* 12'h258 */
  volatile uint32_t sch_qtr7;        /* 12'h25c */
  volatile uint32_t sch_qtr8;        /* 12'h260 */
  volatile uint32_t sch_qtr9;        /* 12'h264 */
  volatile uint32_t sch_qtr10;       /* 12'h268 */
  volatile uint32_t sch_qtr11;       /* 12'h26c */
  volatile uint32_t sch_qtr12;       /* 12'h270 */
  volatile uint32_t sch_qtr13;       /* 12'h274 */
  volatile uint32_t sch_qtr14;       /* 12'h278 */
  volatile uint32_t sch_qtr15;       /* 12'h27c */

};

int  run_data_training(unsigned int *dqs_lat_b0, unsigned int *dqs_lat_b1);
int  start_data_training(struct dw_device *);
//int  start_data_training(struct rxi310_dramc_portmap *ddr_ptr);
void get_data_training_result(struct rxi310_dramc_portmap *ddr_ptr, unsigned int *bl0, unsigned int *bl1);
int  get_data_training_status(struct rxi310_dramc_portmap *ddr_ptr);
void get_training_pattern(struct rxi310_dramc_portmap *ddr_ptr, int *addr, int *data1, int *data2);
void set_training_pattern(struct dw_device *, unsigned int addr, unsigned int data1, unsigned int data2,
                          unsigned int data3, unsigned int data4);

//void set_training_pattern(struct rxi310_dramc_portmap *ddr_ptr, int addr, int data1, int data2);
void reset_itm(struct rxi310_dramc_portmap *ddr_ptr);
void dereset_itm(struct rxi310_dramc_portmap *ddr_ptr);
int  data_training(struct rxi310_dramc_portmap *ddr_ctrl_ptr, 
                   int max_loop, unsigned int addr, 
                   unsigned int data1, unsigned int data2, unsigned int *bl0_dt_res, unsigned int *bl1_dt_res,
                   int DEBUG);
void get_dqs_drift(unsigned int *drift_b0, unsigned int *drift_b1);
void delay_loop(int cnt);
//int pass_ddr_test(void);
//int fail_ddr_test(int status, unsigned int fail_cnt, unsigned int rd_err_cnt, 
//                  unsigned int wr_err_cnt);
void set_dqs_trm(struct dw_device *dev, unsigned int trm_value);
unsigned int get_dqs_phase(struct dw_device *dev);
//#endif // DDR_CTRL_H
