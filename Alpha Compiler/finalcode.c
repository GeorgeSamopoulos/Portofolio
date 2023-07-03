#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "syntax_functions.h"
#include "intermediate.h"
#include "finalcode.h"
struct avm_memcell *main_memory=NULL  ;
extern int quad_count;
extern struct quad* mainq;
struct incomplete_q * incomplete_jump_quad=NULL;
struct incomplete_i * incomplete_jump_instr=NULL;
struct instruction * inlist=NULL;

int strConsts_length = 0;
int intConsts_length = 0;
int floatConsts_length = 0;
int userfunc_length = 0;
int libfunc_length=12;

struct str_table* strConsts_table = NULL;
struct int_table* intConsts_table = NULL;
struct float_table* floatConsts_table = NULL;
struct func_table* userfunc_table = NULL;

typedef void (*generator_fun_t)(struct quad*);
int icount=0;

generator_fun_t gens [] = {
    gen_ADD,
    gen_SUB,
    gen_MUL,
    gen_DIV,
    gen_MOD,
    gen_NEWTABLE,
    gen_TABLESETELEM,
    gen_TABLEGETELEM,
    gen_ASSIGN,
    gen_NOP,
    gen_JUMP,
    gen_IF_EQ,
    gen_IF_NOTEQ,
    gen_IF_GREATER,
    gen_IF_GREATEREQ,
    gen_IF_LESS,
    gen_IF_LESSEQ,
    gen_NOT,
    gen_OR,
    gen_AND,
    gen_CALL,
    gen_PARAM,
    gen_GETRETVAL,
    gen_FUNCSTART,
    gen_RETURN,
    gen_FUNCEND,
};


void make_operand (struct expr* e,struct vmarg ** arg) { 
    switch (e->type) {
/* All those below use a variable for storage
    */  
        case var_e :
        case tableitem_e: 
        case floatexpr_e:
        case intexpr_e: 
        case boolexpr_e: 
        case newtable_e : {
                (*arg)->val = e->sym->offset;
                switch  (e->sym->space){
                    case programvar :    (*arg)->type = global_a; break;
                    case functionlocal : (*arg)->type = local_a;  break;
                    case formalarg :    (*arg)->type = formal_a; break;
                    default : assert(0);
                }
                break;
        }
        case constbool_e: {
            (*arg)->val = e->boolConst;
            (*arg)->type = bool_a;    
            break ;
        }
        case conststring_e: {
            
            (*arg)->val = consts_newString(e->strConst);
            (*arg)->type = string_a ;    
            break;
        }case constint_e:{
            (*arg)->val =  const_newInt(e->intConst); 
            (*arg)->type = int_a; 
            break ;

        }case constfloat_e:{
            (*arg)->val = const_newFloat(e->floatConst); 
            (*arg)->type = float_a; 
            break ;

        }case nil_e:{ 
            (*arg)->type=nil_a;
            break;
        }case programfunc_e :{
            (*arg)->type = userfunc_a;
            (*arg)->val= find_userFunc(e->sym->name, e->sym->scope, e->sym->local_num, e->sym->formal_num, icount);
            break;
        }case libraryfunc_e : {
            (*arg)->type = libfunc_a ;
            (*arg)->val= find_libfunc(e->sym->name);
            break;
        }
        default : assert(0) ;
    }
}
int find_userFunc(char* func, int scope,int locals, int formals, int address){
    struct func_table*tmp = userfunc_table;
    for(int i=0; i<userfunc_length;i++){
    // printf("%s %d",tmp->id,tmp->scope);

        if(strcmp(tmp->id,func)==0 && scope==tmp->scope){
            return i;
        }
        tmp=tmp->next;
    }
    return new_userFunc(func, scope, locals, formals, address);
}
int new_userFunc(char* name, int scope, int locals, int formals, int address){
        struct func_table* new = (struct func_table*) malloc(sizeof(struct func_table));
        new->address = address;
        new->localvars = locals;
        new->formalargs =  formals;
        new->scope = scope;
        new->id = strdup(name);
        new->next=NULL;
        if(userfunc_table==NULL){
            userfunc_table=new;
        }else{
            struct func_table* tmp=userfunc_table;
            while(tmp->next!=NULL){
                tmp=tmp->next;
            }
            tmp->next=new;
        }
        userfunc_length++;
    return userfunc_length-1;
}
int const_newInt(int num){
    struct int_table* new = (struct int_table*) malloc(sizeof(struct int_table));
    new->intConst=num;
    new->next=NULL;
    if(intConsts_table==NULL){
        intConsts_table=new;
    }else{
        struct int_table* tmp=intConsts_table;
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=new;
    }
    intConsts_length++;
    return intConsts_length-1;
}

