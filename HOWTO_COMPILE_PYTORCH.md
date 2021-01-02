# 如何编译 Pytorch

# 从代码仓库克隆

```
git clone --recursive https://github.com/pytorch/pytorch
```

然后切换到 pytorch 目录中。接下来的操作区分不同操作系统，详情如下：

# Ubuntu 20.04

参照[官方](https://github.com/pytorch/pytorch)最新说明即可。

# Ubuntu 18.04

Ubuntu 18.04 下 llvm 默认版本为 6.0。而编译 numba 需要 llvm 9.0 或 10.0。因此需要将 llvm 6.0 删除，并安装 llvm 9.0 或 10.0 及其开发包。

```
$ sudo apt remove --purge llvm -y
$ sudo apt update
$ sudo apt install llvm-10 llvm-10-dev -y
```

其余参照官方最新说明即可。

# Ubuntu 16.04

Ubuntu 16.04 官方安装源不包括 llvm 9.0 或 llvm 10.0，因此需要参照[llvm 官方说明](https://apt.llvm.org/)来安装。

注意！在添加安装源之前，请先下载 llvm 安装源的 GPG Key：
```
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
```

然后再添加安装源：
```
deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-10 main
deb-src http://apt.llvm.org/xenial/ llvm-toolchain-xenial-10 main
```

最后再按照 Ubuntu 18.04 的说明安装 llvm。

# Windows 10 Pro 20H2 x64

参照[官方](https://github.com/pytorch/pytorch)最新说明安装，但要在最后一步前主动禁用`ninja`：
```
set USE_NINJA=0
```
然后再运行安装命令。

注意！Windows 下的 numpy 1.19.4 与操作系统有兼容性问题，请使用 1.19.3 版。

> Windows 下的编译时间比 Ubuntu 下长得多。务请耐心等待。

# 通用

## 创建虚拟环境
```
python3 -m venv venv3x
```

> 请将 `venv3x` 替换为具体版本。例如，安装的是 Python 3.8，则替换为`venv38`。

按照[官方](https://github.com/pytorch/pytorch)在虚拟环境中安装所需代码包。然后再运行编译：
```
python setup.py install
```
> 在 Python 2 和 Python 3 共存的环境则需要使用 `python3`。
