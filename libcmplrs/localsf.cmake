#aux_source_directory(${LIBCMPLERS} WGEN_SRC_FOUND)


SET(CFILES      
    array_alloc.c
    make_depend.c
)


foreach(ONE_C_FILE IN CFILES )
  list(APPEND LIBCMPLRS ${LIB_CMPLR_DIR}/${ONE_C_FILE})
endforeach()




#foreach(ONE_C_FILE IN LISTS FRONT_END_C_SRCS )
#  list(APPEND WGEN_SRC ${ONE_C_FILE})
#endforeach()

#foreach(ONE_C_FILE IN LISTS FRONT_END_CXX_SRCS )
#  list(APPEND WGEN_SRC ${ONE_C_FILE})
#endforeach()

