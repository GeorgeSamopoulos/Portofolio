enum iopcode{
        assign, add, sub,
        mul, divide, mod,
        uminus,	and, or,
        not, if_eq,	if_not_eq,
        if_lesseq,	if_greatereq, if_less,
        if_greater,	call, param,
        ret, getretval,	funcstart,
        funcend, jump, tablecreate,	
        tablegetelem, tablesetelem
};

enum expr_t {
        var_e ,
        tableitem_e,

        programfunc_e,
        libraryfunc_e,

        intexpr_e,
        floatexpr_e,
        boolexpr_e,
        assignexpr_e,
        newtable_e,

        constint_e,
        constfloat_e,
        constbool_e,
        conststring_e,

        nil_e,
};

struct expr {
        enum expr_t      type;
        struct hashnode* sym;
        struct expr*     index;
        float            floatConst;
        int              intConst;
        char*            strConst;
        int              boolConst;
        struct expr*     next;
};

struct quad {
        int             quadno;
        enum iopcode    op;
        struct expr*    result;
        struct expr*    arg1;
        struct expr*    arg2;
        unsigned        label;
        unsigned        line;
        struct quad*    next ; //----
        int             taddress;
};

struct bcr_stack{
        struct jump_stack* head;
        struct bcr_stack* next;
};

struct jump_stack{
        struct quad* jump;
        struct jump_stack* next;
};

struct loop{
        int num;
        struct loop* next;
};
struct local_flag{
        int num;
        struct local_flag* next;
};
struct quad* emit(enum iopcode, struct expr*, struct expr*, struct expr*, int, int);

struct hashnode* find_sym(char*, char*, char*,  int);

void fillExp(struct expr*);

struct expr * find_expr(char*, char*, char*, int);

char * var_name(void);

enum expr_t change_type(struct expr*);

void print_quads();

struct expr* copy_expr(struct expr*);

int arith_compare_type(struct expr*, struct expr*);

struct expr * arith_calc(char,struct expr *,struct expr *, struct expr *);

enum expr_t arith_ret_type(int);

int compare_t(struct expr *, struct expr *);

void make_boolean(struct expr*);

struct expr * compare_calc(char *  , struct expr * ,struct expr *  , struct expr *  );

void print_expr();

void reset_var_name();

struct expr * log_calc(char *, struct expr *, struct expr *,struct expr *);

void fill_jump_quads(struct quad* );

void fill_label_jumps();

void push_jump_stack(struct quad*, struct jump_stack**);

struct quad* pop_jump_stack(struct jump_stack**);

void push(int, struct loop**);

int pop(struct loop**);

void fill_elist_quads(enum iopcode ,struct expr* ,int ,struct quad** );

void emit_elist_quads(struct quad** );

struct expr * insert_index(struct expr *,struct expr *);

struct quad * creat_q(struct expr * , struct expr *);

struct expr* add_e(struct expr * , struct expr *);

struct expr* free_temp(struct expr *);

int check_table(struct expr* tabl); 

void fill_tabelem(struct expr* tabl , struct expr* elem) ; 

struct expr* check_index(struct expr* tabl , char* name);

struct expr* find_index(struct expr* tabl , char* name);

struct expr* check_index2(struct expr* table , struct expr* elem );

struct expr* update_index (char* name , struct expr* in);

int non_boll_log_calc(struct expr* );

void push_local(int el, struct local_flag**);

int pop_local(struct local_flag** );

void push_bcr_stack(struct bcr_stack**);

struct bcr_stack* pop_bcr_stack(struct bcr_stack** );