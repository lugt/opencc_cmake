add_library(bgen_util_o ${WGENUTILO_SRC})
target_compile_options(bgen_util_o PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
target_include_directories(bgen_util_o PUBLIC ${LOCAL_INC_DIR} ${HOST_INC_DIR})
target_compile_definitions(bgen_util_o PRIVATE ${HOST_DEF} ${LOCAL_DEF} -DMONGOOSE_BE)

add_library(bcommon_gen_func ${COMMON_WN_FUNCS})
target_compile_options(bcommon_gen_func PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
target_include_directories(bcommon_gen_func PUBLIC ${LOCAL_INC_DIR} ${HOST_INC_DIR})
target_compile_definitions(bcommon_gen_func PUBLIC ${HOST_DEF} ${LOCAL_DEF})
target_link_libraries(bcommon_gen_func comutils spin cmplrs iberty wgen_util_o)


if(DEBUG_CMAKE)
message(STATUS "BGEN_SRCS: " ${BGEN_SRCS})
message(STATUS "adding bgen src:" ${BGEN_SRC})
endif()

add_library(bgen SHARED ${BGEN_SRC})
target_compile_options(bgen PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
target_include_directories(bgen PUBLIC ${LOCAL_INC_DIR} ${HOST_INC_DIR})
target_compile_definitions(bgen PUBLIC ${HOST_DEF} ${LOCAL_DEF})
target_link_libraries(bgen comutils bgen_util_o common_gen_func comutils spin cmplrs iberty)


#add_executable(jwtest ${JREAD_SRC})
#target_compile_options(jwtest PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
#target_include_directories(jwtest PUBLIC ${LOCAL_INC_DIR} ${HOST_INC_DIR})
#target_compile_definitions(jwtest PUBLIC ${HOST_DEF} ${LOCAL_DEF})
#target_link_libraries(jwtest comutils jgen_util_o common_gen_func comutils spin cmplrs iberty)
