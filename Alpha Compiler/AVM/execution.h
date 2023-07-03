
void exec_assign(struct instruction *);

void exec_add(struct instruction *);

void exec_sub(struct instruction *);

void exec_mul(struct instruction *);

void exec_uminus(struct instruction *);

void exec_div(struct instruction *);

void exec_mod(struct instruction *);

void exec_jeq(struct instruction *);

void exec_jne(struct instruction *);

void exec_jge(struct instruction *);

void exec_jle(struct instruction *);

void exec_jlt(struct instruction *);

void exec_jgt(struct  instruction *);

void exec_call(struct  instruction *);

void exec_pusharg(struct  instruction *);

void exec_funcenter(struct  instruction *);

void exec_funcexit(struct  instruction *);

void exec_newtable(struct  instruction *);

void exec_tablegetelem(struct  instruction *);

void exec_tablesetelem(struct  instruction *);

void exec_nop(struct  instruction *);

void execute_cycle();

//------------------------

float add_impl(float , float );

float sub_impl(float , float );

float mul_impl(float , float );

float div_impl(float  , float );

float mod_impl(float  , float );

void execute_arithmetic(struct instruction * );

unsigned int  int_tobool(struct avm_memcell * );

unsigned int  float_tobool(struct avm_memcell * );

unsigned int  string_tobool(struct avm_memcell * );

unsigned int bool_tobool(struct avm_memcell * );

unsigned int table_tobool(struct avm_memcell * );

unsigned int userfunc_tobool(struct avm_memcell * );

unsigned int libfunc_tobool(struct avm_memcell * );

unsigned int nil_tobool(struct avm_memcell * );

unsigned int undef_tobool(struct avm_memcell * );

struct avm_memcell* push_func_in_stack(struct vmarg * , struct avm_memcell* );

struct avm_memcell* pop_func_in_stack();

void avm_memcellclear(struct avm_memcell* );