int const_newFloat(float num){
    struct float_table* new = (struct float_table*) malloc(sizeof(struct float_table));
    new->floatConst=num;
    new->next=NULL;
    if(floatConsts_table==NULL){
        floatConsts_table=new;
    }else{
        struct float_table* tmp=floatConsts_table;
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=new;
    }
    floatConsts_length++;
    return floatConsts_length-1;
}

int consts_newString(char* str){
    struct str_table* new = (struct str_table*) malloc(sizeof(struct str_table));
    // printf("%d\n",icount);
    new->strConst=str;
    new->next=NULL;
    if(strConsts_table==NULL){
        strConsts_table=new;
    }else{
        struct str_table* tmp=strConsts_table;
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=new;
    }
    strConsts_length++;
    return strConsts_length-1;
}

int find_libfunc(char* name){
    if(strcmp(name,"print")){
        return print_t;
    }
    if(strcmp(name,"input")){
        return input_t;
    }
    if(strcmp(name,"objectmemberkeys")){
        return objectmemberkeys_t;
    }
    if(strcmp(name,"objecttotalmembers")){
        return objecttotalmembers_t;
    }
    if(strcmp(name,"objectcopy")){
        return objectcopy_t;
    }
    if(strcmp(name,"totalarguments")){
        return totalarguments_t;
    }
    if(strcmp(name,"argument")){
        return argument_t;
    }
    if(strcmp(name,"typeof")){
        return typeof_t;
    }
    if(strcmp(name,"strtonum")){
        return strtonum_t;
    }
    if(strcmp(name,"sqrt")){
        return sqrt_t;
    }
    if(strcmp(name,"cos")){
        return cos_t;
    }
    if(strcmp(name,"sin")){
        return sin_t;
    }
    return -1;
}

void gen_ADD(struct quad * q){
    generate_i(add_v,q);

}


void gen_SUB(struct quad * q){
    generate_i(sub_v,q);
}


void gen_MUL(struct quad * q){
    generate_i(mul_v,q);
}

void gen_DIV(struct quad * q){
    generate_i(divide_v,q);
}

void gen_MOD(struct quad * q){
    generate_i(mod_v,q);
}

void gen_NEWTABLE(struct quad * q){
    generate_i(tablecreate_v,q);
}

void gen_TABLESETELEM(struct quad * q){
    generate_i(tablesetelem_v,q);
    
}

void gen_TABLEGETELEM(struct quad * q){
    generate_i(tablegetelem_v,q);
    
}
void gen_ASSIGN(struct quad * q){
    generate_i(assign_v,q);
}
void gen_NOP(struct quad * q){
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->srcLine=q->line;
    i->next=NULL;
    i->arg1=NULL;
    i->arg2=NULL;
    i->result=NULL;
    i->opcode=nop_v;
    addi(i);
}


void generate_i(int op,struct quad * q){
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    if(q->arg1!=NULL) i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    if(q->arg2!=NULL||q->op==uminus) i->arg2=(struct vmarg *)malloc(sizeof(struct vmarg));
    if(q->result!=NULL) i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->next=NULL;
    i->opcode=op;
    i->srcLine=q->line;
    if(q->arg1!=NULL) make_operand(q->arg1,&(i->arg1));
    else{
        i->arg1=NULL;
    }
    if(q->op==uminus){
        i->arg2->val =  const_newInt(-1); 
        i->arg2->type = int_a;
    }else if(q->arg2!=NULL){
        make_operand(q->arg2,&(i->arg2));
    }else{
        i->arg2=NULL;
    }
    if(q->result!=NULL) make_operand(q->result,&(i->result));
    else{
        i->result=NULL;
    }
    q->taddress=icount;
    icount++;
    addi(i);
}
//------------------------RELATIONAL---------------------------------
void gen_JUMP(struct quad * q){
    generate_relational(jump_v,q);
}

