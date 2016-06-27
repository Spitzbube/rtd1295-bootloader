
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

  volatile uint32_t pctl_dtr2;        /* 8'h38 */       
  volatile uint32_t pctl_dtr3;        /* 8'h3c */       

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

  volatile uint32_t sch_scr;         /* 12'h124 */
  volatile uint32_t sch_qcr;         /* 12'h130 */ 
  volatile uint32_t sch_pcr;         /* 12'h134 */
  volatile uint32_t sch_qtr0;        /* 12'h140 */
  volatile uint32_t sch_qtr1;        /* 12'h144 */
  volatile uint32_t sch_qtr2;        /* 12'h148 */
  volatile uint32_t sch_qtr3;        /* 12'h14c */
  volatile uint32_t sch_qtr4;        /* 12'h150 */
  volatile uint32_t sch_qtr5;        /* 12'h154 */
  volatile uint32_t sch_qtr6;        /* 12'h158 */
  volatile uint32_t sch_qtr7;        /* 12'h15c */
  volatile uint32_t sch_qtr8;        /* 12'h160 */
  volatile uint32_t sch_qtr9;        /* 12'h164 */
  volatile uint32_t sch_qtr10;       /* 12'h168 */
  volatile uint32_t sch_qtr11;       /* 12'h16c */
  volatile uint32_t sch_qtr12;       /* 12'h170 */
  volatile uint32_t sch_qtr13;       /* 12'h174 */
  volatile uint32_t sch_qtr14;       /* 12'h178 */
  volatile uint32_t sch_qtr15;       /* 12'h17c */

};

