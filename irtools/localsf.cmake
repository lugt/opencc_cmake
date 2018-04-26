aux_source_directory(${IR_TOOLS_SRC_DIR} IR_TOOLS_SRC_FOUND)

foreach(ONE_C_FILE IN LISTS IR_TOOLS_SRC_FOUND)
  list(APPEND IR_TOOLS_SRC ${ONE_C_FILE})
endforeach()
