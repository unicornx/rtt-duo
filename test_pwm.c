// 参考 https://www.rt-thread.org/document/api/pwm_led_sample_8c-example.html

/*
 * 程序清单：这是一个 PWM 设备使用例程
 * 例程导出了 test_pwm 命令到控制终端
 * 命令调用格式：test_pwm
 * 程序功能：通过 PWM 设备产生占空比为 50% 的方波。
 */

#include <rtthread.h>
#include <rtdevice.h>

#define PWM_DEV_NAME "pwm1" /* PWM 设备名称 */
#define PWM_DEV_CHANNEL 5 /* PWM 通道号 */

struct rt_device_pwm *pwm_dev; /* PWM设备句柄 */

static void test_pwm()
{
    rt_uint32_t period, pulse, dir;

    rt_kprintf("Running PWM test!\n");
    
    // 产生 PWM 方波的频率 Fpwm = 2000hz, 换算成周期就是 0.5ms
    period = 500000; /* 周期为0.5ms，单位为纳秒ns */
    // 按照 duty 50% 计算
    pulse = 250000; /* PWM脉冲宽度值，单位为纳秒ns */
    
    /* 查找设备 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return;
    }

    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(test_pwm, "pwm sample");