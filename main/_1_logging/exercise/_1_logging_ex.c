#include <stdio.h>
#include <string.h>
#include "esp_log.h"

void logging_ex(void)
{
    /***************
     * Task 1
     * Get these 2 to print
     ************/
    printf("************* should see 2 lines below ***********\n");
    ESP_LOGD("log ex", "Debug");
    ESP_LOGV("log ex", "Verbose");
    printf("************************\n");

    /***************
     * Task 2
     * The information log is too chatty. hide the information messages and display the rest
     ************/
    printf("suppress \"hide me\"\n");
    ESP_LOGI("log ex", "hide me");
    ESP_LOGW("log ex", "a warning");
    ESP_LOGI("log ex", "hide me");
    ESP_LOGE("log ex", "an error");
    ESP_LOGI("log ex", "hide me");

    /***************
     * Task 3
     * we only care about the "print me" tag hide the rest
     ************/
    printf("suppress \"hide me\"\n");
    ESP_LOGI("print me", "show me");
    ESP_LOGW("print me", "show me");
    ESP_LOGI("hide me", "hide me");
    ESP_LOGE("print me", "print me");
    ESP_LOGE("hide me", "hide me");

    /***************
     * clean up
     * reset the log level to its default
     ************/
}