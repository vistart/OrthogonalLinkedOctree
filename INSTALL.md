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

> Ubuntu 16.04 的环境准备请参照[此文档](INSTALL_UBUNTU1604.md)。

> 其它 Linux 发行版尚未测试。不保证在除 Ubuntu 以外的 Linux 发行版中可用。

## 代码

使用以下命令克隆项目仓库：

```
$ git clone https://github.com/vistart/OrthogonalLinkedOctree
```

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

> 我们推荐你在 64 位系统中使用 64 位代码包，以获得更好的性能。

安装完成后，需要将 `vcpkg` 管理的代码包集成到我们的项目中，以便我们能找到它：
```
$ vcpkg/vcpkg integrate install
```
执行完此命令会告知您编译时需要附加的选项，您会看到类似如下提示：
```
Applied user-wide integration for this vcpkg root.

CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=<Your VCPKG Directory>/scripts/buildsystems/vcpkg.cmake"
```
您需要做的就是将这个编译条件添加到您的编译器或集成开发环境中。Visual Studio 2019 一般会自动寻找 vcpkg 配置，无须特别设置。CLion 则需要在`File` | `Settings` | `Build, Execution, Deployment` | `CMake` 中为每个配置文件的 `CMake options` 添加上述选项。

例如，我使用的编译选项为：
```
"-DCMAKE_TOOLCHAIN_FILE=/home/vistart/Projects/vcpkg/scripts/buildsystems/vcpkg.cmake"
```
如果您也选择按照我的路径放置 vcpkg 及管理的代码包，则不需要做任何改动。

已经下载的代码包放置在
```
$ vcpkg/downloads
```
目录下。您可以将此文件夹下的所有文件（不包括子文件夹）全部备份，以供移植使用，可以明显节省下载等待时间。

### 安装 [Python](https://python.org)

此项目还用到了 Python，因此需要您自行安装 [Python 解释器](https://python.org)，且将 Python 的引用和库目录添加到环境变量的 `Path` 中。

在 Windows 中，以 Python 3.9.1 为例，默认情况下，Python 的引用和库目录地址分别为：
- `C:\Program Files\Python39\include`
- `C:\Program Files\Python39\libs`

> 您需要在使用 Visual Studio 2019 打开或编译项目前将上述目录加入到系统变量的 `Path` 变量中。在打开和编译时修改任何环境变量都不起效。

安装时，需要勾选：
- `Add Python 3.9 to PATH`
- `Install for all Users`
- `Precompile standard library`
- `Download debugging symbols`
- `Download debug binaries (requires VS 2017 or later)`

如果您不勾选最后三项，则无法编译调试。

在 Ubuntu 中则沿用安装 `pybind` 时自动下载的 `Python`，无须单独处理。但 `pybind` 依赖的 `Python` 版本通常与操作系统默认的版本不相同。如 Ubuntu 20.04 的默认 `Python` 版本为 `3.8.5`，而目前 `pybind` 依赖的 `Python` 版本为 `3.9.0`，二者并不匹配。引用不同版本 `Python` 编译的代码版不能互通。为了能保证二者相同，则需要在编译时通过指定 Python 版本实现。

以 CLion 和 Ubuntu 20.04 为例，在 CLion 中，选择 `File` | `Settings` | `Build, Execution, Deplyment` | `CMake` 中为每个配置文件中的 `CMake options` 添加：
```
-DPYTHON_EXECUTABLE=/usr/bin/python3
```
直接添加 Python 可执行文件后，`pybind11` 会自动寻找当前 Python 版本和对应的引用和库目录。

> Python 可执行路径请根据自己的实际情况修改。