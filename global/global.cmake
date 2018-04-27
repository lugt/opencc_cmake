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
#        /usr/local/Cellar/libelf/0.8.13_1/include/libelf
        /usr/include
	/include)


set(HOST_C_FLAG -D_LANGUAGE_C)
set(HOST_CXX_FLAG -D_LANGUAGE_C_PLUS_PLUS -fpermissive)
set(HOST_COMPILER_OPT  -shared-libgcc -m64 -mtune=generic -march=x86-64
  -funsigned-char -fPIC -fstack-protector-strong -Wformat -Wformat-security -Wno-constant-conversion
  -Wno-c++11-compat-deprecated-writable-strings -Wno-dangling-else -Wno-array-bounds -Wno-return-type)

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
