//#include <stdio.h>
#include "DW_common.h"
#include "ms_rxi310_defs.h"
#include "rle0272_defs.h"
#include "rxi310_public.h"

void rxi_dramc_pad_init(struct dw_device*, struct pctl_zqcr*);
void rxi_dramc_set_scheduler(struct dw_device*, struct scheduler_config*);
void rxi_dramc_set_dram_mode(struct dw_device*, struct pctl_mr0*, struct pctl_mr1*, struct pctl_emr*);
void rxi_dramc_set_dram_timing(struct dw_device*, struct pctl_tpr0*);
void rxi_dramc_set_dram_refresh(struct dw_device*, struct pctl_drr*);
void rxi_dramc_init(struct dw_device*);
void rxi_dramc_set_io_control(struct dw_device*, struct pctl_iocr*);
void rxi_dramc_set_dram_config(struct dw_device*, struct pctl_dcr*);

struct pctl_zqsr rxi_dramc_check_pad_init(struct dw_device*);
struct pctl_csr  rxi_dramc_check_status(struct dw_device*);

void rxi_dramc_start_bist(struct dw_device *, struct pctl_bcr*);
struct pctl_bsr rxi_dramc_check_bist_status(struct dw_device*);


volatile int dly_cnt;  
void extra_delay(int);

