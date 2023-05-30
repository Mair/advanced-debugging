#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "cJSON.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MEM";

static void fix_this_leaky_function(void);

void memory_leaks_sol(void)
{

    fix_this_leaky_function();
}

static void fix_this_leaky_function(void)
{

    uint32_t start_of_function = heap_caps_get_free_size(MALLOC_CAP_8BIT);

    printf("start function %ld\n", start_of_function);

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "question", "life, universe and everything");
    cJSON_AddNumberToObject(json, "answer", 42);

    // print memory here using ESP_LOGI
    ESP_LOGI(TAG, "before cJSON_Print(json) %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    char *json_str = cJSON_Print(json);

    //  print memory here
    ESP_LOGI(TAG, "after cJSON_Print(json) %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    printf("%s\n", json_str);

    //  clean up here
    /******************/
    cJSON_Delete(json);
    ESP_LOGI(TAG, "after cJSON_Delete(json) %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    free(json_str);
    /******************/

    uint32_t end_of_function = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    ;
    printf("end function %ld\n", end_of_function);
    uint32_t memory_leaked = start_of_function - end_of_function;
    printf("memory leaked = %ld\n", memory_leaked);

    assert((memory_leaked < 500) && "oh dear we still have a big leak");
    // after cleanup we still lost some memory. how much did we loose?   =
    // -464 bytes
}
