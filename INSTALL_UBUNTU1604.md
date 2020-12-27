# Ubuntu 16.04

1. cmake

Ubuntu 16.04 环境下 cmake 的默认版本为 3.5.1。此版本不符合此项目的最低版本要求 3.8。因此需要自行准备新版本。

您可以在 [cmake-3.17.5](https://github.com/Kitware/CMake/releases/tag/v3.17.5) 中选择适合您的操作系统的版本安装即可。安装完成后在集成开发环境中使用新版 cmake。

2. gcc

Ubuntu 16.04 环境下 gcc 的默认版本 5.4.0。此版本不支持 C++17。因此需要自行准备新版本。您需要安装 9.1.0 或更新版本的 gcc。

以 [gcc-10.2.0](https://github.com/gcc-mirror/gcc/releases/tag/releases%2Fgcc-10.2.0) 为例说明安装过程：

下载代码包：

```
$ wget https://github.com/gcc-mirror/gcc/archive/releases/gcc-10.2.0.tar.gz
```

解压：

```
$ tar -zxf gcc-10.2.0.tar.gz
```

切换到解压后的文件夹：
```
$ cd gcc-releases-gcc-10.2.0
```

下载依赖项：
```
$ contrib/download_prerequisites
```

> 此步骤可能会花费比较长的时间。

新建一个专用于 build 的文件夹，并配置和编译：
```
$ mkdir build
$ cd build
$ ../configure  -enable-checking=release -enable-languages=c,c++ -disable-multilib
$ make -j 8
$ sudo make install
```

> 因为我们不需要 32 位开发环境，所以禁用了多重库。
