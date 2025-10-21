@echo off
echo 正在测试ATM Windows GUI系统...

echo.
echo 编译程序...
gcc -o atm_gui.exe *.c -lgdi32 -luser32 -lcomctl32 -mwindows

if %errorlevel% equ 0 (
    echo 编译成功！
    echo.
    echo 程序信息：
    echo - 可执行文件: atm_gui.exe
    echo - 文件大小: 
    dir atm_gui.exe | findstr atm_gui.exe
    echo.
    echo 测试账户信息：
    echo - 卡号: 622202000001-622202000025
    echo - 密码: 123456
    echo.
    echo 是否立即运行程序？(y/n)
    set /p choice=
    if /i "%choice%"=="y" (
        echo 启动程序...
        atm_gui.exe
    )
) else (
    echo 编译失败！
    pause
)

pause
