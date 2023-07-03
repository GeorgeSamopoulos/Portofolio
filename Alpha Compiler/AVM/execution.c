#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "memory.h"
#include "execution.h"
#include "funclib.h"

#define AVM_MAX_INSTRUCTIONS 25
#define AVM_ENDING_PC ending_pc

int executionFinished = 0;
int paramc=0;
struct avm_memcell * ax = NULL;
struct avm_memcell * bx = NULL;
struct avm_memcell * paramlist=NULL; 
int pc=0;
extern struct instruction* code;
extern int ending_pc;
extern struct avm_memcell * retval;
extern int top;
extern struct avm_memcell * stack[];
int currLine=0;
typedef void (*execute_fun_t)(struct instruction *);
typedef float (*arithmetic_fun_t)(float x,float y);
typedef unsigned int (*tobool_fun_t)(struct avm_memcell* m);
execute_fun_t executeFuncs[]={

    exec_assign,
    exec_add,
    exec_sub,
    exec_mul,
    exec_div,
    exec_mod,
    NULL,
    NULL,
    NULL,
    NULL,
    exec_jeq,
    exec_jne,
    exec_jge,
    exec_jle,
    exec_jgt,
    exec_jlt,
    exec_call,
    exec_pusharg,
    exec_funcenter,
    exec_funcexit,
    exec_newtable,
    exec_tablegetelem,
    exec_tablesetelem,
    exec_nop
};


arithmetic_fun_t arithmeticFuncs[]={
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl,
};

float add_impl(float x , float y){
    return x+y;
}
float sub_impl(float x , float y){
    return x-y;
}
float mul_impl(float x , float y){
    return x*y;
}
float div_impl(float x , float y){
    return x/y;
}
float mod_impl(float x , float y){
    return ((unsigned)x) % ((unsigned)y);
}

void execute_arithmetic(struct instruction * i){
    struct avm_memcell * result = avm_translate_operand(i->result,NULL);
    struct avm_memcell * arg1 = avm_translate_operand(i->arg1,ax);
    struct avm_memcell * arg2 = avm_translate_operand(i->arg2,bx);

    if(arg1->type > float_m || arg2->type > float_m){
        printf("not arithmetic\n");
        executionFinished=1;
    }else{
        arithmetic_fun_t op = arithmeticFuncs[i->opcode];
        avm_memcellclear(result);
        if(arg1->type==float_m||arg2->type==float_m){
            result->type=float_m;
            float a1=arg1->dat->floatVal+arg1->dat->intVal;
            float a2=arg2->dat->floatVal+arg2->dat->intVal;
            result->dat->floatVal = (*op)(a1,a2);
        }else{
            result->type=int_m;
            float a1=arg1->dat->floatVal+arg1->dat->intVal;
            float a2=arg2->dat->floatVal+arg2->dat->intVal;
            result->dat->intVal =(int)(*op)(a1,a2);
        }
    }

}

void avm_memcellclear(struct avm_memcell* t){
    t->name=NULL;
    t->type=undef_m;
    if(t->dat!=NULL){
        t->dat->boolVal=0;
        t->dat->intVal=0;
        t->dat->floatVal=0;
        t->dat->libfuncVal=NULL;
        t->dat->funcVal=NULL;
        t->dat->strVal=NULL;
        t->dat->tableVal=NULL;
    }
}

tobool_fun_t toboolFuncs[]={
    int_tobool,
    float_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};

char * types[]={
    "int",
    "float",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"
};

unsigned int  int_tobool(struct avm_memcell * m){
    return (m->dat->intVal!=0);
}

unsigned int  float_tobool(struct avm_memcell * m){
    return (m->dat->floatVal!=0);
}

unsigned int  string_tobool(struct avm_memcell * m){
    return (m->dat->strVal[0]!=0);
}

unsigned int bool_tobool(struct avm_memcell * m){
    return (m->dat->boolVal);
}

unsigned int table_tobool(struct avm_memcell * m){
    return 1;
}

unsigned int userfunc_tobool(struct avm_memcell * m){
    return 1;
}

unsigned int libfunc_tobool(struct avm_memcell * m){
    return 1;
}

unsigned int nil_tobool(struct avm_memcell * m){
    return 0;
}

unsigned int undef_tobool(struct avm_memcell * m){
    assert(0);
    return 0;
}

unsigned int avm_tobool(struct avm_memcell * m){
    assert(m->type>=0 && m->type<undef_m);
    return(*toboolFuncs[m->type])(m);
}


