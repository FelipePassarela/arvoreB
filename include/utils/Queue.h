// Felipe dos Santos Passarela - 2023100256

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue Queue;

Queue *Queue_create(int capacity, size_t dataSize);
void Queue_destroy(Queue *queue);
bool Queue_enqueue(Queue* queue, const void* data);
bool Queue_dequeue(Queue *queue, void *outData);
bool Queue_isEmpty(Queue *queue);
bool Queue_isFull(Queue *queue);
int Queue_getCount(Queue *queue);

#endif // QUEUE_H