# 正交链表八叉树

# 安装

## 开发环境

### Windows

- Windows 10 Pro x64 20H2
- Visual Studio 2019 (16.8.3)
  - 需要 NuGet 包管理器
  - 需要 Python 语言支持
  - 需要 Boost.Test 测试适配器（测试时需要）
  - 需要 C++ 用于 Windows 的 CMake 工具
  - 需要英语语言包。
- Windows Subsystem for Linux
  - Ubuntu 20.04

### Ubuntu（仅供在 Windows 下远程操纵）

- Ubuntu 18.04/20.04
  - openssh-server
  - build-essential
  - gcc
  - g++
  - gdb
  - rsync
  - cmake
  - ninja-build
  - make
  - zip
  - pkg-config
- CLion 2020.3

> 其它 Linux 发行版尚未测试。不保证在除 Ubuntu 以外的 Linux 发行版中可用。

## 第三方库

此项目使用到 [Boost](https://www.boost.org) 和 [pybind11](https://github.com/pybind/pybind11)。

以上若干项目均使用 [vcpkg](https://github.com/microsoft/vcpkg) 管理，但此项目并未将需要用到的第三方库置于子项目。因此，在使用前，您需要做一下准备：

### 安装 [vcpkg](https://github.com/microsoft/vcpkg)

在任意目录下克隆 `vcpkg`：

```
$ git clone https://github.com/microsoft/vcpkg
```

克隆后编译 `vcpkg`：
```
$ vcpkg/bootstrap-vcpkg.sh
```

上述命令会下载 `cmake` 和 `ninja-build` 源码并编译。如果你想使用系统自带的 `cmake` 和 `ninja-build`，则可以附加 `-useSystemBinaries`：
```
$ vcpkg/bootstrap-vcpkg.sh -useSystemBinaries
```

然后执行安装 `boost` 和 `pybind` 命令：
```
$ vcpkg/vcpkg install boost pybind11
```

上述命令会安装 32 位应用，而不论当前操作系统是 32 位还是 64 位。如果您当前使用的是 64 位操作系统，也需要 64 位应用，则可以使用以下命令：
```
$ vcpkg/vcpkg install boost:x64-linux pybind11:x64-linux
```

安装完成后，需要将 `vcpkg` 管理的代码包集成到我们的项目中，以便我们能找到它：
```
$ vcpkg/vcpkg integrate install
```
执行完此命令会告知您编译时需要附加的选项，您会看到类似如下提示：
```
Applied user-wide integration for this vcpkg root.

CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=<Your Home Directory>/Projects/vcpkg/scripts/buildsystems/vcpkg.cmake"
```
您需要做的就是将这个编译条件添加到您的编译器或集成开发环境中。

默认的编译选项为：
```
"-DCMAKE_TOOLCHAIN_FILE=~/Projects/vcpkg/scripts/buildsystems/vcpkg.cmake"
```
如果您也选择按照我的路径放置 vcpkg 及管理的代码包，则不需要做任何改动。

已经下载的代码包放置在
```
$ vcpkg/downloads
```
目录下。您可以将此文件夹下的所有文件（不包括子文件夹）全部备份，以供移植使用，可以明显节省下载等待时间。
