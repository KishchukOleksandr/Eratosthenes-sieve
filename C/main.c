#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

size_t size = 0;
bool *sieve;
bool withOutput = false;

void display(void);
void get_primes(void);
uint32_t read_size(void);

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        size = (size_t)atoi(argv[1]);
    }

    if (argc > 2)
    {
        if (argv[2][0] == '-')
        {
            if (argv[2][1] == 'o')
                withOutput = true;
            else
            {
                printf("Unknown option %c\r\n", argv[2][1]);
                return 0;
            }
        }
        else
        {
            printf("Incorect format: use prime [size] [-o(utout)]\r\n");
            return 0;
        }
    }

    if (size == 0)
        size = read_size();

    sieve = (bool *)malloc(size);
    memset(sieve, true, size);
    sieve[0] = false;
    sieve[1] = false;
    get_primes();

    display();

    printf("\r\n");
    return 0;
}

uint32_t read_size(void)
{
    uint32_t size;

    do
    {
        size = 0;
        fflush(stdin);
        printf("\x1b[32mPlese enter a sizeber greater than 2: \x1b[0m");
        scanf("%d", &size);
    } while (size <= 2);

    return size;
}

void get_primes(void)
{
    for (uint32_t i = 2; (i * i) < size; i++)
    {
        if (sieve[i] == true)
        {
            for (uint32_t j = i * i; j < size; j += i)
            {
                sieve[j] = false;
                if (withOutput)
                {
                    display();
                    Sleep(100);
                }
            }
        }
    }
}

void display(void)
{
    static uint32_t row = 0;
    static int32_t col = 0;

    if (row > 0)
        printf("\x1b[%dA", row);
    printf("\x1b[300D");
    row = 0;
    col = 0;
    for (uint32_t k = 1; k < size; k++)
    {
        if (sieve[k])
            printf("\x1b[42m%02d \x1b[0m", k);
        else if (withOutput)
            printf("\x1b[41m%02d \x1b[0m", k);
        col++;
        if (k % 20 == 0 && withOutput)
        {
            row++;
            col = 0;
            printf("\r\n");
        }
    }
}