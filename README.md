# 正交链表八叉树

此项目用于实现“多维度正交链表”。

此项目分为以下若干个模块

- file_format
  - point_cloud_base_presentation (点云的抽象表示)
  - plyfile (Ply 文件格式表示的点云)
- orthogonal_linked
  - orthogonal_linked_list (多维度正交链表)
  - orthogonal_linked_octree (三维正交链表八叉树)

## [point_cloud_base_presentation](file_format/point_cloud_base_presentation)

此项目负责实现“点云的抽象表示”。考虑到点云有诸多流行文件格式，为了屏蔽不同文件格式之间的差异且方便点云处理，需要“点云的抽象表示”。

> 此项目的详细介绍请点击标题的链接查看。

## [plyfile](file_format/plyfile)

此项目负责实现“Ply 文件格式表示的点云”。此项目继承自 `point_cloud_base_presentation`。此项目没有使用官方给出的 ply文件格式 处理源代码，因其编写年代较早，尚不支持 C++。此项目使用 C++ 17 重新编写。

> 此项目的详细介绍请点击标题的链接查看。

## [orthogonal_linked_list](orthogonal_linked/orthogonal_linked_list)

此项目负责实现“多维度正交链表”。“正交”指的是任意两个维度之间互不相干，谓之曰“正交”。在中文领域还有一个广泛流行的词汇——“十字链表”。“多维度正交链表”指的是正交空间的维度可以是任意的。此项目支持最少二维空间，到最多十六维空间。更高维度的空间同样支持，但效率会大打折扣，而现实中使用也很少，故实际使用维度不超过八维空间。

> 此项目的详细介绍请点击标题的链接查看。

## [orthogonal_linked_octree](orthogonal_linked/orthogonal_linked_octree)

此项目负责实现“三维正交链表八叉树”。此项目继承自 `orthogonal_linked_list`，是“多维度正交链表”项目在三维体素化表示点云空间领域的特化。

> 此项目的详细介绍请点击标题的链接查看。

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

在 Ubuntu 中则沿用安装 `pybind` 时自动下载的 `Python`，无须单独处理。

# 测试

TBD

# 联系我

i#vistart.me（请把“#”替换为“@”）

# 捐助

如果此项目对您有帮助，请给予我 USD 1.59 或 RMB 9.99 的 [捐助](https://paypal.me/vistart)。请捐助时留下您的姓名或昵称，以便鸣谢。
