#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include "memory.h"
#include "execution.h"
#include "funclib.h"
extern int paramc;
extern struct avm_memcell* paramlist;
extern struct avm_memcell *retval ;
extern struct avm_memcell * stack[]; 
extern int top;

char *typeStrings ( int c ){
    char *s ;
    if ( c == 0 ){
        s= strdup("int");
    }else if ( c == 1){
        s= strdup("float");
    }else if ( c == 2){
        s= strdup("string");
    }else if ( c == 3){
        s= strdup("bool");
    }else if ( c == 4){
        s= strdup("table");
    }else if ( c == 5){
        s= strdup("usefunction");
    }else if ( c == 6){
        s= strdup("libraryfunction");
    }else if ( c == 7){
        s= strdup("nil");
    }else if ( c == 8){
        s= strdup("undefined");
    }
    return s ; 
}



library_func_t avm_getlibraryfunc(char * n){
    if ( strcmp(n,"print" )== 0 ){
        return libfunc_print ; 
    }else if ( strcmp(n , "sin") == 0 ){
        return libfunc_sin;
    }else if ( strcmp(n , "sqrt") == 0 ){
        return libfunc_sqrt;
    }else if ( strcmp(n , "cos") == 0 ){
        return libfunc_cos;
    }else if ( strcmp(n , "input") == 0 ){
        return libfunc_input;
    }else if ( strcmp(n , "totalarguments") == 0 ){
        return libfunc_totalarguments;
    }else if ( strcmp(n , "argument") == 0 ){
        return libfunc_argument;
    }else if ( strcmp(n , "typeof") == 0 ){
        return libfunc_typeof;
    }else if ( strcmp(n , "strtonum") == 0 ){
        return libfunc_strtonum;
    }else if ( strcmp(n , "objectcopy") == 0 ){
        return libfunc_objectcopy;
    }else if ( strcmp(n , "objecttotalmembers") == 0 ){
        return libfunc_objecttotalmembers;
    }else if ( strcmp(n , "objectmemberkeys") == 0 ){
        return libfunc_objectmemberkeys;
    }
}

void avm_calllibfunc(char * n){
    library_func_t lib = avm_getlibraryfunc(n);
    if ( !lib ){
        printf("Error unsupported lib-function %s called .\n" , n);
    }
    (*lib)() ; 
}




int avm_totalactuals(){
    return paramc;
}

struct avm_memcell *avm_getactual(int i ){
    struct avm_memcell *tmp = paramlist ; 
    for(int j=0; j<i; j++){
        tmp=tmp->next;
    }
    return tmp;
}

char* avm_tostring(struct avm_memcell* me){
    char* s = (char*)malloc(sizeof(char)*10); 
   if ( me->type == int_m){
        sprintf(s,"%d",me->dat->intVal);
    }else if (me->type == float_m){
        sprintf(s,"%f",me->dat->floatVal);
    }else if ( me->type == string_m){
        strcpy(s,me->dat->strVal);
    }else if ( me->type == bool_m){
        if ( me->dat->boolVal == 1 )
            strcpy(s,"true");
        else 
            strcpy(s,"false");
     }else if ( me->type == userfunc_m){
        sprintf(s,"%d" , me->dat->funcVal);
     }else if ( me->type == libfunc_m){
         sprintf(s,"%d" , me->dat->funcVal);
     }else if ( me->type == nil_m){
        strcpy(s,"nil");
     }else if ( me->type == undef_m){
         strcpy(s,"Undefined");
    }
    return s ; 
}


void libfunc_print(){
    unsigned n = avm_totalactuals();
    char *st = (char*)malloc(sizeof(char)*30);
    for (  int i = 0 ; i < n ; i++){
        st = strdup(avm_tostring(avm_getactual(i)));
        printf("%s ",st);
    }
    return;
}

float convert_float(struct avm_memcell *c){
    float f ; 
    if ( c->type == int_m)
        f = (float)c->dat->intVal;
    else if ( c->type == float_m)
        f = c->dat->floatVal ;
    return f ; 
         
}

void libfunc_sin(){
    int n = avm_totalactuals() ; 
    float num ; 
    if ( n != 1){
        printf("Error expected only one argument in 'libfunc_sin' not %d .\n" , n );
    }else {
        if ( avm_getactual(0)->type > 1){
            printf("ERROR in libfunc_sin() incompatible data input .\n") ; 
            return ;
        }else{
            num = convert_float(avm_getactual(0));
        }
    }
    retval->dat->floatVal = (float)sin(num*(3.14159265/180.00)) ; 
    retval->type = float_m ; 
    return ;
}

void libfunc_typeof(){
    int n = avm_totalactuals();
    if ( n != 1){
        printf("Error expected only one argument in 'typeof' not %d .\n" , n );
    }else {
        avm_memcellclear(retval); 
        retval->dat->strVal = strdup(typeStrings(avm_getactual(0)->type));
        retval->type = string_m ;
    }
    return ; 
}



void libfunc_cos() {
    int n = avm_totalactuals() ; 
    float num ; 
    if ( n != 1){
        printf("Error expected only one argument in 'libfunc_cos' not %d .\n" , n );
    }else {
        if ( avm_getactual(0)->type > 1){
            printf("ERROR in libfunc_cos() incompatible data input .\n") ; 
            return ;
        }else{
            num = convert_float(avm_getactual(0));
        }
    }
    retval->dat->floatVal = (float)cos(num*(3.14159265/180.00)) ; 
    retval->type = float_m ; 
    return ;
}

