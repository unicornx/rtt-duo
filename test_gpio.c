#include <rtdevice.h>
#include <stdio.h>

static rt_base_t pinno;

static int led_init(void)
{
    pinno = rt_pin_get("C24");
    rt_kprintf("pin number is: %d\n", pinno);

    rt_pin_mode(pinno, PIN_MODE_OUTPUT);

    return 0;
}

static int led_on(void)
{
    rt_pin_write(pinno, PIN_HIGH);
    rt_kprintf("%d\n", rt_pin_read(pinno));
    return 0;
}

static int led_off(void)
{
    rt_pin_write(pinno, PIN_LOW);
    rt_kprintf("%d\n", rt_pin_read(pinno));
    return 0;
}


static void test_gpio()
{
    rt_kprintf("Running GPIO test!\n");

    led_init();

    for (int i = 0; i < 10; i++)
    {
        rt_kprintf("LED ON\n");
        led_on();

        rt_thread_mdelay(1000);

        rt_kprintf("LED OFF\n");
        led_off();

        rt_thread_mdelay(1000);
    }

    rt_kprintf("Test Done!\n");
}
MSH_CMD_EXPORT(test_gpio, "test gpio");