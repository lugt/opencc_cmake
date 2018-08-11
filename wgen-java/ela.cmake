set(LOCAL_INC_DIR
  ${OSPREY_SRC_DIR}/../libspin
  ${NEW_WGEN_DIR}/extra
  ${NEW_WGEN_DIR}/common/com/${BUILD_TARGET_PREFIX}
  ${NEW_WGEN_DIR}/common/util/${BUILD_TARGET_PREFIX}
  ${NEW_WGEN_DIR}/common/util
  ${NEW_WGEN_DIR}/common/com
  ${NEW_WGEN_DIR}/common/targ_info/access
  ${NEW_WGEN_DIR}/wgen
  ${OSPREY_SRC_DIR}/ir_tools
  ${OSPREY_SRC_DIR}/be/com
  ${OSPREY_SRC_DIR}/be/opt
  ${OSPREY_SRC_DIR}/be/region
  ${OSPREY_SRC_DIR}/include
  ${OSPREY_SRC_DIR}/macos/include
  ${OSPREY_SRC_DIR}/ipa/main/analyze
  ${OSPREY_SRC_DIR}/libdwarf/libdwarf
  ${OSPREY_SRC_DIR}/cygnus/include
#  ${OSPREY_SRC_DIR}/gnu/include
  ${BUILD_DIR}
)

set(LOCAL_DEF
#  -DIN_GCC
#  -DHAVE_CONFIG_H
#-D_SGI_SOURCE
#-D_LANGUAGE_C
  -DHAVE_CONFIG_H
  -DFRONT_END
#  -DMONGOOSE_BE
#  -DIR_TOOLS
  -DUSE_DECL_SRCPOS
  -DFE_GNU_4_2_0
  -DFRONT_END_C
  -DCFE
  -DCIL
  -DDO_IL_LOWERING=0
  -DNO_USR_INCLUDE=TRUE
  -DAUTOMATIC_TEMPLATE_INSTANTIATION=0
  -DINSTANTIATION_BY_IMPLICIT_INCLUSION=0
  -DBACK_END_IS_C_GEN_BE=0
  -DMONGOOSE_CIF
#  -DBACK_END
   -DSGI_RAG_BACKEND
   -DSGI_MONGOOSE
   -DHANDLE_PRAGMA_WEAK
#   -DNEW_INITIALIZER  # for wgen-java only
   -DDEBUG=1
   -DCHECKING=1
   -DGPLUSPLUS_FE
)

set(LOCAL_COMPILER_OPT -Wno-writable-strings -fwritable-strings)
set(LOCAL_C_OPT )
set(LOCAL_CPP_OPT -Wno-writable-strings)