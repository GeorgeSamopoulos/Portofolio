#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "memory.h"
#define AVM_STACKSIZE 4096

struct avm_memcell *main_memory  ; // pointer to main memory 
struct int_node * intmem = NULL;
struct float_node * floatmem = NULL;
struct str_node* strmem= NULL;
struct userf_node * userfmem = NULL;
struct libf_node * libfmem = NULL;
struct instruction * code=NULL;
int top=-1;
struct avm_memcell * stack[AVM_STACKSIZE]; 
struct avm_memcell * retval = NULL;
int ending_pc = 0;

void read_binfile(){
    FILE *fp = NULL;
    fp = fopen("../out.bin", "rb");
    
    unsigned int magic;
    
    fread(&magic, sizeof(int), 1, fp);
    
    unsigned int globals;
    if(fread(&globals, sizeof(unsigned int), 1, fp)!=1)
        printf("Error in binary\n");
    
    unsigned int strings;
    if(fread(&strings, sizeof(unsigned int), 1, fp)!=1)
        printf("Error in binary\n");
    int i = 0;
    for(i=0; i<strings; i++){
        unsigned int length = 0;
        if(fread(&length,sizeof(unsigned int), 1, fp) != 1)
            printf("Error in binary\n");

        char * str = (char *)malloc(sizeof(char )*(length+1));
        if(fread(str,sizeof(char )*length , 1, fp)!= 1)
            printf("Error in binary\n");
        str[length]='\0';
        insert_strConst(i,str);
    }

    unsigned int ints;
    fread(&ints, sizeof(unsigned int), 1, fp);
    for(i=0; i<ints; i++){
        int int_num;
        if(fread(&int_num,sizeof(int), 1, fp)!=1)
            printf("Error in binary\n");
        
        insert_intConst(i,int_num);
    }
    
    unsigned int floats;
    if(fread(&floats, sizeof(float), 1, fp)!=1)
        printf("Error in binary\n");
    for(i=0; i<floats; i++){
        float float_num;
        if(fread(&float_num,sizeof(int), 1, fp)!=1)
            printf("Error in binary\n");

        insert_floatConst(i,float_num);
    }

    unsigned int userfuncs;
    if(fread(&userfuncs, sizeof(unsigned int), 1, fp)!=1)
        printf("Error in binary\n");

    for(i=0; i<userfuncs; i++){
        unsigned int addr;
        if(fread(&addr,sizeof(unsigned int), 1, fp)!=1)
            printf("Error in binary\n"); 
        
        unsigned int localsize;
        if(fread(&localsize,sizeof(unsigned int), 1, fp)!=1)
            printf("Error in binary\n"); 
        
            unsigned int formalsize;
        if(fread(&formalsize,sizeof(unsigned int), 1, fp)!=1)
            printf("Error in binary\n"); 

        unsigned int length;
        if(fread(&length,sizeof(unsigned int), 1, fp)!=1)
            printf("Error in binary\n"); 
        
        char * id = malloc(sizeof(char )*(length+1));
        if(fread(id,sizeof(char )*length , 1, fp)!=1)
            printf("Error in binary\n");
        id[length]='\0';
        insert_userfunc(i, addr, localsize, formalsize, id);
    }

    unsigned int libfuncs;
    if(fread(&libfuncs, sizeof(unsigned int), 1, fp)!=1)
        printf("Error in binary\n");

    for(i=0; i<libfuncs; i++){
        unsigned int length;
        if(fread(&length,sizeof(unsigned int), 1, fp)!=1)
            printf("Error in binary\n"); 
        char * libfunc = malloc(sizeof(char )*(length+1));
        if(fread(libfunc,sizeof(char )*length, 1, fp)!=1)
            printf("Error in binary\n"); 
            libfunc[length]='\0';
        insert_libfunc(i, libfunc);
    }

    unsigned int instructions;
    if(fread(&instructions, sizeof(unsigned int), 1, fp)!=1)
            printf("Error in binary\n"); 
    ending_pc = instructions;

    for (i = 0; i < instructions; i++) {
        unsigned int opcode;
        if(fread(&opcode,sizeof(int ), 1, fp)!=1)
            printf("Error in binary\n"); 
        
        unsigned int res_type;
        if(fread(&res_type,sizeof( int), 1, fp)!=1)
            printf("Error in binary\n"); 
        
        unsigned int res_val;
        if(fread(&res_val,sizeof(int), 1, fp)!=1)
            printf("Error in binary\n"); 
                
        unsigned int arg1_type;
        if(fread(&arg1_type,sizeof( int), 1, fp)!=1)
            printf("Error in binary\n"); 
        
        unsigned int arg1_val;
        if(fread(&arg1_val,sizeof(int), 1, fp)!=1)
            printf("Error in binary\n"); 
        
        unsigned int arg2_type;
        if(fread(&arg2_type,sizeof( int), 1, fp)!=1)
            printf("Error in binary\n"); 
        
        unsigned int arg2_val;
        if(fread(&arg2_val,sizeof(int), 1, fp)!=1)
            printf("Error in binary\n"); 

        unsigned int line;    
        if(fread(&line,sizeof(int), 1, fp)!=1)
            printf("Error in binary\n"); 
        insert_instruction(i, opcode, res_type, res_val, arg1_type, arg1_val, arg2_type, arg2_val, line);
    }
    fclose(fp);
}

