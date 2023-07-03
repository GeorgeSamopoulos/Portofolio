
struct incomplete_q{
    struct quad * q;
    struct incomplete_q * next;
};

struct incomplete_i{
    struct instruction * i;
    struct incomplete_i * next;
};

enum vmarg_t{
    libfunc_a,
    userfunc_a,
    nil_a,
    float_a,
    int_a,
    bool_a,
    string_a,
    global_a,
    local_a,
    formal_a,
    retval_a,
    label_a
};

enum vmopcode{
    add_v, 
    sub_v,
    mul_v, 
    divide_v, 
    mod_v,
    tablecreate_v,
    tablesetelem_v,
    tablegetelem_v,
    assign_v,
    nop_v,
    jump_v, 
    if_eq_v,	
    if_not_eq_v,
    if_greater_v, 
    if_greatereq_v, 
    if_less_v,
    if_lesseq_v,
    not_v, 
    or_v,
    and_v,
    call_v, 
    param_v,
    getretval_v,
    funcstart_v,
    ret_v,
    funcend_v
};

struct vmarg {
    enum vmarg_t type;
    unsigned int val; 
};

struct instruction {
    enum vmopcode opcode;
    struct vmarg * result;
    struct vmarg * arg1;
    struct vmarg * arg2;
    unsigned int srcLine;
    struct instruction * next;
};
enum libfunc_t{
    print_t,
    input_t,
    objectmemberkeys_t,
    objecttotalmembers_t,
    objectcopy_t,
    totalarguments_t,
    argument_t,
    typeof_t,
    strtonum_t,
    sqrt_t,
    cos_t,
    sin_t
};
struct func {

	unsigned int 	address;
	unsigned int 	localvars;
	unsigned int 	formalargs;
	unsigned int 	scope;
	char* 			id;

};
struct int_table{
    int intConst;
    struct int_table* next;
};
struct float_table{
    float floatConst;
    struct float_table* next;
};
struct str_table{
    char* strConst;
    struct str_table* next;
};
struct func_table{
    unsigned int 	address;
	unsigned int 	localvars;
	unsigned int 	formalargs;
	unsigned int 	scope;
	char* 			id;
    struct func_table* next;
};
void make_operand (struct expr * , struct vmarg **);
void gen_ADD();
void gen_ADD(struct quad *);
void gen_SUB(struct quad *);
void gen_MUL(struct quad *);
void gen_DIV(struct quad *);
void gen_MOD(struct quad *);
void gen_NEWTABLE(struct quad *);
void gen_TABLESETELEM(struct quad *);
void gen_TABLEGETELEM(struct quad *);
void gen_ASSIGN(struct quad *);
void gen_NOP(struct quad *);
void gen_JUMP(struct quad *);
void gen_IF_EQ(struct quad *);
void gen_IF_NOTEQ(struct quad *);
void gen_IF_GREATER(struct quad *);
void gen_IF_GREATEREQ(struct quad *);
void gen_IF_LESS(struct quad *);
void gen_IF_LESSEQ(struct quad *);
void gen_NOT(struct quad *);
void gen_OR(struct quad *);
void gen_AND(struct quad *);
void gen_CALL(struct quad *);
void gen_PARAM(struct quad *);
void gen_GETRETVAL(struct quad *);
void gen_FUNCSTART(struct quad *);
void gen_RETURN(struct quad *);
void gen_FUNCEND(struct quad *);
void generate_relational (int,struct quad *);
void generate_i(int,struct quad *);
void gen(void);
void make_booloperand(struct vmarg ** , int);
void addi(struct instruction *);
unsigned int con(int );
int find_taddress(int);
void fill_incomplete_jumps();
void add_inc_i(struct instruction* i);
void add_inc_q(struct quad* q);
void print_in();
void print_lists(struct expr*);
int find_libfunc(char* );
int consts_newString(char* );
int const_newFloat(float );
int const_newInt(int );
int new_userFunc(char* , int , int , int , int );
int find_userFunc(char* , int ,int , int , int );
void read_binfile();
void create_bin();
