# 多维度正交链表八叉树

## 适用于 Python 的扩展。

此项目使用 `C++` 编写。如果需要适用于 Python 的扩展，请参与 [`orthogonal_linked_octree_for_python`](../orthogonal_linked_octree_for_python)。

## 编译

此项目使用 cmake 作为组织项目代码结构的工具，因此，你的开发环境中必须包含 cmake，且版本不低于3.8。

### 允许 AVX2 或 AVX512F

此项目部分方法用到了 AVX2 或 AVX512F 指令。如果你想启用此指令，请在编译选项中加入：
```
-DENABLE_AVX2=1
```
或
```
-DENABLE_AVX512F=1
```
具体启用哪种指令，请根据使用环境 CPU 支持情况而定。如果使用不支持的指令，则编译时会出错。