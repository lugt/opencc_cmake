set(LOCAL_INC_DIR )
set(LOCAL_DEF )
set(LOCAL_COMPILER_OPT )
set(LOCAL_C_OPT )
set(LOCAL_CPP_OPT )


foreach(ONE_C_FILE IN LISTS COMMON_COM_SRC)
  list(APPEND COMMON_SRC ${COMON_COM_DIR}/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS COMMON_COM_TARG_SRC)
  list(APPEND COMMON_SRC ${COMMON_COM_DIR}/x8664/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS COMMON_COM_CXX_SRC)
  list(APPEND COMMON_SRC ${COMMON_COM_DIR}/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS COMMON_COM_TARG_CXX_SRC)
  list(APPEND COMMON_SRC ${COMMON_COM_DIR}/x8664/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS BE_COM_SRC)
  list(APPEND COMMON_SRC ${BE_COM_DIR}/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS IR_TOOLS_SRC_FOUND)
  list(APPEND IR_TOOLS_SRC ${ONE_C_FILE})
endforeach()

#set(IR_TOOLS_SRC
#  ${IR_TOOLS_SRC_DIR}/ir_a2b.cxx)
#message(WARNING This is IR_TOOLS_SRC : ${IR_TOOLS_SRC})
