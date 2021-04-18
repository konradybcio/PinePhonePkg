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

#include "panels.h"

struct sunxi_lcd_drv g_lcd_drv;

extern __lcd_panel_t default_panel;

__lcd_panel_t* panel_array[] = {
  &default_panel,
  /* add new panel below */

  NULL,
};

static void lcd_set_panel_funs(void)
{
  int i;

  for (i=0; panel_array[i] != NULL; i++) {
    sunxi_lcd_set_panel_funs(panel_array[i]->name, &panel_array[i]->func);
  }

  return ;
}

int lcd_init(void)
{
  sunxi_disp_get_source_ops(&g_lcd_drv.src_ops);
  lcd_set_panel_funs();

  return 0;
}
