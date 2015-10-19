#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TOTAL_RINGS 3

typedef struct
{
    int* stack;
    int* top;
} STACK;

int pop(int stack, STACK* stacks[])
{
    int data = *(stacks[stack]->top);
    
    *(stacks[stack]->top) = 0;
    if (&(stacks[stack]->stack[0]) == stacks[stack]->top) {
        return data;
    }
    stacks[stack]->top--;
    return data;
}

void push(int data, int stack, STACK* stacks[])
{
    if (&(stacks[stack]->stack[0]) == stacks[stack]->top && stacks[stack]->stack[0] == 0) {
        *(stacks[stack]->top) = data;
        return;
    }
    else
    {
        stacks[stack]->top++;
        *(stacks[stack]->top) = data;
    }
}


void printBoard(STACK* stacks[])
{
    int d;
    int a;
    
    for(d = TOTAL_RINGS-1; d >= 0; d--)
    {
        for(a = 0; a < 3; a++)
        {
            printf("%d\t", stacks[a]->stack[d]);
        }
        printf("\n");
    }
}

void initialize(STACK* stacks[])
{
    int i;
    int j;
    
    for(j = 0; j < 3; j++)
    {
        stacks[j] = malloc(sizeof(STACK));
        
        stacks[j]->stack = malloc(sizeof(int)*TOTAL_RINGS);
        
        stacks[j]->top = malloc(sizeof(int));
        
        for(i = 0; i < TOTAL_RINGS; i++)
            stacks[j]->stack[i] = 0;
    }
    
    for(i = 1; i <= TOTAL_RINGS; i++)
        stacks[0]->stack[TOTAL_RINGS-i] = i;
}


bool won(int stick[])
{
    int i;
    
    for(i = 0; i < TOTAL_RINGS; i++)
    {
        if(stick[i] != TOTAL_RINGS-i)
            return false;
    }
    
    return true;
}

bool valid(int input, int source)
{
    return ( (1 <= input) && (input <= 3) && input != source);
}


int main(void) {
    
    
    int userInput;
    int source;
    
    STACK* stacks[3];
    
    initialize(stacks);
    
    stacks[0]->top = &stacks[0]->stack[TOTAL_RINGS-1];
    stacks[1]->top = &stacks[1]->stack[0];
    stacks[2]->top = &stacks[2]->stack[0];
    
    printf("Welcome to Towers of Hanoi!\n");
    
    while(1)
    {
        printf("Please select a starting stick.\n");
        scanf("%d", &userInput );
        
        source = userInput;
        
        if(!valid(userInput, -1))
        {
            printf("Invalid stick, try again please!\n");
            continue;
        }
        
        printf("Now please select a destination stick.\n");
        scanf("%d", &userInput);
        
        if(!valid(userInput, source))
        {
            printf("Invalid stick, try again please!\n");
            continue;
        }
        
        if (*(stacks[source-1]->top) > *(stacks[userInput-1]->top) && *(stacks[userInput-1]->top) != 0) {
            printf("You can't move a big ring over a small ring!\n");
        }
        
        else if (*(stacks[source-1]->top) != 0)
            push(pop(source-1, stacks), userInput-1, stacks);
        
        if(won(stacks[2]->stack))
        {
            printf("Woo, you won!\n");
            printBoard(stacks);
            return 1;
        }
        
        printBoard(stacks);
    }
    
    return 0;
}


