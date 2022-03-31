#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <stdbool.h>
#include <unistd.h>


void swap (int *first, int *second);
void randomTable (int *array, int total);
void print (int *array, int lenght);
void invert (int *array, int lenght);

double selectionSort(int lenght);
double insertionSort(int lenght);
double mergeSort(int lenght);
double radixSort(int lenght);

int main(){
    int seed = time(0);
    int size = 100000;
    srand(seed);
    //printf("Selection sort: %f sec\n", selectionSort(size));
    //srand(seed);
    //printf("insertion sort: %f sec\n", insertionSort(size));
    //srand(seed);
    printf("merge sort: %f sec\n", mergeSort(size));
    //srand(seed);
    //printf("radix sort: %f sec\n", radixSort(size));
    return 0;
}

/// Selection sort
double selectionSort(int lenght){
    int array[lenght];
    randomTable(array, lenght);
    int *currentStart, *lowest;

    print(&array, lenght);

    mergeSortSort(&array,0,lenght-1);
    //invert(&array, lenght);

    clock_t begin = clock();

    for(int i = 0; i < lenght; i++){
        currentStart = array+i;
        lowest = currentStart;
        for(int y = i; y < lenght; y++){
            if(*lowest > *(array+y)){
                lowest = (array+y);
            }
        }
        swap(lowest, currentStart);
    }

    clock_t end = clock();

    print(array, lenght);

    return (double)(end - begin) / CLOCKS_PER_SEC;
}

/// insertion sort
double insertionSort(int lenght){
    int array[lenght];
    randomTable(&array, lenght);
    print(&array, lenght);

    int i, element, j;

    mergeSortSort(&array,0,lenght-1);
    //invert(&array, lenght);

    clock_t begin = clock();

    for (i = 1; i < lenght; i++) {
        element = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > element) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = element;
    }

    clock_t end = clock();

    print(array, lenght);

    return (double)(end - begin) / CLOCKS_PER_SEC;
}

/// Merge sort
double mergeSort(int lenght){
    int array[lenght];
    randomTable(&array, lenght);
    print(&array, lenght);

    mergeSortSort(&array,0,lenght-1);
    //invert(&array, lenght);

    clock_t begin = clock();

    mergeSortSort(array,0,lenght-1);

    clock_t end = clock();

    print(array, lenght);

    return (double)(end - begin) / CLOCKS_PER_SEC;
}
//27 1 48 2 3 7 99
//27 1 48 2
//27 1
//27
void mergeSortSort(int *array, int low, int high){
    if(low < high){
        int center = low + (high - low) / 2;

        mergeSortSort(array, low, center);
        mergeSortSort(array, center+1, high);

        mergeSortMerge(array, low, high, center);
    }
}
void mergeSortMerge(int *array, int low, int high, int center){
    int s1 = center-low+1, s2 = high-center;

    int left[s1], right[s2];

    int l, r;

    for(l = 0; l < s1; l++){
        left[l] = *(array+low+l);
    }
    for(r = 0; r < s2; r++){
        right[r] = *(array+center+1+r);
    }

    l = 0;
    r = 0;

    int k = low;
    while(l < s1 && r < s2){
        if(left[l] <= right[r]){
            *(array+k) = left[l];
            l++;
        }
        else{
            *(array+k) = right[r];
            r++;
        }
        k++;
    }

    while(l < s1){
        *(array+k) = left[l];
        l++;
        k++;
    }

    while(r < s2){
        *(array+k) = right[r];
        r++;
        k++;
    }
}

/// radix sort
double radixSort(int lenght){
    int array[lenght];
    randomTable(&array, lenght);
    print(&array, lenght);

    mergeSortSort(&array,0,lenght-1);
    //invert(&array, lenght);

    clock_t begin = clock();

    int max = getMax(array, lenght);

    for(int place = 1; max / place > 0; place *= 10){
        radixSortCountingSort(array, lenght, place);
    }

    clock_t end = clock();

    print(array, lenght);

    return (double)(end - begin) / CLOCKS_PER_SEC;
}
int getMax(int *array, int n) {
  int max = *array;
  for (int i = 1; i < n; i++)
    if (*(array+i) > max)
      max = *(array+i);
  return max;
}
void radixSortCountingSort(int *array, int size, int place) {
  int output[size + 1];
  int max = (array[0] / place) % 10;

  for (int i = 1; i < size; i++) {
    if (((*(array+i) / place) % 10) > max)
      max = *(array+i);
  }
  int count[max + 1];

  for (int i = 0; i < max; ++i)
    count[i] = 0;

  for (int i = 0; i < size; i++)
    count[(*(array+i) / place) % 10]++;

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = size - 1; i >= 0; i--) {
    output[count[(*(array+i) / place) % 10] - 1] = *(array+i);
    count[(*(array+i) / place) % 10]--;
  }

  for (int i = 0; i < size; i++)
    *(array+i) = output[i];
}

void swap(int *first, int *second){
    int temp;
    temp = *first;
    *first = *second;
    *second = temp;
}

void randomTable (int *array, int total){
    for(int i = 0; i < total; i++){
        *(array+i) = rand() % 100000;
    }
}

void print(int *table, int lenght){
    if(true){
        for(int i = 0; i < lenght; i++){
            printf("%d ", *(table+i));
        }
        printf("\n");
    }
}

void invert(int *array, int lenght){
    int len = lenght, lenHalf;
    int temp, *start, *end;

     lenHalf = len / 2;

    len--;

    for(int i = 0; i < lenHalf; i++){
        start = array+i;
        end = array+len-i;
        temp = *start;
        *start = *end;
        *end = temp;
    }
}
