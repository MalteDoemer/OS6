@echo off

setlocal enabledelayedexpansion

set "ROOT_DIR=%~dp0"
set "INCLUDE_DIR=%ROOT_DIR%\src\Headers\"
set "BUILD_DIR=%ROOT_DIR%\obj\"
set "SRC_DIR=%ROOT_DIR%\src\"
set "LINKER_SCRIPT=%ROOT_DIR%\link.ld"
set "CFLAGS= -ggdb -m64 -c -ffreestanding -fno-PIE -nostartfiles -nostdlib -std=c99 -I %INCLUDE_DIR%"
set "ASMFLAGS= -f elf64 -g"

set "ASM=nasm"
set "CC=x86_64-elf-gcc"
set "LINK=x86_64-elf-ld"
set "OBJCOPY=x86_64-elf-objcopy"
set "QEMU=qemu-system-x86_64"

set "LINKED_FILE=%BUILD_DIR%os.o"
set "LOADER=%ROOT_DIR%bin\loader.bin"
set "KERNEL=%ROOT_DIR%bin\kernel.bin"
set "RESULT_FILE=%ROOT_DIR%bin\os.bin"

if "%1"=="" (
    call:all
) else (
    call:%1
)

endlocal 
exit /b

:all
call:clean
call:build
call:link
call:objcopy
goto:eof

:build
    pushd "%SRC_DIR%"

    for /r "." %%i in (*.asm) do (
        %ASM% %ASMFLAGS% "%%~fi" -o "%BUILD_DIR%%%~ni.asm.o" || rem
        if errorlevel 1 call:aboard %ASM%
    )

    for /r "." %%i in (*.c) do (
        %CC% %CFLAGS% "%%~fi" -o "%BUILD_DIR%%%~ni.c.o" || rem
        if errorlevel 1 call:aboard %CC%
    )

    popd
goto:eof

:link
    pushd %BUILD_DIR%
    for /r "." %%i in (*.o) do (
        set "objs=!objs!%%~nxi "
    )
    %LINK% %objs% -T "%LINKER_SCRIPT%" -o "%LINKED_FILE%" || rem
    if errorlevel 1 call:aboard %LINK%
    popd
goto:eof

:objcopy
    %OBJCOPY% -j .loader -O binary "%LINKED_FILE%" "%LOADER%"
    %OBJCOPY% -R .loader -O binary "%LINKED_FILE%" "%KERNEL%"
    copy "%LOADER%" + "%KERNEL%" "%RESULT_FILE%"
    REM %OBJCOPY% -O binary "%LINKED_FILE%" "%RESULT_FILE%"
    if errorlevel 1 call:aboard %OBJCOPY%
goto:eof

:clean
    del /q "%ROOT_DIR%\obj"
    del /q "%ROOT_DIR%\bin"
goto:eof

:run
%QEMU% %RESULT_FILE% || rem
if errorlevel 1 call:aboard %QEMU%
goto:eof

:debug
%QEMU% %RESULT_FILE% -S -gdb tcp::9000 || rem
if errorlevel 1 call:aboard %QEMU%
goto:eof

:aboard
echo.
echo *** task '%1' failed ***
echo.
exit