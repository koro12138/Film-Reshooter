# 安装与首次启动

## Windows

1. 下载应用 ZIP：标准版适合日常使用，全量版另含 NVIDIA 实验后端。
2. 完整解压，保留 `_internal`、资源和许可文件。
3. 双击 `FilmReshooter.exe` 或随包启动脚本。
4. 添加照片，选择滤镜和水印，设置保存位置，点击“批量导出”。

默认使用 DirectML，自动模式可在失败时回退 CPU。NVIDIA 后端需手动选择，首次编译可能需要时间。

## macOS（Apple Silicon）

目标为 macOS 14+、Apple Silicon arm64；当前构建配置不生成 Intel Mac 应用。

1. 打开对应版本的 DMG。
2. 将 `Film Reshooter.app` 拖入 `Applications` / “应用程序”。
3. 复制完成后从“应用程序”启动。
4. 如果无法验证开发者，先核对下载来源和对应 Release 的 SHA256；确认信任后，在“系统设置 → 隐私与安全性”中找到该应用的“仍要打开”，按系统提示确认。

以上采用 Apple 的[单个应用打开流程](https://support.apple.com/en-au/102445)，不需要全局关闭 Gatekeeper。遇到损坏提示时先重新下载并核对该文件自己的校验码，不把这一提示直接等同于“文件一定完好”。

旧指南中的 DMG 文件名、大小和 SHA256 仅对应原安装包，不能用于合并源码或未来发布包。

## 使用

- 流程为“导入 → 选择滤镜 → 配置水印 → 批量导出”。
- 默认输出目录为用户图片目录中的 `FilmReshooter输出`，可自行指定。
- 水印取照片真实元数据，没有 GPS 不会推算位置。
- 预览完成的行略微变灰，成功导出的照片进入“已导出”。
- macOS 可分别控制 M9 CoreML 和启动预编译；不承诺固定首次编译时间，也不把 CoreML 名称当作 ANE 实际运行证明。
- 水印显示开关与 EXIF 保留独立；隐藏水印信息不等于删除文件元数据。

源码运行需要安装 Python 依赖，macOS 重建还需 Xcode Command Line Tools，见 [README](../README.md) 和 [构建说明](BUILD.md)。

用户提供的[原版 macOS 安装指南](reference/macos-install-original-v1.0.0.pdf)作为历史参考保留。模板数量、校验码及验证状态以当前文档为准。
