#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "esp_heap_caps.h"

static const char *TAG = "MEM";

static char *leaky_function(void);

void memory_leaks(void)
{
    // we can use esp_get_free_heap_size() to get how much memory is available
    //  we can also use heap_caps_get_free_size(MALLOC_CAP_SPIRAM) to get PSRAM if we are using it

    uint32_t before = esp_get_free_heap_size();
    char *message = leaky_function();
    // free(message);
    uint32_t after = esp_get_free_heap_size();

    if (before != after)
    {
        ESP_LOGW(TAG, "⚠️   MEMORY LEAK DETECTED!: Before %ld, After %ld, amount lost %ld", before, after, before - after);
    }
    else
    {
        ESP_LOGI(TAG, "No leak detected: Before %ld, After %ld, amount lost %ld", before, after, before - after);
    }
}

static char *leaky_function(void)
{
    char *message = malloc(100);
    strcpy(message, "This message was dynamically created on the heap");
    return message;
}