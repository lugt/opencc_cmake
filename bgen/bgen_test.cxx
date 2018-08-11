extern void JGEN_File_Finish (void) ;
extern void JGEN_Finish () ;
extern void JGEN_File_Init(char *);
extern void JGEN_Init(char *);


int main(){
  const char * p = "MyOutput.B";
  printf("######## start init, output file path: %s.\n", p);
  JGEN_Init((char *) p);
  JGEN_File_Init((char *) p);

  printf("######## finishing BGEN.\n");
  JGEN_Finish();
  JGEN_File_Finish();
  printf("######## finish all.\n");
  
    
}
