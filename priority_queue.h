#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdlib.h>
#include <stdint.h>
#include "queue.h"

#define PQ_SUCCESS 0
#define PQ_ERROR 1

typedef enum {VERY_LOW, LOW, NORMAL, HIGH, VERY_HIGH} priority_t;

typedef struct queue_t Priority_Queue;



Priority_Queue *pq_allocate_custom( enum priority_t priority_levels,
                                    size_t levelLines,
                                    size_t line_capacity);
Priority_Queue *pq_allocate(void);
void pq_free(Priority_Queue *pq);
int pq_insert(Priority_Queue *pq, void *content, enum priority_t priority);
int pq_insert_default(Priority_Queue *pq, void *content);
void *pq_dequeue_highest(Priority_Queue *pq);
void *pq_dequeue_lowest(Priority_Queue *pq);
void pq_shrink(Priority_Queue *pq);

#endif

