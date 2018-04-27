
set(GLOBAL_TARGET_PREFIX x8664)

set(LOCAL_INC_DIR
  ${OSPREY_SRC_DIR}/common/com
  ${OSPREY_SRC_DIR}/common/com/${GLOBAL_TARGET_PREFIX}
)

set(LOCAL_DEF )

if(DEBUG)
  set(LOCAL_DEF ${LOCAL_DEF} -DIs_True_On -DInsist_On)
endif()

set(LOCAL_COMPILER_OPT )
set(LOCAL_C_OPT )
set(LOCAL_CPP_OPT )
