#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"

typedef struct fib_params_t
{
    int number_of_elements;
    void (*callback)(int number);
} fib_params_t;

typedef struct linked_list
{
    int fib_number;
    struct linked_list *next;
} linked_list_t;

linked_list_t *linked_list;

static void gdb_debug_task(void *params);
static void append_linked_list(int fib_number);
static void do_fibonacci(fib_params_t *fib_params);
static void print_linked_list(void);

void gdb_debug(void)
{
    xTaskCreate(gdb_debug_task, "gdb_debug_task", 1024 * 5, NULL, 5, NULL);
}

static void gdb_debug_task(void *params)
{
    fib_params_t fib_params = {
        .number_of_elements = 30,
        .callback = append_linked_list};
    do_fibonacci(&fib_params);
    print_linked_list();
    vTaskDelete(NULL);
}

static void append_linked_list(int fib_number)
{
    linked_list_t *prev = NULL, *current = linked_list;
    if (linked_list == NULL)
    {
        linked_list = malloc(sizeof(linked_list_t));
        memset(linked_list, 0, sizeof(linked_list_t));
        current = linked_list;
    }
    else
    {
        while (current)
        {
            prev = current;
            current = current->next;
        }
        prev->next = malloc(sizeof(linked_list_t));
        memset(prev->next, 0, sizeof(linked_list_t));
        current = prev->next;
    }
    current->fib_number = fib_number;
}

static void print_linked_list(void)
{
    linked_list_t *current = linked_list;
    while (current)
    {
        printf("%d->", current->fib_number);
        current = current->next;
    }
    fflush(NULL);
}

static void do_fibonacci(fib_params_t *fib_params)
{
    int n1 = 0, n2 = 1, n3;
    for (int i = 0; i < fib_params->number_of_elements; i++)
    {
        n3 = n1 + n2;
        fib_params->callback(n3);
        n1 = n2;
        n2 = n3;
    }
    fflush(NULL);
}
