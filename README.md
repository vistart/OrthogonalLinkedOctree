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

安装部分请参阅[此文档](INSTALL.md)。

# 测试

测试部分请参阅具体项目的相关介绍。项目链接为上方项目的标题。

# 联系我

i#vistart.me（请把“#”替换为“@”）

# 捐助

如果此项目对您有帮助，请给予我 USD 1.59 或 RMB 9.99 的 [捐助](https://paypal.me/vistart)。请捐助时留下您的姓名或昵称，以便鸣谢。
