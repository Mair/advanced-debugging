#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "esp_heap_trace.h"

/*********************************
 * menuconfig: Component config->Heap memory degugging
 * choose corruption detection level
 * choose the heap tracing stack depth
 */

static const char *TAG = "MEM TRACE";
#define NUM_RECORDS 1000
static heap_trace_record_t trace_record[NUM_RECORDS]; // This buffer must be in internal RAM

static char *leaky_function(void);

void memory_trace(void)
{
    // we can use esp_get_free_heap_size() to get how much memory is available
    //  we can also use heap_caps_get_free_size(MALLOC_CAP_SPIRAM) to get PSRAM if we are using it

    ESP_ERROR_CHECK(heap_trace_init_standalone(trace_record, NUM_RECORDS));
    ESP_ERROR_CHECK(heap_trace_start(HEAP_TRACE_LEAKS));

    uint32_t before = esp_get_free_heap_size();
    char *message = leaky_function();
    // free(message);
    uint32_t after = esp_get_free_heap_size();
    heap_trace_dump();

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
