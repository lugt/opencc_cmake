add_library(libcomutils
  ${SHARED_BUILD}
  ${COMMON_SRC}
)
target_compile_options(libcomutils PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
target_include_directories(libcomutils PUBLIC ${HOST_INC_DIR} ${LOCAL_INC_DIR})
target_compile_definitions(libcomutils PUBLIC ${IR_TOOLS_DEF} ${HOST_DEF} ${LOCAL_DEF})
