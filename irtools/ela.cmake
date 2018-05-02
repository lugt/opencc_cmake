set(LOCAL_INC_DIR
  ${OSPREY_SRC_DIR}/libdwarf/libdwarf
  #${OSPREY_SRC_DIR}/libelf/lib
  /usr/local/include/libelf
)
set(LOCAL_DEF -DMONGOOSE_BE)
set(LOCAL_COMPILER_OPT -Wno-c++11-narrowing)
set(LOCAL_C_OPT )
set(LOCAL_CPP_OPT )
