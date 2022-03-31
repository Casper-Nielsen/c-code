#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void backwards (char *str);
void sort (int *arr, int length);
int countwords (char *str);
char* sortwords(char *str);

int main()
{
    printf("Hello world!\n");
    char a[6] = "hello";
    printf("before %s \n", a);
    backwards(&a);
    printf("after %s \n", a);

    int b[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }, size = sizeof(b)/ sizeof(b[0]);
    printf("before \n");
    for(int i = 0; i < size; i++) {
        printf("%d, ",*(b+i));
    }
    printf("\n");
    sort(b, size);
    printf("after \n");
    for(int i = 0; i < size; i++) {
        printf("%d, ",*(b+i));
    }
    printf("\n");

    char c[20] = "hello world im here";
    printf("word: %s words: %d \n", c, countwords(&c));

    char d[20] = "hello world im here";
    printf("before %s \n", d);
    char *newd = sortwords(d);
    printf("after %s \n", newd);

    return 0;
}

// opgave 2
void backwards (char *str){
    // Not the fun way
    /* strrev(str);
    return; */
    // fun way
    int len = strlen(str), lenHalf, i = 0;
    char temp, *start, *end;

     lenHalf = len / 2;

    len--;

    for(i = 0; i < lenHalf; i++){
        start = str+i;
        end = str+len-i;
        temp = *start;
        *start = *end;
        *end = temp;
    }
}

// opgave 3
void sort(int *arr, int size){
    int temp, i, *current, *next;
    for(int j = 0; j < size; j++){
        for (i = 0; i < size-1-j; i++)
        {
            current = arr+i;
            next = current+1;

            if(*current > *next){
                temp = *current;
                *current = *next;
                *next = temp;
            }
        }
    }
}

// opgave 4
int countwords(char *str){
    bool wasletter = false;
    int len = strlen(str), wordcount = 0;

    for(int i = 0; i < len; i++){
        if(*(str+i) != ' '){
            wasletter = true;
        }else{
            wasletter = false;
            wordcount++;
        }
    }

    if(wasletter){
        wordcount++;
    }
    return wordcount;
}

// opgave 5
char* sortwords(char *str){
    bool wasletter = false;
    int wordcount = countwords(str), count = 0, wordnumber = 0, len = strlen(str);
    char words[wordcount][256], x[256], *start = str, *word;

    for(int i = 0; i < len; i++){

        if(*(str+i) != ' '){
            wasletter = true;
            count++;
        }else{
            strncpy(words[wordnumber], start, count);
            words[wordnumber][count] = '\0';
            start = str+i+1;
            wasletter = false;
            count = 0;
            wordnumber++;
        }
    }

    if(wasletter){
            strncpy(words[wordnumber], start, count);
            words[wordnumber][count] = '\0';
            wasletter = false;
            count = 0;
            wordnumber++;
    }

    for (int i = 0; i<wordcount; i++)
    {
        for (int j = 0; j<wordcount-1-i; j++)
        {
            if (strcmp(words[j], words[j+1]) <= 0)
            {
                strcpy(x, words[j+1]);
                strcpy(words[j+1], words[j]);
                strcpy(words[j], x);
            }
        }

    }

    word = words[0];
    for(int i = 1; i < wordnumber; i++){
        word = strcat(strcat(word," "), words[i]);
    }
    return word;
}
