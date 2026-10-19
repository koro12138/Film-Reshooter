# Windows / macOS 源码合并记录

日期：2026-10-19，产品版本：v1.0.0。

## 输入

- 最新 Windows：徕卡5修订版源码，包含新增信息90度方向修复、机型缩小淡化并排到曝光上方。
- 用户提供的 macOS v1.0.0 源码：Metal、CoreML、六个 dylib、原生编译与安装资料。

## 合并方式

采用一套公共界面、信息控制和导出流程，通过平台分派选择渲染后端，没有把两套应用简单并排打包。

- 保留 Windows 的预览服务、会话/风格缓存、内存预算流水线、高位深处理、模型校验和 NVIDIA 手动实验策略。
- 共享最新 `watermark_info.py` / `original_marks.py`。没有用 Mac 原包的旧水印实现覆盖去重、信息开关或徕卡5修复；保留85套/188版式。
- 合入 Metal LUT/胶片、输入降噪与 Monopan；M9 合入 CoreML 提供程序选择及本机模型缓存。
- 原生库严格按平台选择 DLL/dylib，不会因缺库去尝试另一平台的二进制。M3 同时支持当前 step ABI 和输入 Mac dylib 的 RGB ABI；HDR 同时兼容旧采样版本、Mac 高光保护与当前打包接口。
- macOS 字体使用系统中文字体，设置页展示 Metal/CoreML、CoreML 开关与启动预编译；Windows 继续显示 DirectML。
- 修正 Metal 预览/导出多个实例共用全局设备状态的问题：整张照片加锁，切换实例时失效驻留照片、LUT、容量与 Monopan 缓存。
- CoreML/Metal 选择纳入预览缓存身份。关闭 CoreML 后不会复用先前加速结果或旧提供程序实例；批量导出时禁用相关开关。
- 预编译失败记录错误，不写虚假的成功标记。新建 macOS 自检入口，避免调用 Windows 专属验收断言；实机测试尚未执行。

## 仓库整理

排除大型可选 NVIDIA 运行库、EXE/APP/DMG、缓存及历史打包/本机路径脚本。保留必要模型、LUT、水印、原生代码、平台构建配置、安装脚本与第三方许可。添加 README、GitHub About 文案、安装/构建/发布指南、CI 配置与实际 Windows 截图。

Mac 原指南中的67套模板、旧校验码、固定测速和 GPU+ANE 标识说明不作为合并版承诺。原 PDF 保留在 docs/reference/，当前步骤见 INSTALL.md。

修改与来源文件身份记录在 validation/merge_manifest.json。历史输入包的权利归属及第三方声明保留，未增加全仓库统一许可证。未创建远程仓库或公开上传。

## macOS最低版本修订

原安装指南写macOS 13+，但本仓库固定依赖的官方wheel标签中，PySide6-Essentials 6.12.0 / shiboken6 6.12.0与onnxruntime 1.24.4都要求macOS 14.0+。因此合并版的文档、clang部署目标、APP最低系统版本和doctor检查统一为14+。如需支持13，需要另做依赖降版及实机验证，不能仅修改plist。

来源：[Qt/PySide发布文件](https://pypi.org/project/PySide6-Essentials/6.12.0/#files)、[ONNX Runtime发布文件](https://pypi.org/project/onnxruntime/1.24.4/#files)。元数据摘要见validation/dependency_metadata.json。
