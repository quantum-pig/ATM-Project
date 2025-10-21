# PowerShell版本的运行脚本
# 解决Windows CMD乱码问题

# 设置控制台编码
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
[Console]::InputEncoding = [System.Text.Encoding]::UTF8

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "        ATM Windows原生版本" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""

# 检查可执行文件是否存在
if (-not (Test-Path "atm_windows_native.exe")) {
    Write-Host "❌ 未找到可执行文件 atm_windows_native.exe" -ForegroundColor Red
    Write-Host ""
    Write-Host "请先运行构建脚本:" -ForegroundColor Yellow
    Write-Host "  build_windows.ps1" -ForegroundColor Cyan
    Write-Host "  或 build_windows.bat" -ForegroundColor Cyan
    Write-Host ""
    Read-Host "按回车键退出"
    exit 1
}

Write-Host "✅ 程序文件检查完成" -ForegroundColor Green
Write-Host ""
Write-Host "🚀 启动ATM Windows原生版本..." -ForegroundColor Yellow
Write-Host ""
Write-Host "测试账户信息:" -ForegroundColor Yellow
Write-Host "  卡号: 622202000001-622202000025" -ForegroundColor Cyan
Write-Host "  密码: 123456" -ForegroundColor Cyan
Write-Host ""
Write-Host "✨ 特色功能:" -ForegroundColor Yellow
Write-Host "  - Windows原生界面" -ForegroundColor Cyan
Write-Host "  - 无需额外依赖" -ForegroundColor Cyan
Write-Host "  - 完整ATM功能" -ForegroundColor Cyan
Write-Host "  - 现代化用户体验" -ForegroundColor Cyan
Write-Host ""

Read-Host "按回车键继续"

# 启动程序
try {
    Start-Process -FilePath "atm_windows_native.exe" -Wait
    Write-Host ""
    Write-Host "✅ 程序正常退出" -ForegroundColor Green
} catch {
    Write-Host ""
    Write-Host "❌ 程序运行出错" -ForegroundColor Red
    Write-Host ""
    Write-Host "可能的解决方案:" -ForegroundColor Yellow
    Write-Host "1. 检查程序文件是否完整" -ForegroundColor Cyan
    Write-Host "2. 重新构建程序" -ForegroundColor Cyan
    Write-Host "3. 检查系统兼容性" -ForegroundColor Cyan
    Write-Host ""
    Read-Host "按回车键退出"
}
