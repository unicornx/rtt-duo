// 参考 https://www.rt-thread.org/document/api/adc_vol_sample_8c-example.html

/*
 * 程序清单： ADC 设备使用例程
 * 例程导出了 test_adc 命令到控制终端
 * 命令调用格式：test_adc
 * 程序功能：通过 ADC 设备采样电压值并转换为数值。
 * 示例代码参考电压为 1.5V, 分辨率为 12 位。
 */

#include <rtthread.h>
#include <rtdevice.h>

#define ADC_DEV_NAME "adc1" /* ADC 设备名称 */
#define ADC_DEV_CHANNEL 1 /* ADC 通道 */

static void test_adc()
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;

    rt_kprintf("Running ADC test!\n");

    /* 查找设备 */
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
	    rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
	    return;
    }

    /* 使能设备 */
    ret = rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);
    /* 读取采样值 */
    value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
    rt_kprintf("Read channel value is :%d\n", value);

    /* 转换为对应电压值,1.5V 对应 12 位最大值 4096, 数据精度乘以 100 保留 2 位小数 */
    vol = value * 150 / 4096;
    rt_kprintf("Calculated voltage is: %d.%02dV\n", vol / 100, vol % 100);

    /* 关闭通道 */
    rt_adc_disable(adc_dev, ADC_DEV_CHANNEL);

    rt_kprintf("Test Done!\n");

    return;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(test_adc, "adc voltage convert sample");
