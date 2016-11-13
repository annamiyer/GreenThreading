//
//

#include "priority_queue.h"

#define PQ_PRIORITY_LEVELS 5
#define PQ_LINES 4
#define PQ_LINE_CAPACITY 50



//keeps separate queues based on priority.
struct Priority_Queue
{
    Queue *index; //Queue array
    size_t element_count;
    enum priority_t priority_levels;
};

//Internal methods
static void deallocate_queues(Priority_Queue *pq)
{
    for(enum priority_t i = 0; i < pq->priority_levels; i++)
        q_free(pq->index[i]);
}


//Public methods
//Allocate all data structures according to given values
Priority_Queue *pq_allocate(enum priority_t priority_levels, size_t lines_per_priority_level,
                                    size_t line_capacity)
{
    if(priority_levels < 2 || lines_per_priority_level < 2 || line_capacity < 1) {
        return NULL;
    }


    //Allocate queue and index
    Priority_Queue *pq = malloc(sizeof(Priority_Queue) + sizeof Queue* priority_levels);
    if (pq == NULL) {
        return NULL;
    }

    //Point the index to the right location
    pq->index = Queue*(pq + 1);

    //Create the queues
    for(enum priority_t i = 0; i < priority_levels; ++i){
        pq->index[i] = pq_allocate(lines_per_priority_level, line_capacity);

        //Handle error
        if(pq->index[i] == NULL){

            //set successfully created queues so deallocation will work
            pq->priority_levels = i;
            deallocate_queues(pq);
            free(pq);

            return NULL;
        }
    }

    //Set values
    pq->element_count = 0;
    pq->priority_levels = priority_levels;

    return pq;
}



Priority_Queue *pq_allocate(void)
{
    return pq_allocate(PQ_PRIORITY_LEVELS, PQ_LINES, PQ_LINE_CAPACITY);
}



void pq_free(Priority_Queue *pq)
{
    if(pq == NULL) {
        return;
    }

    deallocate_queues(pq);
    free(pq);
}



//Will break if priority is not in range
int pq_insert(Priority_Queue *pq, void *content, enum priority_t priority)
{
    //Try to insert at the correct queue
    if(qu_enqueue(pq->index[priority], content) == QU_ERROR) {
        return PQ_ERROR;
    }


    ++pq->element_count;
    return PQ_SUCCESS;
}



int pq_insert_default(Priority_Queue *pq, void *content)
{
    return pq_insert(pq, content, pq->priority_levels / 2);
}



void *pq_dequeue_highest(Priority_Queue *pq)
{
    if(pq->element_count == 0)
        return NULL;

    //Find the first queue with element count > 0
    enum priority_t i;
    for(i = pq->priority_levels - 1; qu_get_count(pq->index[i]) == 0; i--){}


    --pq->element_count;
    return qu_dequeue(pq->index[i]);
}



void *pq_dequeue_lowest(Priority_Queue *pq)
{
    if(pq->element_count == 0) {
        return NULL;
    }


    //Find the first queue with element count > 0
    enum priority_t i;
    for(i = 0; qu_get_count(pq->index[i]) == 0; i++) {}

    --pq->element_count;
    return qu_dequeue(pq->index[i]);
}



void pq_shrink(Priority_Queue *pq)
{
    for(enum priority_t i = 0; i < pq->priority_levels; i++) {
        qu_shrink_to_fit(pq->index[i]);
    }

}