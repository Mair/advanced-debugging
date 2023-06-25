#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "cJSON.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_trace.h"

/*********************************
 * menuconfig: Component config->Heap memory degugging
 * choose corruption detection level
 * choose the heap tracing stack depth
 */

char *buffer;
char *buffer2;

static int BUFFER_SIZE = 100;
#define NUM_RECORDS 1000
static heap_trace_record_t trace_record[NUM_RECORDS]; // This buffer must be in internal RAM

static void single_byte_buffer_overflow(void);
static void multiple_byte_buffer_overflow(void);
static void buffer_overflow_with_trace(void);
static void buffer_overflow_with_integrity_check(void);

void memory_poisoning(void)
{
    /*******comment out all but 1************/

    single_byte_buffer_overflow();
    // multiple_byte_buffer_overflow();
    // multiple_byte_buffer_overflow_with_trace();
    // buffer_overflow_with_integrity_check();
}

static void single_byte_buffer_overflow(void)
{
    buffer = malloc(BUFFER_SIZE);
    buffer2 = malloc(BUFFER_SIZE);

    buffer2[BUFFER_SIZE] = NULL;

    free(buffer);
    free(buffer2);
}

static int get_overflow_amount()
{
    return 10;
}
static void multiple_byte_buffer_overflow(void)
{
    buffer = malloc(BUFFER_SIZE);
    buffer2 = malloc(BUFFER_SIZE);

    memset(buffer2, 'x', BUFFER_SIZE + get_overflow_amount());

    free(buffer);
    free(buffer2);
}

static void buffer_overflow_with_trace(void)
{
    ESP_ERROR_CHECK(heap_trace_init_standalone(trace_record, NUM_RECORDS));
    ESP_ERROR_CHECK(heap_trace_start(HEAP_TRACE_ALL));
    buffer = malloc(BUFFER_SIZE);
    buffer2 = malloc(BUFFER_SIZE);

    memset(buffer2, 'x', BUFFER_SIZE + get_overflow_amount());
    heap_trace_dump();

    free(buffer);
    free(buffer2);
}

static void buffer_overflow_with_integrity_check(void)
{
    heap_caps_check_integrity_all(true);
    buffer = malloc(BUFFER_SIZE);
    buffer2 = malloc(BUFFER_SIZE);

    memset(buffer2, 'x', BUFFER_SIZE + get_overflow_amount());
    heap_caps_check_integrity_all(true);

    free(buffer);
    free(buffer2);
}
