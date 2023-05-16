#include <stdio.h>
#include <string.h>
#include "esp_log.h"

#define BUFFER_SIZE 256

typedef struct my_data_struct_t
{
    int an_int;
    char a_char;
    char a_str[10];
} my_data_struct_t;

void memory_print_ex_sol(void)
{
    // set up our buffer
    char *buffer = malloc(BUFFER_SIZE);
    for (size_t i = 0; i < BUFFER_SIZE; i++)
        // buffer[1] = i;
        buffer[i] = i;

    /***************
     * Task 1
     * use hexdump in green to validate it as correct
     ************/
    ESP_LOG_BUFFER_HEXDUMP("buffer", buffer, BUFFER_SIZE, ESP_LOG_INFO);

    /***************
     * Task 2
     * what should we do in relation to the above?
     ************/
    free(buffer);

    my_data_struct_t my_struct = {
        .an_int = 0xDEADBEEF,
        .a_char = 'x',
        .a_char = "my string"};

    /***************
     * Task 3
     * print the above structure as a hexdump in yellow
     ************/
    ESP_LOG_BUFFER_HEXDUMP("struct", &my_struct, sizeof(my_data_struct_t), ESP_LOG_WARN);

    /***************
     * Task 4
     * what can you say about the way the int is printed out? why?
     ************/
    // reversed due to little endian
}
