SET PATH=E:\keil5\ARM\ARMCC\Bin;C:\Python38\Scripts\;C:\Python38\;D:\Python38\Scripts\;D:\Python38\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;D:\Develop\nodejs\;D:\ServerTool\Git\cmd;C:\Program Files\Microsoft SQL Server\130\Tools\Binn\;C:\Program Files\dotnet\;D:\matlab 2018b\runtime\win64;D:\matlab 2018b\bin;C:\Program Files\TortoiseGit\bin;E:\mingw64\mingw64\bin;D:\微信web开发者工具\dll;D:\mingw64\bin;D:\Xshell\;D:\pandoc\;C:\Program Files (x86)\CodeSourcery\Sourcery_CodeBench_Lite_for_ARM_GNU_Linux\bin;C:\Users\li007\AppData\Local\Microsoft\WindowsApps;D:\Develop\nodejs\node_global;D:\Develop\nodejs;D:\Develop\nodejs\node_modules\npm;D:\altera\ModelSim_10.5se\win64;D:\altera\13.1\modelsim_ase\win32aloem;D:\altera\13.1\modelsim_ae\win32aloem;C:\Python38\Scripts\;C:\Python38;C:\mingw64\bin;C:\Users\li007\AppData\Local\gitkraken\bin;C:\Users\li007\AppData\Local\Programs\Microsoft VS Code\bin;C:\Infineon\LauncherService;D:\QQGameTempest\Hall.57821\
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\main.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_it.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\system_stm32f10x.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\lcd.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\delay.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\sys.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\usart.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\core_cm3.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmAsm" --Via "..\obj\startup_stm32f10x_hd._ia"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\misc.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_gpio.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_rcc.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_usart.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmLink" --Via "..\OBJ\OLED.lnp"
"E:\keil5\ARM\ARMCC\Bin\fromelf.exe" "..\OBJ\OLED.axf" --i32combined --output "..\OBJ\OLED.hex"
