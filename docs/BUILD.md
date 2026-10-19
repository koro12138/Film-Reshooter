# 构建说明

Windows 建议 Python 3.11 x64；macOS 建议 Python 3.13 arm64。使用对应平台独立的虚拟环境。

## Windows

```powershell
py -3.11 -m venv .venv
.venv\Scripts\python.exe -m pip install -r requirements-windows.txt -r requirements-dev.txt
.venv\Scripts\python.exe dev.py doctor
.venv\Scripts\python.exe dev.py test
.venv\Scripts\python.exe dev.py build --edition standard
```

输出为 `dist/FilmReshooter-v1.0.0-Standard/FilmReshooter.exe`。分发整个目录，并保留第三方许可。

全量版先运行 `python tools/install_nvidia.py`，再运行 `python dev.py build --edition full`，输出位于 `dist/FilmReshooter-v1.0.0-Full/`。可选脚本安装项目局部 EP，不替换全局 DirectML。

重建 C 库使用 Zig 0.13.0：`python dev.py native --zig C:\tools\zig\zig.exe`。

## macOS arm64

```bash
xcode-select --install
python3 -m venv .venv
.venv/bin/python -m pip install -r requirements-macos.txt -r requirements-dev.txt
.venv/bin/python dev.py native
.venv/bin/python dev.py doctor
.venv/bin/python dev.py test
.venv/bin/python dev.py build
open "dist/Film Reshooter.app"
```

`native` 以当前 Xcode SDK、clang 和 `-ffp-contract=off` 重建六个 dylib；目标 macOS 14.0 / arm64。`CameraLook-macos.spec` 的产品名为 Film Reshooter，排除 Windows DLL 和 NVIDIA 专用组件。

本次 Windows 环境无法生成或实测新 APP/DMG。发布前须在 Mac 完成原生编译、Metal 对照、M3/M9 和高位深实际导出测试，并按发布方式签名/公证。仓库不含 Apple 开发者证书。

## 验证

`python dev.py test --portable` 只测试公共逻辑。Windows 默认完整测试需要 OpenGL/DirectML；已安装 NVIDIA 可选组件时另运行 CUDA resident 测试。macOS 默认测试公共逻辑及 `metal_regression.py`，不是 Windows 完整测试的替代证明。

`python dev.py verify` 校验交付快照。修改源码或重建二进制后出现 changed 属于预期，不能沿用旧测试结果宣称新版本已通过。

## macOS最低版本修订

原安装指南写macOS 13+，但本仓库固定依赖的官方wheel标签中，PySide6-Essentials 6.12.0 / shiboken6 6.12.0与onnxruntime 1.24.4都要求macOS 14.0+。因此合并版的文档、clang部署目标、APP最低系统版本和doctor检查统一为14+。如需支持13，需要另做依赖降版及实机验证，不能仅修改plist。

来源：[Qt/PySide发布文件](https://pypi.org/project/PySide6-Essentials/6.12.0/#files)、[ONNX Runtime发布文件](https://pypi.org/project/onnxruntime/1.24.4/#files)。元数据摘要见validation/dependency_metadata.json。