void gen_IF_EQ(struct quad * q){
    generate_relational(if_eq_v,q);
}

void gen_IF_NOTEQ(struct quad * q){
    generate_relational(if_not_eq_v,q);
}

void gen_IF_GREATER(struct quad * q){
    generate_relational(if_greater_v,q);
}

void gen_IF_GREATEREQ(struct quad * q){
    generate_relational(if_greatereq_v,q);
}

void gen_IF_LESS(struct quad * q){
    generate_relational(if_less_v,q);
}

void gen_IF_LESSEQ(struct quad * q){
    generate_relational(if_lesseq_v,q);
}



void generate_relational (int op,struct quad * q) {
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    if(q->arg1!=NULL) i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    if(q->arg2!=NULL) i->arg2=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->next=NULL;
	i->opcode = op;
    i->srcLine=q->line;
	if(q->arg1!=NULL)make_operand(q->arg1,&(i->arg1));
    else{
        i->arg1=NULL;
    }
    if(q->arg2!=NULL) make_operand(q->arg2,&(i->arg2));
    else{
        i->arg2=NULL;
    }
    i->result->type=label_a;
    q->taddress=icount;
    icount++;
    addi(i);
    add_inc_q(q);
    add_inc_i(i);
}

//------------------------------ END REL---------------------------------------
void add_inc_q(struct quad* q){

    if(incomplete_jump_quad==NULL){
        incomplete_jump_quad=(struct incomplete_q *)malloc(sizeof(struct incomplete_q));
        incomplete_jump_quad->q=q;
        incomplete_jump_quad->next=NULL;
        return;
    }
    struct incomplete_q * tmp_quad = incomplete_jump_quad;
    while(tmp_quad->next!=NULL){
        tmp_quad=tmp_quad->next;
    }
    tmp_quad->next=(struct incomplete_q *)malloc(sizeof(struct incomplete_q));
    tmp_quad->next->q=q;
    tmp_quad->next->next=NULL;
}

void add_inc_i(struct instruction* i){
    if(incomplete_jump_instr==NULL){
        incomplete_jump_instr=(struct incomplete_i *)malloc(sizeof(struct incomplete_i));
        incomplete_jump_instr->i=i;
        incomplete_jump_instr->next=NULL;
        return;
    }
    struct incomplete_i * tmp_instr = incomplete_jump_instr;
    while(tmp_instr->next!=NULL){
        tmp_instr=tmp_instr->next;
    }
    tmp_instr->next=(struct incomplete_i *)malloc(sizeof(struct incomplete_i));
    tmp_instr->next->i=i;
    tmp_instr->next->next=NULL;
}


void addi(struct instruction * i){
    if(inlist==NULL){
        inlist=i;
        return;
    }
    struct instruction * t = inlist;
    while(t->next!=NULL){  
        t=t->next;
    }
    t->next=i;
}

void gen(void){
    struct quad * t = mainq;
    int i=0;
    while(t!=NULL){
        // printf("haha %d\n",++i);
        (*gens[con(t->op)])(t);
        t=t->next;
    }
    fill_incomplete_jumps();
}


unsigned int con(int i){
    if(i==add){
        return add_v;
    }
    if(i==sub){
        return sub_v;
    }
    if(i==mul){
        return mul_v;
    }
    if(i==assign){
        return assign_v;
    }
    if(i==divide){
        return divide_v;
    }
    if(i==mod){
        return mod_v;
    }
    if(i==and){
        return and_v;
    }
    if(i==or){
        return or_v;
    }
    if(i==not){
        return not_v;
    }
    if(i==if_eq){
        return if_eq_v;
    }
    if(i==if_not_eq){
        return if_not_eq_v;
    }

    if(i==if_lesseq){
        return if_lesseq_v;
    }

    if(i==if_greatereq){
        return if_greatereq_v;
    }

    if(i==if_less){
        return if_less_v;
    }
    if(i==if_greater){
        return if_greater_v;
    }
    if(i==call){
        return call_v;
    }
    if(i==param){
        return param_v;
    }
    if(i==ret){
        return ret_v;
    }
    if(i==getretval){
        return getretval_v;
    }
    if(i==funcstart){
        return funcstart_v;
    }
    if(i==funcend){
        return funcend_v;
    }
    if(i==jump){
        return jump_v;
    }
    if(i==tablecreate){
        return tablecreate_v;
    }
    if(i==tablegetelem){
        return tablegetelem_v;
    }
    if(i==tablesetelem){
        return tablesetelem_v;
    }
    if(i==uminus){
        return mul_v;
    }
    return nop_v;
}



