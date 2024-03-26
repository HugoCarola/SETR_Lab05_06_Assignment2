/**
 * \file:   sensor.c
 * \author: Francisco Heleno <francisco.c.heleno@ua.pt> and Hugo Carola <hugocarola@ua.pt>
 *
 * \date 25, March, 2024
 * \brief Implementation of the Doubly Linked List (DLL) module.
 * 
 */

#include "sensor.h"



static unsigned char rx_BUFFER[MAX_STRING_SIZE];   // buffer to store the received characters
static uint8_t rx_index;             // iondex of the next char in buffer
static bool FRAME_IN_PROGRESS;      // Flag indicating ongoing frame reception

sensor_data data = {0,0,400};


/**
 * @brief Inserts a new element into the DLL.
 * @param dll Pointer to the DLL structure.
 * @param key Key of the new element.
 * @param data Data of the new element.
 * @return 0 on success, -1 on failure.
 */
int CMD_DATA(uint8_t tx)
{
	if(!FRAME_IN_PROGRESS){
        
        if (tx == FRAME_START){
            FRAME_IN_PROGRESS = true;
            rx_index = 0;
        }
    }
    else{

        if (tx == FRAME_END)
        {
            /* verify checksum */
            uint8_t rx_CS = rx_BUFFER[rx_index - 1];
            uint8_t calc_CS = calc_checksum(rx_BUFFER, rx_index-2) ;
        
            if (rx_CS == calc_CS)
            {
                command_t cmd;
              
            }
            
        
        }
           
    }

    return 0;
}


/**
 * @brief Selects the measurement we want to see.
 * @param cmd Comand inputed by user in current frame .
 * @return the value of the desired sensor.
 */


command_t Single_measure_Select(uint8_t cmd){

  switch (cmd) {
                case 'H':
                    return CMD_HUMIDITY;
                break;
                
                case 'T':
                    return CMD_TEMPERATURE;    
                break;
                
                case 'C':
                    return CMD_AIRQ;    
                break;
                default:
                    break;
            }
}

/**
 * @brief Calculates the checksum.
 * @param data Pointer to the sensor_data structure.
 * @param size size of the current frame.
 * @return Value of the calcuted checksum.
 */
unsigned char calc_checksum(uint8_t *data, uint8_t size){
    
    uint8_t checksum = 0;

    for (int i = 0; i<size; i++){
        checksum+=data[i];
    }
    return checksum;
}