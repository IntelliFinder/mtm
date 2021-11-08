#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//==============================================================================


/** request user inserts number of numbers */
int readSize();

/** request user to insert numbers */
void readNumbers( int* num_array, int size );

/** calculates sum of exponents of two*/
int sumExponents( int size, int* num_array, int* power_array);

/** print numbers that are powers of two and sum of exponents */
void printResults(int size, int exp,int* num_array, int* power_array);

/** returns power of two if number is a power of two, -1 otherwise */
int isPowerOfTwo(int num);


//==============================================================================


int main ()
{

    int size = readSize();
    if( size <  1 )
    {
        printf("Invalid size\n");
    }
    int* num_array = (int*)malloc( sizeof(int)*size);
    int* power_array = (int*)malloc( sizeof(int)*size);
    if (num_array == NULL || power_array == NULL) {
        exit(0);
    }
    readNumbers( num_array, size );
    int exp = sumExponents( size, num_array, power_array );
    printResults(size, exp, num_array, power_array);
    free( num_array );
    free( power_array );
    return 0;
}

int readSize()
{
    int num;
    printf("Enter size of input:\n");
    scanf("%d", &num);
    return num;
}
void readNumbers( int* num_array, int size )
{
    printf("Enter numbers:\n");
    for(int i =0; i<size; i++)
        if(!scanf( "%d", &num_array[i] ))
        {
            printf("Invalid number\n");
            exit(0);
        }
}
int isPowerOfTwo(int num)
{
    if ( num < 0)
        return -1;
    int exp, counter ;
    exp = 0 ;
    counter = 1;
    while ( counter < num )
    {
        ++exp;
        counter *= 2;
    }
    if( counter == num )
        return exp;
    return -1;
}
int sumExponents( int size, int* num_array, int* power_array)
{
    int exp = 0;
    for(int i=0; i < size; i++)
    {
        power_array[i] = isPowerOfTwo(num_array[i]);
        if(power_array[i] != -1)
        {
            exp += power_array[i];
        }
    }
    return exp;
}
void printResults(int size, int exp, int* num_array, int* power_array)
{
    for(int i =0; i<size; i++)
    {
        if( power_array[i] != -1)
        {
            printf("The number %d is a power of 2: %d = 2^%d\n", num_array[i], num_array[i], power_array[i]);
        }
    }

    printf("Total exponent sum is %d\n", exp);
}