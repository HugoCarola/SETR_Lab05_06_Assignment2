/**
 * \file:   sensor.h
 * \author: Francisco Heleno <francisco.c.heleno@ua.pt> and Hugo Carola <hugocarola@ua.pt>
 *
 * \date 25, March, 2024
 * \brief Node and Dll datas structures, and function signatures.
 * 
 */

#ifndef SENSOR_H
#define SENSOR_H
#define MAX_STRING_SIZE 16 /**< Maximum number of elements in data string */
#define FRAME_START '#'
#define FRAME_END '!'

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef enum {
    CMD_ALL,
    CMD_TEMPERATURE,
    CMD_HUMIDITY,
    CMD_AIRQ,
}command_t;


typedef struct 
{
    char temperature[20];
    int temp_count;
    char humidity[20];
    int humi_count;
    char air_quality[20];
    int airq_count;
}sensor_data;


/**
 * @brief Inserts a new element into the DLL.
 * @return 0 on success, -1 on failure.
 */
int CMD_DATA(uint8_t tx);

/**
 * @brief Sorts the elements of the DLL in ascending or descending order based on the specified order.
 */
void CMD_List_Sort(bool order);

/**
 * @brief Resets the list.
 * @return 0 on success, -1 on failure.
 */
int CMD_Reset(void);

#endif // DLL_H