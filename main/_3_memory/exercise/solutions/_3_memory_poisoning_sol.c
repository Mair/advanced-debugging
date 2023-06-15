#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "cJSON.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_trace.h"

/*****************
 * Task 1
 * Ensure the menuconfig
 * * Heap memory debugging -> Heap cooruption detection is set to "light impact"
 * * Heap memory debugging -> tracing stack depth is set to 10
 */

static int BUFFER_SIZE = 100;

static int get_overflow_amount()
{
    return 10;
}

void memory_poisoning_sol(void)
{
    char *buffer = malloc(BUFFER_SIZE);

    /***********
     * Task 2
     * fix this error
     */
    buffer[BUFFER_SIZE - 1] = '\0';
    /**********/

    // dont change the below
    memset(buffer, 'x', BUFFER_SIZE + get_overflow_amount());
    /***********
     * Task 3
     * use assert on the response of heap_caps_check_integrity_all to ensure program stops and finds the above corruption
     */
    assert(heap_caps_check_integrity_all(true));

    free(buffer);
}
