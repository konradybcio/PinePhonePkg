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


#ifndef  __SUNXI_MBR_H__
#define  __SUNXI_MBR_H__

#include <IndustryStandard/Mbr.h>
#include <Uefi/UefiBaseType.h>

#define  SUNXI_MBR_OFFSET         (40960)
#define  GET_BLOCK_ADDR(addr)     (SUNXI_MBR_OFFSET + (addr))

#define     DOWNLOAD_MAP_NAME   "dlinfo.fex"
#define     SUNXI_MBR_NAME      "sunxi_mbr.fex"
/* MBR       */
#define     SUNXI_MBR_SIZE          (16 * 1024)
#define     SUNXI_DL_SIZE       (16 * 1024)
#define     SUNXI_MBR_MAGIC         "softw411"
#define     SUNXI_MBR_MAX_PART_COUNT  120
#define     SUNXI_MBR_COPY_NUM          4    //mbr的备份数量
#define     SUNXI_MBR_RESERVED          (SUNXI_MBR_SIZE - 32 - 4 - (SUNXI_MBR_MAX_PART_COUNT * sizeof(sunxi_partition)))   //mbr保留的空间
#define     SUNXI_DL_RESERVED           (SUNXI_DL_SIZE - 32 - (SUNXI_MBR_MAX_PART_COUNT * sizeof(dl_one_part_info)))

#define     SUNXI_NOLOCK                (0)
#define     SUNXI_LOCKING               (0xAA)
#define     SUNXI_RELOCKING             (0xA0)
#define     SUNXI_UNLOCK                (0xA5)

/* GPT */
#define     SUNXI_GPT_SIZE          (16 * 1024)
#define     SUNXI_GPT_MAGIC         "softw411"
#define     SUNXI_GPT_MAX_PART_COUNT  120
#define     SUNXI_GPT_COPY_NUM          4    //GPT靠靠?
#define     SUNXI_GPT_RESERVED          (SUNXI_GPT_SIZE - 32 - (SUNXI_GPT_MAX_PART_COUNT * sizeof(gpt_partition)))   //mbr靠靠?


/* partition information */
typedef struct gpt_partition_t
{
  unsigned  int       addrhi;       //靠靠, 靠靠靠
  unsigned  int       addrlo;       //
  unsigned  int       lenhi;        //靠
  unsigned  int       lenlo;        //
  unsigned  char      classname[16];    //靠靠
  unsigned  char      name[16];     //靠靠
  unsigned  int       user_type;          //靠靠
  unsigned  int       keydata;            //靠靠靠靠靠靠
  unsigned  int       ro;                 //靠靠
        EFI_GUID      type;
  EFI_GUID      uniqueguid;
  unsigned  int     attrhi;       //靠靠
  unsigned  int     attrlo;
  unsigned  char      reserved[28];   //靠靠靠靠靠?128靠
} //__attribute__ ((packed))sunxi_partition;
gpt_partition;

/* gpt information */
typedef struct sunxi_gpt
{
  unsigned  int       crc32;                // crc 1k - 4
  unsigned  int       version;              // 靠靠? 0x00000100
  unsigned  char      magic[8];             //"softw311"
  unsigned  int       copy;               //靠
  unsigned  int       index;                //靠縢pt靠
  unsigned  int       PartCount;              //靠靠
  unsigned  int       stamp[1];         //靠
  gpt_partition       array[SUNXI_GPT_MAX_PART_COUNT];  //
  unsigned  char      res[SUNXI_GPT_RESERVED];
}//__attribute__ ((packed)) sunxi_mbr_t;
sunxi_gpt_t;

/* GPT table info */
typedef struct gpt_table_info
{
  EFI_LBA MyLBA;  
  EFI_LBA AlternateLBA; 
  EFI_LBA FirstLBA;
  EFI_LBA LastLBA;  
  EFI_LBA EntryLBA;   
  UINT32 EntryNum;   
  UINT32 EntrySize;  
  EFI_GUID Guid;
}gpt_table_info_t;

/* partition information */
typedef struct sunxi_partition_t
{
  unsigned  int       addrhi;       //起始地址, 以扇区为单位
  unsigned  int       addrlo;       //
  unsigned  int       lenhi;        //长度
  unsigned  int       lenlo;        //
  unsigned  char      classname[16];    //次设备名
  unsigned  char      name[16];     //主设备名
  unsigned  int       user_type;          //用户类型
  unsigned  int       keydata;            //关键数据，要求量产不丢失
  unsigned  int       ro;                 //读写属性
  unsigned  int       sig_verify;     //签名验证属性
  unsigned  int       sig_erase;          //签名擦除属性
  unsigned  int       sig_value[4];
  unsigned  int       sig_pubkey;
  unsigned  int       sig_pbumode;
  unsigned  char      reserved2[36];    //保留数据，匹配分区信息128字节
}__attribute__ ((packed))sunxi_partition;

/* mbr information */
typedef struct sunxi_mbr
{
  unsigned  int       crc32;                // crc 1k - 4
  unsigned  int       version;              // 版本信息， 0x00000100
  unsigned  char      magic[8];             //"softw311"
  unsigned  int       copy;               //分数
  unsigned  int       index;                //第几个MBR备份
  unsigned  int       PartCount;              //分区个数
  unsigned  int       stamp[1];         //对齐
  sunxi_partition     array[SUNXI_MBR_MAX_PART_COUNT];  //
  unsigned  int       lockflag;
  unsigned  char      res[SUNXI_MBR_RESERVED];
}__attribute__ ((packed)) sunxi_mbr_t;

typedef struct tag_one_part_info
{
  unsigned  char      name[16];           //所烧写分区的主设备名
  unsigned  int       addrhi;             //所烧写分区的高地址，扇区单位
  unsigned  int       addrlo;             //所烧写分区的低地址，扇区单位
  unsigned  int       lenhi;        //所烧写分区的长度，高32位，扇区单位
  unsigned  int       lenlo;        //所烧写分区的长度，低32位，扇区单位
  unsigned  char      dl_filename[16];    //所烧写分区的文件名称，长度固定16字节
  unsigned  char      vf_filename[16];    //所烧写分区的校验文件名称，长度固定16字节
  unsigned  int       encrypt;            //所烧写分区的数据是否进行加密 0:加密   1：不加密
  unsigned  int       verify;             //所烧写分区的数据是否进行校验 0:不校验 1：校验
}__attribute__ ((packed)) dl_one_part_info;

//分区烧写信息
typedef struct tag_download_info
{
  unsigned  int       crc32;                            //crc
  unsigned  int       version;                                    //版本号  0x00000101
  unsigned  char      magic[8];                         //"softw311"
  unsigned  int       download_count;                         //需要烧写的分区个数
  unsigned  int       stamp[3];                 //对齐
  dl_one_part_info  one_part_info[SUNXI_MBR_MAX_PART_COUNT];  //烧写分区的信息
  unsigned  char      res[SUNXI_DL_RESERVED];
}
__attribute__ ((packed)) sunxi_download_info;


#endif
