#ifndef memory_struct_h
#define memory_struct_h
//
extern struct ram OS_Ram[] ;
extern struct ram PR_Ram[] ;
extern int Var_Mem[] ;
extern int Stck_Mem[] ;
extern int Eip_Mem[] ;  // point to line of ram which read .
extern int reg[] ;
extern int os_pr_flag ;
/*
struct memory_struct{
    char command[5] ;
    int v1 ,
        v2 ,
        v3 ;
};
*/
#endif