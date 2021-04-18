/** @file
*
*  Copyright (c) 2007-2014, Allwinner Technology Co., Ltd. All rights reserved.
*  http://www.allwinnertech.com
*
*  tangmanliang <tangmanliang@allwinnertech.com>
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

#ifndef __MACH_SUN50I_CLK__H
#define __MACH_SUN50I_CLK__H

#define PLL_CPU             0x0000
#define PLL_AUDIO           0x0008
#define PLL_VIDEO0          0x0010
#define PLL_VE              0x0018
#define PLL_DDR0            0x0020
#define PLL_PERIPH0         0x0028
#define PLL_PERIPH1         0x002c
#define PLL_VIDEO1          0x0030
#define PLL_GPU             0x0038
#define MIPI_PLL            0x0040
#define PLL_HSIC            0X0044
#define PLL_DE              0x0048
#define PLL_DDR1            0x004c


#define CPU_CFG             0x0050
#define AHB1_CFG            0x0054
#define APB2_CFG            0x0058
#define AHB2_CFG            0x005c
#define BUS_GATE0           0x0060
#define BUS_GATE1           0x0064
#define BUS_GATE2           0x0068
#define BUS_GATE3           0x006c
#define BUS_GATE4           0x0070
#define THS_CFG             0x0074
#define NAND_CFG            0x0080
#define SD0_CFG             0x0088
#define SD1_CFG             0x008c
#define SD2_CFG             0x0090
#define TS_CFG              0x0098
#define CE_CFG              0x009c
#define SPI0_CFG            0x00A0
#define SPI1_CFG            0x00A4
#define I2S0_CFG            0x00B0
#define I2S1_CFG            0x00B4
#define I2S2_CFG            0x00B8
#define SPDIF_CFG           0x00C0
#define USB_CFG             0x00CC
#define DRAM_CFG            0x00F4
#define DDR_CFG             0x00F8
#define MBUS_RST            0x00FC
#define DRAM_GATE           0x0100

#define DE_CFG              0x0104
#define TCON0_CFG           0x0118
#define TCON1_CFG           0x011C
#define DEINTERLACE_CFG     0x0124
#define CSI_MISC            0x0130
#define CSI_CFG             0x0134
#define VE_CFG              0x013C
#define ADDA_CFG            0x0140
#define AVS_CFG             0x0144
#define HDMI_CFG            0x0150
#define HDMI_SLOW           0x0154
#define MBUS_CFG            0x015C
#define MIPI_DSI            0x0168
#define GPU_CFG             0x01A0

#define PLL_PERI1PAT        0x027C
#define PLL_CPUPAT          0x0280
#define PLL_AUDIOPAT        0x0284
#define PLL_VIDEO0PAT       0x0288
#define PLL_VEPAT           0x028c
#define PLL_DRR0PAT         0x0290
#define PLL_VEDEO1PAT       0x0298
#define PLL_GPUPAT          0x029c
#define PLL_MIPIPAT         0x02A0
#define PLL_HSICPAT         0x02A4
#define PLL_DEPAT           0x02A8
#define PLL_DDR1PAT         0x02AC
#define PLL_CLK_CTRL        0x0320

#define BUS_RST0            0x02C0
#define BUS_RST1            0x02C4
#define BUS_RST2            0x02C8
#define BUS_RST3            0x02D0
#define BUS_RST4            0x02D8

#define SUNXI_CLK_MAX_REG   0x0320

#define CPUS_CFG            0x0000
#define CPUS_APB0           0x000c
#define CPUS_APB0_GATE      0x0028
#define CPUS_CIR            0x0054
#define CPUS_APB0_RST       0x00B0
#define CPUS_CLK_MAX_REG    0x00B0
#define LOSC_OUT_GATE       0x01F00060
#define ADDA_PR_CFG_REG     0x1C0

#define F_N8X7_M0X4(nv,mv) FACTOR_ALL(nv,8,7,0,0,0,mv,0,4,0,0,0,0,0,0,0,0,0)
#define F_N8X5_K4X2(nv,kv) FACTOR_ALL(nv,8,5,kv,4,2,0,0,0,0,0,0,0,0,0,0,0,0)
#define F_N8X7_M0X2(nv,mv) FACTOR_ALL(nv,8,7,0,0,0,mv,0,2,0,0,0,0,0,0,0,0,0)
#define F_N8X5_K4X2_M0X2(nv,kv,mv) FACTOR_ALL(nv,8,5,kv,4,2,mv,0,2,0,0,0,0,0,0,0,0,0)
#define F_N8X5_K4X2_M0X2_P16x2(nv,kv,mv,pv) \
               FACTOR_ALL(nv,8,5, \
                          kv,4,2, \
                          mv,0,2, \
                          pv,16,2, \
                          0,0,0,0,0,0)


#define PLLCPU(n,k,m,p,freq)    {F_N8X5_K4X2_M0X2_P16x2(n, k, m, p),  freq}
#define PLLVIDEO0(n,m,freq)   {F_N8X7_M0X4( n, m),  freq}
#define PLLVE(n,m,freq)     {F_N8X7_M0X4( n, m),  freq}
#define PLLDDR0(n,k,m,freq)   {F_N8X5_K4X2_M0X2( n, k, m),  freq}
#define PLLPERIPH0(n,k,freq)    {F_N8X5_K4X2( n, k),  freq}
#define PLLPERIPH1(n,k,freq)    {F_N8X5_K4X2( n, k),  freq}
#define PLLVIDEO1(n,m,freq)   {F_N8X7_M0X4( n, m),  freq}
#define PLLGPU(n,m,freq)      {F_N8X7_M0X4( n, m),  freq}
#define PLLHSIC(n,m,freq)     {F_N8X7_M0X4( n, m),  freq}
#define PLLDE(n,m,freq)     {F_N8X7_M0X4( n, m),  freq}
#define PLLDDR1(n,m,freq)     {F_N8X7_M0X2(n,m),  freq}

#endif
