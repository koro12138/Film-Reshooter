# GitHub 发布准备

建议仓库名：`FilmReshooter`。

About 简介：

> Windows / macOS 本地批量胶片滤镜与 EXIF 水印工具，支持 CPU/GPU 加速、M3/M9、RAW 和高位深导出。

英文简介：

> Local batch film filters and EXIF watermarks for Windows and Apple Silicon Mac, with CPU/GPU acceleration and high-bit-depth export.

Topics：`photography`、`image-processing`、`film-simulation`、`watermark`、`pyside6`、`directml`、`metal`、`coreml`。

## 上传源码

解压后将源码目录内容作为仓库根目录，替换下方自己的账号名：

```bash
git init -b main
git add .
git commit -m "Merge Windows and macOS source for Film Reshooter v1.0.0"
git remote add origin https://github.com/YOUR_ACCOUNT/FilmReshooter.git
git push -u origin main
```

若已有仓库，使用其现有分支管理，不要覆盖历史。本次交付没有创建远程仓库或公开上传。

应用 ZIP/DMG 放在 Releases，并附各自 SHA256；源码不放 EXE、APP、构建缓存和个人照片。

GitHub [单文件限制](https://docs.github.com/en/repositories/working-with-files/managing-large-files/about-large-files-on-github)阻止大于 100 MiB 的普通 Git 文件。大型可选 NVIDIA 运行库已排除，保留安装脚本和忽略规则；不要强制提交生成的 `assets/nvidia_runtime/`。

## 权利说明与 CI

原有作者及资源署名、第三方许可均保留。合并不自动赋予第三方资源 MIT/GPL 授权；当前未擅自新增全仓库统一许可证，见 [THIRD_PARTY_NOTICE.md](../THIRD_PARTY_NOTICE.md)。

CI 配置用于运行 Windows/macOS 公共逻辑测试；真实 GPU 渲染需在对应设备上测试。
