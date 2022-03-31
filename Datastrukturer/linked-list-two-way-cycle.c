#include <stdio.h>
#include <stdlib.h>

int* create(int value);
void add(int *start, int value);
void addToIndex(int *start, int value, int index);
void removeTop(int *start);
void removeAtIndex(int *start, int index);
int count(int *start);
int get(int *start, int index);
int* toArray(int *start, int length);

int main()
{
    printf("Hello world!\n");
    int *list = create(13), *array;

    printf("adding to list\n");
    for(int i = 0; i < 15; i++){
        add(list, 10*i);
    }

    removeTop(list);
    printf("getting array from list\n");
    printList(list, count(list));

    printf("removing top\n");
    removeTop(list);

    printf("getting array from list\n");
    printList(list, count(list));

    printf("adding to index 0\n");
    addToIndex(list, 99, 0);

    printf("getting array from list\n");
    printList(list, count(list));

    printf("removing at index 0\n");
    removeAtIndex(list, 0);

    printf("getting array from list\n");
    printList(list, count(list));

    printf("removing at index 0\n");
    array = toArray(list, count(list));

    printf("getting array from list\n");
    print(array, count(list));

    return 0;
}

// linked list one way
int* create(int value){
    int *start = calloc(3, sizeof(int));
    start++;
    *(start) = value;
    *(start + 1) = start;
    *(start - 1) = start;
    return start;
}

void add(int *start, int value){
    int *newItem = create(value);

    *(newItem+1) = start;
    int *currentItem = start;

    while(*(currentItem + 1) != start){
        currentItem++;
        currentItem = *currentItem;
    }

    *(newItem - 1) = currentItem;
    *(currentItem + 1) = newItem;
    *(start-1) = newItem;
}

void addToIndex(int *start, int value, int index){
    int *newItem = create(value);

    int *currentItem = start;
    if(index == 0){
        int temp = *start;
        *start = *newItem;
        *newItem = temp;
        *(newItem-1) = start;
        *(newItem+1) = *(start+1);
        *(start+1) = newItem;
        return;
    }

    for(int i = 0; i < index-1 && *(currentItem+1) != start; i++){
        currentItem++;
        currentItem = *currentItem;
    }

    *(newItem + 1 ) = *(currentItem +  1);
    *(newItem - 1 ) = currentItem;

    int *nextItem = *(currentItem + 1);

    *(nextItem - 1) = newItem;
    *(currentItem + 1) = newItem;
}

void removeTop(int *start){
    int *currentItem = start;

    while(*(currentItem + 1) != start){
        currentItem++;
        currentItem = *currentItem;
    }

    if(*(currentItem - 1) != 0){
        int *lastItem = *(currentItem - 1);
        *(lastItem + 1) = *(currentItem + 1);
        free(currentItem-1);
    }
}

void removeAtIndex(int *start, int index){
    int *currentItem = start;

    if(index == 0){
        int *next = *(currentItem + 1);
        int temp = *next;
        *next = *currentItem;
        *currentItem = temp;
        index++;
    }

    for(int i = 0; i < index; i++){
        currentItem++;
        if(*currentItem == start){
            return;
        }
        currentItem = *currentItem;
    }
    int *lastItem = *(currentItem - 1);
    int *nextItem = *(currentItem + 1);
    *(lastItem + 1) = nextItem;
    *(nextItem - 1) = lastItem;

    free(currentItem - 1);
}

int count(int *start){
    int *currentItem = start;
    int count = 1;

    while(*(currentItem + 1) != start){
        currentItem++;
        currentItem = *currentItem;
        count++;
    }

    return count;
}

int get(int *start, int index){

    int *currentItem = start;

    for(int i = 0; i < index; i++){
        currentItem++;
        currentItem = *currentItem;
    }

    return *currentItem;
}

int* toArray(int *start, int length){
    int *array = calloc(length, sizeof(int));

    int *currentItem = start;

    for(int i = 0; i < length; i++){
        *(array+i) = *currentItem;
        currentItem++;
        if(*currentItem == start){
            return array;
        }
        currentItem = *currentItem;
    }

    return array;

}

void printList(int *start, int length){
    int *currentItem = start;

    printf("%d <-%d -> %d \n",*(currentItem-1), *currentItem, *(currentItem+1));

    for(int i = 1; i < length; i++){
        currentItem++;
        currentItem = *currentItem;
        printf("%d <-%d -> %d \n",*(currentItem-1), *currentItem, *(currentItem+1));
    }
}

void print(int *table, int lenght){
    for(int i = 0; i < lenght; i++){
        printf("%d ", *(table+i));
    }
    printf("\n");
}
