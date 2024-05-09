#include <rtdevice.h>
#include <rtthread.h>

// 目前只能运行在 Duo64M 的版本
// LED_PIN 指向的是 Duo 开发板上的 LED 针脚
// 目前 rt_pin_read() 任然无法获取到针脚的电平信息。
// rt_thread_mdelay() 是一个定时器，使得 led 的变化情况更加可视

#define LED_PIN 536

int led_init(void)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    return 0;
}

int led_on(void)
{
    rt_pin_write(LED_PIN, PIN_HIGH);
    rt_kprintf("%d\n",rt_pin_read(LED_PIN));
    return 0;
}

int led_off(void)
{
    rt_pin_write(LED_PIN, PIN_LOW);
    rt_kprintf("%d\n",rt_pin_read(LED_PIN));
    return 0;
}


void led_test(){
    led_init();
    rt_thread_mdelay(1000);
    rt_kprintf("LED ON\n");
    led_on();
    rt_thread_mdelay(1000);
    rt_kprintf("LED OFF\n");
    led_off();
}

MSH_CMD_EXPORT(test_led,test led);