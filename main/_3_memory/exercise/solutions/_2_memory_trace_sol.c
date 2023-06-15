#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "cJSON.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/**********
 * Task 1
 * add the "esp_heap_trace.h" include file
 */

#include "esp_heap_trace.h"

#define NUM_RECORDS 1000
static heap_trace_record_t trace_record[NUM_RECORDS];

/*****************
 * Task 2
 * Ensure the menuconfig
 * * Heap memory debugging -> Heap cooruption detection is set to "light impact"
 * * Heap memory debugging -> tracing stack depth is set to 10
 */

/***************
 * Task 3
 * set up the structure globally
 * * #define NUM_RECORDS 1000
 * * static heap_trace_record_t trace_record[NUM_RECORDS];
 */
#define NUM_RECORDS 1000
static heap_trace_record_t trace_record[NUM_RECORDS]; // This buffer must be in internal RAM

static const char *TAG = "MEM";
static void fix_this_leaky_function(void);

void memory_trace_sol(void)
{
    /**************
     * Task 4
     * initialise the heap dump hint heap_trace_init_standalone
     */

    ESP_ERROR_CHECK(heap_trace_init_standalone(trace_record, NUM_RECORDS));

    fix_this_leaky_function();
}

static void fix_this_leaky_function(void)
{
    /***********
+-     * Task 5
     * Start the heap dump
     */
    ESP_ERROR_CHECK(heap_trace_start(HEAP_TRACE_LEAKS));
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "question", "life, universe and everything");
    cJSON_AddNumberToObject(json, "answer", 42);
    char *json_str = cJSON_Print(json);
    printf("%s\n", json_str);

    //  clean up here
    /******************/
    cJSON_Delete(json);
    ESP_LOGI(TAG, "after cJSON_Delete(json) %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    free(json_str);
    /******************/

    /***********
     * Task 6
     * end the heap dump
     */
    heap_trace_dump();
}
