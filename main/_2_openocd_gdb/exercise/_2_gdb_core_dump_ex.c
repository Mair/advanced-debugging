#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "esp_random.h"

/*********************
 * In order for the core dump to work we need to put it somewhere.
 * In the menu config file we can push it out the serial line or we can store it onto flash
 * In this case we will store it into flash
 * We start by creating a custom partition table that has place for the core dump
 * 1. create a file called partitions.csv in the project root with the following content
 *
 * #########################
 *  nvs,      data, nvs,           ,  0x6000
 *  phy_init, data, phy,           ,  0x1000
 *  factory,  app,  factory,       ,  1M
 *  coredump, data, coredump,      ,  64K
 * ########################
 * 2. open the menuconfig and open the partitions table setting
 * 3. set the partition table to a custom partition table
 * 4. set the Custom partition CSV file to partitions.csv
 * 5. flash and monitor the code below and notice it crashes
 * 6. stop the monitor
 * 7. run the following command
 *  "python <idf path>/components/espcoredump/espcoredump.py -p COM35 info_corefile build/advaned-debugging.elf"
 * 8. see if you can spot what caused the panic
 * 9. run the following command
 *  "python <idf path>/components/espcoredump/espcoredump.py -p COM35 dbg_corefile build/advaned-debugging.elf"
 * 10. once gdb is loaded get the backtrace: bt
 * 11. select the best frame to review: f <frame number>
 * 12. enable tui: tui enable
 * 13. inspect the variables
 * 14. How could this error be prevented?
 *
 *  ************** BONUS *********
 * 1. Go to the menuconfig
 * 2. In the search type panic
 * 3. set the panic handler behavior  to GDBStub on panic
 * 4. run the application so that is crashes again.
 * 5. what happens
 *
 * ***********************
 */

typedef struct linked_list
{
    int fib_number;
    int random;
    struct linked_list *next;
} linked_list_t;

linked_list_t *linked_list;

static void print_linked_list(void);
static int generate_random(int fib_number);
static void append_linked_list(int fib_number);
static void do_fibonacci();

void gdb_core_dump_ex(void)
{
    do_fibonacci();
    print_linked_list();
    vTaskDelete(NULL);
}

static void do_fibonacci()
{
    int n1 = 0, n2 = 1, n3;
    for (int i = 0; i < 30; i++)
    {
        n3 = n1 + n2;
        append_linked_list(n3);
        n1 = n2;
        n2 = n3;
    }
    fflush(NULL);
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

static int generate_random(int fib_number)
{
    uint32_t random = esp_random();
    int short_random = random % 5;
    int new_number = fib_number / short_random;
    return new_number;
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
