#include <string.h>
#include "esp_log.h"

void logging_demo(void)
{

    ESP_LOGI("This is the tag", "this is the message");

    // we can use formatting
    ESP_LOGI("log 1", "log with %d format %s", 1, "string");

    // logging types
    ESP_LOGE("log 1", "error");
    ESP_LOGW("log 1", "warning");
    ESP_LOGI("log 1", "infomation");
    // this will only work once updating the menuconfig
    ESP_LOGD("log 1", "Debug");
    // Same with this
    ESP_LOGV("log 1", "Verbose");

    // suppressing log levels
    esp_log_level_set("log 1", ESP_LOG_WARN);
    // now this one will not print
    ESP_LOGI("log 1", "you cant see me");
    // but this one still works
    ESP_LOGW("log 1", "I see this warning");
}