void insert_strConst(int index, char* str){
    struct str_node * new = (struct str_node *)malloc(sizeof(struct str_node));
    new->next=NULL;
    new->index=index;
    new->value=strdup(str);
    if(strmem==NULL){
        strmem=new;
    }else{
        struct str_node * tmp=strmem;
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=new;
    }
}


void insert_intConst(int index,int num){
    struct int_node * new = (struct int_node *)malloc(sizeof(struct int_node));
    new->next=NULL;
    new->index=index;
    new->value=num;
    if(intmem==NULL){
        intmem=new;
    }else{
        struct int_node * tmp=intmem;
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=new;
    }
}

void insert_floatConst(int index,float num){
    struct float_node * new = (struct float_node *)malloc(sizeof(struct float_node));
    new->next=NULL;
    new->index=index;
    new->value=num;
    if(floatmem==NULL){
        floatmem=new;
    }else{
        struct float_node * tmp=floatmem;
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=new;
    }
}


void insert_userfunc(int index, int address, int localsize, int formalsize, char* id){
    struct userf_node * new = (struct userf_node *)malloc(sizeof(struct userf_node));
    new->next=NULL;
    new->index=index;
    new->id=strdup(id);
    new->address=address;
    new->localsize=localsize;
    new->formalsize=formalsize;
    if(userfmem==NULL){
        userfmem=new;
    }else{
        struct userf_node * tmp=userfmem;
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=new;
    }
}

void insert_libfunc(int index, char* libf){
    struct libf_node * new = (struct libf_node*)malloc(sizeof(struct libf_node));
    new->index=index;
    new->id=strdup(libf);
    new->next=NULL;
    new->id=strdup(libf);
    if(libfmem==NULL){
        libfmem=new;
    }else{
        struct libf_node * tmp=libfmem;
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=new;
    }
}

void insert_instruction(int index, int opcode, int rtype, int rvalue, int arg1type, int arg1value, int arg2type, int arg2value, int line){
    struct instruction * new = (struct instruction*)malloc(sizeof(struct instruction));
    new->next=NULL;
    new->srcLine=line;
    new->opcode=opcode;
    new->result = (struct vmarg*)malloc(sizeof(struct vmarg));
    new->result->type=rtype;
    new->result->val=rvalue;
    new->arg1 = (struct vmarg*)malloc(sizeof(struct vmarg));
    new->arg1->type=arg1type;
    new->arg1->val=arg1value;
    new->arg2 = (struct vmarg*) malloc(sizeof(struct vmarg));
    new->arg2->type=arg2type;
    new->arg2->val=arg2value;
    if(code==NULL){
        code=new;
    }else{
        struct instruction * tmp=code;
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=new;
    }
}