//void rxi_dramc_example()
int main(void)
{
  struct pctl_zqsr zqsr;
  struct dw_device dmac;
  struct pctl_zqcr zq_control = {0,0,0,0,0,0};
  struct scheduler_config sch_conf = {0,0,0};
  struct pctl_mr0 dram_mr0 = {0,0,0,0,0,0,0};
  struct pctl_mr1 dram_mr1 = {0,0,0};
  struct pctl_emr dram_mr2 = {0,0};
  struct pctl_tpr0 dram_tpr0 = {0,0,0,0,0,0,0,0,0};
  struct pctl_drr dram_ref = {0,0,0,0,0};
  struct pctl_iocr pad_iocr = {0,0,0,0,0};
  struct pctl_bcr bcr = {0,0,0,0,0};
  struct pctl_dcr dram_config = {0, 0};
  struct pctl_csr csr;
  struct pctl_bsr bsr;
  unsigned int try_val;
  unsigned int *record = 0xb0002800;
  volatile unsigned int *dram_ptr = 0xa0001000;

  dmac.base_address    = ms_rxi310_BASE;

  //Set DRAM type first
  dram_config.dram_type = DDR3;
  rxi_dramc_set_dram_config(&dmac, &dram_config);

  if(dram_config.dram_type == DDR2)
  {
    sch_conf.page_size   = Byte_2048;
    sch_conf.bank_number = Bank_8;
    dram_mr0.bst_length  = 0x2; //BL4
    dram_mr0.bst_type    = 0;   //INCR
    dram_mr0.cas_lat     = 0xe; //7 cycle
    dram_mr0.wr_recov    = 4;   //5 cycle
    dram_mr1.odt         = 0;   //DRAM ODT Off
    pad_iocr.sstl_odt    = 0;   //ASIC ODT Off
    dram_tpr0.tRAS       = 0x15; 
    dram_tpr0.tRRD       = 0x6;  
    dram_tpr0.tWR        = 0x8;  
    dram_tpr0.tRCD       = 0x8;  
    dram_tpr0.tRP        = 0x8;  
    dram_tpr0.tWTR       = 0x4;  
    dram_tpr0.tRTP       = 0x4;  
    dram_tpr0.tMRD       = 0x2;  
    dram_ref.rd          = 1; 
    dram_ref.rfc2rfc     = 0x72; 
    dram_ref.rfprd       = 0x0f00; 
  }
  else //DDR3
  {
    sch_conf.page_size   = Byte_2048;
    sch_conf.bank_number = Bank_8;
    dram_mr0.bst_length  = 0x2; //BL4
    dram_mr0.bst_type    = 0;   //INCR
    dram_mr0.cas_lat     = 0x2; //6 cycle
    dram_mr0.wr_recov    = 4;   //8 cycle
    dram_mr1.odt         = 0;   //DRAM ODT Off
    dram_mr2.emr         = 0;   //CWL = 5 cycles
    pad_iocr.sstl_odt    = 3;   //ASIC ODT Off
    dram_tpr0.tRAS       = 0x15; 
    dram_tpr0.tRRD       = 0x6;  
    dram_tpr0.tWR        = 0x8;  
    dram_tpr0.tRCD       = 0x8;  
    dram_tpr0.tRP        = 0x8;  
    dram_tpr0.tWTR       = 0x4;  
    dram_tpr0.tRTP       = 0x4;  
    dram_tpr0.tMRD       = 0x2;  
    dram_ref.rd          = 1; 
    dram_ref.rfc2rfc     = 0x72; 
    dram_ref.rfprd       = 0x0f00; 
  }
  bcr.num_elm          = 2;

  //Auto-cal
  zq_control.ovrd_en    = 0;
  zq_control.ovrd_data  = 0;
  zq_control.zprog      = 0x56;
  zq_control.clk_sel    = 1;

  //Step 0. Setup scheduler & controller
  rxi_dramc_set_scheduler(&dmac, &sch_conf);
  rxi_dramc_set_dram_timing(&dmac, &dram_tpr0);
  rxi_dramc_set_dram_refresh(&dmac, &dram_ref);

  for(try_val = 0; try_val < 1000; try_val++)
  {
    *(record+try_val) = 0;
  }

  unsigned int start_value = *(record - 1);
  unsigned int stop_value = *(record - 2);

  //for(try_val = 0x18c6b4; try_val < 0x18c6ff; try_val++)
  for(try_val = start_value; try_val < stop_value; try_val++)
  {
    //Get value from try_value
    //if(try_val & 0x1 == 0)
    //  dram_mr1.odt         = 0;   //DRAM ODT Off
    //else
    //  dram_mr1.odt         = 1;   //DRAM ODT On
    //if(try_val & 0x2 == 0)
    //  pad_iocr.sstl_odt         = 0;   //ASIC ODT Off
    //else
    //  pad_iocr.sstl_odt         = 1;   //ASIC ODT On
    //zq_control.ovrd_data = try_val >> 2;
    zq_control.zprog     = try_val >> 2;
    printf("Trying %x\n", zq_control.zprog);

 
    //Step 0: Set DRAM mode
    rxi_dramc_set_dram_mode(&dmac, &dram_mr0, &dram_mr1, &dram_mr2);
    rxi_dramc_set_io_control(&dmac, &pad_iocr);

    //Step 1: start pad initialization
    rxi_dramc_pad_init(&dmac, &zq_control);
    //printf("Start ZQ Cal Operation!!");

    //Step 2: Wait pad initialization done
    while(zq_control.ovrd_en ==0){
        extra_delay(100); //delay some period
        zqsr = rxi_dramc_check_pad_init(&dmac);
        if(zqsr.zqdone == 1){
            break;
        }
    }
    //printf("ZQ Cal Done!!");
    //Double check the result
    if(zq_control.ovrd_en == 0)
    {
      if(zqsr.zqerr == 0) 
      {
        printf("ZQ Pass and Result = %d\n", zqsr.zctrl);  
      }
      else
      {
        //while(1){}
        continue;
      }
    }
    else
    {
      extra_delay(5000); //delay some period
    }

    //Step 3: start dram initialization
    rxi_dramc_dram_init(&dmac);
    extra_delay(5000); //delay some period
  
    //Step 4: Wait dram initialization done
    while(1){
        extra_delay(200); //delay some period
        csr = rxi_dramc_check_status(&dmac);
        if(csr.init_done == 1){
            break;
        }
    }
  
    //Step 5: start data training
    rxi_dramc_datatrain(&dmac);
  
    //Step 6: Wait data training done
    while(1){
        extra_delay(5000); //delay some period
        csr = rxi_dramc_check_status(&dmac);
        if(csr.dt_done == 1){
            break;
        }
    }
    //Double check the result
    if(csr.dt_error == 0)
    {
      printf("Data Training Pass with %x\n", zq_control.zprog);  
    }
    else
    {
      continue;
    }
    //Step 7: Apply BIST
    //rxi_dramc_start_bist(&dmac, &bcr);
    //while(1)
    //{
    //  extra_delay(5000); //delay some period
    //  bsr = rxi_dramc_check_bist_status(&dmac);
    //  if(bsr.bist_done == 1)
    //  {
    //    break;
    //  }
    //}
    //if(bsr.bist_fail == 0)
    //{
    //  *record++ = try_val;
    //}
    
  }

  return pass_uart();
};

void extra_delay(int dly_max)
{
  for(dly_cnt = 0; dly_cnt < dly_max; dly_cnt++)
  { }
  return;
}
