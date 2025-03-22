// Felipe dos Santos Passarela - 2023100256
// Fábio Henrique Pascoal - 2024102901
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

/**
* @brief Generic queue data structure
*
* A first-in, first-out (FIFO) data structure that can store elements
* of any data type.
*/
typedef struct Queue Queue;

/**
* @brief Creates a new queue with specified capacity and element size
*
* @param capacity The maximum number of elements the queue can hold
* @param dataSize The size in bytes of each element (e.g., sizeof(int))
* @return A pointer to the newly created Queue
*/
Queue *Queue_create(int capacity, size_t dataSize);

/**
* @brief Deallocates memory used by the queue
*
* @param queue The queue to destroy
*/
void Queue_destroy(Queue *queue);

/**
* @brief Adds an element to the back of the queue
*
* @param queue The queue to add the element to
* @param data Pointer to the data to enqueue
* @return true if the element was successfully added, false if the queue is full
*/
bool Queue_enqueue(Queue* queue, const void* data);

/**
* @brief Removes an element from the front of the queue
*
* @param queue The queue to remove the element from
* @param outData Pointer where the dequeued data will be stored
* @return true if an element was successfully removed, false if the queue is empty
*/
bool Queue_dequeue(Queue *queue, void *outData);

/**
* @brief Checks if the queue is empty
*
* @param queue The queue to check
* @return true if the queue is empty, false otherwise
*/
bool Queue_isEmpty(Queue *queue);

/**
* @brief Checks if the queue is full
*
* @param queue The queue to check
* @return true if the queue is full, false otherwise
*/
bool Queue_isFull(Queue *queue);

/**
* @brief Gets the current number of elements in the queue
*
* @param queue The queue to get the count from
* @return The number of elements currently in the queue
*/
int Queue_getCount(Queue *queue);

#endif // QUEUE_H