void print_memories(){
    printf("\nSTRING\n");
    struct str_node* tmp1 = strmem;
    while(tmp1!=NULL){
        printf("%d: %s\n", tmp1->index, tmp1->value);
        tmp1=tmp1->next;
    }

    printf("\nINT\n");
    struct int_node* tmp2 = intmem;
    while(tmp2!=NULL){
        printf("%d: %d\n", tmp2->index, tmp2->value);
        tmp2=tmp2->next;

    }

    printf("\nFLOAT\n");
    struct float_node* tmp3 = floatmem;
    while(tmp3!=NULL){
        printf("%d: %d\n", tmp3->index, tmp3->value);
        tmp3=tmp3->next;

    }
    
    printf("\nUSER FUNCTIONS\n");
    struct userf_node* tmp4 = userfmem;
    while(tmp4!=NULL){
        printf("%d: %s\n", tmp4->index, tmp4->id);
        tmp4=tmp4->next;

    }

    printf("\nLIBRARY FUNCTIONS\n");
    struct libf_node* tmp5 = libfmem;
    while(tmp5!=NULL){
        printf("%d: %s\n", tmp5->index, tmp5->id);
        tmp5=tmp5->next;

    }

    printf("\nINSTRUCTIONS\n");
    struct instruction* tmp6=code;
    for(int i=0; i<ending_pc; i++){
        printf("%d: %d\n", tmp6->srcLine, tmp6->opcode);
        tmp6=tmp6->next;

    }



}
struct avm_memcell * ith_form(int n){
    struct avm_memcell* tmp = stack[top]->dat->funcVal->form ; 
    for ( int i = 0 ; i < n ; i ++){
        if ( tmp == NULL ){
            printf("ERROR\n");
            return NULL;
        }else{
            tmp = tmp->next ;
        }
    }
    return tmp;
}

struct avm_memcell * ith_local(int n){
    struct avm_memcell* tmp = stack[top]->dat->funcVal->loc_var ; 
    for ( int i = 0 ; i < n ; i ++){
        if ( tmp == NULL ){
            printf("ERROR\n");
            return NULL;
        }else{
            tmp = tmp->next ;
        }
    }
    return tmp;
}

struct avm_memcell *make_localVars(int n){
    struct avm_memcell *list  = NULL ;
    struct avm_memcell *tmp ; 
    struct avm_memcell *ret;
    for ( int i = 0 ; i < n ; i++){
        tmp = (struct avm_memcell*)malloc(sizeof(struct avm_memcell));
        tmp->type = undef_m ;
        if ( list == NULL ){
            list = tmp ;
            struct avm_memcell *ret  = list ; 
        }else{
            list->next = tmp ;
            list = list->next ;
        }
    } 
    return ret ; 

}

struct avm_memcell* avm_translate_operand(struct vmarg * arg, struct avm_memcell * reg){
    switch(arg->type){
    case global_a : return stack[AVM_STACKSIZE-1-arg->val];
    case local_a : return ith_local(arg->val);
    case formal_a : return ith_form(arg->val);
    case retval_a : return retval;
    case string_a : {
        reg->type =string_m;
        reg->dat->strVal=const_getstring(arg->val);
        return reg;
    }
    case bool_a:{
        reg->type =bool_m;
        reg->dat->boolVal=arg->val;
    }
    case nil_a: reg->type =nil_m; return reg;
    case userfunc_a : {
        reg->type = userfunc_m;
        struct userf_node* tmp = const_getuserf(arg->val);
        reg->name = strdup(tmp->id);
        reg->dat->funcVal->form_num = tmp->formalsize;
        reg->dat->funcVal->local_num = tmp->localsize;
        reg->dat->funcVal->loc_var=make_localVars(tmp->localsize);
        reg->dat->funcVal->address = tmp->address;
        return reg;
    }
    case libfunc_a:{
        reg->type = libfunc_m;
        reg->dat->libfuncVal=const_getlib(arg->val);
        return reg;
    }
    case float_a:{
        reg->type=float_m;
        reg->dat->floatVal=const_getfloat(arg->val);
        return reg;
    }
    case int_a:{
        reg->type=int_m;
        reg->dat->intVal=const_getint(arg->val);
        return reg;
    }
    }


}


char* const_getstring(int index){
    struct str_node* tmp = strmem;
    while(tmp!=NULL){
        if(tmp->index==index){
            return tmp->value;
        }
        tmp=tmp->next;
    }
    return NULL;
}

int const_getint(int index){
    struct int_node* tmp = intmem;
    while(tmp!=NULL){
        if(tmp->index==index){
            return tmp->value;
        }
        tmp=tmp->next;
    }
    return 0;
}

float const_getfloat(int index){
    struct float_node* tmp = floatmem;
    while(tmp!=NULL){
        if(tmp->index==index){
            return tmp->value;
        }
        tmp=tmp->next;
    }
    return 0.0f;
}

char* const_getlib(int index){
    struct libf_node* tmp = libfmem;
    while(tmp!=NULL){
        if(tmp->index==index){
            return tmp->id;
        }
        tmp=tmp->next;
    }
    return NULL;
}

struct userf_node* const_getuserf(int index){
    struct userf_node* tmp = userfmem;
    while(tmp!=NULL){
        if(tmp->index==index){
            return tmp;
        }
        tmp=tmp->next;
    }
    return NULL;
}