void gen_NOT(struct quad * q){
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=if_eq_v;
    i->srcLine=q->line;
    make_operand(q->arg1,&(i->arg1));
    make_booloperand(&(i->arg2),0);
    i->result->type=label_a;
    i->result->val=icount+3;
    icount++;
    addi(i);
    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=assign_v;
    i->srcLine=q->line;
    make_booloperand(&(i->arg1),0);
    make_operand(q->result,&(i->result));
    icount++;
    addi(i);

    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=NULL;
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=jump_v;
    i->srcLine=q->line;
    i->result->type=label_a;
    i->result->val =icount+2;
    icount++;
    addi(i);

    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=assign_v;
    i->srcLine=q->line;
    make_booloperand(&(i->arg1),1);
    i->arg2=NULL;
    i->result->type=label_a;
    make_operand(q->result,&(i->result));
    addi(i);
}

void gen_OR(struct quad * q){
    q->taddress=icount;
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=if_eq_v;
    i->srcLine=q->line;
    make_operand(q->arg1,&(i->arg1));
    make_booloperand(&(i->arg2),1);
    i->result->type=label_a;
    icount++;
    i->result->val=icount+4;
    addi(i);

    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=if_eq_v;
    i->srcLine=q->line;
    make_operand(q->arg2,&(i->arg1));
    make_booloperand(&(i->arg2),1);
    i->result->type=label_a;
    icount++;
    i->result->val=icount+3;
    addi(i);

    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=assign_v;
    i->srcLine=q->line;
    make_booloperand(&(i->arg1),0);
    make_operand(q->result,&(i->result));
    icount++;
    addi(i);

    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=NULL;
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=jump_v;
    i->srcLine=q->line;
    i->result->type=label_a;
    icount++;
    i->result->val=icount+2;
    addi(i);

    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=assign_v;
    i->srcLine=q->line;
    make_booloperand(&(i->arg1),1);
    make_operand(q->result,&(i->result));
    icount++;
    addi(i);

}

void gen_AND(struct quad * q){
    q->taddress=icount;
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=if_eq_v;
    i->srcLine=q->line;
    make_operand(q->arg1,&(i->arg1));
    make_booloperand(&(i->arg2),0);
    i->result->type=label_a;
    icount++;
    i->result->val=icount+4;
    addi(i);

    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=if_eq_v;
    i->srcLine=q->line;
    make_operand(q->arg2,&(i->arg1));
    make_booloperand(&(i->arg2),0);
    i->result->type=label_a;
    icount++;
    i->result->val=icount+3;
    addi(i);

    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=assign_v;
    i->srcLine=q->line;
    make_booloperand(&(i->arg1),1);
    make_operand(q->result,&(i->result));
    icount++;
    addi(i);

    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=NULL;
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=jump_v;
    i->srcLine=q->line;
    i->result->type=label_a;
    icount++;
    i->result->val=icount+2;
    addi(i);

    i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->opcode=assign_v;
    i->srcLine=q->line;
    make_booloperand(&(i->arg1),0);
    make_operand(q->result,&(i->result));
    icount++;
    addi(i);
}


void gen_CALL(struct quad * q){
    q->taddress=icount;
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=NULL;
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->next=NULL;
    i->opcode=call_v;
    i->srcLine=q->line;
    make_operand(q->result,&(i->result));
    icount++;
    addi(i);
}
void gen_PARAM(struct quad * q){
    q->taddress=icount;
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=NULL;
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->next=NULL;
    i->opcode=param_v;
    i->srcLine=q->line;
    make_operand(q->result,&(i->result));
    icount++;
    addi(i);
}
void gen_GETRETVAL(struct quad * q){
    q->taddress=icount;
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->next=NULL;
    i->opcode=assign_v;
    i->srcLine=q->line;
    make_operand(q->result,&(i->result));
    i->arg1->type=retval_a;
    icount++;
    addi(i);
}
void gen_FUNCSTART(struct quad * q){
    q->taddress=icount;
    q->result->sym->taddress=icount;
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=NULL;
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->next=NULL;
    i->opcode=funcstart_v;
    i->srcLine=q->line;
    q->taddress=icount;
    i->result->type=userfunc_a;
    i->result->val = new_userFunc(q->result->sym->name,q->result->sym->scope,q->result->sym->local_num,q->result->sym->formal_num,icount);
    icount++;
    addi(i);
}

