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
| **Command**                          | **short cut**     | **Description**                         |
|--------------------------------------|-------------------|-----------------------------------------|
| ***Break-Points***                                                                                 |
| break <number>                       | b 5               | break on line                           |
| break <function name>                | b app_main        | break on function                       |
| info break                           | info b            | list breakpoints                        |
| condition <break number> <condition> | condition 1 foo==5| conditonal breakpoint                   |
| watch <var>                          | watch foo         | break if variable changes               |
| clear <number> <function_name>       | clear 40          | remove breakpoint                       |
|                                                                                                    |
| ***Stepping***                                                                                     |
| next                                 | n                 | step over                               |
| step                                 | s                 | step into                               |
| finish                               | f                 | finish current function                 |
| continue                             | c                 | continue execution                      |
|                                                                                                    |
| ***inspecting***                                                                                   |
| print <var>                          | p foo             | print variable                          |
| print *var                           | p *foo            | print the value (de-refrence)           |
| print &var                           | p &foo            | print the address                       |
| print/<x><d><o>                      | p/x foo           | print as <hex> <decimal <octal>         |
| x                                    | x foo             | print at memmory address                |
| x/<len>x                             | x/16x foo         | print 16 bytes at memory address as hex |
| info locals                          | info locals       | list out local variables                |
|                                                                                                    |
| ***back-trace***                                                                                   |
| backtrace                            | bt                | print stack frame                       |
| frame <number>                       | f 3               | got to frame                            |
|                                                                                                    |
| ***Terminal User Interface***                                                                      |
| tui enable                           | tui enable        | enable terminal user interface          |
| tui disable                          | tui disable       | disable terminal user interface         |
| layout                               | layout            | show layout options                     |
| layout <regs><asm><src>              | layout regs       | tui layout show registers               |
|                                                                                                    |
| ***Misc***                                                                                         |
| list                                 | l                 | list current source code                |
| quit                                 | q                 | stop gdb                                |