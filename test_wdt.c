// 参考 https://www.rt-thread.org/document/api/iwdg_sample_8c-example.html

/*
 * 程序清单：这是一个看门狗设备使用例程
 * 例程导出了 test_wdt 命令到控制终端
 * 命令调用格式：test_wdt feed
 * 命令解释：命令第二个参数是指定是否喂狗，为空则不喂狗。
 * 程序功能：程序通过设备名称查找看门狗设备，然后初始化设备并设置看门狗设备溢出时间。
 * 然后设置空闲线程回调函数，根据命令行指定是否在回调函数里喂狗。
 * 如果喂狗则系统正常
 * 否则超时后系统会重启
 */

#include <rtthread.h>
#include <rtdevice.h>

#define IWDG_DEVICE_NAME "wdt0" /* 默认看门狗设备名称 */

static rt_device_t wdg_dev; /* 看门狗设备句柄 */

static void idle_hook(void)
{
    /* 在空闲线程的回调函数里喂狗 */
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);

    // 不打印，否则屏幕显示太多，只要控制台不重启说明喂狗正常
    //rt_kprintf("feed the dog!\n ");
}

static void test_wdt(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    int flag_feed = 0; /* 默认不喂狗 */

    rt_uint32_t timeout = 3000; /* 溢出时间，单位为 ms */

    rt_kprintf("Running Watchdog Timer test!\n");

    char str_feed[] = "feed";
    /* 判断命令行参数是否指定启动喂狗 */
    if (argc == 2)
    {
	if (!rt_strncmp(str_feed, argv[1], 4))
	{
	    flag_feed = 1;
	}
    }

    /* 根据设备名称查找看门狗设备，获取设备句柄 */
    wdg_dev = rt_device_find(IWDG_DEVICE_NAME);
    if (!wdg_dev)
    {
	rt_kprintf("find %s failed!\n", IWDG_DEVICE_NAME);
	return;
    }

    /* 初始化设备 */
    ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
	rt_kprintf("initialize %s failed!\n", IWDG_DEVICE_NAME);
	return;
    }

    /* 设置看门狗溢出时间 */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
	rt_kprintf("set %s timeout failed!\n", IWDG_DEVICE_NAME);
	return;
    }
    
    rt_kprintf("Watchdog Timer is launched!\n");
    
    /* 设置空闲线程回调函数 */
    if (flag_feed)
    {
	rt_thread_idle_sethook(idle_hook);
	rt_kprintf("Thanks for feeding me, I'm alive!\n");
    }
    else
    {
	rt_kprintf("Oops, I am so hungary and will be killed in seconds!\n");
    }

    /* 延迟足够时间，看看系统会不会被看门狗重启 */
    rt_thread_mdelay(2 * timeout);

    /* 如果喂狗成功，还有机会走到这里关闭关门狗 */
    rt_device_close(wdg_dev);
    rt_kprintf("Watchdog Timer is closed!\n");

    rt_kprintf("Test Done!\n");

    return;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(test_wdt, "watchdog sample");