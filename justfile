set shell := ["powershell.exe", "-c"]

flash-monitor:
    idf.py flash monitor

openocd:
    idf.py openocd

gdb:
    xtensa-esp32s3-elf-gdb -x build/gdbinit/connect build/advaned-debugging.elf