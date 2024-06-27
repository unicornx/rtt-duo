# rtt-duo

<!-- TOC -->

- [rtt-duo](#rtt-duo)
	- [下载仓库](#下载仓库)
	- [下载和配置编译工具链](#下载和配置编译工具链)
	- [配置和编译](#配置和编译)
	- [运行](#运行)

<!-- /TOC -->

## 下载仓库

```bash
cd $YOUR_WORKSPACE
git clone git@github.com:unicornx/rt-thread.git
cd rt-thread
git checkout rtt-duo-v5.1.0
git submodule init
git submodule update
```

测试用例的代码在 `$YOUR_WORKSPACE/rt-thread/bsp/cvitek/cv18xx_risc-v/applications/test/` 下。

注意，如果你访问 github 比较慢，也可以从本仓库在 gitee 的 mirror 下载，地址是：`git@gitee.com:unicornx/rt-thread.git`。

## 下载和配置编译工具链

参考 `$YOUR_WORKSPACE/rt-thread/bsp/cvitek/cv18xx_risc-v/README.md`

我们使用标准版 RT-Thread，下载工具链 `riscv64-unknown-elf-gcc` 下载地址  [https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz](https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz)

```bash
cd $YOUR_WORKSPACE
wget https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz
tar xzf Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz
```

因为主线中默认 GCC 的路径在 `/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1/bin`，所以我们为了方便，可以将下载的工具链解压后移动到 `/opt` 下去

```bash
sudo mv Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1 /opt/
```

## 配置和编译

先编译小核 RT-Thread，生成 fip.bin，具体编译操作步骤参考 `$YOUR_WORKSPACE/rt-thread/bsp/cvitek/cv18xx_risc-v/README.md`。

```bash
cd $YOUR_WORKSPACE/rt-thread/bsp/cvitek/c906_little
scons --menuconfig # 假设我们编译 duo，则需要选择 Board Type 为 milkv-duo，默认为 milkv-duo256m
scons
```

再编译大核 RT-Thread, 生成 boot.sd，具体编译操作步骤参考 `$YOUR_WORKSPACE/rt-thread/bsp/cvitek/cv18xx_risc-v/README.md`。

```bash
cd $YOUR_WORKSPACE/rt-thread/bsp/cvitek/cv18xx_risc-v
scons --menuconfig # 假设我们编译 duo，则需要选择 Board Type 为 milkv-duo，默认为 milkv-duo256m
scons
```

最终生成的 fip.bin 和 boot.sd 都在 `$YOUR_WORKSPACE/rt-thread/bsp/cvitek/output/milkv-duo` 下。

**注意** 我们虽然只关心大核运行的 RT-Thread，但目前仍然需要同时构建两者，特别是需要构建出 fip.bin，只有 boot.sd 是无法启动的。

## 运行

将 `fip.bin` 和 `boot.sd` 复制到 sd-card 的第一个 FAT32 分区。

如果要查看大核的串口输出，串口连接 duo 的 GP12/GP13。





