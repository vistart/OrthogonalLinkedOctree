# 点云基础表示

此项目用于统一表示点云数据，而避免不同文件格式之间的差异。

## 结构

此项目定义以下概念：

- PointCloud (点云)
  - PointList (点列表)
    - Point (点)
  - PointEdgeList (边列表)
    - PointEdge (边)
  - PointFaceList (面列表)
    - PointFace (面)

以上名称同时也是类名，且均为模板类。名称之间的层次关系代表了包含关系，也即定义上级类时，不仅要指定当前类模板的特化类型，也要指定所有下级类模板的特化类型。

## 应用举例

本项目中包含了应用举例：[plyfile](../plyfile)