void gen_RETURN(struct quad * q){
    q->taddress=icount;
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->next=NULL;
    i->result->type=retval_a;
    i->opcode=assign_v;
    i->srcLine=q->line;
    make_operand(q->result,&(i->arg1));
    icount++;
    addi(i);

}

void gen_FUNCEND(struct quad * q){
    q->taddress=icount;
    struct instruction * i = (struct instruction *) malloc(sizeof(struct instruction));
    i->arg1=NULL;
    i->arg2=NULL;
    i->result=(struct vmarg *)malloc(sizeof(struct vmarg));
    i->next=NULL;
    i->opcode=funcend_v;
    i->srcLine=q->line;
    make_operand(q->result,&(i->result));
    icount++;
    addi(i);
}

void make_booloperand(struct vmarg ** arg , int bool){
    (*arg)->val = bool;
    (*arg)->type = bool_a;
    return;
}


void fill_incomplete_jumps(){
    struct incomplete_i* tmp_instr = incomplete_jump_instr;
    struct incomplete_q* tmp_quad = incomplete_jump_quad;
    while(tmp_instr!=NULL){
        tmp_instr->i->result->val=find_taddress(tmp_quad->q->label);
        tmp_instr=tmp_instr->next;
        tmp_quad=tmp_quad->next;
    }
    return;
}

int find_taddress(int n){
    struct quad* tmp_quad=mainq;
    int i;
    if(quad_count==n){
        return icount;
    }
    while(tmp_quad->quadno!=n){
        tmp_quad=tmp_quad->next;
    }
    return tmp_quad->taddress;
}

void print_in(){
    printf("--------------------------------phase4------------------------------------------\n");
    char * t[]={"ADD", "SUB",
        "MUL", "DIVIDE", "MOD",
        "TABLECREATE",	"TABLEGETELEM","TABLESETELEM",
        "ASSIGN", "NOP","JUMP","IF_EQ",	"IF_NOT_EQ","IF_GREATER",	"IF_GREATEREQ",
        "IF_LESS","IF_LESSEQ","NOT", "OR","AND","CALL", "PARAM", "GETRETVAL",	"FUNCSTART",
        "RETURN","FUNCEND"};
    struct int_table* tmp = intConsts_table;
    int i=0;
    while(tmp!=NULL){
        printf("%d: %d, ",i, tmp->intConst);
        i++;
        tmp=tmp->next;
    }
    struct float_table* tmp1 = floatConsts_table;
    i=0;
        printf("\n");
    while(tmp1!=NULL){
        printf("%d: %d, ",i, tmp1->floatConst);
        i++;
        tmp1=tmp1->next;
    }
        printf("\n");
    struct str_table* tmp2 = strConsts_table;
    i=0;
    while(tmp2!=NULL){
        printf("%d: %s, ",i, tmp2->strConst);
        i++;
        tmp2=tmp2->next;
    }
        printf("\n");
    struct func_table* tmp3 = userfunc_table;
    i=0;
    while(tmp3!=NULL){
        printf("%d: %s %d, ",i, tmp3->id, tmp3->scope);
        i++;
        tmp3=tmp3->next;
    }
        printf("\n-------------------------\n");
    struct instruction * tempi = inlist;
    int c=1;
    while(tempi!=NULL){
        printf("%d: %s ", c, t[tempi->opcode]);
        if(tempi->result!=NULL){
            printf("%d %d ",tempi->result->type, tempi->result->val);
        }
        if(tempi->arg1!=NULL){
            printf("%d %d ",tempi->arg1->type, tempi->arg1->val);
        }
        if(tempi->arg2!=NULL){
            printf("%d %d ",tempi->arg2->type, tempi->arg2->val);
        }
        printf("(line %d)\n",tempi->srcLine);
        printf("\n");
        c++;
        tempi=tempi->next;
    }
    return;

}


