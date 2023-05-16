#include <string.h>
#include "esp_log.h"
#include "esp_debug_helpers.h"

void log_vars_demo(void)
{
    // You can print information about the source line being run as follows
    ESP_LOGI("TAG", "running in FILE %s on LINE %d in FUNCTION %s", __FILE__, __LINE__, __FUNCTION__);

    // ITS also possible to print a stack trace (without a crash) after including esp_debug_helpers
    esp_backtrace_print(20);
}