void libfunc_sqrt() {
    int n = avm_totalactuals() ; 
    float num ; 
    if ( n != 1){
        printf("Error expected only one argument in 'libfunc_sqrt' not %d .\n" , n );
    }else {
        if ( avm_getactual(0)->type > 1){
            printf("ERROR in libfunc_sqrt() incompatible data input .\n") ; 
            return ;
        }else{
            num = convert_float(avm_getactual(0));
        }
    }
    if ( num >= 0){
        retval->dat->floatVal = (float)sqrt(num) ; 
        retval->type = float_m ; 
    }else {
        retval->type = nil_m ; 
    }
    return ;
}

void libfunc_input(){
    char* inp = (char*)malloc(sizeof(char)*200) ; 
    fgets(inp,200, stdin ); 
    assert(inp) ; 
    inp[strlen(inp)] = '\0';

    if ( strcmp(inp , "nil") == 0 ){
        retval->dat->strVal = "nil";
        retval->type = nil_m ; 
        return ;
    }

    if ( strcmp(inp , "true") == 0 ){
        retval->dat->boolVal = 1 ; 
        retval->type = bool_m ;
        return ;
    }else if (strcmp(inp , "false") == 0 ){
        retval->dat->boolVal = 0 ; 
        retval->type = bool_m ;
        return ;
    }else if (isdigit(inp[0])){
        char *tmp ; 
        float num = strtof(inp , &tmp);
        retval->dat->floatVal=num;
        retval->type = float_m;
        return ;
    }else { 
        retval->dat->strVal = strdup(inp);
        retval->type = string_m ; 
        return ;
    }
}

void libfunc_totalargumets(){
    int n = avm_totalactuals() ;
    if ( n != 1){
        printf("Error expected only one argument in 'libfunc_totalargumets' not %d .\n" , n );
        return ;
    }else {
        if(avm_getactual(0)->type == userfunc_m){
            retval->type=int_m;
            retval->dat->intVal=stack[top]->dat->funcVal->form_num;
            return;
        }else{
            printf("Error argument in libfunc_totalargumets not userfunction\n");
        }
    }
    return;
}

void libfunc_argument(){
    int n = avm_totalactuals() ;
    if ( n != 1){
        printf("Error expected only one argument in 'libfunc_totalargumets' not %d .\n" , n );
        return ;
    }else {
        if(avm_getactual(0)->type == userfunc_m){
            struct avm_memcell* tmp = stack[top]->dat->funcVal->form;
            for(int i=0; i<avm_getactual(0)->dat->intVal; i++){
                if(tmp==NULL){
                    retval->type = nil_m;
                    retval->dat->strVal = "nil";
                    return;
                }
                tmp=tmp->next;
            }
            retval=tmp;
            return;
        }else{
            printf("Error argument in libfunc_totalargumets not userfunction\n");
        }
    }
    return;
}

void libfunc_strtonum(){
    char *str ; 
    float num ;
    int digits = 0 ; 
    int n = avm_totalactuals() ; 
    if ( n != 1){
        printf("Error expected only one argument in 'libfunc_strtonum' not %d .\n" , n );
        return ;
    }else {
        if ( avm_getactual(0)->type == string_m){
            str=strdup(avm_getactual(0)->dat->strVal);
        }else {
            printf("Error in 'libfunc_strtonum' unexpected type of variable .\n") ; 
            return ; 
        }
    }
    for ( int i = 0 ; i < strlen(str) ; i ++){
        if ( isdigit(str[i]) )
            digits++ ;  
    }
    if ( digits != 0 ){
        char *tmp ; 
        num = strtof(str , &tmp);
        retval->dat->floatVal = num ; 
        retval->type = float_m ; 
    }else{
        retval->type = nil_m ;
        retval->dat->strVal = "nil";
    }
    return ;
}





// void libfunc_objectmemberkeys() {
    // unsigned n = avm_totalactuals() ; 
    // if ( n != 1){
    //     printf("Error expected only one argument in 'libfunc_objectmemberkeys' not %d .\n" , n );
    //     return ;
    // }else {
    //     if ( avm_getactual(0)->type == table_m){
    //         struct avm_table *inp = avm_getactual(0)->dat->tableVal ; 
    //         struct avm_table *new_l = (struct avm_table*)malloc(sizeof(struct avm_table));
    //         struct avm_table *tmp ;
    //         int counter = 0 ; 
    //         while (inp != NULL ){
    //             if ( counter == 0 ){
    //                 retval->dat->tableVal->members->dat->strVal =strdup(inp->index);
    //                 retval->dat->tableVal->members->type = string_m ; 
    //                 sprintf(retval->dat->tableVal->index, "%d", counter);
    //                 new_l =  retval->dat->tableVal ; 
    //             }else{
    //                 new_l->next = (struct avm_table*)malloc(sizeof(struct avm_table));
    //                 new_l->next->members->dat->strVal = strdup(inp->index); 
    //                 new_l->next->members->type = string_m ; 
    //                 sprintf(new_l->next->index,"%d",counter) ;
    //                 if (counter == 1)
    //                     retval->dat->tableVal->next = new_l->next ; 
    //                 new_l = new_l->next ; 
    //             }
    //             inp = inp->next ; 
    //             counter++ ; 
    //         }
    //     }else{
    //          printf("Error in 'libfunc_objectmemberkeys' unexpected type of variable .\n") ; 
    //     }
    // }
    // return ;
// }


