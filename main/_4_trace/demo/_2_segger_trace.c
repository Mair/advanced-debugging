#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_system.h"
#include "esp_sysview_trace.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_random.h"

// 1. menuconfig enable FreeRTOS SystemView Tracing -> SystemView Tracing Enable
// 2. disable most events (it gets a bit noisy. only enable the ones you need)
// 1. idf.py openocd
// 2. in a separate terminal: telnet localhost 4444
// esp sysview start file://<filename cpu 1> file://<filename cpu 2> 1 -1 -1 0 0
// 3. esp sysview start file://cpu0.SVDat file://cpu1.SVDat 1 -1 -1 0 0
// 4. add the following snipit to your code
/*************************************************/
void sysview_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    esp_sysview_vprintf(format, args);
    va_end(args);
    esp_sysview_flush(ESP_APPTRACE_TMO_INFINITE);
}
/*************************************************/

typedef struct payload_t
{
    int buffer_len;
    char *buffer;
    int payload_id;
} payload_t;

static void trace_task_1(void *params);
static void trace_task_2(void *params);

static QueueHandle_t trace_queue;

void segger_trace(void)
{
    trace_queue = xQueueCreate(100, sizeof(payload_t));
    sysview_printf("creating tasks");
    xTaskCreatePinnedToCore(trace_task_1, "trace_task_1", 1024 * 5, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(trace_task_2, "trace_task_2", 1024 * 5, NULL, 5, NULL, 0);
}

static void trace_task_1(void *params)
{
    int count = 0;
    while (true)
    {
        uint16_t random = esp_random() % 20;
        if (!random)
            continue;

        payload_t payload = {
            .buffer = malloc(random),
            .buffer_len = random,
            .payload_id = count++};
        memset(payload.buffer, 'x', random);
        sysview_printf("sending payload %d with %d bytes on to queue", count, random);

        xQueueSend(trace_queue, &payload, portMAX_DELAY);
        if (count % 50 == 0)
        {
            vTaskDelay(pdMS_TO_TICKS(20));
            sysview_printf("stop watchdog from barking");
        }
    }
}

static void trace_task_2(void *params)
{
    payload_t payload;
    while (true)
    {
        xQueueReceive(trace_queue, &payload, portMAX_DELAY);
        sysview_printf("received payload %d with %d bytes on to queue", payload.payload_id, payload.buffer_len);
        free(payload.buffer);
    }
}
