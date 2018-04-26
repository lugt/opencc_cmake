#set(TEMP_C_OPT ${CMAKE_C_FLAGS})
#set(TEMP_CXX_OPT ${CMAKE_CXX_FLAGS})
#set(CMAKE_C_FLAGS ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
#set(CMAKE_CXX_FLAGS ${TEMP_CXX_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_CXX_OPT} ${LOCAL_CXX_OPT})

add_executable(ir ${IR_TOOLS_SRC})
target_compile_options(ir PUBLIC ${TEMP_C_OPT} ${HOST_COMPILER_OPT} ${LOCAL_COMPLER_OPT} ${HOST_C_OPT} ${LOCAL_C_OPT})
target_include_directories(ir PUBLIC ${HOST_INC_DIR} ${LOCAL_INC_DIR})
target_compile_definitions(ir PUBLIC ${IR_TOOLS_DEF} ${HOST_DEF} ${LOCAL_DEF})

#target_link_libraries(ir_b2a libcomutils)
# -- backup --
#add_headers_and_sources(ir_b2a $)
