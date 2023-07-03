typedef void (*library_func_t)(void) ; 
library_func_t avm_getlibraryfunc (char *) ; 

void libfunc_print() ; 
void libfunc_sin();
void libfunc_sqrt() ; 
void libfunc_cos() ;
void libfunc_input() ;
void libfunc_totalarguments() ;
void libfunc_argument() ;
void libfunc_typeof() ;
void libfunc_strtonum() ;
void libfunc_objectcopy() ;
void libfunc_objecttotalmembers() ;
void libfunc_objectmemberkeys() ;

void avm_calllibfunc(char *);
library_func_t avm_getlibraryfunc(char *) ; 
int avm_totalactuals(void) ; 
struct avm_memcell *avm_getactual(int) ; 
int avm_get_envvalue(int );
char* avm_tostring(struct avm_memcell*);
void libfunc_strtonum(){
float conver_float(struct avm_memcell*);