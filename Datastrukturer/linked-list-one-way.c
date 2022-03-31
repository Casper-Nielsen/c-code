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
    int *start = malloc(2 * sizeof(int));
    *start = value;
    *(start+1) = 0;
    return start;
}

void add(int *start, int value){
    int *newItem = create(value);

    int *currentItem = start;

    while(*(currentItem+1) != 0){
        currentItem++;
        currentItem = *currentItem;
    }

    *(currentItem+1) = newItem;
}

void addToIndex(int *start, int value, int index){
    int *newItem = create(value);

    int *currentItem = start;
    if(index == 0){
        int temp = *start;
        *start = *newItem;
        *newItem = temp;

        *(newItem+1) = *(start+1);
        *(start+1) = newItem;
        return;
    }

    for(int i = 0; i < index-1 && *(currentItem+1) != 0; i++){
        currentItem++;
        currentItem = *currentItem;
    }

    *(newItem+1) = *(currentItem+1);

    *(currentItem+1) = newItem;
}

void removeTop(int *start){
    int *currentItem = start, *lastItem = 0;

    while(*(currentItem + 1) != 0){
        lastItem = currentItem;
        currentItem++;
        currentItem = *currentItem;
    }

    if(lastItem != 0){
        *(lastItem+1) = 0;
        free(currentItem);
    }
}

void removeAtIndex(int *start, int index){
    int *currentItem = start, *lastItem = 0;

    if(index == 0){
        int *next = *(currentItem+1);
        int temp = *next;
        *next = *currentItem;
        *currentItem = temp;
        index++;
    }

    for(int i = 0; i < index; i++){
        lastItem = currentItem;
        currentItem++;
        if(*currentItem == 0){
            return;
        }

        currentItem = *currentItem;
    }

    *(lastItem+1) = *(currentItem+1);

    free(currentItem);
}

int count(int *start){
    int *currentItem = start;
    int count = 1;

    while(*(currentItem + 1) != 0){
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
        if(*currentItem == 0){
            return array;
        }
        currentItem = *currentItem;
    }

    return array;

}

void printList(int *start, int length){
    int *currentItem = start;

    printf("%d ", *currentItem);

    for(int i = 1; i < length; i++){
        currentItem++;
        currentItem = *currentItem;
        printf("%d ", *currentItem);
    }
    printf("\n");
}

void print(int *table, int lenght){
    for(int i = 0; i < lenght; i++){
        printf("%d ", *(table+i));
    }
    printf("\n");
}
