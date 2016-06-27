/* Define the ZQ Control Register */
struct pctl_zqcr{
  uint32_t ovrd_data:20;     //19-0  
  uint32_t zprog:8;          //27-20  
  uint32_t ovrd_en:1;        //28
  uint32_t clk_sel:1;        //29
  uint32_t reserv0:1;  
  uint32_t start:1;          //31
};                      

/* Define the ZQ Status Register */
struct pctl_zqsr{
  uint32_t zctrl:20;          //19-0  
  uint32_t zqpd:2;            //21-20  
  uint32_t zqpu:2;            //23-22  
  uint32_t odtpd:2;           //25-24  
  uint32_t odtpu:2;           //27-26
  uint32_t reserv:2;          //29-28
  uint32_t zqerr:1;           //30
  uint32_t zqdone:1;          //31
};                      

/* Define page size selection in Scheduler */
enum rxi310_sch_page_size {
  Byte_512  = 0x0, 
  Byte_1024 = 0x1,
  Byte_2048 = 0x2 
};

/* Define bank number selection in Scheduler */
enum rxi310_sch_bank_number {
  Bank_4  = 0x0, 
  Bank_8  = 0x1
};

/* Scheduler Configure Register*/
struct scheduler_config{
  uint32_t page_size:2;
  uint32_t bank_number:1;
  uint32_t reserv:29;
};

/* PCTL DRAM Mode Register */
struct pctl_mr0{
  uint32_t bst_length:3;    //2-0
  uint32_t bst_type:1;      //3
  uint32_t cas_lat:4;       //7-4
  uint32_t reserv0:1;       //8
  uint32_t wr_recov:3;      //11-9
  uint32_t pd_mode:1;       //12
  uint32_t reserv1:19;       
};

/* PCTL DRAM Extend Mode Register 1 */
struct pctl_mr1{
  uint32_t reserv0:2;    //1-0
  uint32_t odt:1;        //2
  uint32_t reserv1:29;    //
};

/* PCTL DRAM Extend Mode Register 2-3 */
struct pctl_emr{
  uint32_t emr: 14;      //13-0
  uint32_t reserv1:18;    //
};

/* PCTL DRAM Timing Parameter Register 0 */
struct pctl_tpr0{
  uint32_t tMRD:2;    //1-0
  uint32_t tRTP:3;    //4-2
  uint32_t tWTR:3;    //7-5
  uint32_t tRP:4;     //11-8
  uint32_t tRCD:4;    //15-12
  uint32_t tWR:4;     //19-16
  uint32_t reserv0:1;    
  uint32_t tRRD:4;    //24-21
  uint32_t tRAS:5;    //29-25
  uint32_t reserv1:2;    
};

/* PCTL DRAM Refresh Parameter Register  */
struct pctl_drr{
  uint32_t rfc2rfc:8;   //7-0
  uint32_t rfprd:16;    //23-8
  uint32_t reserv1:4;    
  uint32_t rd:1;        //28
  uint32_t reserv0:3;    
};

/* RXI310 Controller Status Register  */
struct pctl_csr{
  uint32_t dqs_drift:4;         //3-0
  uint32_t reserv0:16;           
  uint32_t dt_error:1;          //20
  uint32_t reserv1:3;           
  uint32_t dt_done:1;           //24
  uint32_t mig_idly_rdy:1;      //25
  uint32_t mig_init_result:4;   //29-36
  uint32_t mig_init_done:1;     //30
  uint32_t init_done:1;         //31
};

/* RXI310 Controller BIST Control  */
struct pctl_bcr{
  uint32_t bist_start:1;        //0
  uint32_t reserv1:3;           
  uint32_t num_elm:4;           //7-4    
  uint32_t error_mask:8;        //15-8
  uint32_t reserv2:16;           
};

/* RXI310 Controller BIST Status  */
struct pctl_bsr{
  uint32_t bist_done:1;        //0
  uint32_t bist_fail:1;        //1          
  uint32_t fail_op:6;           //7-2    
  uint32_t fail_count:8;        //15-8
  uint32_t reserv1:16;           
};

/* RXI310 Controller IO control  */
struct pctl_iocr{
  uint32_t sstl_odt:2;        //0-1
  uint32_t dll_ato0:1;        //2          
  uint32_t sstl_iddq:1;       //3   
  uint32_t dll_ato1:1;        //4
  uint32_t reserv1:27;           
};

/* Define DRAM type */
enum rxi310_dram_type {
  DDR2  = 0x0, 
  DDR3  = 0x1
};

/* RXI310 DRAM Controller */
struct pctl_dcr{
  uint32_t dram_type:1;       //0
  uint32_t reserv1:31;           
};
