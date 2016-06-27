#include <stdio.h>
#include "ddr_ctrl.h"

#define DEBUG_DATA_TRAINING 0

/*
int data_training(struct rxi310_dramc_portmap *ddr_ptr) 
{
  int                   timeout_cnt = 0;
  unsigned int          cur_pctl_csr;
  unsigned int          cur_pctl_rslr0;
  unsigned int          cur_pctl_rdgr0;
  unsigned int          last_pctl_rslr0;
  unsigned int          last_pctl_rdgr0;
  volatile unsigned int *training_result_ptr = TRAINING_RESULT_BASE;

  last_pctl_rslr0 = *(training_result_ptr);
  last_pctl_rdgr0 = *(training_result_ptr + 1);

  // printf("Before training, data training status: %08x\n", ddr_ptr->pctl_csr);
  ddr_ptr->pctl_ccr = 0x40000000;
  cur_pctl_csr      = ddr_ptr->pctl_csr;

  while( (cur_pctl_csr&0x81000000) != 0x81000000) {
     if (timeout_cnt == 20) {
       printf("Data training timeout, training status: %08x\n", cur_pctl_csr);
       return 1;
     } else {
       timeout_cnt = timeout_cnt + 1;
     }
     cur_pctl_csr = ddr_ptr->pctl_csr;
  }
  if ( ( (cur_pctl_csr&0x00100000) == 0x00100000)) {
    printf ("Data training fail, training status: %08x\n", cur_pctl_csr);
    return 1;
  } else {
    cur_pctl_rslr0 = ddr_ptr->pctl_rslr0;
    cur_pctl_rdgr0 = ddr_ptr->pctl_rdgr0;
    // printf ("Data traing success, RSLR0(%d,%d), RDGR0(%d,%d)!\n",
    //     cur_pctl_rslr0 & 0x7, (cur_pctl_rslr0>>3) & 0x7,
    //     cur_pctl_rdgr0 & 0x3, (cur_pctl_rdgr0>>3) & 0x3);
    if (cur_pctl_rslr0!= last_pctl_rslr0) {
      printf("Training latency changed: ORG (%d, %d) NEW (%d, %d).\n",
        last_pctl_rslr0 & 0x7, (last_pctl_rslr0>>3) & 0x7, 
        cur_pctl_rslr0 & 0x7, (cur_pctl_rslr0>>3) & 0x7);
      *(training_result_ptr) = cur_pctl_rslr0;
    }
    if (cur_pctl_rdgr0 != last_pctl_rdgr0) {
      printf("Training phase changed: ORG (%d, %d) NEW (%d,%d)\n",
        last_pctl_rdgr0 & 0x3, (last_pctl_rdgr0>>3) & 0x3,
        cur_pctl_rdgr0 & 0x3, (cur_pctl_rdgr0>>3) & 0x3);
      *(training_result_ptr + 1) = cur_pctl_rdgr0;
    }
    return 0;
  }
}
*/

//int run_data_training(unsigned int *bl0_dt_res, unsigned int *bl1_dt_res)
//{
//  struct rxi310_dramc_portmap *ddr_ctrl_ptr = DDR_BASE;
//  int timeout_cnt = 0;
//  int run_loop;
//  int dt_res;
//  int fail_cnt = 0; 
//  unsigned int  addr, data1, data2;
//  int data_training_enable;
//  volatile unsigned int *training_result_ptr = TRAINING_RESULT_BASE;
//
//  data_training_enable = *(training_result_ptr + 2);
//  if (data_training_enable == 0) {
//    get_data_training_result(ddr_ctrl_ptr, bl0_dt_res, bl1_dt_res);
//    printf("Abort data training\n");
//    return 0;
//  }
//
//  //Generate address and data from training
//  addr  = 0x000018a8;
//  data1 = 0xfdb0de48;
//  data2 = 0x7ee20c19;
//  data1 = data1 & 0xefefffff;
//  data2 = data2 & 0xefefffff;
//   
//  fail_cnt =  data_training(ddr_ctrl_ptr, 100, addr, data1, data2, bl0_dt_res, bl1_dt_res,  DEBUG_DATA_TRAINING);
//  if (fail_cnt > 10) {
//    printf("Too much fail count: %d/100 fail/total\n", fail_cnt);
//    return 1;
//  }
//
//  // printf("Done and got %d fails\n", fail_cnt);
//  // printf("Data Training Result: DQS_LAT0=%d, DQS_LAT1=%d\n", *bl0_dt_res, *bl1_dt_res);
//  *(training_result_ptr) = *bl0_dt_res;
//  *(training_result_ptr+1) = *bl1_dt_res;
//  return 0;
//
//}

