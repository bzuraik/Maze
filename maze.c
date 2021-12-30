#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#if defined(_OPENMP)
    #include <omp.h>
#endif

#include <time.h>
#include <unistd.h>

#define SIZE 100
#define MAX 100


int cl[2];
int x = 11;
int y = 11;
int array[4] = {1,2,3,4};
int n = 0;
int r0 = 0;
int r1= 0;
int r2 = 0;
int r3 = 0;
int sFlag = 0;

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack2 {
    int top;
    unsigned capacity;
    int* array;
};

// https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack2* createStack2(unsigned capacity)
{
    struct Stack2* stack = (struct Stack2*)malloc(sizeof(struct Stack2));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
 
// Stack is full when top is equal to the last index
int isFull2(struct Stack2* stack)
{
    return stack->top == stack->capacity - 1;
}
 
// Stack is empty when top is equal to -1
int isEmpty2(struct Stack2* stack)
{
    return stack->top == -1;
}
 
// Function to add an item to stack.  It increases top by 1
void push2(struct Stack2* stack, int item)
{
    if (isFull2(stack))
        return;
    stack->array[++stack->top] = item;
}
 
// Function to remove an item from stack.  It decreases top by 1
int pop2(struct Stack2* stack)
{
    if (isEmpty2(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}
 
// Function to return the top from stack without removing it
int peek2(struct Stack2* stack)
{
    if (isEmpty2(stack))
        return INT_MIN;
    return stack->array[stack->top];
}
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
 
// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
 
// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}
 
// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}
 
// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}
 
// Function to return the top from stack without removing it
int peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}
 





// function to shuffle an array to create random order of nieghboru visiting 
void shuffle(int array[], int n)
{
    
    if(sFlag == 0) // dont shuffle 
    {
        array[0] = 1;
        array[1] = 2;
        array[2] = 3;
        array[3] = 4;
        
    }
    else
    {
        if (n > 1) 
        {
            size_t i;
            for (i = 0; i < n - 1; i++) 
            {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
            }
        }
    }
    
}

// function to print the grid 
void print (char grid[x][y], int x, int y)
{


    for (int i = 0; i < x; i++)
            {
                
                for (int j = 0;  j < y; j++)
                {
                    printf("%c  ",grid[i][j]);
                    
                }
                printf("\n");
            }

}

int check_neighbour(char grid[x][y], struct Stack* stack, struct Stack2* stack2, int thread_count, int cl[])
{
    
    int temp[2];
    int randomnumber;
    shuffle(array, 4);
    
    int i =0;
#if defined(_OPENMP)    
#pragma omp parallel num_threads(thread_count) private(i, randomnumber) shared(grid)
    {
#endif
    
    for( i = 0; i< 4;i++)
    {
        #if defined(_OPENMP)
        int my_rank = omp_get_thread_num();
        #endif

        #if !defined(_OPENMP)
            int my_rank = 0;
        #endif
        randomnumber = array[i];
        if(randomnumber == 1)
        {
            if(grid[cl[0] - 1 ][cl[1]] == '.' && grid[cl[0] - 2 ][cl[1]] == '.' && cl[0] - 1 > 0 && cl[0] - 2 > 0) //check above neighbour
            {
            
                    grid[cl[0] - 1 ][cl[1]] = my_rank + '0';
                    grid[cl[0] - 2 ][cl[1]] = my_rank + '0';
                    temp[0] = cl[0] - 2;
                    temp[1] = cl[1];
                    
                    
                    if(my_rank == 0)
                    {
                        r0 += 2;
                    }
                    else if(my_rank == 1)
                    {
                        r1 += 2;
                    }
                    else if(my_rank == 2)
                    {
                        r2 += 2;
                    }
                    else
                    {
                        r3 += 2;
                    }
                    n += 2;
                    push(stack, temp[0]);
                    push2(stack2, temp[1]);
                
    
            }
        }
        else if(randomnumber == 2)
        {
            if(grid[cl[0]][cl[1] + 1] == '.' && grid[cl[0]][cl[1] + 2] == '.' && cl[1] + 1 < x - 1 && cl[1] + 2 < x - 1) // check right neighbour
            {
                
                    grid[cl[0]][cl[1] + 1] = my_rank + '0';
                    grid[cl[0]][cl[1] + 2] = my_rank + '0';
                    temp[0] = cl[0];
                    temp[1] = cl[1] + 2;
                    
                    
                
                    if(my_rank == 0)
                    {
                        r0 += 2;
                    }
                    else if(my_rank == 1)
                    {
                        r1 += 2;
                    }
                    else if(my_rank == 2)
                    {
                        r2 += 2;
                    }
                    else
                    {
                        r3 += 2;
                    }
                    n += 2;
                    push(stack, temp[0]);
                    push2(stack2, temp[1]);
                
                
                
            }
        }
        else if(randomnumber == 3)
        {
            if(grid[cl[0]][cl[1] - 1] == '.' && grid[cl[0]][cl[1] - 2] == '.'  && cl[1] - 1 > 0 && cl[1] - 2 > 0) // check left neighbour
            {
               
                    grid[cl[0]][cl[1] - 1] = my_rank + '0';
                    grid[cl[0]][cl[1] - 2] = my_rank + '0';
                    temp[0] = cl[0];
                    temp[1] = cl[1] - 2;
                    
                    
                    if(my_rank == 0)
                    {
                        r0 += 2;
                    }
                    else if(my_rank == 1)
                    {
                        r1 += 2;
                    }
                    else if(my_rank == 2)
                    {
                        r2 += 2;
                    }
                    else
                    {
                        r3 += 2;
                    }
                    n += 2;
                    push(stack, temp[0]);
                    push2(stack2, temp[1]);
                
                
             
                
            }
        }
        else
        {
            if(grid[cl[0] + 1 ][cl[1]] == '.' && grid[cl[0] + 2 ][cl[1]] == '.' && cl[0] + 1 < x - 1 && cl[0] + 2 < x - 1) // check below neighbour
            {
                
                    grid[cl[0] + 1 ][cl[1]] = my_rank + '0';
                    grid[cl[0] + 2 ][cl[1]] = my_rank + '0';
                    temp[0] = cl[0] + 2;
                    temp[1] = cl[1];
                    
                    
                     if(my_rank == 0)
                    {
                        r0 += 2;
                    }
                    else if(my_rank == 1)
                    {
                        r1 += 2;
                    }
                    else if(my_rank == 2)
                    {
                        r2 += 2;
                    }
                    else
                    {
                        r3 += 2;
                    }
                    n += 2;
                    push(stack, temp[0]);
                    push2(stack2, temp[1]); 
    
            }
        }  
        
    }
#if defined(_OPENMP)    
    }
#endif
    
    return 0;
    
}





int main(int argc, char *argv[])
{
    int Par = 0;
  

    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-s") == 0)
        {
            sFlag = 1;
        }
        if(strcmp(argv[i], "-n") == 0)
        {
            if(atoi(argv[i + 1]) % 2 == 0)
            {
                x = atoi(argv[i + 1]) - 1;
                y = atoi(argv[i + 1]) - 1;
            }
            else
            {
                x = atoi(argv[i + 1]);
                y = atoi(argv[i + 1]);
            }
            
        }
        
    }


    int thread_count = 4;
    struct Stack* stack = createStack(50);
    struct Stack2* stack2 = createStack2(50);

    char grid[x][y];
    
    srand(time(NULL));   // Initialization, should only be called oncey
    

        for (int i = 0; i < x; i++)
        { 
            for (int j = 0;  j < y; j++)
            {
                grid[i][j] = '.';   
            }
        }

    printf("\n");
    

    
  
        cl[0] = 1;
        cl[1] = 1;
        push(stack, cl[0]);
        push2(stack2, cl[1]);
    
        grid[cl[0]][cl[1]] = '0';

        
        #if defined(_OPENMP)
        push(stack, 1);
        push2(stack2, x - 2);
    
        grid[1][x - 2] = '1';

        push(stack, x - 2);
        push2(stack2, 1);
    
        grid[x - 2][1] = '2';

        push(stack, x -2);
        push2(stack2, x - 2);
    
        grid[x - 2][x - 2] = '3';
        #endif

        

        
        int count = 0;
//printf("peek = %d, %d \n", peek(stack), peek2(stack2));

    
    while (!isEmpty(stack))
    {
         
        shuffle(array, 4);
        check_neighbour(grid, stack, stack2, thread_count, cl);
       
        cl[0] = pop(stack) + 0; // getting the x value
        cl[1] = pop2(stack2) + 0; // getting the y-value
        count += 1;
        
    }


    
    
        
        print(grid, x, y);
        
        #if defined(_OPENMP)
        printf("Rank 0 = %d \n", r0 +1);
        printf("Rank 1 = %d \n", r1 +1);
        printf("Rank 2 = %d \n", r2 +1);
        printf("Rank 3 = %d \n", r3 +1);
        
        #endif

        #if !defined(_OPENMP)
            printf("Thread 0 = %d \n", n +1);
            #endif

    return 0;

    
}