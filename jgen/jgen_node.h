#ifndef JGEN_NODE_H
#define JGEN_NODE_H

#include <json/json.h>
#include <string>

using namespace std;

class JGEN_NODE{
  wn * whirl;
  string name;
  JGEN_NODE root;
}

class JGEN_Function : public JGEN_NODE{
  JGEN_Function(JGEN_Root parent){
    root = parent;

    if (!map_mempool_initialized) {
      MEM_POOL_Initialize(&Map_Mem_Pool, "Map_Mem_Pool" , FALSE);
      map_mempool_initialized = TRUE;
    } else {
      MEM_POOL_Pop(&Map_Mem_Pool);
    }

    MEM_POOL_Push(&Map_Mem_Pool);
    
    /* create the map table for the next PU */
    (void)WN_MAP_TAB_Create(&Map_Mem_Pool);
    New_Scope (CURRENT_SYMTAB + 1, Malloc_Mem_Pool, TRUE);
    jgen_set_line_and_file (lineno, fn);    
  }
}

class JGEN_Variable : public JGEN_NODE{
}

class JGEN_Root : public JGEN_NODE{
  JGEN_Root();
  string output_file;
  void init();
  void finish();

}

void JGEN_Root::finish(){
  Verify_SYMTAB (GLOBAL_SYMTAB);
  Write_Global_Info (PU_Tree_Root);
  Close_Output_Info ();
  IR_reader_finish ();
  MEM_POOL_Pop (&MEM_src_pool);
}

void JGEN_Root::init(const char * fn){
  Open_Output_Info ( fn );
}


#endif
