/**
 * \file:   sensor.h
 * \author: Francisco Heleno <francisco.c.heleno@ua.pt> and Hugo Carola <hugocarola@ua.pt>
 *
 * \date 25, March, 2024
 * \brief Node and Dll datas structures, and function signatures.
 * 
 */

#ifndef DLL_H
#define DLL_H
#define MAX_ELEM_SIZE 256 /**< Maximum size of element data */
#define MAX_ELEMENTS 64 /**< Maximum number of elements in the DLL */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Node structure for the Doubly Linked List (DLL).
 */
typedef struct Node{
    uint16_t key;       //usar para definir a hora da medida
    unsigned char data[MAX_ELEM_SIZE];      
    struct Node *prev;
    struct Node *next;
}Node;

/**
 * @brief Doubly Linked List (DLL) structure.
 */
typedef struct{
    Node nodes[MAX_ELEMENTS];
    Node *head;
    Node *tail;
    uint16_t max_elem;
    uint16_t count;
}DLL;

/**
 * @brief Initializes the DLL module.
 */
void MyDLLInit(DLL *dll, uint16_t max_elements);

/**
 * @brief Inserts a new element into the DLL.
 * @return 0 on success, -1 on failure.
 */
int MyDLLInsert(DLL *dll, uint16_t key, unsigned char *data);

/**
 * @brief Removes an element from the DLL.
 * @return 0 on success, -1 if the element with the specified key is not found.
 */
int MyDLLRemove(DLL *dll, uint16_t key);

/**
 * @brief Finds an element in the DLL by its key.
 * @return Pointer to the data of the element if found, NULL otherwise.
 */
unsigned char *MyDLLFind(DLL *dll, uint16_t key);

/**
 * @brief Finds the data of the next element in the DLL.
 * @return Pointer to the data of the next element if found, NULL otherwise.
 */
unsigned char *MyDLLFindNext(DLL *dll, uint16_t key);

/**
 * @brief Finds the data of the previous element in the DLL.
 * @return Pointer to the data of the previous element if found, NULL otherwise.
 */
unsigned char *MyDLLFindPrevious(DLL *dll, uint16_t key);

/**
 * @brief Sorts the elements of the DLL in ascending or descending order based on the specified order.
 */
void MyDLLSort(DLL *dll, bool order);

/**
 * @brief Prints the real time values of all elements.
 */
void Print_Real_time_DLL(DLL *dll);

/**
 * @brief Prints the real time values of all elements.
 */
void Print_Single_Measure_DLL(DLL *dll);

/**
 * @brief Resets the list.
 * @return 0 on success, -1 on failure.
 */
void MyDLLReset(DLL *dll);

#endif // DLL_H