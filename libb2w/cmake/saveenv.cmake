add_library(B2w_util_o ${WGENUTILO_SRC})
target_compile_options(B2w_util_o PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
target_include_directories(B2w_util_o PUBLIC ${LOCAL_INC_DIR} ${HOST_INC_DIR})
target_compile_definitions(B2w_util_o PRIVATE ${HOST_DEF} ${LOCAL_DEF} -DMONGOOSE_BE)

add_library(bcommon_gen_func ${COMMON_WN_FUNCS})
target_compile_options(bcommon_gen_func PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
target_include_directories(bcommon_gen_func PUBLIC ${LOCAL_INC_DIR} ${HOST_INC_DIR})
target_compile_definitions(bcommon_gen_func PUBLIC ${HOST_DEF} ${LOCAL_DEF})
target_link_libraries(bcommon_gen_func comutils spin cmplrs iberty wgen_util_o)


if(DEBUG_CMAKE)
message(STATUS "B2w_SRCS: " ${B2w_SRCS})
message(STATUS "adding B2w src:" ${B2w_SRC})
endif()

add_library(b2w SHARED ${B2w_SRCS})
target_compile_options(b2w PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
target_include_directories(b2w PUBLIC ${LOCAL_INC_DIR} ${HOST_INC_DIR})
target_compile_definitions(b2w PUBLIC ${HOST_DEF} ${LOCAL_DEF})
target_link_libraries(b2w comutils B2w_util_o common_gen_func comutils spin cmplrs iberty)


add_executable(B2wtest ${B2wTEST_SRCS})
target_compile_options(B2wtest PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
target_include_directories(B2wtest PUBLIC ${LOCAL_INC_DIR} ${HOST_INC_DIR})
target_compile_definitions(B2wtest PUBLIC ${HOST_DEF} ${LOCAL_DEF})
target_link_libraries(B2wtest comutils jgen_util_o common_gen_func comutils spin cmplrs iberty b2w)
