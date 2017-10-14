# Install script for directory: /root/dev/freeDiameter/extensions

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/root/dev/freeDiameter/fDbuild/extensions/dict_nasreq/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dict_eap/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dict_dcca/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dict_dcca_3gpp/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dict_dcca_starent/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dict_sip/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dict_mip6a/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dict_mip6i/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dict_nas_mipv6/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dict_rfc5777/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/rt_default/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/rt_redirect/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/rt_busypeers/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/rt_ignore_dh/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/rt_change_dh/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/rt_load_balance/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/acl_wl/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dbg_monitor/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dbg_msg_timings/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dbg_msg_dumps/cmake_install.cmake")
  include("/root/dev/freeDiameter/fDbuild/extensions/dbg_rt/cmake_install.cmake")

endif()

