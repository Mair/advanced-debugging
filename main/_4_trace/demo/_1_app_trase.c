#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_app_trace.h"
#include "esp_log.h"

/***********
 * APPTRACE
 * 1. set up menuconfig
 *  menuconfig -> component config ->Application level tracing.
 *  Set data destination to JTAG
 * 2. start openocd:
 *  idf.py openocd
 * 3. telnet into openocd (telnet can be installed under windows with add / remove features):
 *   telnet localhost 4444
 * 4. esp apptrace start file://apptrace.log 1 -1 -1 0 0
 * 5. (optional) if running esp_log_set_vprintf then use
 */

#define TAG "APP TRACE"
#define TWENTY_MILI_SECS (1000 * 20)

static void app_trace_task(void *params);
static void fast_loop(void);
static void fast_loop_with_debug(void);
static void fast_loop_with_app_trace_write(void);
static void fast_loop_with_app_trace_write(void);
static void fast_loop_with_app_trace_ESP_LOG(void);

void app_trace(void)
{
    xTaskCreatePinnedToCore(app_trace_task, "app_trace_task", 1024 * 5, NULL, 5, NULL, 1);
}

static void app_trace_task(void *params)
{
    fast_loop();
    fast_loop_with_debug();

    // CHOOSE ONE OF THESE 2
    // fast_loop_with_app_trace_write();
    fast_loop_with_app_trace_ESP_LOG();

    vTaskDelete(NULL);
}

static void fast_loop(void)
{
    int64_t start_time = esp_timer_get_time();
    int64_t seconds_1_from_now = start_time + TWENTY_MILI_SECS;
    int count = 0;
    while (seconds_1_from_now > esp_timer_get_time())
    {
        count++;
    }
    printf("fast loop count: %d\n", count);
}

static void fast_loop_with_debug(void)
{
    int64_t start_time = esp_timer_get_time();
    int64_t seconds_1_from_now = start_time + TWENTY_MILI_SECS;
    int count = 0;
    while (seconds_1_from_now > esp_timer_get_time())
    {
        printf("fast loop count: %d\n", count);
        count++;
    }
    printf("fast loop with debug count: %d\n", count);
}

static void fast_loop_with_app_trace_write(void)
{
    while (!esp_apptrace_host_is_connected(ESP_APPTRACE_DEST_JTAG))
    {
        vTaskDelay(1);
    }

    int64_t start_time = esp_timer_get_time();
    int64_t seconds_1_from_now = start_time + TWENTY_MILI_SECS;
    int count = 0;
    char log_text[50];

    // esp_log_set_vprintf(esp_apptrace_vprintf);

    while (seconds_1_from_now > esp_timer_get_time())
    {
        sprintf(log_text, "current count is: %d\n", count);
        esp_err_t res = esp_apptrace_write(ESP_APPTRACE_DEST_JTAG, log_text, strlen(log_text), ESP_APPTRACE_TMO_INFINITE);
        if (res != ESP_OK)
        {
            ESP_LOGE("TRACE", "Failed to write data to host [0x%x] (%s)", res, esp_err_to_name(res));
        }
        // ESP_LOGI("TAG", "count %d", count);
        // printf("fast loop count: %d\n", count);
        if (count++ % 500 == 0)
            esp_apptrace_flush(ESP_APPTRACE_DEST_JTAG, 1000);
    }
    esp_apptrace_flush(ESP_APPTRACE_DEST_JTAG, ESP_APPTRACE_TMO_INFINITE);
    // esp_log_set_vprintf(vprintf);
    printf("fast loop with trace count: %d\n", count);
}

static void fast_loop_with_app_trace_ESP_LOG(void)
{
    while (!esp_apptrace_host_is_connected(ESP_APPTRACE_DEST_JTAG))
    {
        vTaskDelay(1);
    }

    int64_t start_time = esp_timer_get_time();
    int64_t seconds_1_from_now = start_time + TWENTY_MILI_SECS;
    int count = 0;
    char log_text[50];

    esp_log_set_vprintf(esp_apptrace_vprintf);

    while (seconds_1_from_now > esp_timer_get_time())
    {
        ESP_LOGI("TAG", "count %d", count);

        if (count++ % 500 == 0)
            esp_apptrace_flush(ESP_APPTRACE_DEST_JTAG, 1000);
    }
    esp_apptrace_flush(ESP_APPTRACE_DEST_JTAG, ESP_APPTRACE_TMO_INFINITE);
    esp_log_set_vprintf(vprintf);
    printf("fast loop with trace count: %d\n", count);
}
