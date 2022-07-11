# Install script for directory: /home/iwo/clock/Pico_Lcd_Clock/c

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/iwo/clock/Pico_Lcd_Clock/c/build/pico-sdk/cmake_install.cmake")
  include("/home/iwo/clock/Pico_Lcd_Clock/c/build/lib/Config/cmake_install.cmake")
  include("/home/iwo/clock/Pico_Lcd_Clock/c/build/lib/Infrared/cmake_install.cmake")
  include("/home/iwo/clock/Pico_Lcd_Clock/c/build/lib/Icm20948/cmake_install.cmake")
  include("/home/iwo/clock/Pico_Lcd_Clock/c/build/lib/LCD/cmake_install.cmake")
  include("/home/iwo/clock/Pico_Lcd_Clock/c/build/lib/Fonts/cmake_install.cmake")
  include("/home/iwo/clock/Pico_Lcd_Clock/c/build/lib/GUI/cmake_install.cmake")
  include("/home/iwo/clock/Pico_Lcd_Clock/c/build/Pico_Clock/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/iwo/clock/Pico_Lcd_Clock/c/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