int start_data_training(struct dw_device *dev) 
{
  unsigned int raw_result;
  struct rxi310_dramc_portmap *ddr_ptr;
  ddr_ptr = dev->base_address;

  if(1) 
  {
    ddr_ptr->pctl_rslr0 = 0x0;
    ddr_ptr->pctl_rdgr0 = 0x0;

    delay_loop(100);
    ddr_ptr->sch_scr  = ddr_ptr->sch_scr; //dummy for previous command complete
    delay_loop(100);
    ddr_ptr->pctl_ccr = 0x40000000;
    delay_loop(2000);
    raw_result = (ddr_ptr->pctl_csr) & 0x81100000;
    if(raw_result == 0x80000000) //not done
    {
      return 1;
    }
    else if(raw_result == 0x81000000) //done and pass
    { 
      return 0;
    }
    else if(raw_result == 0x81100000) //done and fail
    {
      return -1;
    }
  }
return -1;
}

//int get_data_training_status(struct rxi310_dramc_portmap *ddr_ptr) 
//{
//  unsigned int raw_result;
//
//  raw_result = ddr_ptr->pctl_csr & 0x81100000;
//  if(raw_result == 0x80000000) //not done
//  {
//    return -1;
//  }
//  else if(raw_result == 0x81000000) //done and pass
//  { 
//    return 1;
//  }
//  else if(raw_result == 0x81100000) //done and fail
//  {
//    return 0;
//  }
//}

//void get_data_training_result(struct rxi310_dramc_portmap *ddr_ptr, unsigned int *bl0, unsigned int *bl1) 
//{
//  unsigned int dt_latency, dt_phase;
//
//  dt_latency = ddr_ptr->pctl_rslr0;
//  dt_phase   = ddr_ptr->pctl_rdgr0;
//  *bl0 = ((dt_latency & 0x7) << 2) | (dt_phase & 0x3);
//  *bl1 = ((dt_latency & 0x38) >> 1) | ((dt_phase & 0xc) >> 2);
//}
//
//void get_training_pattern(struct rxi310_dramc_portmap *ddr_ptr, int *addr, int *data1, int *data2) {
//  *addr = ddr_ptr->pctl_dtar;
//  *data1 = ddr_ptr->pctl_dtr0;
//  *data2 = ddr_ptr->pctl_dtr1;
//  // printf("get_training_data DTAR:%08x, DTR0:%08x, DTR1:%08x.\n", *addr, *data1, *data2);
//} 
//
void set_training_pattern(struct dw_device *dev, unsigned int addr, unsigned int data1, unsigned int data2,
                          unsigned int data3, unsigned int data4) {
  struct rxi310_dramc_portmap *ddr_ptr;
  ddr_ptr = dev->base_address;
  //int i;
  //char *pt = 0xb0000010;
  //for(i = 0; i < 10; i ++){*pt = *pt + 1;}

  ddr_ptr->pctl_dtar = addr;
  ddr_ptr->pctl_dtr0 = data1;
  ddr_ptr->pctl_dtr1 = data2;
  ddr_ptr->pctl_dtr2 = data3;
  ddr_ptr->pctl_dtr3 = data4;
  //printf("set_training_data DTAR:%08x, DTR0:%08x, DTR1:%08x.\n", addr, data1, data2);
} 

