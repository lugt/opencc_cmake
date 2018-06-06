option(BUILD_TARGET_X8664 "Is Target X8664 " ON)
if(BUILD_TARGET_X8664)
    set(TARGET_DEF ${TARGET_DEF} -D__MIPS_AND_IA64_ELF_H)
    set(BUILD_TARGET_PREFIX x8664)
endif()

set(COMMON_COM_TARG_DIR ${OSPREY_SRC_DIR}/common/com/${BUILD_TARGET_PREFIX})
set(COMMON_BUILD_SRC ${TARGET_DIR})

if(CMAKE_COMPILER_IS_GNUCXX)
    #add_compile_options(-std=c++11)
    message(STATUS "using GNU CXX")   
endif(CMAKE_COMPILER_IS_GNUCXX)

set(HOST_INC_DIR
#        /usr/local/Cellar/libelf/0.8.13_1/include/libelf
/usr/include
/include
)

# Host Platform

set(HOST_C_FLAG -D_LANGUAGE_C)
set(HOST_CXX_FLAG -D_LANGUAGE_C_PLUS_PLUS -fpermissive)
set(HOST_COMPILER_OPT -m64 -mtune=generic -march=x86-64
  -funsigned-char -fPIC -fstack-protector-strong -Wformat -Wformat-security -Wno-constant-conversion
  -Wno-c++11-compat-deprecated-writable-strings -Wno-dangling-else -Wno-array-bounds -Wno-return-type
  -Wno-c++11-narrowing)

set(HOST_DEF
	-D_GNU_SOURCE
        -D_SGI_SOURCE
        -D__GNU_BUG_WORKAROUND
        -D_NOTHREADS
        -DVENDOR_OSP
	-DNO_VALGRIND
	-DInsist_On
        -DDEBUG_IR
        -DPSC_TO_OPEN64
        -DSHARED_BUILD
        -D_GNU_SOURCE
      #  -DIR_TOOLS
        -D_NEW_SYMTAB
        -D__STDC_LIMIT_MACROS
        -DTARG_X8664
        -DKEY
        -DOSP_OPT
        -DPATHSCALE_MERGE
        -DPSC_TO_OPEN64
        -DSHARED_BUILD
	${TARGET_DEF}
        -D_MIPSEL
        -D_LONGLONG
        -D_MIPS_SZINT=32
        -D_MIPS_SZPTR=64
        -D_MIPS_SZLONG=64
        -D_LP64)

if(DEBUG)
  set(HOST_COMPILER_OPT ${HOST_COMPILER_OPT} -g -O0)
endif()


# Host(Building) Platform


2
3
4
5
6
7
8
9
10
11
12
13
14
15
MESSAGE(STATUS "###################################")

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
  MESSAGE(STATUS "current platform: Linux ")
  set(BUILD_LINUX 1)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
  MESSAGE(STATUS "current platform: Windows")
    set(BUILD_WINDOWS 1)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
  MESSAGE(STATUS "current platform: FreeBSD")
ELSE ()
  MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
  set(BUILD_MACOS 1)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

MESSAGE(STATUS "###################################")

if(BUILD_MACOS)

  set(HOST_DEF
    ${HOST_DEF}
    -DBUILD_OS_DARWIN)
  
  set(BUILD_PLATFORM_INC_DIR ${OSPREY_SRC_DIR}/macos/include)

endif()

if(BUILD_LINUX)

  set(HOST_DEF
    ${HOST_DEF}
    -DBUILD_OS_LINUX
    -DBUILD_LINUX)
  
  set(BUILD_PLATFORM_INC_DIR ${OSPREY_SRC_DIR}/linux/include)
endif()
