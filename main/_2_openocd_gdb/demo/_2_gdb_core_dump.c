#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "esp_random.h"

/*********************
 * In order for the core dump to work we need to put it somewhere.
 * In the menu config file we can put it into push it out the serial line or we can store it onto flash
 * In this case we will store it into flash
 * We start by creating a custom partition table that has place for the core dump
 * #########################
 *  nvs,      data, nvs,           ,  0x6000
 *  phy_init, data, phy,           ,  0x1000
 *  factory,  app,  factory,       ,  1M
 *  coredump, data, coredump,      ,  64K
 * ########################
 *
 *
 * ***********************
 */

typedef struct fib_params_t
{
    int number_of_elements;
    void (*callback)(int number);
} fib_params_t;

typedef struct linked_list
{
    int fib_number;
    int random;
    struct linked_list *next;
} linked_list_t;

linked_list_t *linked_list;

static void gdb_core_dump_task(void *params);
static void append_linked_list(int fib_number);
static void do_fibonacci(fib_params_t *fib_params);
static void print_linked_list(void);

void gdb_core_dump(void)
{
    xTaskCreate(gdb_core_dump_task, "gdb_core_dump_task", 1024 * 5, NULL, 5, NULL);
}

static void gdb_core_dump_task(void *params)
{
    fib_params_t fib_params = {
        .number_of_elements = 30,
        .callback = append_linked_list};

    do_fibonacci(&fib_params);
    print_linked_list();
    vTaskDelete(NULL);
}

static int generate_random(int fib_number)
{
    uint32_t random = esp_random();
    int short_random = random % 5;
    int new_number = fib_number / short_random;
    return new_number;
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
    current->random = generate_random(fib_number);
}

static void print_linked_list(void)
{
    linked_list_t *current = linked_list;
    while (current)
    {
        printf(" %d:(%d)->", current->fib_number, current->random);
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
