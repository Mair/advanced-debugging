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

static const char *TAG = "MEM";
static void fix_this_leaky_function(void);

void memory_trace_ex(void)
{
    /**************
     * Task 4
     * initialise the heap dump hint heap_trace_init_standalone
     *
     */
    fix_this_leaky_function();
}

static void fix_this_leaky_function(void)
{
    /***********
     * Task 5
     * run this code as is (without freeing memory) and make a note of the output
     * then follow the rest of the tasks including memory cleanup
     *  to see how much memory you can save
     */

    /***********
     * Task 6
     * Start the heap dump
     */
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "question", "life, universe and everything");
    cJSON_AddNumberToObject(json, "answer", 42);
    char *json_str = cJSON_Print(json);
    printf("%s\n", json_str);

    //  clean up here
    /******************/
    // use cJSON_Delete() to delete the json structure
    // cJSON_Delete(json);
    ESP_LOGI(TAG, "after cJSON_Delete(json) %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    // now free the string
    // free(json_str)
    ESP_LOGI(TAG, "after freeing json_str %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    /******************/

    /***********
     * Task 6
     * end the heap dump
     * Is the rest of the memory something we can or should control?
     */
}
