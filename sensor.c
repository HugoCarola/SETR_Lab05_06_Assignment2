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

data.temp_count = 0;
data.humi_count = 0;
data.airq_count = 0;


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
            uint8_t rx_CS[3]; //array to store the rx checksum characters 
            for (int i = 0; i < 3; i++){
                rx_CS[i] = rx_BUFFER[rx_index - 3 + i];
            }
            uint8_t calc_CS = calc_checksum(rx_BUFFER, rx_index-4);

            //conversion to ASCII (3 digits)
            char calc_CS_str[4];
            sprintf(calc_CS_str,"%03u", calc_CS);

            //Compare checksums
            bool CS_match = true;
            for (int i = 0; i < 3; i++){
                if (rx_CS[i] != calc_CS_str[i]){
                CS_match = false;
                }
            } 
            if (CS_match)
            {
                command_t cmd = select_option(rx_BUFFER[1]);

                switch (cmd){

                    case 'A':
                        break;
                    case 'P':

                        printf("Select sensor reading to show:/n");
                        command_t cmd_option = Single_measure_Select(rx_BUFFER[2]);

                        break;
                    case 'L':
                        break;
                    case 'R': 
                        break;    
                }
              
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


command_t Single_measure_Select(uint8_t cmd_option){

  switch (cmd_option) {
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
    return checksum % 256;   //performs modulo 256 operation
}