void set_dqs_trm(struct dw_device *dev, unsigned int trm_value)
{
  struct rxi310_dramc_portmap *ddr_ptr;
  ddr_ptr = dev->base_address;

  ddr_ptr->pctl_dqstr = trm_value;
}
//void reset_itm(struct rxi310_dramc_portmap *ddr_ptr)
//{
//  //ddr_ptr->pctl_srst  = ddr_ptr->pctl_srst & 0xfffffbff;
//  ddr_ptr->pctl_srst  = 0x180ffbff;
//  ddr_ptr->sch_scr    = ddr_ptr->sch_scr; //dummy for previous command complete
//}
//
//void dereset_itm(struct rxi310_dramc_portmap *ddr_ptr)
//{
//  //ddr_ptr->pctl_srst  = ddr_ptr->pctl_srst | 0x00000400;
//  ddr_ptr->pctl_srst  = 0x180fffff;
//  ddr_ptr->sch_scr    = ddr_ptr->sch_scr; //dummy for previous command complete
//}
//
//int data_training(struct rxi310_dramc_portmap *ddr_ctrl_ptr, int max_loop, unsigned int addr, 
//                  unsigned data1, unsigned data2, unsigned int *bl0_dt_res, unsigned int *bl1_dt_res,
//                  int DEBUG)
//{
//  unsigned int res_storage[10][2];
//  int run_loop;
//  int dt_res;
//  int index, offset;
//  int fail_cnt = 0;
// 
//  unsigned int max_res = 0, max_cnt = 0;
//  
//  //Clean storage
//  for(index = 0; index < 10; index++)
//  {
//     res_storage[index][0] = 0;
//     res_storage[index][1] = 0;
//  }
//  
//  //1. Set pattern 
//  set_training_pattern(ddr_ctrl_ptr, addr, data1, data2);
//  for(run_loop = 0; run_loop < max_loop; run_loop++)
//  {
//    //reset ITMs
//    reset_itm(ddr_ctrl_ptr);
//    delay_loop(1000);
//    dereset_itm(ddr_ctrl_ptr);
//
//    //2. Run data training
//    start_data_training(ddr_ctrl_ptr);
//  
//    delay_loop(100);
//
//    //3. Check result
//    dt_res = get_data_training_status(ddr_ctrl_ptr);
//    if(dt_res == 1)
//    {
//      get_data_training_result(ddr_ctrl_ptr, bl0_dt_res, bl1_dt_res);
//      if(bl0_dt_res == 0) //remove all zero result
//      {
//        fail_cnt++;
//      }
//      else
//      {
//        if(DEBUG)
//        {
//          printf("%3d:DT result=%x, %x (0x%x=0x%x_%x)\n", run_loop, *bl0_dt_res, *bl1_dt_res, addr, data1, data2);
//        }
//        offset = (*bl0_dt_res << 4) | *bl1_dt_res;
//        for(index = 0; index < 10; index++)
//        {
//          if(res_storage[index][0] == offset)
//          {
//            res_storage[index][1]++;
//            break;
//          }
//          else if(res_storage[index][0] == 0)
//          {
//            res_storage[index][0] = offset;
//            res_storage[index][1] = 1;
//            break;
//          }
//        }
//      }
//    }
//    else
//    {
//      if(DEBUG)
//      {
//        printf("%3d:DT Failed! (0x%x=0x%x_%x)\n", run_loop, addr, data1, data2);
//      }
//      fail_cnt++;
//    }
//  }
//
//  max_cnt = 0;
//  for(index = 0; index < 10; index++)
//  {
//    if(res_storage[index][0] != 0)
//    {
//      if(DEBUG)
//      {
//        printf("%x=%d\n", res_storage[index][0], res_storage[index][1]);
//      }
//      if(res_storage[index][1] > max_cnt)
//      {
//        max_res = res_storage[index][0];
//        max_cnt = res_storage[index][1];
//      }  
//    }
//  }
//
//  *bl0_dt_res = (max_res & 0xf0) >> 4;
//  *bl1_dt_res = max_res & 0xf;
//
//  reset_itm(ddr_ctrl_ptr);
//  delay_loop(1000);
//  dereset_itm(ddr_ctrl_ptr);
//
//  ddr_ctrl_ptr->pctl_rslr0 = ((*bl1_dt_res & 0xc) << 1) | ((*bl0_dt_res & 0xc) >> 2);
//  ddr_ctrl_ptr->pctl_rdgr0 = ((*bl1_dt_res & 0x3) << 2) | (*bl0_dt_res & 0x3);
//
//  //if ((fail_cnt < 10) && ((*bl0_dt_res == 0) || (*bl1_dt_res == 0))){
//  //  for (index=0; index< 10; index++) {
//  //    printf("res_storage[%d] res: %x, cnt:%d\n", res_storage[index][0], res_storage[1]); 
//  //  }
//  //}
//  return fail_cnt;
//}
//
//void get_dqs_drift(unsigned int *drift_b0, unsigned int *drift_b1)
//{
//  struct rxi310_dramc_portmap *ddr_ctrl_ptr = DDR_BASE;
//  unsigned int pctl_csr;
//  pctl_csr = ddr_ctrl_ptr->pctl_csr;
//  *drift_b0 = pctl_csr & 0x03;
//  *drift_b1 = (pctl_csr>>2) & 0x03;
//}

void delay_loop(int cnt)
{
  int index;
  struct rxi310_dramc_portmap *ddr_ctrl_ptr =(struct rxi310_dramc_portmap *) DDR_BASE;
  for(index = 0; index < cnt; index++)
  {
    ddr_ctrl_ptr->sch_qtr0 = ddr_ctrl_ptr->sch_qtr0 + 1;
  }
} 

unsigned int get_dqs_phase(struct dw_device *dev)
{
  struct rxi310_dramc_portmap *ddr_ptr;
  ddr_ptr = dev->base_address;

  return ddr_ptr->pctl_rdgr0;
}

//int pass_ddr_test()
//{
//  volatile unsigned int *status_ptr = LOG_ADDR;
//  *status_ptr       = 0xabcd;
//  *(status_ptr+1)   = 0x0;
//  return pass_uart();
//}

//int fail_ddr_test(int status, unsigned int fail_cnt, unsigned int rd_err_cnt, 
//                  unsigned int wr_err_cnt)
//{
//  volatile unsigned int *status_ptr = LOG_ADDR;
//  if (status == 0)
//  {
//    *status_ptr       = 0x0000dead;
//    *(status_ptr+1)   = fail_cnt;
//    *(status_ptr+2)   = rd_err_cnt;
//    *(status_ptr+3)   = wr_err_cnt;
//  } 
//  else if (status == 1)
//  {
//    *status_ptr       = 0x0001dead;
//  }
//  return fail_uart();
//}
