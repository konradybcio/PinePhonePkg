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


#ifndef  __spare_head_h__
#define  __spare_head_h__

/* work mode */
#define WORK_MODE_PRODUCT      (1<<4)
#define WORK_MODE_UPDATE       (1<<5)

#define WORK_MODE_BOOT      0x00  //正常启动
#define WORK_MODE_USB_PRODUCT 0x10  //用于USB量产
#define WORK_MODE_CARD_PRODUCT  0x11  //用于卡量产
#define WORK_MODE_USB_DEBUG     0x12    //利用usb量产协议完成的测试
#define WORK_MODE_USB_UPDATE  0x20  //用于USB升级
#define WORK_MODE_OUTER_UPDATE  0x21  //用于外部盘升级

#define WORK_MODE_USB_TOOL_PRODUCT  0x04  //用于量产
#define WORK_MODE_USB_TOOL_UPDATE 0x08  //用于升级

#define UEFI_VERSION      "2.3.1"
#define UEFI_PLATFORM       "sunxi"
/* Mike update, 05/17/2016 */
//#define UEFI_FD_BASE_ADDR     0x2A000000
#define UEFI_FD_BASE_ADDR     0x4A000000

#define UEFI_MAGIC        "uboot"
#define STAMP_VALUE             0x5F0A6C39
#define ALIGN_SIZE        16 * 1024
#define MAGIC_SIZE              8
#define STORAGE_BUFFER_SIZE     (256)

#define SUNXI_UPDATE_NEXT_ACTION_NORMAL     (1)
#define SUNXI_UPDATE_NEXT_ACTION_REBOOT     (2)
#define SUNXI_UPDATE_NEXT_ACTION_SHUTDOWN   (3)
#define SUNXI_UPDATE_NEXT_ACTION_REUPDATE   (4)
#define SUNXI_UPDATE_NEXT_ACTION_BOOT     (5)

//#define BOOT0_SDMMC_START_ADDR                  (16)
#define BOOT0_SDMMC_START_ADDR                  (256)
//#define UBOOT_START_SECTOR_IN_SDMMC             (38192)
#define UBOOT_START_SECTOR_IN_SDMMC             (512)
#define BOOT0_EMMC3_START_ADDR                  (384)
#define BOOT0_EMMC3_BACKUP_START_ADDR           (512)
//#define CONFIG_MMC_LOGICAL_OFFSET               (20 * 1024 * 1024/512)
#define CONFIG_MMC_LOGICAL_OFFSET               (0)
#define MMC_LOGICAL_OFFSET                      CONFIG_MMC_LOGICAL_OFFSET

#define SUNXI_USB_MASS_PART_NUM 2
#define SUNXI_USB_MASS_GPT_PART_NUM 3
#define SUNXI_GPT_PRIMARY_HEADER_LBA 1

typedef struct _normal_gpio_cfg
{
  char      port;                       //端口号
  char      port_num;                   //端口内编号
  char      mul_sel;                    //功能编号
  char      pull;                       //电阻状态
  char      drv_level;                  //驱动驱动能力
  char      data;                       //输出电平
  char      reserved[2];                //保留位，保证对齐
}
normal_gpio_cfg;

typedef struct _special_gpio_cfg
{
  unsigned char   port;       //靠靠?
  unsigned char   port_num;     //靠靠靠??
  char        mul_sel;      //靠靠靠
  char        data;       //靠靠靠
}special_gpio_cfg;

//SD卡相关数据结构
typedef struct sdcard_spare_info_t
{
  int       card_no[4];                   //当前启动的卡控制器编号
  int       speed_mode[4];                //卡的速度模式，0：低速，其它：高速
  int       line_sel[4];                  //卡的线制，0: 1线，其它，4线
  int       line_count[4];                //卡使用线的个数
}
sdcard_spare_info;

typedef enum
{
  STORAGE_NAND =0,
  STORAGE_SD,
  STORAGE_EMMC,
  STORAGE_NOR,
        STORAGE_EMMC3
}SUNXI_BOOT_STORAGE;

#endif


