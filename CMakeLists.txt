cmake_minimum_required(VERSION 3.4)
project(osprey)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_C_STANDARD 99)

# Global DIR

set(OSPREY_SRC_DIR /Users/me/xc5/open64/osprey)
set(BUILD_DIR /Users/me/xc5/cmake-builder)



# LOCAL Source Directories

set(IR_TOOLS_SRC_DIR ${OSPREY_SRC_DIR}/ir_tools)

set(TARGET_DIR ${OSPREY_SRC_DIR}/targets)
set(LIB_BUILD_DIR ${BUILD_DIR}/target_lib)
set(LIB_BUILD_DIR2 ${BUILD_DIR}/target_lib2)

set(BE_COM_DIR ${OSPREY_SRC_DIR}/be/com)
set(BE_OPT_DIR ${OSPREY_SRC_DIR}/be/opt)
set(COMMON_UTIL_DIR ${OSPREY_SRC_DIR}/common/util)
set(COMMON_COM_DIR ${OSPREY_SRC_DIR}/common/com)
# set(COMMON_COM_TARG_DIR ${OSPREY_SRC_DIR}/common/com/${BUI})
set(BUILD_BASE ${OSPREY_SRC_DIR}/com/com})



# Global Variables

option(BUILD_TARGET_X8664 "Is Target X8664 " ON)
if(BUILD_TARGET_X8664)
    set(TARGET_DEF ${TARGET_DEF} __MIPS_AND_IA64_ELF_H)
    set(BUILD_TARGET_PREFIX x8664)
endif()

set(COMMON_BUILD_SRC ${TARGET_DIR})

if(CMAKE_COMPILER_IS_GNUCXX)
    #add_compile_options(-std=c++11)
    message(STATUS "using GNU CXX")   
endif(CMAKE_COMPILER_IS_GNUCXX)

set(HOST_INC_DIR
        ${OSPREY_SRC_DIR}/ir_tools
        ${OSPREY_SRC_DIR}/common/com
        ${OSPREY_SRC_DIR}/common/com/x8664
        ${OSPREY_SRC_DIR}/common/util
        ${OSPREY_SRC_DIR}/be/com
        ${OSPREY_SRC_DIR}/be/opt
        ${OSPREY_SRC_DIR}/include
        ${OSPREY_SRC_DIR}/macos/include
        ${TARGET_DIR}
        ${TARGET_DIR}/include
	${OSPREY_SRC_DIR}/libdwarf/libdwarf
        /usr/local/Cellar/libelf/0.8.13_1/include/libelf
        /usr/include
	/include)


set(HOST_C_FLAG -D_LANGUAGE_C)
set(HOST_CXX_FLAG -D_LANGUAGE_C_PLUS_PLUS -fpermissive)
set(HOST_COMPILER_OPT  -shared-libgcc -m64 -mtune=generic -march=x86-64
  -funsigned-char -fPIC -fstack-protector-strong -Wformat -Wformat-security)
set(HOST_DEF
	-D_GNU_SOURCE
        #-DBUILD_OS_DARWIN
        -D_SGI_SOURCE
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

if(DEBUG)
  set(HOST_COMPILER_OPT ${HOST_COMPILER_OPT} -g -O0)
endif()

      
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
#${COMMON_COM_DIR}/${BUILD_TARGET_PREFIX}/config_host.c
#${COMMON_COM_DIR}/${BUILD_TARGET_PREFIX}/config_platform.c
)

# In total

set(CFILES
${COMMON_COM_SRC}
${COMMON_COM_TARG_SRC} )

set(CXXFILES
${COMMON_COM_CXX_SRC}
${COMMON_COM_TARG_CXX_SRCS}
${BE_COM_SRCS})

      
#Exec, Library Definition

set(LOCAL_INC_DIR )
set(LOCAL_DEF )
set(LOCAL_COMPILER_OPT )
set(LOCAL_C_OPT )
set(LOCAL_CPP_OPT )


# Targets

#add_library(libcommon
#  ${COMMON_COM_SRC}
#  ${COMMON_COM_TARG_SRC}
#)

set(IR_TOOLS_SRC ${IR_TOOLS_SRC_DIR}/ir_a2b.cxx)


# 1. libcomutil
# -- >include
# 2. ir_tools


#add_library(libcomutils
#  ${SHARED_BUILD}
#  ${COMMON_LIB_SOURCE}
#  ${CFILES}
#  ${CXXFILES})


# Saving the environment

#set(TEMP_C_OPT ${CMAKE_C_FLAGS})
#set(TEMP_CXX_OPT ${CMAKE_CXX_FLAGS})
#set(CMAKE_C_FLAGS ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
#set(CMAKE_CXX_FLAGS ${TEMP_CXX_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_CXX_OPT} ${LOCAL_CXX_OPT})

add_executable(ir_b2a ${IR_TOOLS_SRC})
target_compile_options(ir_b2a PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
target_include_directories(ir_b2a PUBLIC ${HOST_INC_DIR} ${LOCAL_INC_DIR})
target_compile_definitions(ir_b2a PUBLIC ${IR_TOOLS_DEF} ${LOCAL_DEF})

#target_link_libraries(ir_b2a libcomutils)




# -- backup --



#add_headers_and_sources(ir_b2a $)
