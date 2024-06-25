#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static float ff(float f, int i)
{
    return f/i;
}

static double dd(double d, float f)
{
    return d * f;
}

static void test_math()
{
    int i= 0;
    float f = -123;
    double d = -1.1;

    rt_kprintf("Running math test!\n");

    i = atoi("100");
    rt_kprintf("atoi i = %d\n", i);

    f = fabsf(f);
    printf("printf fabsf f = %f\n", f);
    d = fabs(d);
    printf("printf fabs d = %f\n", d);

    f = ff(f, i);
    // rt_kprintf 不支持浮点数打印
    // 如果需要实现 rt_kprintf 打印浮点数，参考 <https://github.com/mysterywolf/rt_vsnprintf_full>
    // 也可以简单使用 printf，但在多任务下存在安全风险
    printf("printf float f = %f\n", f);

    d = dd(d, f);
    printf("printf double d = %f\n", d);
}
MSH_CMD_EXPORT(test_math, "math sample");