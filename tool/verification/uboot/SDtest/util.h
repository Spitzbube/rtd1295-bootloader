#ifndef _typedef_H_
   #define _typedef_H_
      
   
   // Define Data type

   typedef unsigned int       UINT32;
   typedef unsigned short int UINT16;
   typedef unsigned char      UINT8;
   typedef int                INT32;
   typedef short int          INT16;
   typedef char               INT8;
   typedef unsigned char      BOOLEAN;
   #define true               (1 == 1)
   #define false              (0 == 1)
   #define OK                 true
   #define NG                 false
   #define M1_0               ((UINT32)(0x1))
   #define M1_1               ((UINT32)(0x1) << 1)
   #define M1_2               ((UINT32)(0x1) << 2)
   #define M1_3               ((UINT32)(0x1) << 3)
   #define M1_4               ((UINT32)(0x1) << 4)
   #define M1_5               ((UINT32)(0x1) << 5)
   #define M1_6               ((UINT32)(0x1) << 6)
   #define M1_7               ((UINT32)(0x1) << 7)
   #define M1_8               ((UINT32)(0x1) << 8)
   #define M1_9               ((UINT32)(0x1) << 9)
   #define M1_10              ((UINT32)(0x1) << 10)
   #define M1_11              ((UINT32)(0x1) << 11)
   #define M1_12              ((UINT32)(0x1) << 12)
   #define M1_13              ((UINT32)(0x1) << 13)
   #define M1_14              ((UINT32)(0x1) << 14)
   #define M1_15              ((UINT32)(0x1) << 15)
   #define M1_16              ((UINT32)(0x1) << 16)
   #define M1_17              ((UINT32)(0x1) << 17)
   #define M1_18              ((UINT32)(0x1) << 18)
   #define M1_19              ((UINT32)(0x1) << 19)
   #define M1_20              ((UINT32)(0x1) << 20)
   #define M1_21              ((UINT32)(0x1) << 21)
   #define M1_22              ((UINT32)(0x1) << 22)
   #define M1_23              ((UINT32)(0x1) << 23)
   #define M1_24              ((UINT32)(0x1) << 24)
   #define M1_25              ((UINT32)(0x1) << 25)
   #define M1_26              ((UINT32)(0x1) << 26)
   #define M1_27              ((UINT32)(0x1) << 27)
   #define M1_28              ((UINT32)(0x1) << 28)
   #define M1_29              ((UINT32)(0x1) << 29)
   #define M1_30              ((UINT32)(0x1) << 30)
   #define M1_31              ((UINT32)(0x1) << 31)
   #define M0_0               (~M1_0 )
   #define M0_1               (~M1_1 )
   #define M0_2               (~M1_2 )
   #define M0_3               (~M1_3 )
   #define M0_4               (~M1_4 )
   #define M0_5               (~M1_5 )
   #define M0_6               (~M1_6 )
   #define M0_7               (~M1_7 )
   #define M0_8               (~M1_8 )
   #define M0_9               (~M1_9 )
   #define M0_10              (~M1_10)
   #define M0_11              (~M1_11)
   #define M0_12              (~M1_12)
   #define M0_13              (~M1_13)
   #define M0_14              (~M1_14)
   #define M0_15              (~M1_15)
   #define M0_16              (~M1_16)
   #define M0_17              (~M1_17)
   #define M0_18              (~M1_18)
   #define M0_19              (~M1_19)
   #define M0_20              (~M1_20)
   #define M0_21              (~M1_21)
   #define M0_22              (~M1_22)
   #define M0_23              (~M1_23)
   #define M0_24              (~M1_24)
   #define M0_25              (~M1_25)
   #define M0_26              (~M1_26)
   #define M0_27              (~M1_27)
   #define M0_28              (~M1_28)
   #define M0_29              (~M1_29)
   #define M0_30              (~M1_30)
   #define M0_31              (~M1_31)

#endif  // _typedef_H_

#ifndef _RegisterAccess_H_
#define _RegisterAccess_H_

   // macro definition   
   #define Rreg32(Addr)        	   rtd_inl(Addr)  
   #define Wreg32(Addr,Value)      rtd_outl(Addr,Value)
   #define Rreg8(Addr)         	   rtd_inb(Addr)
   #define Wreg8(Addr,Value)  	   rtd_outb(Addr,Value)
   
   //extern void sys_wait_us(UINT32);


#endif  // _RegisterAccess_H_
