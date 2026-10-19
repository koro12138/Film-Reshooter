@echo off
setlocal
set "CAMERALOOK_EXPERIMENTAL_NVIDIA="
if exist "%~dp0.venv\Scripts\pythonw.exe" (
 start "" "%~dp0.venv\Scripts\pythonw.exe" "%~dp0app.py" %*
) else (
 py -3.11 "%~dp0app.py" %*
)
