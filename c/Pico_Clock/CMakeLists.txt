# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_examples_SRCS 变量
include_directories(../lib/Config)
include_directories(../lib/GUI)
include_directories(../lib/Infrared)
include_directories(../lib/LCD)
include_directories(../lib/Icm20948)

# 生成链接库
add_library(Pico_Clock Pico_Clock.c ImageData.c)
target_link_libraries(Pico_Clock PUBLIC Config LCD Infrared Icm20948 pico_stdlib)