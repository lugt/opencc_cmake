cmake_minimum_required(VERSION 3.4)
project(osprey)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_C_STANDARD 99)

# Main Entry

# Whether building middle libraries as Dynamic Libraries
option(SPLIT_SHARED "Do you need the used library to be built as shared library? SHARED / blank" "SHARED")
if(SPLIT_SHARED)
    set(SHARED_BUILD SHARED)
else()
    set(SHARED_BUILD )
endif()


# Building DIR

# option(OSPREY_BUILD_DESIRE "Where is the osprey sources (not to open64 dir, but to osprey dir)" "~/")
# "Where do you like to build whole files?"
set(OSPREY_SRC_DIR /Users/me/xc5/open64/osprey)
set(BUILD_DIR /Users/me/xc5/cmake-builder)

set(IR_TOOLS_SRC_DIR ${OSPREY_SRC_DIR}/ir_tools)

set(TARGET_DIR ${OSPREY_SRC_DIR}/targets)
set(LIB_BUILD_DIR ${BUILD_DIR}/target_lib)
set(LIB_BUILD_DIR2 ${BUILD_DIR}/target_lib2)

# Linking Options


# Compiling Parameters

set(STD_COMPILE_OPT -Wno-narrowing)
set(STD_C_OPT ${STD_COMPILE_OPT} ${STD_C_OPT} -std=c99)
set(STD_CXX_OPT ${STD_COMPILE_OPT} -std=c++11)


# Source Directories

set(BE_COM_DIR ${OSPREY_SRC_DIR}/be/com)
set(BE_OPT_DIR ${OSPREY_SRC_DIR}/be/opt)
set(COMMON_UTIL_DIR ${OSPREY_SRC_DIR}/common/util)
set(COMMON_COM_DIR ${OSPREY_SRC_DIR}/common/com)
# set(COMMON_COM_TARG_DIR ${OSPREY_SRC_DIR}/common/com/${BUI})
# set(BUILD_BASE ${OSPREY_SRC_DIR}/com/com})


# Definitions (something to do with switches)

set(IR_DEF "")
set(TARGET_DEF "")
set(C_DEF "")
set(C++_DEF "")

#X8664
option(BUILD_TARGET_X8664 "Is Target X8664 " ON)

if(BUILD_TARGET_X8664)
    set(TARGET_DEF ${TARGET_DEF} __MIPS_AND_IA64_ELF_H)
    set(BUILD_TARGET_PREFIX x8664)
endif()

option(BUILD_MACOS "Is it building on macOS " ON)

set(COMMON_BUILD_SRC ${TARGET_DIR})

#Source File Locating

set(COMMON_COM_CXX_SRC
config.cxx
config_elf_targ.cxx
const.cxx
dwarf_DST.cxx
dwarf_DST_dump.cxx
dwarf_DST_mem.cxx
glob.cxx
ir_bcom.cxx
ir_bread.cxx
ir_bwrite.cxx
ir_reader.cxx
irbdata.cxx
mtypes.cxx
opcode.cxx
opcode_core.cxx
pu_info.cxx
strtab.cxx
symtab.cxx
symtab_verify.cxx
wn.cxx
wn_map.cxx
wn_pragmas.cxx
wn_simp.cxx
wn_util.cxx
wutil.cxx
xstats.cxx
intrn_info.cxx)

set(BE_COM_SRCS
wssa_defs.cxx
wssa_sym.cxx
wssa_mgr.cxx
wssa_wn.cxx
wssa_io.cxx
wssa_utils.cxx )

set(COMMON_COM_TARG_CXX_SRCS
config_targ.cxx
targ_const.cxx
targ_sim.cxx)

set(COMMON_COM_TARG_SRC
${COMMON_COM_DIR}/${BUILD_TARGET_PREFIX}/config_host.c
${COMMON_COM_DIR}/${BUILD_TARGET_PREFIX}/config_platform.c)

# In total

set(CFILES
${COMMON_COM_SRC}
${COMMON_COM_TARG_SRC} )

set(CXXFILES
${COMMON_COM_CXX_SRC}
${COMMON_COM_TARG_CXX_SRCS}
${BE_COM_SRCS})


add_definitions(-D_GNU_SOURCE
        #-DBUILD_OS_DARWIN
        -D_SGI_SOURCE -D_LANGUAGE_C_PLUS_PLUS
        -D__GNU_BUG_WORKAROUND
        -D_NOTHREADS
        -DVENDOR_OSP
        -DInsist_On
        -DDEBUG_IR
        -DPSC_TO_OPEN64
        -DSHARED_BUILD
        -D_GNU_SOURCE
        -DIR_TOOLS
        -D_NEW_SYMTAB
        -D__STDC_LIMIT_MACROS
        -DTARG_X8664
        -DKEY
        -DOSP_OPT
        -DPATHSCALE_MERGE
        -DPSC_TO_OPEN64
        -DSHARED_BUILD
        -D__GNU_BUG_WORKAROUND
        -D__MIPS_AND_IA64_ELF_H
        -D_MIPSEL
        -D_LONGLONG
        -D_MIPS_SZINT=32
        -D_MIPS_SZPTR=64
        -D_MIPS_SZLONG=64
        -D_LP64)


add_compile_options(-MMD -MQ -shared-libgcc -m64 -mtune=generic -march=x86-64)
add_compile_options(-funsigned-char -fPIC -fstack-protector-strong -Wformat -Wformat-security)
if(DEBUG)
add_compile_options(-g -O0)
endif()

#Exec, Library Definition

set(HOST_INCLUDE
        ${OSPREY_SRC_DIR}/ir_tools
        ${OSPREY_SRC_DIR}/common/com
        ${OSPREY_SRC_DIR}/common/com/x8664
        ${OSPREY_SRC_DIR}/common/util
        ${OSPREY_SRC_DIR}/be/com
        ${OSPREY_SRC_DIR}/be/opt
        ${OSPREY_SRC_DIR}/include
        ${OSPREY_SRC_DIR}/macos/include
        ${TARGET_DIR}
        ${TARGET_DIR}/include/libelf
        ${TARGET_DIR}/include
        /usr/local/Cellar/libelf/0.8.13_1/include/libelf
        /usr/include)


include_directories(${HOST_INCLUDE})

add_library(libcommon
  ${COMMON_COM_SRC}
  ${COMMON_COM_TARG_SRC}
)

set(IR_TOOLS_SRC ${IR_TOOLS_SRC_DIR}/ir_a2b.cxx)


# 1. libcomutil
# -- >include
# 2. ir_tools


#add_library(libcomutils
#  ${SHARED_BUILD}
#  ${COMMON_LIB_SOURCE}
#  ${CFILES}
#  ${CXXFILES})


add_executable(ir_b2a ${IR_TOOLS_SRC})
target_link_libraries(ir_b2a libcomutils)

#Platform Based Configuration

#if(LINUX)
#	target_compile_definitions(ir_b2a PRIVATE __LINUX__=1)
#endif()


#if(APPLE)
#	target_compile_definitions(ir_b2a PRIVATE __APPLE__=1)
#endif()


#add_headers_and_sources(ir_b2a $)