//-----------------------
void exec_assign(struct instruction * i){
    struct avm_memcell * res = avm_translate_operand(i->result,NULL);
    struct avm_memcell * arg1 = avm_translate_operand(i->arg1,ax);
    res->type=arg1->type;
    res->dat->intVal=arg1->dat->intVal;
    res->dat->floatVal=arg1->dat->floatVal;
    res->dat->libfuncVal=arg1->dat->libfuncVal;
    if(arg1->dat->strVal!=NULL)res->dat->strVal=arg1->dat->strVal;
    res->dat->tableVal=arg1->dat->tableVal;
    res->dat->funcVal=arg1->dat->funcVal;

}

//-----------------------
void execute_jeq(struct instruction * i){
    unsigned char result=0;
    struct avm_memcell * arg1 = avm_translate_operand(i->arg1,ax);
    struct avm_memcell * arg2 = avm_translate_operand(i->arg2,bx);
    if(arg1->type==undef_m||arg2->type==undef_m){
        printf("ERROR !!! UNDEF ARG\n");
        executionFinished=1;
    }else{
        if(arg1->type==nil_m||arg2->type==nil_m){
            result = arg1->type==nil_m && arg2->type==nil_m;
            
        }else{
            if(arg1->type==bool_m||arg2->type==bool_m){
                result=(avm_tobool(arg1)==avm_tobool(arg2));
            }else{
                if((arg1->type>float_m||arg2->type>float_m)&&arg1->type!=arg2->type){
                    printf("%s == %s is illegal",types[arg1->type],types[arg2->type]);
                    executionFinished=1;
                }else{
                    if(arg1->type<=float_m){
                        result = (arg1->dat->intVal+arg1->dat->floatVal) == (arg2->dat->intVal+arg1->dat->floatVal);
                    }else if(arg1->type==string_m){
                        if(strcmp(arg1->dat->strVal,arg2->dat->strVal)==0){
                            result = 1;
                        }
                    }else if(arg1->type==libfunc_m){
                        if(strcmp(arg1->dat->libfuncVal,arg2->dat->libfuncVal)==0){
                            result = 1;
                        }
                    }else if(arg1->type==userfunc_m){
                        if(strcmp(arg1->name,  arg2->name)==0){
                            result=1;
                        }
                    }else if(arg1->type==table_m){
                        result=1;
                    }
                }
            }
            
        }
        
    }
    
    if((executionFinished==0)&&(result==1)){
        pc=i->result->val;
    }

}


void execute_jne(struct instruction * i){
    unsigned char result=0;
    struct avm_memcell * arg1 = avm_translate_operand(i->arg1,ax);
    struct avm_memcell * arg2 = avm_translate_operand(i->arg2,bx);
    if(arg1->type==undef_m||arg2->type==undef_m){
        printf("ERROR !!! UNDEF ARG");
        executionFinished=1;
    }else{
        if(arg1->type==nil_m||arg2->type==nil_m){
            result=arg1->type==nil_m && arg2->type==nil_m;
            
        }else{
            if(arg1->type==bool_m||arg2->type==bool_m){
                result=(avm_tobool(arg1)==avm_tobool(arg2));
            }else{
                if((arg1->type>float_m||arg2->type>float_m)&&arg1->type!=arg2->type){
                    printf("%s == %s is illegal",types[arg1->type],types[arg2->type]);
                    executionFinished=1;
                }else{
                    if(arg1->type<=float_m){
                        result = (arg1->dat->floatVal + arg1->dat->intVal) == (arg2->dat->intVal + arg2->dat->floatVal);
                    }else if(arg1->type==string_m){
                        if(strcmp(arg1->dat->strVal,arg2->dat->strVal)==0){
                            result = 1;
                        }
                    }else if(arg1->type==libfunc_m){
                        if(strcmp(arg1->dat->libfuncVal,arg2->dat->libfuncVal)==0){
                            result = 1;
                        }
                    }else if(arg1->type==userfunc_m){
                        if(strcmp(arg1->name,  arg2->name)==0){
                            result=1;
                        }
                    }else if(arg1->type==table_m){
                        result=1;
                    }
                }
            }
            
        }
        
    }
    
    if((executionFinished==0)&&(result==0)){
        pc=i->result->val;
    }

}

void exec_jge(struct instruction * i){
    unsigned char result=0;
    struct avm_memcell * arg1 = avm_translate_operand(i->arg1,ax);
    struct avm_memcell * arg2 = avm_translate_operand(i->arg2,bx);
    if(arg1->type>float_m||arg2->type>float_m){
        printf("%s == %s is illegal",types[arg1->type],types[arg2->type]);
        executionFinished=1;
    }else{
        result = (arg1->dat->floatVal + arg1->dat->intVal) >= (arg2->dat->intVal + arg2->dat->floatVal);
    }
    if((executionFinished==0)&&(result==1)){
        pc=i->result->val;
    }
}

