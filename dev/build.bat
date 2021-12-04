@echo off

:: Compile
::cd devkit
::sdcc -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 _sms_manager.c
::sdcc -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 _snd_manager.c
::cd ..

cd engine
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 asm_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 actor_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 audio_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 board_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 boss_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 collision_manager.c
::::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 command_manager.c
::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 content_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 enemy_manager.c
::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 enum_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 font_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 function_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 gamer_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 global_manager.c
::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 hack_manager.c
::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 input_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 level_manager.c
::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 locale_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 main_manager.c
::::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 mask_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 memo_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 move_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 option_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 score_manager.c
::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 screen_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 sprite_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 state_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 storage_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 tile_manager.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 timer_manager.c
cd ..

cd screen
::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 none_screen.c
::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 splash_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 begin_screen.c
sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 title_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 start_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 init_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 load_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 ready_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 play_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 pass_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 dead_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 cont_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 over_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 prep_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 fight_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 boss_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 beat_screen.c
::::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 option_screen.c
::sdcc --debug -c -mz80 --opt-code-size --peep-file ..\peep-rules.txt --std-c99 test_screen.c
cd ..

:: echo Build main
sdcc -c -mz80 --opt-code-size --peep-file peep-rules.txt --std-c99 main.c

sdcc -o output.ihx -mz80 --no-std-crt0 --data-loc 0xC000 ^
..\crt0\crt0_sms.rel main.rel ^
-Wl-b_BANK2=0x8000  -Wl-b_BANK3=0x8000 ^
..\lib\SMSlib.lib ^
..\lib\PSGlib.rel ^
banks\bank2.rel  banks\bank3.rel ^
devkit\_sms_manager.rel devkit\_snd_manager.rel ^
engine\content_manager.rel engine\enum_manager.rel ^
engine\font_manager.rel engine\hack_manager.rel ^
engine\input_manager.rel engine\locale_manager.rel ^
engine\screen_manager.rel ^
screen\none_screen.rel screen\splash_screen.rel screen\title_screen.rel ^
screen\test_screen.rel

:: Execute
ihx2sms output.ihx output.sms


:: Delete
if exist "*.ihx" del "*.ihx" > nul; if exist "*.lk"  del "*.lk"  > nul; if exist "*.asm" del "*.asm" > nul
if exist "*.noi" del "*.noi" > nul; if exist "*.sym" del "*.sym" > nul; if exist "*.lst" del "*.lst" > nul


java -jar C:\SEGA\Emulicious\Emulicious.jar output.sms
::output.sms