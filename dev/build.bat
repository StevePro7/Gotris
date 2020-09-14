@echo off

sdcc -c -mz80 main.c

sdcc -o output.ihx -mz80 --data-loc 0xC000 --no-std-crt0 ..\crt0\crt0_sms.rel main.rel ..\lib\SMSlib.lib

ihx2sms output.ihx output.sms


:: Delete
if exist "*.ihx" del "*.ihx" > nul; if exist "*.lk"  del "*.lk"  > nul; if exist "*.asm" del "*.asm" > nul
if exist "*.noi" del "*.noi" > nul; if exist "*.sym" del "*.sym" > nul; if exist "*.lst" del "*.lst" > nul


output.sms