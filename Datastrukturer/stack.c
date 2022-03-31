#include <stdio.h>
#include <stdlib.h>
typedef struct Stack Stack, *pno;
struct Stack{
    int *array;
    int length;
    int high;
};

Stack create();
int pop(Stack *stack);
int peek(Stack *stack);
void push(Stack *stack, int value);
void sizeUp(Stack *stack);
void sizeDown(Stack *stack);

int main()
{
    Stack stack = create();
    printf("createed stack\n");
    printf("----------\n");
    push(&stack, 1);
    printf("pushed %d\n", 1);
    printf("----------\n");
    push(&stack, 2);
    printf("pushed %d\n", 2);
    printf("----------\n");
    push(&stack, 3);
    printf("pushed %d\n", 3);
    printf("----------\n");
    push(&stack, 4);
    printf("pushed %d\n", 4);
    printf("----------\n");
    push(&stack, 5);
    printf("pushed %d\n", 5);
    printf("----------\n");
    printf("peeked => %d\n", peek(&stack));
    printf("----------\n");
    printf("peeked => %d\n", peek(&stack));
    printf("----------\n");
    printf("poped => %d\n", pop(&stack));
    printf("----------\n");
    printf("poped => %d\n", pop(&stack));
    printf("----------\n");
    printf("poped => %d\n", pop(&stack));
    printf("----------\n");
    printf("poped => %d\n", pop(&stack));
    printf("----------\n");
    printf("poped => %d\n", pop(&stack));
    printf("----------\n");

    return 0;
}

Stack create(){
    printf("    create\n");
    struct Stack stack;
    stack.array = calloc(1, sizeof(int));
    stack.length = 1;
    stack.high = 0;
    return stack;
}

int pop(Stack *stack){
    if(stack->high > 0){
        printf("    pop value: %d from place: %d\n", *(stack->array+stack->high-1), stack->high-1);
        stack->high = stack->high-1;
        if(stack->high < stack->length/4){
            sizeDown(stack);
        }
        return *(stack->array+stack->high);
    }
}
int peek(Stack *stack){
    if(stack->high > 0){
        printf("    peek value: %d from place: %d\n", *(stack->array+stack->high-1), stack->high-1);
        return *(stack->array+stack->high-1);
    }
}

void push(Stack *stack, int value){
    printf("    push value: %d to place: %d\n", value, stack->high);
    if(stack->high >= stack->length){
        sizeUp(stack);
    }
    *(stack->array+stack->high) = value;
    stack->high = stack->high+1;
}

void sizeUp(Stack *stack){
    printf("    sizeUp ");
    printf("%d => ", stack->length);
    stack->array = realloc(stack->array, (stack->length*2)*sizeof(int));
    stack->length = stack->length * 2;
    printf("%d\n", stack->length);
}

void sizeDown(Stack *stack){
    printf("    sizeDown ");
    printf("%d => ", stack->length);
    stack->array = realloc(stack->array, (stack->length/2)*sizeof(int));
    stack->length = stack->length / 2;
    printf("%d\n", stack->length);
}
