// 参考 https://www.rt-thread.org/document/api/spi_w25q_sample_8c-example.html

/*
 * 程序清单：这是一个 SPI 设备使用例程
 * 例程导出了 test_spi 命令到控制终端
 * 命令调用格式：test_spi 
 * 命令解释：
 * 程序功能：
 */

#include <rtthread.h>
#include <rtdevice.h>

#define BUS_NAME     "spi2"
#define SPI_NAME     "spi20"

static struct rt_spi_device *spi_dev = RT_NULL;

/* spi loopback mode test case */
static int spi_sample(int argc, char *argv[])
{
    rt_err_t ret;
    struct rt_spi_configuration cfg;
    rt_uint8_t t_buf[8] = {1, 2, 3, 4, 5, 6, 7, 8}, r_buf[8];
    int i = 0;
    static struct rt_spi_message msg1;

#if 0
    if (argc != 9)
    {
        rt_kprintf("Please Usage:\n");
        rt_kprintf("spi_sample 1 2 3 4 5 6 7 8\n");
        return -RT_ERROR;
    }

    for (i = 0; i < 8; i++)
    {
        t_buf[i] = atoi(argv[i+1]);
    }
#endif

    /* attach the device to spi bus*/
    spi_dev = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
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

    msg1.send_buf   = &t_buf;
    msg1.recv_buf   = &r_buf;
    msg1.length     = sizeof(t_buf);
    msg1.cs_take    = 1;
    msg1.cs_release = 0;
    msg1.next       = RT_NULL;

    rt_spi_transfer_message(spi_dev, &msg1);

    rt_kprintf("spi rbuf : ");
    for (i = 0; i < sizeof(t_buf); i++)
    {
        rt_kprintf("%x ", r_buf[i]);
    }

    rt_kprintf("\nspi loopback mode test over!\n");

    return RT_EOK;
}
MSH_CMD_EXPORT(spi_sample, spi loopback test);
