set shell := ["powershell.exe", "-c"]

flash-monitor:
    idf.py flash monitor

openocd:
    idf.py openocd

gdb:
    xtensa-esp32s3-elf-gdb -x build/gdbinit/connect build/advaned-debugging.elf

coredump-info:
     python C:/esp/esp-idf/components/espcoredump/espcoredump.py -p COM35 info_corefile build/advaned-debugging.elf

coredump-dbg:
    python C:/esp/esp-idf/components/espcoredump/espcoredump.py -p COM35 dbg_corefile build/advaned-debugging.elf

