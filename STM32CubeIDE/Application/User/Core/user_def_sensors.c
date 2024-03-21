/* SENSORS includes ----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "hts221_reg.h"

#include "user_def_sensors.h"
#include "stdlib.h"


/* SENSORS define ------------------------------------------------------------*/
#define SENSOR_BUS hi2c1
#define BOOT_TIME 5
#define TX_BUF_DIM 1000

/* SENSORS variables ---------------------------------------------------------*/
static uint8_t whoamI, rst;
static uint8_t tx_buffer[TX_BUF_DIM];

stmdev_ctx_t dev_ctx_hts221;
stmdev_ctx_t dev_ctx_lps22hh;
lin_t lin_hum;
lin_t lin_temp;

static int16_t data_raw_humidity;
static int16_t data_raw_temperature;
static uint32_t data_raw_pressure;
const char *compassDirections[] = { "N", "NNE", "NE", "ENE", "E", "ESE", "SE",
		"SSE", "S", "SSO", "SO", "OSO", "O", "ONO", "NO", "NNO" };

float humidity_perc;
float temperature_degC;
float pressure_hPa;
float windspeed_kph;
uint8_t wind_direction;
double rainfall_mmh;

float log_humidity[100];
float log_temperature[100];
float log_pressure[100];
float log_windspeed[100];
uint8_t log_wind_direction[100];
double log_rainfall[100];

int index_HT = 0;
int index_Pr = 0;
int index_WS = 0;
int index_WD = 0;
int index_Rf = 0;

/* SENSORS functions ---------------------------------------------------------*/
//SENSORS GEN
void tx_com(uint8_t *tx_buffer, uint16_t len) {
	HAL_UART_Transmit(&huart1, tx_buffer, len, 1000);
}

void platform_delay(uint32_t ms) {
	HAL_Delay(ms);
}

//SENSOR hts221
void SENSOR_hts221_Init(void) {
	dev_ctx_hts221.write_reg = hts221_write;
	dev_ctx_hts221.read_reg = hts221_read;
	dev_ctx_hts221.handle = & SENSOR_BUS;
	/* Check device ID */
	whoamI = 0;
	int result = hts221_device_id_get(&dev_ctx_hts221, &whoamI);

	if (result == 0) {
		printf("WHO_AM_I: %d\r\n", whoamI);
	} else {
		printf("Error reading WHO_AM_I register\r\n");
	}

	if (whoamI != HTS221_ID)
		while (1)
			; /*manage here device not found */

	/* Read humidity calibration coefficient */
	hts221_hum_adc_point_0_get(&dev_ctx_hts221, &lin_hum.x0);
	hts221_hum_rh_point_0_get(&dev_ctx_hts221, &lin_hum.y0);
	hts221_hum_adc_point_1_get(&dev_ctx_hts221, &lin_hum.x1);
	hts221_hum_rh_point_1_get(&dev_ctx_hts221, &lin_hum.y1);

	/* Read temperature calibration coefficient */
	hts221_temp_adc_point_0_get(&dev_ctx_hts221, &lin_temp.x0);
	hts221_temp_deg_point_0_get(&dev_ctx_hts221, &lin_temp.y0);
	hts221_temp_adc_point_1_get(&dev_ctx_hts221, &lin_temp.x1);
	hts221_temp_deg_point_1_get(&dev_ctx_hts221, &lin_temp.y1);

	/* Enable Block Data Update */
	hts221_block_data_update_set(&dev_ctx_hts221, PROPERTY_ENABLE);

	/* Set Output Data Rate */
	hts221_data_rate_set(&dev_ctx_hts221, HTS221_ONE_SHOT);

	hts221_drdy_on_int_set(&dev_ctx_hts221, PROPERTY_ENABLE);

	/* Device power on */
	hts221_power_on_set(&dev_ctx_hts221, PROPERTY_ENABLE);
}

int32_t hts221_write(void *handle, uint8_t reg, const uint8_t *bufp,
		uint16_t len) {
	reg |= 0x80;
	HAL_I2C_Mem_Write(handle, HTS221_I2C_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT,
			(uint8_t*) bufp, len, 1000);
	return 0;
}

int32_t hts221_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len) {
	/* Read multiple command */
	reg |= 0x80;
	HAL_I2C_Mem_Read(handle, HTS221_I2C_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT,
			bufp, len, 1000);
	return 0;
}

float linear_interpolation(lin_t *lin, int16_t x) {
	return ((lin->y1 - lin->y0) * x
			+ ((lin->x1 * lin->y0) - (lin->x0 * lin->y1))) / (lin->x1 - lin->x0);
}

void SENSOR_hts221_Start_Conversion(void) {
	hts221_one_shoot_trigger_set(&dev_ctx_hts221, PROPERTY_ENABLE);
}

void SENSOR_hts221_Read_Data(void) {
	/* Read humidity data */
	memset(&data_raw_humidity, 0x00, sizeof(int16_t));
	hts221_humidity_raw_get(&dev_ctx_hts221, &data_raw_humidity);
	humidity_perc = linear_interpolation(&lin_hum, data_raw_humidity);

	if (humidity_perc < 0) {
		humidity_perc = 0;
	}
	if (humidity_perc > 100) {
		humidity_perc = 100;
	}
	//sprintf((char*) tx_buffer, "Humidity [%%]: %3.2f\r\n", humidity_perc);
	//tx_com(tx_buffer, strlen((char const*) tx_buffer));

	/* Read temperature data */
	memset(&data_raw_temperature, 0x00, sizeof(int16_t));
	hts221_temperature_raw_get(&dev_ctx_hts221, &data_raw_temperature);
	temperature_degC = linear_interpolation(&lin_temp, data_raw_temperature);
	//sprintf((char*) tx_buffer, "Temperature [degC]: %6.2f\r\n",
	//		temperature_degC);
	tx_com(tx_buffer, strlen((char const*) tx_buffer));
}
float SENSOR_hts221_Data_temp(void)
{
	return temperature_degC;
}
float SENSOR_hts221_Data_hum(void)
{
	return humidity_perc;
}

void SENSOR_hts221_Add_Data(void) {
	log_temperature[index_HT] = temperature_degC;
	log_humidity[index_HT] = humidity_perc;
	index_HT++;
}


//SENSOR Wind Speed
float calculateWindSpeed(uint16_t switchClosures) {
	// Conversion factor: 1.492 mph corresponds to 1 switch closure per second
	float countsPerSecond = (float) switchClosures / 5.0;
	// Conversion factor: 1 mph = 1.60934 kph
	float windSpeedKph = countsPerSecond * 1.492 * 1.60934;

	return windSpeedKph;
}




