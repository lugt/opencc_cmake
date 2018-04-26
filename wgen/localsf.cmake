aux_source_directory(${WGEN_DIR} WGEN_SRC_FOUND)

foreach(ONE_C_FILE IN LISTS WGEN_SRC_FOUND)
  list(APPEND WGEN_SRC ${ONE_C_FILE})
endforeach()
