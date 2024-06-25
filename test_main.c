#include <rtthread.h>
#include <stdio.h>

static float ff(float f, int i)
{
    return f/i;
}

static double dd(double d, float f)
{
    return d * f;
}

int main(void)
{
    int i= 100;
    float f = 123;
    double d = 1.1;

    rt_kprintf("Hello RTT test!\n");

    f = ff(f, i);
    // rt_kprintf 不支持浮点数打印
    // 如果需要实现 rt_kprintf 打印浮点数，参考 <https://github.com/mysterywolf/rt_vsnprintf_full>
    // 也可以简单使用 printf，但在多任务下存在安全风险
    printf("printf float f = %f\n", f);

    d = dd(d, f);
    printf("printf double d = %f\n", d);

    return 0;
}
