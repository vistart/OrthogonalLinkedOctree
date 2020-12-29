# PyPlyFile

此项目为 Python 提供用于操纵 Ply 文件的类。

## 可用的属性和方法

- `str GetFileFormat()`
- `{True, False} GetIsValid()`

### `str GetFileFormat()`

此方法用于获取文件格式。当前项目下此方法固定返回 `'ply'`。

### `{True, False} GetIsValid()`

此方法用于获取是否正确读取文件。`True` 代表已正确读取；`False` 代表未正确读取。

> 仍然有其他方法待开发。请保持关注。