set(COMMON_COM_CXX_SRC
config.cxx
const.cxx
dwarf_DST.cxx
dwarf_DST_dump.cxx
dwarf_DST_mem.cxx
glob.cxx
ir_bcom.cxx
ir_bread.cxx
ir_bwrite.cxx
ir_reader.cxx
irbdata.cxx
mtypes.cxx
opcode.cxx
opcode_core.cxx
pu_info.cxx
strtab.cxx
symtab.cxx
symtab_verify.cxx
wn.cxx
wn_map.cxx
wn_pragmas.cxx
wn_simp.cxx
wn_util.cxx
wutil.cxx
xstats.cxx
intrn_info.cxx)

set(BE_COM_SRC
wssa_defs.cxx
wssa_sym.cxx
wssa_mgr.cxx
wssa_wn.cxx
wssa_io.cxx
wssa_utils.cxx )

set(COMMON_COM_TARG_CXX_SRC
config_targ.cxx
config_elf_targ.cxx
targ_const.cxx
#targ_sim.cxx
)

set(COMMON_COM_TARG_SRC
  config_host.c
  config_platform.c
)

foreach(ONE_C_FILE IN LISTS COMMON_COM_SRC)
  list(APPEND IR_TOOLS_SRC ${COMON_COM_DIR}/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS COMMON_COM_TARG_SRC)
  list(APPEND IR_TOOLS_SRC ${COMMON_COM_DIR}/x8664/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS COMMON_COM_CXX_SRC)
  list(APPEND IR_TOOLS_SRC ${COMMON_COM_DIR}/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS COMMON_COM_TARG_CXX_SRC)
  list(APPEND IR_TOOLS_SRC ${COMMON_COM_DIR}/x8664/${ONE_C_FILE})
endforeach()

foreach(ONE_C_FILE IN LISTS BE_COM_SRC)
  list(APPEND IR_TOOLS_SRC ${BE_COM_DIR}/${ONE_C_FILE})
endforeach()

set(IR_A2B_SRC
  ${IR_TOOLS_SRC_DIR}/ir_a2b.cxx
)

set(IR_SIZE_SRC
  ${IR_TOOLS_SRC_DIR}/ir_size.cxx
)

set(IR_WALKER_SRC
  ${IR_TOOLS_SRC_DIR}/ir_walker.cxx
)

