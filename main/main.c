#include <stdio.h>
#include "advanced_debugging.h"

void app_main(void)
{
    /*****************IMPORTANT! ONLY UNCOMMENT ONE LINE AT A TIME!!!!!!!!!!!!*******************/

    /***************************LOGGING*********************************************************/

    /******logging********/
    // logging_demo();
    // logging_ex();
    // // logging_ex_sol();

    /******memory_print********/
    // memory_print_demo();
    // memory_print_ex();
    // // memory_print_ex_sol();

    /******memory_print********/
    // memory_print_demo();
    // memory_print_ex();
    // // memory_print_ex_sol();

    /******log vars********/
    // log_vars_demo();
    //  log_vars_demo_ex();
    // // log_vars_demo_ex_sol();

    /****************************GDB******************************************/

    /******open ocd********/
    // gdb_debug();
    // gdb_debug_ex();
    // gdb_debug_sol();

    /******core dump******/
    // gdb_core_dump();
    // gdb_core_dump_ex();
    // gdb_core_dump_sol();

    /*************************Memory******************************************/

    /******App trace and Segger*****/
    // memory_leaks();
    // memory_leaks_ex();
    // memory_leaks_sol();

    memory_trace();
}
