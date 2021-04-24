#
# Copyright (c) 2015 Allwinnertech, Inc.
# Tyle <tyle at allwinnertech.com>
#
#

#obj-$(CONFIG_SUNXI_DISPLAY) += disp.o
obj-y += disp.o

disp-objs	:= dev_disp.o disp_sys_intf.o
disp-objs	+= de/disp_display.o de/disp_features.o de/disp_device.o de/disp_lcd.o de/disp_manager.o de/disp_private.o \
							de/disp_smart_backlight.o de/disp_enhance.o de/disp_capture.o de/disp_hdmi.o de/disp_tv.o de/disp_vdevice.o
disp-objs += lcd/panels.o lcd/lcd_source.o lcd/default_panel.o

obj-y += de/lowlevel_sun50iw1/
