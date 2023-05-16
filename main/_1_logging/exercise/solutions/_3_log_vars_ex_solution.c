#include <string.h>
#include "esp_log.h"
#include "esp_debug_helpers.h"

static void baz(void);
static void bar(void);
static void foo(void);

void log_vars_demo_ex_sol(void)
{
    /***************
     * Task 1
     * print the current source line
     ************/

    ESP_LOGI("TAG", "running in FILE %s on LINE %d in FUNCTION %s", __FILE__, __LINE__, __FUNCTION__);
    foo();
}

static void foo(void)
{
    bar();
}
static void bar(void)
{
    baz();
}
static void baz(void)
{
    /***************
     * Task 2
     * print a 5 level stack trace
     ************/
    esp_backtrace_print(5);

    /***************
     * Task 3
     * check the stacktrace. spot the functions, file name and line number
     * ctrl click on the line to navigate to the line and file
     ************/
}