void create_bin(int global_offset){

	FILE *fp = fopen("test.bin", "wb");
   	unsigned int magic_number = 340200501;
	int i =0;

   	fwrite(&magic_number,sizeof(unsigned int), 1, fp); 
	fwrite(&global_offset,sizeof(unsigned int),1,fp); 
    fwrite(&strConsts_length,sizeof(unsigned int), 1, fp); 
    struct str_table* tmp = strConsts_table;
    while(tmp!=NULL){
        unsigned int len = strlen(tmp->strConst);
		fwrite(&len,sizeof(unsigned int), 1, fp); 
	  	fwrite(tmp->strConst,sizeof(char) *len , 1, fp);
        tmp=tmp->next;
    }
    fwrite(&intConsts_length,sizeof(unsigned int), 1, fp); 
    struct int_table* tmp1 = intConsts_table;
    while(tmp1!=NULL){
        fwrite(&(tmp1->intConst),sizeof(int), 1, fp);
        tmp1=tmp1->next;
    }

    fwrite(&floatConsts_length,sizeof(unsigned int), 1, fp); 
    struct float_table* tmp2 = floatConsts_table;
    while(tmp2!=NULL){
        fwrite(&(tmp2->floatConst),sizeof(float), 1, fp);
        tmp2=tmp2->next;
    }
    
	fwrite(&userfunc_length,sizeof(unsigned int), 1, fp); 
    struct func_table* tmp3 = userfunc_table;
    while(tmp3!=NULL){
        fwrite(&(tmp3->address),sizeof(unsigned int), 1, fp); 
        fwrite(&(tmp3->formalargs),sizeof(unsigned int), 1, fp);
        fwrite(&(tmp3->localvars),sizeof(unsigned int), 1, fp); 
        unsigned int len = strlen(tmp3->id);
        fwrite(&len,sizeof(unsigned int), 1, fp);
        fwrite(tmp3->id,sizeof(char)*len , 1, fp);
        tmp3=tmp3->next;
    }

	
	fwrite(&libfunc_length,sizeof(unsigned int), 1, fp);
    char* libFuncs[12]={
        "print",
        "input",
        "objectmemberkeys",
        "objecttotalmembers",
        "objectcopy",
        "totalarguments",
        "argument",
        "typeof",
        "strtonum",
        "sqrt",
        "cos",
        "sin"
    };
	 
    for(i=0; i<12; i++){
		unsigned int len = strlen(libFuncs[i]);
		fwrite(&len,sizeof(unsigned int), 1, fp); 
		fwrite(libFuncs[i],sizeof(char)*len , 1, fp);
	}
    // icount--;
	fwrite(&icount,sizeof(unsigned int), 1, fp);
    struct instruction* tmp4 = inlist;
    int type = -1;
    int val = -1;
	while(tmp4!=NULL) {
		fwrite(&(tmp4->opcode),sizeof(int ), 1, fp);
 		if (tmp4->result!=NULL) {
 			  fwrite(&(tmp4->result->type),sizeof( int), 1, fp);
			  fwrite(&(tmp4->result->val),sizeof( int), 1, fp);
 		}else{
			fwrite(&type,sizeof( int), 1, fp);
			fwrite(&val,sizeof( int), 1, fp);

		}
		if (tmp4->arg1!=NULL) {
 			  fwrite(&(tmp4->arg1->type),sizeof( int), 1, fp);
			  fwrite(&(tmp4->arg1->val),sizeof( int), 1, fp);
 		}else{ 
			int type = -1;
            int val = -1;
			fwrite(&type,sizeof( int), 1, fp);
			fwrite(&val,sizeof( int), 1, fp);

		}
		if (tmp4->arg2!=NULL) {
 			  fwrite(&(tmp4->arg2->type),sizeof( int), 1, fp);
			  fwrite(&(tmp4->arg2->val),sizeof( int), 1, fp);
 		}
		else{
			fwrite(&type,sizeof( int), 1, fp);
			fwrite(&val,sizeof( int), 1, fp);

		}
        fwrite(&(tmp4->srcLine),sizeof(int), 1, fp);
        tmp4=tmp4->next;
	}
    fclose(fp);
	return;
}




