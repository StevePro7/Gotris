@echo off

:: Compile
::cd devkit
::sdcc -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 _sms_manager.c
::sdcc -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 _snd_manager.c
::cd ..


:: echo Build main
sdcc -c -mz80 --opt-code-size --peep-file peep-rules.txt --std-c99 main.c

sdcc -o output.ihx -mz80 --no-std-crt0 --data-loc 0xC000 ^
..\crt0\crt0_sms.rel main.rel ^
-Wl-b_BANK2=0x8000  -Wl-b_BANK3=0x800 ^
..\lib\SMSlib.lib ^
..\lib\PSGlib.rel ^
banks\bank2.rel  banks\bank3.rel ^
devkit\_sms_manager.rel devkit\_snd_manager.rel 

:: Execute
ihx2sms output.ihx output.sms


:: Delete
if exist "*.ihx" del "*.ihx" > nul; if exist "*.lk"  del "*.lk"  > nul; if exist "*.asm" del "*.asm" > nul
if exist "*.noi" del "*.noi" > nul; if exist "*.sym" del "*.sym" > nul; if exist "*.lst" del "*.lst" > nul


output.sms