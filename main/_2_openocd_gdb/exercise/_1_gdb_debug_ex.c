#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************
 * Info
 * This is a simplified version of the demo. It does not use FreeRtos or callbacks
 * in addition to the fibonacci number we also store the number as a string
 * The output looks as follows
  ========================
  1->2->3->5->8->13->21->34->55->89->0->0->0->
  and now the strings...
  1->2->3->5->8->13->21->34->55->89->144->233->377->
  ========================
  If you look at the numbers printed you will notice there is a problem somewhere.
  Follow the tasks to locate the error
 ************/

typedef struct linked_list
{
    char fib_number_as_str[3];
    uint8_t fib_number;
    struct linked_list *next;
} linked_list_t;

static linked_list_t *linked_list;

static void append_linked_list(int fib_number);
static void print_linked_list(void);

/***************
 * Task 1
 * 1. Get OpenOcd and DBG started
 * 2. enable TUI mode (tui enable)
 * 3. get a break point on fhe function gdb_debug_ex
 * 4. continue (c)
 ************/

void gdb_debug_ex(void)
{
    /*****
     * Task 2
     * step over these line (n)
     ******/
    int n1 = 0, n2 = 1, n3;
    for (int i = 0; i < 13; i++)
    {
        n3 = n1 + n2;

        /******
         * task 3
         * step into this function (s)
         **********/
        append_linked_list(n3);
        n1 = n2;
        n2 = n3;
    }
    print_linked_list();
}

static void append_linked_list(int fib_number)
{
    /******
     * task 4
     * step over theses lines
     **********/
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
    /******
     * task 5
     * 1. add a break point to the next line (b <line number>)
     * 2. get the break-point numer (info b)
     * 2. make the breakpoint conditional if fib_number > 89 (conditional <break number> fib_number>89)
     * 3. continue until condition is met (c)
     * 4. inspect current (p *current)
     * 5. next (n)
     * 6. inspect current (p *current)
     * 7. next (n)
     * 8. inspect current (p *current)
     * 9. what did you observe?
     * 10. why is this happing
     * 11. propose a solution
     **********/
    current->fib_number = fib_number;
    sprintf(current->fib_number_as_str, "%d", fib_number);
    // dont remove this
    printf("%s\n", current->fib_number_as_str);
}

static void print_linked_list(void)
{
    linked_list_t *current = linked_list;
    while (current)
    {
        printf("%d->", current->fib_number);
        current = current->next;
    }
    current = linked_list;
    printf("\n and now the strings...\n");
    while (current)
    {
        printf("%s->", current->fib_number_as_str);
        current = current->next;
    }
    fflush(NULL);
}
