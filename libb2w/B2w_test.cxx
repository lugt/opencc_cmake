extern void B2W_file_finish (void) ;
extern void B2W_finish () ;
extern void B2W_file_init(char *);
extern void B2W_init(char *);

#include <stdio.h>
#include "B2w_handler.h"
#include "B2w_common.h"

int main(){

  const char * p = "MyOutput.B";
  Tracing_Enabled = true;
  printf("######## start init, output file path: %s.\n", p);
  B2W_init((char *) p);
  B2W_file_init((char *) p);
  printf("######## finishing BGEN.\n");

  long long t = B2W_wn_int_const(1);
  printf("--- wn_int_const : %lld", t);
  
  B2W_finish();
  B2W_file_finish();
  printf("######## finish all.\n");    
}
