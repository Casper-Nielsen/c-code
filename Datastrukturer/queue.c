#include <stdio.h>
#include <stdlib.h>
typedef struct Queue Queue, *pno;
struct Queue{
    int *array;
    int length;
    int high;
    int low;
};

Queue create();
int dequeue(Queue *queue);
void enqueue(Queue *queue, int value);
void sizeUp(Queue *queue);
void sizeDown(Queue *queue);

int main()
{
    printf("Hello world!\n");
    struct Queue queue = create();
    enqueue(&queue,1);
    enqueue(&queue,2);
    enqueue(&queue,3);
    enqueue(&queue,4);
    printf("dequeued: %d\n",dequeue(&queue));
    printf("dequeued: %d\n",dequeue(&queue));
    printf("dequeued: %d\n",dequeue(&queue));
    enqueue(&queue,5);
    enqueue(&queue,6);
    enqueue(&queue,7);
    printf("dequeued: %d\n",dequeue(&queue));
    enqueue(&queue,8);
    printf("dequeued: %d\n",dequeue(&queue));
    printf("dequeued: %d\n",dequeue(&queue));
    printf("dequeued: %d\n",dequeue(&queue));
    printf("dequeued: %d\n",dequeue(&queue));
    printf("dequeued: %d\n",dequeue(&queue));
    printf("dequeued: %d\n",dequeue(&queue));
    printf("dequeued: %d\n",dequeue(&queue));
    printf("queue size: %d start: %d end: %d\n",queue.length, queue.low, queue.high);
    return 0;
}

Queue create(){
    struct Queue queue;
    queue.array = calloc(1, sizeof(int));
    queue.length = 1;
    queue.high = 0;
    queue.low = 0;
    return queue;
}
int dequeue(Queue *queue){
    if(queue->low != queue->high){
        int value = *(queue->array+queue->low);
        queue->low++;
        if(queue->low == queue->length){
            queue->low = 0;
        }
        if(queue->low > queue-> high){
            if(queue->low-queue->high >= queue->length/4*3){
                sizeDown(queue);
            }
        }else{
            if(queue->high-queue->low <= queue->length/4){
                sizeDown(queue);
            }
        }
        return value;
    }
    return 0;
}
void enqueue(Queue *queue, int value){
    *(queue->array+queue->high) = value;
    queue->high++;
    if(queue->high == queue->length){
        queue->high = 0;
    }
    if(queue->high == queue->low){
        sizeUp(queue);
    }
}
void sizeUp(Queue *queue){
    int temp[queue->length], length = queue->length;
    for(int i = 0; i < length; i++){
        temp[i] = *(queue->array+queue->low);
        queue->low++;
        if(queue->low == length){
            queue->low = 0;
        }
    }
    queue->array = realloc(queue->array, (queue->length*2)*sizeof(int));
    for(int i = 0; i < length; i++){
        *(queue->array+i) = temp[i];
    }
    queue->low = 0;
    queue->high = length;
    queue->length = queue->length*2;
}
void sizeDown(Queue *queue){
    int temp[queue->length], length = queue->length, i;
    for(i = 0; queue->low != queue->high && i < length; i++){
        temp[i] = *(queue->array+queue->low);
        queue->low++;
        if(queue->low == length){
            queue->low = 0;
        }
    }
    queue->array = realloc(queue->array, (queue->length/2)*sizeof(int));
    for(int y = 0; y < length; y++){
        *(queue->array+y) = temp[y];
    }
    queue->low = 0;
    queue->high = i;
    queue->length = queue->length/2;
}
