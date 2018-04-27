set(COMMON_COM_TARG_SRC )

# 注意区分 HOST（OPENCC 运行平台）。TARGET （OPENCC编译的程序需要跑在那个平台）

# CROSS BUILD
set(COM_UTILS_TARG_SRC
  c_qwmultu.c
)

set(COM_UTILS_H_SRC
  #libcomutil.h 
  bitset.h 
  errors.h 
  file_util.h 
  flags.h 
  linklist.h 
  mempool.h 
  cxx_memory.h 
  quad.h 
  quadsim.h 
  priority_queue.h 
  resource.h 
  mstack.h 
  tracing.h 
  util.h 
  vcg.h
  vstring.h
)

set(COM_UTILS_C_SRC
  bitset.c 
  file_util.c 
  flags.c 
  linklist.c 
  memory.c 
  priority_queue.c 
  resource.c 
  mstack.c 
  tracing.c 
  util.c 
  vstring.c
  c_a_to_q.c 
  c_q_add.c 
  c_q_div.c 
  c_q_mul.c 
  c_q_neg.c 
  c_q_rel.c 
  c_q_sqrt.c 
  c_q_sub.c 
  c_q_to_a.c 
  c_qtenscale.c 
  quadsim.c 
  )

set(COM_UTILS_CXX_SRC
  cxx_memory.cxx
  errors.cxx 
  vcg.cxx
  )

foreach(ONE_C_FILE IN LISTS COM_UTILS_TARG_SRC)
  list(APPEND COM_UTILS_SRCS ${COMMON_UTIL_DIR}/x8664/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS COM_UTILS_C_SRC)
  list(APPEND COM_UTILS_SRCS ${COMMON_UTIL_DIR}/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS COM_UTILS_CXX_SRC)
  list(APPEND COM_UTILS_SRCS ${COMMON_UTIL_DIR}/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS COM_UTILS_H_SRC)
  list(APPEND COM_UTILS_SRCS ${COMMON_UTIL_DIR}/${ONE_C_FILE})
endforeach()
