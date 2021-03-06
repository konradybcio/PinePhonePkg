/** @file
*
*  Copyright (c) 2007-2014, Allwinner Technology Co., Ltd. All rights reserved.
*  http://www.allwinnertech.com
*
*  Jerry Wang <wangflord@allwinnertech.com>
*  
*  This program and the accompanying materials                          
*  are licensed and made available under the terms and conditions of the BSD License         
*  which accompanies this distribution.  The full text of the license may be found at        
*  http://opensource.org/licenses/bsd-license.php                                            
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             
*
**/


#ifndef  __private_uboot_h__
#define  __private_uboot_h__

#include "spare_head.h"
//#include <Sunxi_type/Sunxi_type.h>

/******************************************************************************/
/*               the control information stored in file head                  */
/******************************************************************************/
struct spare_boot_ctrl_head
{
  unsigned int  jump_instruction;   // one intruction jumping to real code
  unsigned char magic[MAGIC_SIZE];  // ="uefi"
  unsigned int  check_sum;          // generated by PC
  unsigned int  align_size;     // align size in byte
  unsigned int  length;             // the size of all file
  unsigned int  uefi_length;       // the size of uefi
  unsigned char version[8];         // uboot version
  unsigned char platform[8];        // platform information
  int           reserved[1];        //stamp space, 16bytes align
};

/******************************************************************************/
/*                          the data stored in file head                      */
/******************************************************************************/
struct spare_boot_data_head
{
  unsigned int                dram_para[32];
  int             run_clock;        // Mhz
  int             run_core_vol;     // mV
  int             uart_port;              // UART??????????
  normal_gpio_cfg             uart_gpio[2];           // UART??????(??????????)GPIO????
  int             twi_port;               // TWI??????????
  normal_gpio_cfg             twi_gpio[2];            // TWI??????GPIO??????????????TWI
  int                       work_mode;              // ????????
  int                         storage_type;           // ????????????  0??nand   1??sdcard    2: spinor
  normal_gpio_cfg             nand_gpio[32];          // nand GPIO????
  char            nand_spare_data[256]; // nand ????????
  normal_gpio_cfg             sdcard_gpio[32];    // sdcard GPIO????
  char                  sdcard_spare_data[256]; // sdcard ????????
  int             reserved[6];      // ??????????, 256bytes align

};

struct spare_boot_head_t
{
  struct spare_boot_ctrl_head    boot_head;
  struct spare_boot_data_head    boot_data;
};

typedef struct toc1_head_info
{
  char name[16] ; //user can modify
  unsigned int  magic ; //must equal TOC_U32_MAGIC
  unsigned int  add_sum ;

  unsigned int  serial_num  ; //user can modify
  unsigned int  status    ; //user can modify,such as TOC_MAIN_INFO_STATUS_ENCRYP_NOT_USED

  unsigned int  items_nr; //total entry number
  unsigned int  valid_len;
  unsigned int  version_main; //only one byte
  unsigned int  version_sub;   //two bytes
  unsigned int  reserved[3];  //reserved for future

  unsigned int  end;
}toc1_head_info_t;


#define BOOT0_MAGIC                     "eGON.BT0"
#define SYS_PARA_LOG                    0x4d415244
#define  TOC0_MAGIC             "TOC0.GLH"
#define  TOC_MAIN_INFO_MAGIC    0x89119800
/******************************************************************************/
/*                              file head of Boot                             */
/******************************************************************************/
typedef struct _Boot_file_head
{
  unsigned int  jump_instruction;   // one intruction jumping to real code
  char          magic[MAGIC_SIZE];  // ="eGON.BT0"
  unsigned int  check_sum;          // generated by PC
  unsigned int  length;             // generated by PC
  unsigned int  pub_head_size;      // the size of boot_file_head_t
  char          pub_head_vsn[4];    // the version of boot_file_head_t
  unsigned int  ret_addr;           // the return value
  unsigned int  run_addr;           // run addr
  char          eGON_vsn[4];        // eGON version
  char          platform[8];        // platform information
}boot_file_head_t;
/******************************************************************************/
/*                              file head of Boot0                            */
/******************************************************************************/
typedef struct _boot0_private_head_t
{
  unsigned int                prvt_head_size;
  char                        prvt_head_vsn[4];       // the version of boot0_private_head_t
  unsigned int                dram_para[32];;         // DRAM patameters for initialising dram. Original values is arbitrary,
  unsigned int        uart_port;              // UART??????????
  normal_gpio_cfg             uart_ctrl[2];           // UART??????(??????????)????????
  unsigned int                enable_jtag;            // 1 : enable,  0 : disable
  normal_gpio_cfg             jtag_gpio[5];           // ????JTAG??????GPIO????
  normal_gpio_cfg             storage_gpio[32];       // ???????? GPIO????
  char                        storage_data[512 - sizeof(normal_gpio_cfg) * 32];      // ????????????????
  //boot_nand_connect_info_t    nand_connect_info;
}boot0_private_head_t;


typedef struct _boot0_file_head_t
{
  boot_file_head_t      boot_head;
  boot0_private_head_t  prvt_head;
}boot0_file_head_t;

#if 0
#define get_spare_head(x)      \
  (struct spare_boot_head_t*)\
  ((unsigned int)x+(((*(unsigned int*)x)&0xffffff)+2)*sizeof(int)+sizeof(int))
#endif
#define get_spare_head(x)      \
  ((struct spare_boot_head_t*)(x))\

#define get_boot0_head(x)      \
  ((boot0_file_head_t*)(x))
#endif


