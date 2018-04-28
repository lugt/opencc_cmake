#aux_source_directory(${WGEN_DIR} WGEN_SRC_FOUND)


SET(CFILES
    alloca.c
    argv.c
    choose-temp.c
    concat.c
    cp-demangle.c
    cplus-dem.c
    dyn-string.c
    fdmatch.c
    fibheap.c
    floatformat.c
    fnmatch.c
    getopt.c
    getopt1.c
    getpwd.c
    getruntime.c
    hex.c
    hashtab.c
    lbasename.c
    mkstemps.c
    md5.c
    objalloc.c
    obstack.c
    partition.c
    pexecute.c
    physmem.c
    safe-ctype.c
    spaces.c
    splay-tree.c
    strerror.c
    strsignal.c
    xatexit.c
    xexit.c
    xmalloc.c
    xmemdup.c
    xstrdup.c
    xstrerror.c
)

SET(INSTALLED_HEADERS
    $(INCDIR)/ansidecl.h
    $(INCDIR)/demangle.h
    $(INCDIR)/dyn-string.h
    $(INCDIR)/fibheap.h
    $(INCDIR)/floatformat.h
    $(INCDIR)/hashtab.h
        $(INCDIR)/libiberty.h
        $(INCDIR)/objalloc.h
$(INCDIR)/partition.h
$(INCDIR)/safe-ctype.h
$(INCDIR)/sort.h
$(INCDIR)/splay-tree.h
$(INCDIR)/ternary.h
)



#SET(FE_CXX_SRCS            
#    )
#SET(OPENMP_SRCS            
#    )
#  
#SET(COMMON_COM_CXX_SRCS    
#)
#SET(COMMON_COM_TARG_SRCS   
#)
#SET(COMMON_COM_TARG_CXX_SRCS  
#   config_targ.cxx      
#   targ_const.cxx       
#   targ_sim.cxx
#)
#SET(FRONT_END_C_SRCS               
#   ${COMMON_UTIL_SRCS}          
#   ${COMMON_COM_SRCS}           
#   ${COMMON_COM_TARG_SRCS}      
#   ${FE_C_SRCS}
#)
#SET(FRONT_END_CXX_SRCS             
#   ${COMMON_COM_CXX_SRCS}       
#   ${COMMON_COM_TARG_CXX_SRCS}  
#   ${FE_CXX_SRCS}
#)





foreach(ONE_C_FILE IN LISTS CFILES )
  list(APPEND LIBIBERTY_DIR/${ONE_C_FILE})
endforeach()


foreach(ONE_C_FILE IN LISTS INSTALLED_HEADERS )
  list(APPEND LIBIBERTY_H_DIR/${ONE_C_FILE})
endforeach()

#foreach(ONE_C_FILE IN LISTS FRONT_END_CXX_SRCS )
#  list(APPEND WGEN_SRC ${ONE_C_FILE})
#endforeach()

