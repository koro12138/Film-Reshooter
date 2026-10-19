# 验证记录（2026-10-19）

## 已执行

| 检查 | 结果 |
| --- | --- |
| 合并版 Windows 回归 | 113项通过，78.077秒，不含未安装的可选NVIDIA硬件测试 |
| 最终公共/水印/平台分派回归 | 40项通过，9.219秒 |
| 水印全版式前后对照 | 752组与最新Windows修订版逐像素一致 |
| 实际Windows界面 | 导入示例、GPU预览、截图成功 |
| macOS设置界面模拟 | 在Windows检查平台标签、CoreML持久设置、无NVIDIA选项、导出时禁用开关 |
| HDR合并C源码 | Windows x64/Zig重新编译；高光保护及float16打包与参考逐像素一致 |
| 开发环境doctor | 本机依赖和必要文件无缺项 |

具体摘要见 validation/。最初一条新增测试使用了错误的PreviewWorker参数顺序，测试夹具已更正；最终回归通过。模拟平台分派不代表运行过Apple GPU。

## 未执行

- 没有在Mac实机编译此合并版、运行Metal/CoreML、生成APP/DMG或验证签名/公证。
- 未执行远程GitHub Actions。
- 未重新构建Windows EXE；本轮交付为源码。此前已发布的Windows包不是本次跨平台合并构建。
- NVIDIA专用运行库未安装到此仓库，因此没有把原Windows发布包的CUDA实测当成本轮结果。

## Mac实机复测

```bash
python dev.py native
python dev.py doctor
python dev.py test
python tools/validate_macos.py --json macos-validation.json
python dev.py build
python tools/validate_macos.py --app "dist/Film Reshooter.app" --json macos-bundle-validation.json
```

还应覆盖多照片/多滤镜导出、M9 CoreML开关、预览与导出交替、RAW、PNG16/TIFF16/Ultra HDR、EXIF和徕卡5左右版式。CoreML差异单独记录，不把其近似结果视作精确CPU等价。
