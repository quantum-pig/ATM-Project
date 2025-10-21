# PowerShell版本的构建脚本
# 解决Windows CMD乱码问题

# 设置控制台编码
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
[Console]::InputEncoding = [System.Text.Encoding]::UTF8

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "      ATM Windows原生版本构建器" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""

# 检查必要的工具
Write-Host "检查构建环境..." -ForegroundColor Yellow

$gccPath = Get-Command gcc -ErrorAction SilentlyContinue
if (-not $gccPath) {
    Write-Host "❌ 未找到GCC编译器" -ForegroundColor Red
    Write-Host ""
    Write-Host "请安装MinGW-w64或MSYS2:" -ForegroundColor Yellow
    Write-Host "  https://www.msys2.org/" -ForegroundColor Cyan
    Write-Host "  https://www.mingw-w64.org/" -ForegroundColor Cyan
    Write-Host ""
    Read-Host "按回车键退出"
    exit 1
}
Write-Host "✅ GCC编译器已找到" -ForegroundColor Green

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "           开始构建过程" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""

# 清理之前的构建
Write-Host "🧹 清理之前的构建文件..." -ForegroundColor Yellow
if (Test-Path "*.exe") { Remove-Item "*.exe" -Force }
if (Test-Path "*.o") { Remove-Item "*.o" -Force }
Write-Host "✅ 清理完成" -ForegroundColor Green

Write-Host ""
Write-Host "🔨 开始编译Windows原生版本..." -ForegroundColor Yellow

# 编译所有源文件
$sourceFiles = @(
    "main.c", "win_main.c", "win_login.c", "win_transaction.c", "win_deposit.c",
    "account_management.c", "encryption.c", "file_operations.c", "transaction.c", "utils.c"
)

foreach ($file in $sourceFiles) {
    if (Test-Path $file) {
        Write-Host "📝 编译 $file..." -ForegroundColor Cyan
        $objectFile = $file.Replace(".c", ".o")
        gcc -Wall -Wextra -std=c99 -g -c $file -o $objectFile
        if ($LASTEXITCODE -ne 0) {
            Write-Host "❌ 编译 $file 失败" -ForegroundColor Red
            Read-Host "按回车键退出"
            exit 1
        }
    }
}

Write-Host "✅ 源文件编译完成" -ForegroundColor Green

Write-Host ""
Write-Host "🔗 链接生成可执行文件..." -ForegroundColor Yellow

# 链接生成可执行文件
gcc main.o win_main.o win_login.o win_transaction.o win_deposit.o account_management.o encryption.o file_operations.o transaction.o utils.o -o atm_windows_native.exe -lcomctl32 -lgdi32 -luser32 -lkernel32

if ($LASTEXITCODE -ne 0) {
    Write-Host "❌ 链接失败" -ForegroundColor Red
    Read-Host "按回车键退出"
    exit 1
}

Write-Host "✅ 链接完成" -ForegroundColor Green

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "           构建完成" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""

Write-Host "🎉 Windows原生版本构建成功！" -ForegroundColor Green
Write-Host ""

if (Test-Path "atm_windows_native.exe") {
    $fileInfo = Get-Item "atm_windows_native.exe"
    Write-Host "📁 生成的文件:" -ForegroundColor Yellow
    Write-Host "✅ atm_windows_native.exe (Windows原生版本)" -ForegroundColor Green
    Write-Host ""
    Write-Host "📊 文件信息:" -ForegroundColor Yellow
    Write-Host "   大小: $($fileInfo.Length) 字节" -ForegroundColor Cyan
    Write-Host "   类型: Windows原生可执行文件" -ForegroundColor Cyan
    Write-Host "   依赖: 仅需Windows系统库" -ForegroundColor Cyan
} else {
    Write-Host "❌ atm_windows_native.exe (未生成)" -ForegroundColor Red
}

Write-Host ""
Write-Host "🚀 运行方式:" -ForegroundColor Yellow
Write-Host "  双击 atm_windows_native.exe 直接运行" -ForegroundColor Cyan
Write-Host "  或使用 run_windows.ps1 启动脚本" -ForegroundColor Cyan
Write-Host ""

Write-Host "📋 测试账户:" -ForegroundColor Yellow
Write-Host "  卡号: 622202000001-622202000025" -ForegroundColor Cyan
Write-Host "  密码: 123456" -ForegroundColor Cyan
Write-Host ""

Write-Host "✨ 优势特色:" -ForegroundColor Yellow
Write-Host "  1. 真正的Windows原生应用" -ForegroundColor Cyan
Write-Host "  2. 无需额外依赖库" -ForegroundColor Cyan
Write-Host "  3. 使用Windows API界面" -ForegroundColor Cyan
Write-Host "  4. 完全兼容Windows系统" -ForegroundColor Cyan
Write-Host ""

Read-Host "按回车键退出"
