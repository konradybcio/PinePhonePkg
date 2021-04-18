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

#include "default_panel.h"

static void LCD_power_on(u32 sel);
static void LCD_power_off(u32 sel);
static void LCD_bl_open(u32 sel);
static void LCD_bl_close(u32 sel);

static void LCD_panel_init(u32 sel);
static void LCD_panel_exit(u32 sel);

static void LCD_cfg_panel_info(panel_extend_para * info)
{
  u32 i = 0, j=0;
  u32 items;
  u8 lcd_gamma_tbl[][2] =
  {
    //{input value, corrected value}
    {0, 0},
    {15, 15},
    {30, 30},
    {45, 45},
    {60, 60},
    {75, 75},
    {90, 90},
    {105, 105},
    {120, 120},
    {135, 135},
    {150, 150},
    {165, 165},
    {180, 180},
    {195, 195},
    {210, 210},
    {225, 225},
    {240, 240},
    {255, 255},
  };

  u32 lcd_cmap_tbl[2][3][4] = {
  {
    {LCD_CMAP_G0,LCD_CMAP_B1,LCD_CMAP_G2,LCD_CMAP_B3},
    {LCD_CMAP_B0,LCD_CMAP_R1,LCD_CMAP_B2,LCD_CMAP_R3},
    {LCD_CMAP_R0,LCD_CMAP_G1,LCD_CMAP_R2,LCD_CMAP_G3},
    },
    {
    {LCD_CMAP_B3,LCD_CMAP_G2,LCD_CMAP_B1,LCD_CMAP_G0},
    {LCD_CMAP_R3,LCD_CMAP_B2,LCD_CMAP_R1,LCD_CMAP_B0},
    {LCD_CMAP_G3,LCD_CMAP_R2,LCD_CMAP_G1,LCD_CMAP_R0},
    },
  };

  items = sizeof(lcd_gamma_tbl)/2;
  for (i=0; i<items-1; i++) {
    u32 num = lcd_gamma_tbl[i+1][0] - lcd_gamma_tbl[i][0];

    for (j=0; j<num; j++) {
      u32 value = 0;

      value = lcd_gamma_tbl[i][1] + ((lcd_gamma_tbl[i+1][1] - lcd_gamma_tbl[i][1]) * j)/num;
      info->lcd_gamma_tbl[lcd_gamma_tbl[i][0] + j] = (value<<16) + (value<<8) + value;
    }
  }
  info->lcd_gamma_tbl[255] = (lcd_gamma_tbl[items-1][1]<<16) + (lcd_gamma_tbl[items-1][1]<<8) + lcd_gamma_tbl[items-1][1];

  memcpy(info->lcd_cmap_tbl, lcd_cmap_tbl, sizeof(lcd_cmap_tbl));

}

static s32 LCD_open_flow(u32 sel)
{
  LCD_OPEN_FUNC(sel, LCD_power_on, 30);   //open lcd power, and delay 50ms
  LCD_OPEN_FUNC(sel, LCD_panel_init, 50);   //open lcd power, than delay 200ms
  LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 100);     //open lcd controller, and delay 100ms
  LCD_OPEN_FUNC(sel, LCD_bl_open, 0);     //open lcd backlight, and delay 0ms

  return 0;
}

static s32 LCD_close_flow(u32 sel)
{
  LCD_CLOSE_FUNC(sel, LCD_bl_close, 0);       //close lcd backlight, and delay 0ms
  LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 0);         //close lcd controller, and delay 0ms
  LCD_CLOSE_FUNC(sel, LCD_panel_exit, 200);   //open lcd power, than delay 200ms
  LCD_CLOSE_FUNC(sel, LCD_power_off, 500);   //close lcd power, and delay 500ms

  return 0;
}

static void LCD_power_on(u32 sel)
{
  sunxi_lcd_power_enable(sel, 0);//config lcd_power pin to open lcd power0
  sunxi_lcd_pin_cfg(sel, 1);
}

static void LCD_power_off(u32 sel)
{
  sunxi_lcd_pin_cfg(sel, 0);
  sunxi_lcd_power_disable(sel, 0);//config lcd_power pin to close lcd power0
}

static void LCD_bl_open(u32 sel)
{
  sunxi_lcd_pwm_enable(sel);
  sunxi_lcd_backlight_enable(sel);//config lcd_bl_en pin to open lcd backlight
}

static void LCD_bl_close(u32 sel)
{
  sunxi_lcd_backlight_disable(sel);//config lcd_bl_en pin to close lcd backlight
  sunxi_lcd_pwm_disable(sel);
}