void exec_jle(struct instruction * i){
    unsigned char result=0;
    struct avm_memcell * arg1 = avm_translate_operand(i->arg1,ax);
    struct avm_memcell * arg2 = avm_translate_operand(i->arg2,bx);
    if(arg1->type>float_m||arg2->type>float_m){
        printf("%s == %s is illegal",types[arg1->type],types[arg2->type]);
        executionFinished=1;
    }else{
        result = (arg1->dat->floatVal + arg1->dat->intVal) <= (arg2->dat->intVal + arg2->dat->floatVal);
    }
    if((executionFinished==0)&&(result==1)){
        pc=i->result->val;
    }
}

void exec_jgt(struct instruction * i){
    unsigned char result=0;
    struct avm_memcell * arg1 = avm_translate_operand(i->arg1,ax);
    struct avm_memcell * arg2 = avm_translate_operand(i->arg2,bx);
    if(arg1->type>float_m||arg2->type>float_m){
        printf("%s == %s is illegal",types[arg1->type],types[arg2->type]);
        executionFinished=1;
    }else{
        result = (arg1->dat->floatVal + arg1->dat->intVal) > (arg2->dat->intVal + arg2->dat->floatVal);
    }
    if((executionFinished==0)&&(result==1)){
        pc=i->result->val;
    }
}

void exec_jlt(struct instruction * i){
    unsigned char result=0;
    struct avm_memcell * arg1 = avm_translate_operand(i->arg1,ax);
    struct avm_memcell * arg2 = avm_translate_operand(i->arg2,bx);
    if(arg1->type>float_m||arg2->type>float_m){
        printf("%s == %s is illegal",types[arg1->type],types[arg2->type]);
        executionFinished=1;
    }else{
        result = (arg1->dat->floatVal + arg1->dat->intVal) > (arg2->dat->intVal + arg2->dat->floatVal);
    }
    if((executionFinished==0)&&(result==1)){
        pc=i->result->val;
    }
} 

void exec_add(struct instruction * i){
    execute_arithmetic(i);
}
    
void exec_sub(struct instruction * i){
    execute_arithmetic(i);
}
void exec_mul(struct instruction * i){
    execute_arithmetic(i);
}
void exec_div(struct instruction * i){
    execute_arithmetic(i);
}
void exec_mod(struct instruction * i){
    execute_arithmetic(i);
}

void exec_pusharg(struct instruction *i){

    struct avm_memcell * t = avm_translate_operand(i->result,ax);
    if(paramlist==NULL){
        paramlist=t;
    }else{
        struct avm_memcell * temp = paramlist;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=t;
    }
    paramc++;
    return;
}

void exec_call(struct instruction *i){
    struct avm_memcell * t = avm_translate_operand(i->result,ax);
    if(t->type==libfunc_m){
        avm_calllibfunc(t->dat->libfuncVal);
    }else if(t->type==string_m){
        avm_calllibfunc(t->dat->strVal);
    }else{
        struct avm_memcell* t = avm_translate_operand(i->result,ax);
        struct avm_memcell* tmp = push_func_in_stack(i->result,t);
        if(tmp->dat->funcVal->form_num==paramc){
            tmp->dat->funcVal->form=paramlist;
            tmp->dat->funcVal->return_address=pc+1;
        } 
        else{ 
            printf("error wrong number of params !!!\n"); 
            executionFinished=1;
        }
        pc=t->dat->funcVal->address;
    }
    return;
}


void exec_funcenter(struct instruction *i){
    paramlist=NULL;
    paramc=0;
}


void exec_funcexit(struct instruction *i){
    pc = (pop_func_in_stack())->dat->funcVal->return_address;
    return;   
}
struct avm_memcell* push_func_in_stack(struct vmarg * arg, struct avm_memcell* node){
    top++;
    stack[top]=avm_translate_operand(arg, node);
    return stack[top];
}
struct avm_memcell* pop_func_in_stack(){
    struct avm_memcell* tmp = stack[top];
    top--;
    return tmp;
}
// void exec_newtable(struct instruction *i){
    
// }

// void exec_tablegetelem(struct instruction *i){
    
// }

// void exec_tablesetelem(struct instruction *i){
    

// }

// void exec_nop(struct instruction *i){

    
// }

void execution_cycle(){
    if(executionFinished){
        return;
    }else if(pc==AVM_ENDING_PC){
            executionFinished=1;
            return;
    }else{
        assert(pc< AVM_ENDING_PC);

        struct instruction* instr = code;
        for(int i=0; i<pc; i++){
            instr=instr->next;
        }
        assert(instr->opcode>=0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        if(instr->srcLine) currLine = instr->srcLine;
        unsigned int oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if(pc==oldPC) ++pc;
    }
}