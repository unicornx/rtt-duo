#include <rtthread.h>
#include <stdio.h>

void test_gpio()
{
    rt_kprintf("Running GPIO test!\n");
}
MSH_CMD_EXPORT(test_gpio, "test gpio");