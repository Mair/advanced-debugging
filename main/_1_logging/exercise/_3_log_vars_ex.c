#include <string.h>
#include "esp_log.h"

static void baz(void);
static void bar(void);
static void foo(void);

void log_vars_demo_ex(void)
{
    /***************
     * Task 1
     * print the current source line
     ************/

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
     * print a 5 level stack trace to follow the function path
     ************/

    /***************
     * Task 3
     * check the stacktrace. spot the functions, file name and line number
     * ctrl+click on the line to navigate to the line and file for each line
     ************/
}
