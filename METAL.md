# Metal / CoreML 后端

Metal 对应 `metal_renderer.py` 与 `tools/metal_tonefilm.m`，负责 LUT/胶片、输入降噪和 M3 Monopan。M9 网络通过 ONNX Runtime CoreML EP 调度，后处理保留原生 C。

公共渲染入口在 macOS 选择 Metal，Windows 继续 OpenGL；Metal 不可用时自动模式回退 CPU。CoreML 可在设置中关闭，CPU 推理保留作精确参考。

Metal 原生封装使用进程级设备状态。合并版用整张照片的锁保护预览/导出调用，并在实例切换时失效照片、LUT 和缓冲区缓存，防止状态串用。CoreML 开关也纳入预览缓存身份。

构建及开发测试命令见 [构建说明](docs/BUILD.md)。
