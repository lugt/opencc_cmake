set(LOCAL_INC_DIR
  ${OSPREY_SRC_DIR}/common/com/${GLOBAL_TARGET_PREFIX}
  ${OSPREY_SRC_DIR}/macos/include
  ${OSPREY_SRC_DIR}/libdwarf/libdwarf
#  ${OSPREY_SRC_DIR}/libelf/lib
  ${OSPREY_SRC_DIR}/common/com
  ${OSPREY_SRC_DIR}/ir_tools
  ${OSPREY_SRC_DIR}/common/util
  ${OSPREY_SRC_DIR}/be/com
  ${OSPREY_SRC_DIR}/be/opt
  ${OSPREY_SRC_DIR}/include
  ${TARGET_DIR}
  ${TARGET_DIR}/include
)
set(LOCAL_DEF
  -DMONGOOSE_BE
  -DIR_TOOLS
  )
set(LOCAL_COMPILER_OPT -Wno-c++11-narrowing
  -Wno-parentheses)
set(LOCAL_C_OPT )
set(LOCAL_CPP_OPT )
