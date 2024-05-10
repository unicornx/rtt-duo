// 参考 https://www.rt-thread.org/document/api/timer_sample_8c-example.html

/*
 * 程序清单：定时器例程
 *
 * 这个例程会创建两个动态定时器，一个是单次定时，一个是周期性定时
 * 并让周期定时器运行一段时间后停止运行
 */
#include <rtthread.h>

/* 定时器的控制块 */
static rt_timer_t timer1;
static rt_timer_t timer2;
static int cnt = 0;

/* 定时器1超时函数 */
static void timeout1(void *parameter)
{
    rt_kprintf("periodic timer is timeout %d\n", cnt);

    /* 运行第 10 次，停止周期定时器 */
    if (cnt++>= 9)
    {
        rt_timer_stop(timer1);
        rt_kprintf("periodic timer was stopped! \n");
    }
}

/* 定时器2超时函数 */
static void timeout2(void *parameter)
{
    rt_kprintf("one shot timer is timeout\n");
}

int test_timer(void)
{
    rt_kprintf("Running Timer test!\n");

    /* 创建定时器1 周期定时器 */
    timer1 = rt_timer_create("timer1", // name
                             timeout1, // timeout function
                             RT_NULL,  // parameter of timeout function
                             10,       // timeout ticks of the timer
                             RT_TIMER_FLAG_PERIODIC);

    /* 启动定时器1 */
    if (timer1 != RT_NULL) rt_timer_start(timer1);

    /* 创建定时器2 单次定时器 */
    timer2 = rt_timer_create("timer2",
                             timeout2,
                             RT_NULL,
                             30,
                             RT_TIMER_FLAG_ONE_SHOT);

    /* 启动定时器2 */
    if (timer2 != RT_NULL) rt_timer_start(timer2);

    rt_kprintf("Test Done!\n");

    return 0;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(test_timer, "timer sample");