void read_binfile(){
				FILE *fp = NULL;
				int i =0;
		 		//   fputs("2", fp);
	   		fp = fopen("out.bin", "rb");
		 		int magic;
		 		unsigned int totalglobal, totalStr, totalInts, totalFloats, totaluserF, totallibF, totalins;
	      fread(&magic, sizeof(int), 1, fp);
	      printf("\nmagic number is: %d \n", magic);
				fread(&totalglobal, sizeof(unsigned int), 1, fp);
                printf("\ntotal global is %d \n", totalglobal);
                fread(&totalStr, sizeof(unsigned int), 1, fp);
				printf("\ntotal string is %d \n", totalStr);

		    for(i=0; i<totalStr; i++){
								unsigned int len = 0;

							 if(fread(&len,sizeof(unsigned int), 1, fp) != 1) //length of each string
							 		printf("Error reading file \n");
							printf("size (%d)  ",len );

								char * str = (char *)malloc(sizeof(char )*len);
								assert(str);
							if(fread(str,sizeof(char )*len , 1, fp)!= 1)
								printf("Error reading file \n");
							printf("str: %s\n",str );
		    }

				fread(&totalInts, sizeof(unsigned int), 1, fp);
				printf("\ntotal nums is %d \n", totalInts);
				for(i=0; i<totalInts; i++){
			        int num;
			        fread(&num,sizeof(int), 1, fp);
			        printf("Int:%d\n", num);
				}
                fread(&totalFloats, sizeof(float), 1, fp);
				printf("\ntotal nums is %d \n", totalFloats);
				for(i=0; i<totalFloats; i++){
			        float flo;
			        fread(&flo,sizeof(int), 1, fp);
			        printf("Int:%f\n", flo);
				}

				fread(&totaluserF, sizeof(unsigned int), 1, fp);
				printf("\ntotal userfuncs is %d \n", totaluserF);

	 	    for(i=0; i<totaluserF; i++){
	 							unsigned int len, addr, formalsize, localsize;
								fread(&addr,sizeof(unsigned int), 1, fp); //total strings
                                fread(&formalsize,sizeof(unsigned int), 1, fp);
								fread(&localsize,sizeof(unsigned int), 1, fp); //total strings
	 						  	fread(&len,sizeof(unsigned int), 1, fp); //total strings
								char * id = malloc(sizeof(char )*len);
	 	  	        			fread(id,sizeof(char )*len , 1, fp);
								printf("size (%d) of userF: %s, with address %d, foramlSize %d and localsize %d\n",len, id, addr,formalsize, localsize );


	 	    }
				fread(&totallibF, sizeof(unsigned int), 1, fp);
				printf("\ntotal libfuncs is %d \n", totallibF);
				for(i=0; i<totallibF; i++){
								unsigned int len;
							  fread(&len,sizeof(unsigned int), 1, fp); //length of each string
								char * libF = malloc(sizeof(char )*(len+1));
								fread(libF,sizeof(char )*len  , 1, fp);
                                libF[len]='\0';
								printf("size (%d) of libF: %s\n",len, libF );
		    }

				fread(&totalins, sizeof(unsigned int), 1, fp);
				printf("\ntotal instructions is %d \n", totalins);


					 for (i = 0; i < totalins; i++) {
						 			 int opcode, type, val,line;
									 fread(&opcode,sizeof(int ), 1, fp);
									 fread(&type,sizeof( int), 1, fp);
					 			   fread(&val,sizeof( int), 1, fp);
									 //TODO
									/* if(type == -1) //ignore
									 if(val == -1) //ignore
									 */
									 printf("%d) opcode(%d) RESULT: type(%d), value(%d) \n",i+1, opcode, type, val );
									 fread(&type,sizeof( int), 1, fp);
					 			   fread(&val,sizeof( int), 1, fp);
									 printf("\tARG1: type(%d), value(%d) \n", type, val );
									 fread(&type,sizeof( int), 1, fp);
					 			   fread(&val,sizeof( int), 1, fp);
									 printf("\tARG2: type(%d), value(%d) \n", type, val );
                                     fread(&line,sizeof( int), 1, fp);
									 printf("\t(line %d)\n",line );


					}
				fclose(fp);
}
