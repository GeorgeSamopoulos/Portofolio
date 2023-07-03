struct avm_table ; 
unsigned static int curr_size  = 0 ; // current size of memory 

//------------------------------ LISTS 

struct str_node{
    int index;
    char * value;
    struct str_node * next;

};

struct int_node{
    int index;
    int value;
    struct int_node * next;


};

struct float_node{
    int index;
    float value;
    struct float_node * next;
};

struct userf_node{
    int index;
    int address;
    int localsize;
    int formalsize;
    char * id;
    int return_address;
    struct userf_node * next;
};

struct libf_node{
    int index;
    char * id;
    struct libf_node * next;
};

struct instruction{
    int srcLine;
    int opcode;
    struct vmarg* result;
    struct vmarg* arg1;
    struct vmarg* arg2;
    struct instruction * next;
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

struct vmarg {
    enum vmarg_t type;
    unsigned int val; 
};

void read_binfile();
void insert_strConst(int,char*);
void insert_intConst(int, int);
void insert_floatConst(int, float);
void insert_userfunc(int , int , int, int, char*);
void insert_libfunc(int, char*);
void insert_instruction(int, int, int , int , int , int , int , int , int );
void print_memories();
//------------------------------ END LISTS

struct func {
    int address; 
    struct  avm_memcell *form ; // list of formal arquments 
    struct avm_memcell *loc_var ; // list of local function's variables
    int form_num ; // number of formal arquments 
    int local_num ; // number of local variables ; 
    int return_address ; //pointer to return to the callee memory 
    struct avm_memcell * returndata; // return data
    struct func * next; //points to the next node
    //2 pointers gia top kai topsp prepei na skeftw ti tupou tha einai kai mporei na xreiastoume pointer datamem 
};


enum avm_memcell_t{
    int_m = 0 ,
    float_m = 1 ,
    string_m = 2 , 
    bool_m = 3   ,
    table_m = 4 , 
    userfunc_m = 5 , 
    libfunc_m = 6 , 
    nil_m = 7 , 
    undef_m = 8

};

struct data{
    int intVal; 
    float floatVal ; 
    char* strVal ; 
    int boolVal ; 
    struct avm_table* tableVal ;
    char* libfuncVal ; 
    struct func* funcVal ; 
};

struct avm_memcell { 
    enum avm_memcell_t type ;
    char * name;
    struct data *dat ; 
    struct avm_memcell *next ; 
};

// void add_stack(struct data * , int ) ; // pointer gia data kai int gia to enum avm_type 
// void init();
// struct data * create_add(double, char* , unsigned char , struct avm_table* , unsigned , int , char *);
// struct avm_memcell* return_cell(int , int  );
// int const_getnumber(struct invalue *);
// char* const_getstring(struct invalue*);
// void print_memory();
// void fill_main_memory(struct avm_memcell *);
struct avm_memcell *avm_translate_operand(struct vmarg *, struct avm_memcell * );
char* const_getstring(int );
int const_getint(int );
float const_getfloat(int );
char* const_getlib(int );
struct userf_node* const_getuserf(int );
struct avm_memcell *make_localVars(int );
struct avm_memcell * ith_local(int );