set shell := ["powershell.exe", "-c"]

IDF_PATH := "C:/esp/esp-idf"

flash-monitor:
    idf.py flash monitor

openocd:
    idf.py openocd

gdb:
    xtensa-esp32s3-elf-gdb -x gdbinit build/advaned-debugging.elf

coredump-info:
     python {{IDF_PATH}}/components/espcoredump/espcoredump.py -p COM35 info_corefile build/advaned-debugging.elf

coredump-dbg:
    python {{IDF_PATH}}/components/espcoredump/espcoredump.py -p COM35 dbg_corefile build/advaned-debugging.elf


tracelog-ESP_LOG:
    # $IDF_PATH/tools/esp_app_trace/logtrace_proc.py /path/to/trace/file /path/to/program/elf/file
    python c:/esp/esp-idf/tools/esp_app_trace/logtrace_proc.py trace.log build/advaned-debugging.elf
