cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
#include(FreeRTOS_Kernel_import.cmake)
project(Pico_ePaper_Code)
pico_sdk_init()

#添加编译子目录
add_subdirectory(lib/Config)
add_subdirectory(lib/Infrared)
add_subdirectory(lib/Icm20948)
add_subdirectory(lib/LCD)
add_subdirectory(lib/Fonts)
add_subdirectory(lib/GUI)
add_subdirectory(Pico_Clock)
set(PICO_SDK_FREERTOS_SOURCE FreeRTOS-Kernel)

add_library(FreeRTOS STATIC FreeRTOS-Kernel/croutine.c
FreeRTOS-Kernel/event_groups.c
FreeRTOS-Kernel/list.c
FreeRTOS-Kernel/queue.c
FreeRTOS-Kernel/stream_buffer.c
FreeRTOS-Kernel/tasks.c
FreeRTOS-Kernel/timers.c 
FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c 
FreeRTOS-Kernel/portable/MemMang/heap_3.c 
IdleMemory.c)
target_include_directories(FreeRTOS PUBLIC FreeRTOS-Kernel/include include/ FreeRTOS-Kernel/portable/GCC/ARM_CM0)


#添加头文件目录
include_directories(.)
include_directories(Pico_Clock)
include_directories(./lib/Config)
include_directories(./lib/GUI)
include_directories(./lib/Icm20948)
include_directories(./lib/LCD)
include_directories(./lib/Infrared)
include_directories(FreeRTOS-Kernel/include)
include_directories(FreeRTOS-Kernel/portable/GCC/ARM_CM0)

# 生成可执行文件
add_executable(main 
main.c
)

target_link_libraries(main Pico_Clock LCD Infrared Icm20948 GUI Fonts Config pico_stdlib hardware_spi hardware_uart FreeRTOS)
# enable usb output, disable uart output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)
