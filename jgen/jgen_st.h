#ifndef OSPREY_JGEN_ST_H
#define OSPREY_JGEN_ST_H

#include <vector>
#include <string>
#include <iostream>
#include "jgen_include.h"

// Return Params

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

namespace JGEN
{
    extern BOOL JGEN_processing_function_prototypes;
    extern BOOL JGEN_Keep_Zero_Length_Structs;

    class JGEN_SymbolTree_Base {

     public:

      virtual void init(void * tree) {};

      // Reading another node (next) (traverse)
      // @return whether there is one to be read(1), or none (0)
      virtual int next() {};

      // read Kind from Node
      virtual U64U getKind(){};

      // read Name from Node
      virtual std::string &getKindName(){};

      // read Kind from Node
      virtual unsigned long long getFlag(){};

      // get DefId form Node
      virtual int getJsonRefId(){};

      // get (Symbol) Name from Node
      virtual std::string &getJsonName(){};

      // retrieve the previously bound Idx
      virtual int getIdx(){};

      // bind Idx to the tree node
      virtual void setTypeIdx(int idx){};

      // bind Idx to the tree node
      virtual JGEN_SymbolTree_Base & getMemberFields(int idx){};

      virtual JGEN_SymbolTree_Base * getParent(){};
    };

    class JGEN_ST {

      static TY_IDX ty_idx;
      static ST *st;
      static char *name;
      static char tempname[32];
      static ST_SCLASS sclass;
      static ST_EXPORT eclass;
      static SYMTAB_IDX level;
      static U64U flag;
      static INT anon_count;
      static JGEN_SymbolTree_Base * context;
      static JGEN_SymbolTree_Base * node;

     public:
      static void getST(JGEN_SymbolTree_Base * tree, int SymTreeId);

     private:
      static bool isPublic (U64U flag)
      {
          return (flag & JGEN_ST_FLAG_MASK_PUBLIC) > 0;
      }

      static bool isWeak (U64U flag)
      {
          return (flag & JGEN_ST_FLAG_MASK_WEAK) > 0;
      }

      static bool isConstructor (U64U flag)
      {
          return 0;
      }

      static bool isPureVFunc (U64U flag)
      {
          return 0;
      }

      static bool isMethodOfClass (U64U flag)
      {
          return 0;
      }

      static int get_method_base_type ()
      {
          return 0;
      }

      static bool isContextNamespace (void *context)
      {
          return false;
      }

      static bool isContextRecord (void *context)
      {
          return false;
      }

      static bool isLangSpecific ()
      {
          return false;
      }

      static bool isReallyExtern ()
      {
          return false;
      }

      static bool isNoThrow ()
      {
          return false;
      }

      static TY_IDX get_related_TY ()
      {
          return 0;
      }

      static void create_func (U64U flag, std::string funcName, bool isMethod);

      static void createParam ();

      static void createVar (U64U kind, U64U flag);

      static void JGEN_add_pragma_to_location (WN_PRAGMA_ID id, ST *st)
      {

      }

      static int getCurrentSymtab ()
      {
          return 0;
      }

      static bool isInitial (U64U flag)
      {
          return true;
      }

      static bool isCommon ()
      {
          return true;
      }

      static bool isExternal ()
      {
          return true;
      }

      static bool isStatic ()
      {
          return true;
      }

      static void createRetVal ()
      {

      }

      static bool hasName (int flag)
      {
          return true;
      }

      static bool is_guard_var ()
      {
          return false;
      }

      static bool startsWith (const char *starter)
      {

      }

      static void createNameSpace ();

      static int getLineNumber ()
      {
          return lineNum;
      }

      JGEN_ST ()
      {
          anon_count = 0;
      }
     public:
      static void setName(char *name);
      static void setFlag(U64U flag);
      static void setLineNum(int lineNum);
     private:
      static void createClass ();
      static int lineNum;
    };

}

#endif
