#aux_source_directory(${LIBCMPLERS} WGEN_SRC_FOUND)


SET(C_FILES
    array_alloc.c
    make_depend.c
)


foreach(ONE_C_FILE IN C_FILES)
  list(APPEND LIB_CMPLR_SRC ${LIB_CMPLR_DIR}/${ONE_C_FILE})
endforeach()




#foreach(ONE_C_FILE IN LISTS FRONT_END_C_SRCS )
#  list(APPEND WGEN_SRC ${ONE_C_FILE})
#endforeach()

#foreach(ONE_C_FILE IN LISTS FRONT_END_CXX_SRCS )
#  list(APPEND WGEN_SRC ${ONE_C_FILE})
#endforeach()