static void LCD_panel_init(u32 sel)
{
  /* Magic sequence to unlock user commands below. */
  u8 commands1[3] = {0xF1, 0x12, 0x83};
  sunxi_lcd_dsi_dcs_write(sel, 0xB9, commands1, ARRAY_SIZE(commands1));

  u8 commands2[27] = {0x33, 0x81, 0x05, 0xf9, 0x0e, 0x0e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x25, 0x00, 0x91, 0x0a, 0x00, 0x00, 0x02, 0x4F, 0x11, 0x00, 0x00, 0x37};
  sunxi_lcd_dsi_dcs_write(sel, 0xBA, commands2, ARRAY_SIZE(commands2));

  u8 commands3[] = {0x25, /* PCCS = 2, ECP_DC_DIV = 1/4 HSYNC */
			  0x22, /* DT = 15ms XDK_ECP = x2 */
			  0x20, /* PFM_DC_DIV = /1 */
			  0x03  /* ECP_SYNC_EN = 1, VGX_SYNC_EN = 1 */};
  sunxi_lcd_dsi_dcs_write(sel, 0xB8, commands3, ARRAY_SIZE(commands3));

  u8 commands4[] = {0x10, /* VBP_RGB_GEN */
			  0x10, /* VFP_RGB_GEN */
			  0x05, /* DE_BP_RGB_GEN */
			  0x05, /* DE_FP_RGB_GEN */
			  /* The rest is undocumented in ST7703 datasheet */
			  0x03, 0xFF,
			  0x00, 0x00,
			  0x00, 0x00};
  sunxi_lcd_dsi_dcs_write(sel, 0xB3, commands4, ARRAY_SIZE(commands4));

  u8 commands5[] = {0x73, /* N_POPON */
			  0x73, /* N_NOPON */
			  0x50, /* I_POPON */
			  0x50, /* I_NOPON */
			  0x00, /* SCR[31,24] */
			  0xC0, /* SCR[23,16] */
			  0x08, /* SCR[15,8] */
			  0x70, /* SCR[7,0] */
			  0x00  /* Undocumented */};
  sunxi_lcd_dsi_dcs_write(sel, 0xC0, commands5, ARRAY_SIZE(commands5));

  u8 commands6[] = { 0x4e };
  sunxi_lcd_dsi_dcs_write(sel, 0xBC, commands6, ARRAY_SIZE(commands6));

  u8 commands7[] = { 0x0B };
  sunxi_lcd_dsi_dcs_write(sel, 0xCC, commands7, ARRAY_SIZE(commands7));

  u8 commands8[] = { 0x80 };
  sunxi_lcd_dsi_dcs_write(sel, 0xB4, commands8, ARRAY_SIZE(commands8));

  u8 commands9[] = { 0xF0, /* NL = 240 */
			  0x12, /* RES_V_LSB = 0, BLK_CON = VSSD,
				 * RESO_SEL = 720RGB
				 */
			  0xF0  /* WHITE_GND_EN = 1 (GND),
				 * WHITE_FRAME_SEL = 7 frames,
				 * ISC = 0 frames
				 */ };
  sunxi_lcd_dsi_dcs_write(sel, 0xB2, commands3, ARRAY_SIZE(commands9));

  u8 commands10[] = { 0x00, /* PNOEQ */
			  0x00, /* NNOEQ */
			  0x0B, /* PEQGND */
			  0x0B, /* NEQGND */
			  0x10, /* PEQVCI */
			  0x10, /* NEQVCI */
			  0x00, /* PEQVCI1 */
			  0x00, /* NEQVCI1 */
			  0x00, /* reserved */
			  0x00, /* reserved */
			  0xFF, /* reserved */
			  0x00, /* reserved */
			  0xC0, /* ESD_DET_DATA_WHITE = 1, ESD_WHITE_EN = 1 */
			  0x10  /* SLPIN_OPTION = 1 (no need vsync after sleep-in)
				 * VEDIO_NO_CHECK_EN = 0
				 * ESD_WHITE_GND_EN = 0
				 * ESD_DET_TIME_SEL = 0 frames
				 */ };
  sunxi_lcd_dsi_dcs_write(sel, 0xE3, commands10, ARRAY_SIZE(commands10));

  u8 commands11[] = { 0x01, 0x00, 0xFF, 0xFF, 0x00 };
  sunxi_lcd_dsi_dcs_write(sel, 0xC6, commands11, ARRAY_SIZE(commands11));

  u8 commands12[] = { 0x74, /* VBTHS, VBTLS: VGH = 17V, VBL = -11V */
			  0x00, /* FBOFF_VGH = 0, FBOFF_VGL = 0 */
			  0x32, /* VRP  */
			  0x32, /* VRN */
			  0x77, /* reserved */
			  0xF1, /* APS = 1 (small),
				 * VGL_DET_EN = 1, VGH_DET_EN = 1,
				 * VGL_TURBO = 1, VGH_TURBO = 1
				 */
			  0xFF, /* VGH1_L_DIV, VGL1_L_DIV (1.5MHz) */
			  0xFF, /* VGH1_R_DIV, VGL1_R_DIV (1.5MHz) */
			  0xCC, /* VGH2_L_DIV, VGL2_L_DIV (2.6MHz) */
			  0xCC, /* VGH2_R_DIV, VGL2_R_DIV (2.6MHz) */
			  0x77, /* VGH3_L_DIV, VGL3_L_DIV (4.5MHz) */
			  0x77  /* VGH3_R_DIV, VGL3_R_DIV (4.5MHz) */ };
  sunxi_lcd_dsi_dcs_write(sel, 0xC1, commands12, ARRAY_SIZE(commands12));

  u8 commands13[] = { 0x07, /* VREF_SEL = 4.2V */
			  0x07  /* NVREF_SEL = 4.2V */ };
  sunxi_lcd_dsi_dcs_write(sel, 0xB5, commands13, ARRAY_SIZE(commands13));
  
  sunxi_lcd_delay_ms(20);

  u8 commands14[] = { 0x2C, /* VCOMDC_F = -0.67V */
			  0x2C  /* VCOMDC_B = -0.67V */ };
  sunxi_lcd_dsi_dcs_write(sel, 0xB6, commands14, ARRAY_SIZE(commands14));

  u8 commands15[] = { 0x02, 0x11, 0x00 };
  sunxi_lcd_dsi_dcs_write(sel, 0xBF, commands15, ARRAY_SIZE(commands15));
  
  u8 commands16[] =  { 0x82, 0x10, 0x06, 0x05, 0xA2, 0x0A, 0xA5, 0x12,
			  0x31, 0x23, 0x37, 0x83, 0x04, 0xBC, 0x27, 0x38,
			  0x0C, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0C, 0x00,
			  0x03, 0x00, 0x00, 0x00, 0x75, 0x75, 0x31, 0x88,
			  0x88, 0x88, 0x88, 0x88, 0x88, 0x13, 0x88, 0x64,
			  0x64, 0x20, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
			  0x02, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  sunxi_lcd_dsi_dcs_write(sel, 0xE9, commands16, ARRAY_SIZE(commands16));

  u8 commands17[] = { 0x02, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x02, 0x46, 0x02, 0x88,
			  0x88, 0x88, 0x88, 0x88, 0x88, 0x64, 0x88, 0x13,
			  0x57, 0x13, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
			  0x75, 0x88, 0x23, 0x14, 0x00, 0x00, 0x02, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0A,
			  0xA5, 0x00, 0x00, 0x00, 0x00 };
  sunxi_lcd_dsi_dcs_write(sel, 0xEA, commands17, ARRAY_SIZE(commands17));

  u8 commands18[] = { 0x00, 0x09, 0x0D, 0x23, 0x27, 0x3C, 0x41, 0x35,
			  0x07, 0x0D, 0x0E, 0x12, 0x13, 0x10, 0x12, 0x12,
			  0x18, 0x00, 0x09, 0x0D, 0x23, 0x27, 0x3C, 0x41,
			  0x35, 0x07, 0x0D, 0x0E, 0x12, 0x13, 0x10, 0x12,
			  0x12, 0x18 };
  sunxi_lcd_dsi_dcs_write(sel, 0xE0, commands18, ARRAY_SIZE(commands18));

  return;
}

static void LCD_panel_exit(u32 sel)
{
  sunxi_lcd_dsi_dcs_write_0para(sel,DSI_DCS_SET_DISPLAY_OFF);
  sunxi_lcd_delay_ms(20);
  return ;
}

//sel: 0:lcd0; 1:lcd1
static s32 LCD_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
  return 0;
}

__lcd_panel_t default_panel = {
  /* panel driver name, must mach the name of lcd_drv_name in sys_config.fex */
  .name = "default_lcd",
  .func = {
    .cfg_panel_info = LCD_cfg_panel_info,
    .cfg_open_flow = LCD_open_flow,
    .cfg_close_flow = LCD_close_flow,
    .lcd_user_defined_func = LCD_user_defined_func,
  },
};
