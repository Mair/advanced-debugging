# Debugging

## Prerequisite 
You may need to replace the standard windows driver for the jtag. 
for instructions on how to do this follow https://learnesp32.com/videos/debugging-with-openocd/openocd-software-configuration at 7:44

1. plug in both USB port
2. flash and monitor the application
3. bring up a second idf terminal

## vs code
* For vs code debugging, in the second terminal type `idf.py openocd` 
* click on the debug tab
* click the green arrow to launch

vs code debugging can be very slloowww!

## gdbtui
* create a `gdbinit` file with the following content
```bash
target remote :3333
set remote hardware-watchpoint-limit 2
mon reset halt
flushregs
thb app_main
c
```
then run 
```bash
xtensa-esp32s3-elf-gdb -x gdbinit build/<name of project>.elf
```
(you may need to use full path
)
