#include "lib/LCD/st7735.h"
#include "lib/Config/DEV_Config.h"
#include <stdlib.h>		
#include <stdio.h>
#include "lib/icm20948/icm20948.h"
#include "lib/arducam/arducam.h"

uint8_t image[96*96*2];
IMU_EN_SENSOR_TYPE result;
IMU_ST_ANGLES_DATA Angles,  Gyro,  Acce, Magn;

struct arducam_config config;

//int main(void)
void setup()
{
//	stdio_uart_init();
	sleep_ms(1000);
	ST7735_Init();

	config.sccb = i2c1;
	config.sccb_mode = I2C_MODE_16_8;
	config.sensor_address = 0x24;
	config.pin_sioc = PIN_CAM_SIOC;
	config.pin_siod = PIN_CAM_SIOD;
	config.power_en = PIN_POWER_EN;
	config.pin_resetb = PIN_CAM_RESETB;
	config.pin_xclk = PIN_CAM_XCLK;
	config.pin_vsync = PIN_CAM_VSYNC;
	config.pin_y2_pio_base = PIN_CAM_Y2_PIO_BASE;
	config.pio = pio0;
	config.pio_sm = 0;
	config.dma_channel = 0;
	arducam_init(&config);
	ST7735_FillScreen(ST7735_BLUE);
}  
void loop()
	{
		arducam_capture_frame(&config, image);
		ST7735_DrawImage(0,0, 96, 96,image);
		ST7735_WriteString(101, 30, "85%", Font_16x26, ST7735_GREEN, ST7735_BLUE);   
	}
    
