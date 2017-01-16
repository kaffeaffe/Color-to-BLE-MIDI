/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This is source code for the PSoC 4 BLE MIDI for iOS/Mac example project.
*
* Note:
*
* Owners:
*  KRIS@CYPRESS.COM
*
* Related Document:
*
* Hardware Dependency:
*  1. PSoC 4 BLE device
*  2. CY8CKIT-042 BLE Pioneer Kit
*
* Code Tested With:
*  1. PSoC Creator 3.1 CP1
*  2. ARM CM3-GCC
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <BLE_Interface.h>
#include <Configuration.h>
#include <Init.h>
#include <Logger.h>
#include <MIDI.h>
#include <Project.h>
#include <UI.h>

#include <I2Cinit.h>
#include <I2C_1_I2C.h>
#include <stdio.h>

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
// This is function declaration 

void write_function(void);
char color_map(uint16 x, uint16 y, uint16 z);
volatile char color = 'U';   // Output color from sensor

int main()
{
    uint8 status;
    uint8 readbuffer[8];   // All colors starting from Z Y IR1 X data
    volatile uint16 x, y, z; 
   
    status = InitializeSystem();
    
    if(status == 0)
    {
       CYASSERT(0);    /* Something went wrong with BLE initialization, check */
    }
    
    write_function();

    while(1)
    {
        
        uint8 I2CreadBuffer[0x01] = {0x94}; //Location from which z data is to be read 
     
        uint16 uiChangeStatus;
        
        BLE_Run();
        
        I2C_1_I2CMasterWriteBuf(I2C_Slave_Address,(uint8 *) I2CreadBuffer, sizeof(I2CreadBuffer), I2C_1_I2C_MODE_COMPLETE_XFER); 
        
        while(!(I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)); //Wait till the master completes writing
        I2C_1_I2CMasterClearStatus(); //Clear I2C master status
        
         I2C_1_I2CMasterReadBuf(I2C_Slave_Address,(uint8 *) readbuffer, sizeof(readbuffer), I2C_1_I2C_MODE_COMPLETE_XFER);
       
       
        while(!(I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT)); //Wait till the master completes reading
        I2C_1_I2CMasterClearStatus(); //Clear I2C master status
        
        z = readbuffer[0] | (readbuffer[1] << 8) ;
        y = readbuffer[2] | (readbuffer[3] << 8) ;
        x = readbuffer[6] | (readbuffer[7] << 8) ;
       
         color = color_map(x,y,z);
        
        uiChangeStatus = UIInput_Run();
        
        Midi_Run(uiChangeStatus);
        
        UIOutput_Run();  
        
    
        if(cyBle_pendingFlashWrite != 0u)
        {
            /* Store bounding data to flash only when all debug information has been sent */
            CyBle_StoreBondingData(0u);
        }  
            
         
        
        
    }
}


void write_function(void)
{
       static  uint8 buffer[BUFFER_SIZE];
        
         /* Turn off sensor */
     buffer[0] = 0x80;   // Address of Enable 
     buffer[1] = 0x00;   // Pon =0  & Aeon = 0 to turn off the sensor and ALS Enable 
   
    
    I2C_1_I2CMasterWriteBuf(I2C_Slave_Address,(uint8 *)buffer, BUFFER_SIZE, I2C_1_I2C_MODE_COMPLETE_XFER); 
    while(!(I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)); //Wait till the master completes writing
    I2C_1_I2CMasterClearStatus(); //Clear I2C master status
    
    CyDelay(5);
    
    //Set ALS integration time
    buffer[0] = 0x81;   // Address of ATIME register 
    buffer[1] = 0x40;   // Ensures full ALS range (0x40 -->  181ms, 65535 max value)
    
    I2C_1_I2CMasterWriteBuf(I2C_Slave_Address,(uint8 *)buffer, BUFFER_SIZE, I2C_1_I2C_MODE_COMPLETE_XFER); 
    while(!(I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)); //Wait till the master completes writing
    I2C_1_I2CMasterClearStatus(); //Clear I2C master status
    
    CyDelay(5);
    
    
    //Set ADC gain
    buffer[0] = 0x90;   // Address of CFG1 Register
    buffer[1] = 0x03;   // Max gain (64x)
    
    I2C_1_I2CMasterWriteBuf(I2C_Slave_Address,(uint8 *)buffer, BUFFER_SIZE, I2C_1_I2C_MODE_COMPLETE_XFER); 
    while(!(I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)); //Wait till the master completes writing
    I2C_1_I2CMasterClearStatus(); //Clear I2C master status
    
    CyDelay(5);
    
    //Turn power on but wait with enabling ALS
    buffer[0] = 0x80;   // Address of ENABLE register 
    buffer[1] = 0x01;   // PON on , ALS off
    
    I2C_1_I2CMasterWriteBuf(I2C_Slave_Address,(uint8 *)buffer, BUFFER_SIZE, I2C_1_I2C_MODE_COMPLETE_XFER); 
    while(!(I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)); //Wait till the master completes writing
    I2C_1_I2CMasterClearStatus(); //Clear I2C master status
    CyDelay(5);
    
    //Enable ALS
    buffer[0] = 0x80;   // Address of ENABLE register  
    buffer[1] = 0x03;   //PON, ALS on
    
    I2C_1_I2CMasterWriteBuf(I2C_Slave_Address,(uint8 *)buffer, BUFFER_SIZE, I2C_1_I2C_MODE_COMPLETE_XFER); 
    while(!(I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)); //Wait till the master completes writing
    I2C_1_I2CMasterClearStatus(); //Clear I2C master status
    CyDelay(5);
    

}

char color_map(uint16 x, uint16 y, uint16 z)
{
    if (((X_min_black <= x) && (x <= X_max_black))&&((Y_min_black <= y) && (y <= Y_max_black))&&((Z_min_black <= z) && (z <= Z_max_black)))
    {
        return 'B';
    }
    else if (((X_min_white <= x) && (x <= X_max_white))&&((Y_min_white <= y) && (y <= Y_max_white))&&((Z_min_white <= z) && (z <= Z_max_white)))
    {
        return 'W';    // White Color 
    }
    else if (((X_min_red <= x) && (x <= X_max_red))&&((Y_min_red <= y) && (y <= Y_max_red))&&((Z_min_red <= z) && (z <= Z_max_red)))
    {
        return 'R';   // Red Color 
    }
    else if (((X_min_green <= x) && (x <= X_max_green))&&((Y_min_green <= y) && (y <= Y_max_green))&&((Z_min_green <= z) && (z <= Z_max_green)))
    {
        return 'G';    // Green Color 
    }
    else if (((X_min_blue <= x) && (x <= X_max_blue))&&((Y_min_blue <= y) && (y <= Y_max_blue))&&((Z_min_blue <= z) && (z <= Z_max_blue)))
    {
        return 'b';   // Blue Color 
    }
    else return 'U';   // unknown color 
}



/* [] END OF FILE */
