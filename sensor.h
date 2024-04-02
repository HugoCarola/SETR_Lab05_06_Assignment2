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
#define BUFFER_SIZE 20
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

typedef struct {
    uint8_t * const temp_cbuffer;
    int head;
    int tail;
    uint16_t maxlen;
    uint16_t count;
} circ_bbuf_T;

/**
 * @brief Inserts a new element into the DLL.
 * @param dll Pointer to the DLL structure.
 * @param key Key of the new element.
 * @param data Data of the new element.
 * @return 0 on success, -1 on failure.
 */

void Data_buff_Init(circ_bbuf_T *circ_buff, uint16_t max_elements)
{
    circ_buff->head = NULL;
    circ_buff->tail = NULL;
    circ_buff->maxlen = max_elements;
    circ_buff->count = 0;
}


int Data_buff_Insert(circ_bbuf_T *circ_buff, unsigned char *data)
{
    int next;

    next = circ_buff->head + 1;  // next is where head will point to after this write.
    if (next >= circ_buff->maxlen)
        next = 0;

    if (next == circ_buff->tail)  // if the head + 1 == tail, circular buffer is full
        return -1;

    circ_buff->temp_cbuffer[circ_buff->head] = data;  // Load data and then move
    circ_buff->head = next;             // head to next data offset.
    return 0;  // return success to indicate successful push.
}

typedef struct {
    char data[BUFFER_SIZE];
    int front;
    int rear;
} Rx_Buffer;

int reset(Rx_Buffer *buffer) {
    int i = buffer->front;
    // Procura pelo próximo EOF (end of frame)
    while (buffer->data[i] != '!') {
        i = (i + 1) % BUFFER_SIZE;
        // Se voltar para a posição inicial, significa que o EOF não foi encontrado
        if (i == buffer->front) {
            printf("Erro: EOF não encontrado no buffer.\n");
            return;
        }
    }
    // Define o front para a próxima posição após o EOF
    return buffer->front = (i + 1) % BUFFER_SIZE;
}

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