
/* Definitions from my side for the sensor TCS3430 */
# define I2C_Slave_Address 0x39   //Slave adrress for TCS3430
// Color Thresholds min & Max 
// Black color 
# define X_min_black 0x0000
# define X_max_black 0x0100
# define Y_min_black 0x0000
# define Y_max_black 0x0100
# define Z_min_black 0x0000
# define Z_max_black 0x0100

// White Color 
# define X_min_white 0x0609
# define X_max_white 0x0799
# define Y_min_white 0x0609
# define Y_max_white 0x0799
# define Z_min_white 0x0205
# define Z_max_white 0x0365

// Red Color 
# define X_min_red 0x018C
# define X_max_red 0x022C
# define Y_min_red 0x00A4
# define Y_max_red 0x0144
# define Z_min_red 0x0000
# define Z_max_red 0x0040

// Green Color 
# define X_min_green 0x02AB
# define X_max_green 0x034B
# define Y_min_green 0x0496
# define Y_max_green 0x0536
# define Z_min_green 0x001A
# define Z_max_green 0x0100

// Blue Color 
# define X_min_blue 0x02FE
# define X_max_blue 0x039E
# define Y_min_blue 0x02FE
# define Y_max_blue 0x0427
# define Z_min_blue 0x0287
# define Z_max_blue 0x0327

#define NO_OF_BYTES		8
#define BUFFER_SIZE     2






/* [] END OF FILE */
