#include <stdio.h>
#include <string.h>
#include <system.h>

void memory_poisoning(void)
{

    heap_caps_check_integrity_all(true);
}