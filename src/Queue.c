#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

struct Queue
{
    int capacity;
    int front;
    int rear;
    int count;
    void *data;
    size_t dataSize;
};

static bool Queue_resize(Queue *queue, int newCapacity);

Queue *Queue_create(int initialCapacity, size_t dataSize)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    queue->capacity = initialCapacity;
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
    queue->dataSize = dataSize;
    queue->data = malloc(dataSize * initialCapacity);

    return queue;
}

void Queue_destroy(Queue *queue)
{
    if (!queue)
        return;
    free(queue->data);
    free(queue);
}

bool Queue_isEmpty(Queue *queue)
{
    return (queue->count == 0);
}

bool Queue_isFull(Queue *queue)
{
    return (queue->count == queue->capacity);
}

int Queue_getCount(Queue* queue)
{
    return queue->count;
}

bool Queue_enqueue(Queue *queue, const void *data)
{
    if (Queue_isFull(queue))
    {
        if (!Queue_resize(queue, queue->capacity * 2))
            return false;
    }
    
    void *dest = (char *)queue->data + queue->rear * queue->dataSize;
    memcpy(dest, data, queue->dataSize);
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->count++;
    
    return true;
}

bool Queue_dequeue(Queue *queue, void *outData)
{
    if (Queue_isEmpty(queue))
        return false;
    
    void *source = (char *)queue->data + queue->front * queue->dataSize;
    memcpy(outData, source, queue->dataSize);
    queue->front = (queue->front + 1) % queue->capacity;
    queue->count--;
    
    return true;
}

bool Queue_resize(Queue *queue, int newCapacity)
{
    if (newCapacity < queue->count)
    {
        fprintf(stderr, "Error: new capacity is less than the current count in Queue\n");
        return false;
    }

    void *newData = malloc(newCapacity * queue->dataSize);
    if (!newData)
        return false;
        
    for (int i = 0; i < queue->count; i++)
    {
        void *src = (char *)queue->data + ((queue->front + i) % queue->capacity) * queue->dataSize;
        void *dest = (char *)newData + i * queue->dataSize;
        memcpy(dest, src, queue->dataSize);
    }
        
    free(queue->data);
    queue->data = newData;
    queue->capacity = newCapacity;
    queue->front = 0;
    queue->rear = queue->count;
    
    return true;
}