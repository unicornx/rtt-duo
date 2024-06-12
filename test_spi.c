// 参考 https://www.rt-thread.org/document/api/spi_w25q_sample_8c-example.html

/*
 * 程序清单：这是一个 SPI 设备使用例程
 * 例程导出了 test_spi 命令到控制终端
 * 命令调用格式: test_spi 
 * 命令解释:
 * 程序功能: 该实验将发送 8 个字节数据，通过 loopback 方式，从 SDO -> SDI
 * 硬件连接: 使用杜邦线连接 duo/duo256 开发板上 SPI2 的 SDO 与 SDI。
 * 编译说明：首先通过 scons --menuconfig 使能 SPI2 并配置 SPI 的管脚
 * ```shell
 * $ scons --menuconfig
 * General Drivers Configuration  --->
 *     [*] Enable SPI 2
 *     (SD1_CLK) spi2 sck pin name
 *     (SD1_CMD) spi2 sdo pin name
 *     (SD1_D0) spi2 sdi pin name
 *     (SD1_D3) spi2 cs pin name
 * ```
 * 配置完成后再运行 scons 进行编译即可
 * 设备上电后正常启动，并进入 msh 命令行，运行 test_spi
 */

#include <rtthread.h>
#include <rtdevice.h>

#define BUS_NAME     "spi2"
#define SPI_NAME     "spi20"

/* attach spi5 device, 该函数只会在系统化初始阶段执行一次 */
static int rt_spi_device_init(void)
{
    rt_err_t ret;
    struct rt_spi_configuration cfg;

    /* attach the device to spi bus*/
    struct rt_spi_device *spi_dev = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_dev != RT_NULL);

    /* initialize the cs pin */
    ret = rt_spi_bus_attach_device(spi_dev, SPI_NAME, BUS_NAME, RT_NULL);
    if (ret != RT_EOK)
    {
        rt_kprintf("%s attach to %s faild, %d", SPI_NAME, BUS_NAME, ret);
        return -RT_ERROR;
    }

    cfg.data_width = 8;
    cfg.mode   = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB | RT_SPI_NO_CS;
    cfg.max_hz = 10 *1000 *1000;
    rt_spi_configure(spi_dev, &cfg);

    return RT_EOK;
}
INIT_APP_EXPORT(rt_spi_device_init);

static int test_spi(void)
{
    rt_uint8_t t_buf[8] = {1, 2, 3, 4, 5, 6, 7, 8}, r_buf[8] = {0};
    int i;
    static struct rt_spi_message msg1;

    struct rt_spi_device *spi_dev = (struct rt_spi_device *)rt_device_find(SPI_NAME);

    if (RT_NULL == spi_dev)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", SPI_NAME);
        return -RT_ERROR;
    }

    msg1.send_buf   = &t_buf;
    msg1.recv_buf   = &r_buf;
    msg1.length     = sizeof(t_buf);
    msg1.cs_take    = 1;
    msg1.cs_release = 0;
    msg1.next       = RT_NULL;

    rt_kprintf("Before transfer, rbuf : ");
    for (i = 0; i < sizeof(t_buf); i++)
    {
        rt_kprintf("%d ", r_buf[i]);
    }
    rt_kprintf("\n");

    rt_spi_transfer_message(spi_dev, &msg1);

    rt_kprintf("After transfer, rbuf : ");
    for (i = 0; i < sizeof(t_buf); i++)
    {
        rt_kprintf("%d ", r_buf[i]);
    }
    rt_kprintf("\n");

    rt_kprintf("SPI loopback test is done!\n");

    return RT_EOK;
}
MSH_CMD_EXPORT(test_spi, spi loopback test);
