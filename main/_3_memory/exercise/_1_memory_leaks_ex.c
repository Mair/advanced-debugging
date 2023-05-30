#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "cJSON.h"

static const char *TAG = "MEM";

static void fix_this_leaky_function(void);

void memory_leaks_ex(void)
{
    fix_this_leaky_function();
}

static void fix_this_leaky_function(void)
{
    uint32_t start_of_function = esp_get_free_heap_size();
    printf("start function %ld\n", start_of_function);

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "question", "life, universe and everything");
    cJSON_AddNumberToObject(json, "answer", 42);
    // print memory here using ESP_LOGI
    char *json_str = cJSON_Print(json);
    // print memory here using ESP_LOGI
    printf("%s\n", json_str);
    // clean up here (hint: you need to free 2 things. One you need to use cJSON_Delete)
    /******************/
    /******************/

    uint32_t end_of_function = esp_get_free_heap_size();

    printf("end function %ld\n", end_of_function);
    uint32_t memory_leaked = start_of_function - end_of_function;
    printf("memory leaked = %ld\n", memory_leaked);
    assert((memory_leaked < 400) && "oh dear we still have a big leak");
    // after cleanup we still lost some memory. how much did we loose?
}
