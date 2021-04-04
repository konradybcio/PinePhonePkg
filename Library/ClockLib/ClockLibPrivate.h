#ifndef __CLOCK_LIB_PRIVATE_H__
#define __CLOCK_LIB_PRIVATE_H__

static const clock_t _clock_uart[] =  {
	/* UART A */ { CLK_RST_CONTROLLER_RST_DEVICES_L, CLK_RST_CONTROLLER_CLK_OUT_ENB_L, CLK_RST_CONTROLLER_CLK_SOURCE_UARTA, 6 , 0, 0 },
	/* UART B */ { CLK_RST_CONTROLLER_RST_DEVICES_L, CLK_RST_CONTROLLER_CLK_OUT_ENB_L, CLK_RST_CONTROLLER_CLK_SOURCE_UARTB, 7 , 0, 0 },
	/* UART C */ { CLK_RST_CONTROLLER_RST_DEVICES_H, CLK_RST_CONTROLLER_CLK_OUT_ENB_H, CLK_RST_CONTROLLER_CLK_SOURCE_UARTC, 23, 0, 0 },
	/* UART D */ { CLK_RST_CONTROLLER_RST_DEVICES_U, CLK_RST_CONTROLLER_CLK_OUT_ENB_U, CLK_RST_CONTROLLER_CLK_SOURCE_UARTD, 1 , 0, 0 },
	/* UART E */ { CLK_RST_CONTROLLER_RST_DEVICES_U, CLK_RST_CONTROLLER_CLK_OUT_ENB_U, 0, 2, 0, 0 }
};

static const clock_t _clock_i2c[] = {
	/* I2C1 */ { CLK_RST_CONTROLLER_RST_DEVICES_L, CLK_RST_CONTROLLER_CLK_OUT_ENB_L, CLK_RST_CONTROLLER_CLK_SOURCE_I2C1, 12, 6, 0 },
	/* I2C2 */ { CLK_RST_CONTROLLER_RST_DEVICES_H, CLK_RST_CONTROLLER_CLK_OUT_ENB_H, CLK_RST_CONTROLLER_CLK_SOURCE_I2C2, 22, 6, 0 },
	/* I2C3 */ { CLK_RST_CONTROLLER_RST_DEVICES_U, CLK_RST_CONTROLLER_CLK_OUT_ENB_U, CLK_RST_CONTROLLER_CLK_SOURCE_I2C3, 3,  6, 0 },
	/* I2C4 */ { CLK_RST_CONTROLLER_RST_DEVICES_V, CLK_RST_CONTROLLER_CLK_OUT_ENB_V, CLK_RST_CONTROLLER_CLK_SOURCE_I2C4, 7,  6, 0 },
	/* I2C5 */ { CLK_RST_CONTROLLER_RST_DEVICES_H, CLK_RST_CONTROLLER_CLK_OUT_ENB_H, CLK_RST_CONTROLLER_CLK_SOURCE_I2C5, 15, 6, 0 },
	/* I2C6 */ { CLK_RST_CONTROLLER_RST_DEVICES_X, CLK_RST_CONTROLLER_CLK_OUT_ENB_X, CLK_RST_CONTROLLER_CLK_SOURCE_I2C6, 6 , 6, 0 },
};

static clock_t _clock_se = { CLK_RST_CONTROLLER_RST_DEVICES_V, CLK_RST_CONTROLLER_CLK_OUT_ENB_V, CLK_RST_CONTROLLER_CLK_SOURCE_SE, 31, 0, 0 };

static clock_t _clock_host1x = { CLK_RST_CONTROLLER_RST_DEVICES_L, CLK_RST_CONTROLLER_CLK_OUT_ENB_L, CLK_RST_CONTROLLER_CLK_SOURCE_HOST1X, 28, 4, 3 };
static clock_t _clock_tsec = { CLK_RST_CONTROLLER_RST_DEVICES_U, CLK_RST_CONTROLLER_CLK_OUT_ENB_U, CLK_RST_CONTROLLER_CLK_SOURCE_TSEC, 19, 0, 2 };
static clock_t _clock_sor_safe = { CLK_RST_CONTROLLER_RST_DEVICES_Y, CLK_RST_CONTROLLER_CLK_OUT_ENB_Y, 0, 30, 0, 0 };
static clock_t _clock_sor0 = { CLK_RST_CONTROLLER_RST_DEVICES_X, CLK_RST_CONTROLLER_CLK_OUT_ENB_X, 0, 22, 0, 0 }; //no CLK_RST_CONTROLLER_CLK_SOURCE_SOR0 on this one ?
static clock_t _clock_sor1 = { CLK_RST_CONTROLLER_RST_DEVICES_X, CLK_RST_CONTROLLER_CLK_OUT_ENB_X, CLK_RST_CONTROLLER_CLK_SOURCE_SOR1, 23, 0, 2 };
static clock_t _clock_kfuse = { CLK_RST_CONTROLLER_RST_DEVICES_H, CLK_RST_CONTROLLER_CLK_OUT_ENB_H, 0, 8, 0, 0 };

static clock_t _clock_cl_dvfs = { CLK_RST_CONTROLLER_RST_DEVICES_W, CLK_RST_CONTROLLER_CLK_OUT_ENB_W, 0, 27, 0, 0 };
static clock_t _clock_coresight = { CLK_RST_CONTROLLER_RST_DEVICES_U, CLK_RST_CONTROLLER_CLK_OUT_ENB_U, CLK_RST_CONTROLLER_CLK_SOURCE_CSITE, 9, 0, 4};

#endif