#include <stdio.h>
#include <string.h>
#include "esp_log.h"

#define BUFFER_SIZE 256

void memory_print_demo(void)
{
    // we might have a piece of memory like so
    /******************************/
    char *buffer = malloc(BUFFER_SIZE);
    for (size_t i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = i;
    /****************************/

    // how can we see whats inside there?

    // we can use
    ESP_LOG_BUFFER_HEX("TAG", buffer, BUFFER_SIZE);

    // but what if we also want to see the printable characters? We use
    ESP_LOG_BUFFER_HEXDUMP("TAG", buffer, BUFFER_SIZE, ESP_LOG_WARN);

    free(buffer);
}
