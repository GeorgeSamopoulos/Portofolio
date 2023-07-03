#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "a.h"
#include "syntax_functions.h"
#include "intermediate.h"

#define INT 7
#define FLOAT 8
#define FLOAT_INT 9
#define INT_FLOAT 10
#define BOOL 11

extern struct jump_stack* else_jump_quads;
extern int quad_count;
struct quad* mainq =NULL; 
struct expr* mainexp=NULL ;
struct quad* emit(enum iopcode oper , struct expr* expr1 , struct expr* expr2 , struct expr* exprr, int label, int line){
    struct quad* q = (struct quad*) malloc(sizeof(struct quad));
    q->quadno=quad_count;
    q->arg1 = copy_expr(expr1) ; 
    q->arg2 = copy_expr(expr2) ; 
    q->op = oper ; 
    q->result = copy_expr(exprr) ;
    q->label = label ; 
    q->line = line ;
    q->next=NULL;
    if ( mainq == NULL ){
        mainq = q ; 
    }else {
        struct quad* tmp = mainq ; 
        while(tmp->next != NULL ){
            tmp = tmp->next ; 
        }
        tmp->next = q ; 
    }
    quad_count++;
    return q;
}


enum expr_t change_type(struct expr* ex){
    if(ex->type==constint_e||ex->type==intexpr_e){
        return intexpr_e;
    }else if(ex->type==constfloat_e||ex->type==floatexpr_e){
        return floatexpr_e;
    }else if(ex->type==boolexpr_e||ex->type==constbool_e){
        return boolexpr_e;
    }else if(ex->type==conststring_e){
        return var_e;
    }
}


int t_var=1; 
char * var_name(){
        char * name;
        int n = floor (log10 (abs (t_var))) + 1;
        name = (char *)malloc((sizeof(char)*n)+3);
		sprintf(name,"%s","_t");
		sprintf(&name[2],"%d",t_var);
        t_var++;
        return name;
}

void reset_var_name(){
    t_var=1;
    return;
}

struct expr * find_expr(char* name , char* type , char* vision ,  int scope){
    struct hashnode * hasht;
    if(strcmp(vision,"::") == 0 ){
        hasht=search0(name);


    }else if(strcmp(vision,"local") == 0){
        hasht= samescope(name,scope);


    }else if(strcmp(type,"variable")==0){
        hasht = samescope (name,scope);
        if(hasht==NULL){
            hasht=betvar(name,scope);
            if(hasht==NULL){
                hasht=search0(name);
            }
        }

    }else if(strcmp(type , "user function") == 0){
        hasht = samescope (name,scope);
        if(hasht==NULL){
            hasht=betfun(name,scope);
            if(hasht==NULL){
                hasht=search0(name);
            }
        }
    }
    if(hasht==NULL){
            return NULL;
    }
    struct expr * extemp=mainexp; 
    while(extemp!=NULL){
        if(extemp->sym==hasht){
            return extemp;

        }
        extemp=extemp->next;
    }
    return NULL;
}
void push_local(int el, struct local_flag** list){
    struct local_flag* tmp = (struct local_flag*) malloc(sizeof(struct local_flag));
    tmp->num=el;
    tmp->next=*list;
    *list=tmp;
    return;
}

int pop_local(struct local_flag** list){
    int tmp = (*list)->num;
    *list=(*list)->next;
    return tmp;
}

void push(int el, struct loop** list){
    struct loop* tmp = (struct loop*) malloc(sizeof(struct loop));
    tmp->num=el;
    tmp->next=*list;
    *list=tmp;
    return;
}

int pop(struct loop** list){
    int tmp = (*list)->num;
    *list=(*list)->next;
    return tmp;
}

void push_jump_stack(struct quad* el, struct jump_stack** list){
    struct jump_stack* tmp = (struct jump_stack*) malloc(sizeof(struct jump_stack));
    tmp->jump=el;
    tmp->next=*list;
    *list=tmp;
    return;
}

struct quad* pop_jump_stack(struct jump_stack** list){
    struct quad* tmp = (*list)->jump;
    *list=(*list)->next;
    return tmp;
}
void push_bcr_stack(struct bcr_stack** list){
    struct bcr_stack* tmp = (struct bcr_stack*) malloc(sizeof(struct jump_stack));
    tmp->head=NULL;
    tmp->next=*list;
    *list=tmp;
    return;
}

struct bcr_stack* pop_bcr_stack(struct bcr_stack** list){
    struct bcr_stack* tmp = (*list);
    *list=(*list)->next;
    return tmp;
}
void fillExp(struct expr* ex){
    ex->next = mainexp ;
    mainexp = ex; 
    return;
}

void fill_elist_quads(enum iopcode op,struct expr* el,int line,struct quad** list){
    struct quad* tmp = (struct quad*) malloc(sizeof(struct quad));
    tmp->op=op;
    tmp->result=el;
    tmp->label=-1;
    tmp->line=line;
    tmp->next= *list;
    *list=tmp;
}
void emit_elist_quads(struct quad** list){
    while(*list!=NULL){
        emit((*list)->op,NULL,NULL,(*list)->result,(*list)->label,(*list)->line);
        *list=(*list)->next;
    }
}

void print_quads(FILE* quadfile){
    char * t[26]={"ASSIGN", "ADD", "SUB",
        "MUL", "DIVIDE", "MOD",
        "UMINUS",	"AND", "OR",
        "NOT", "IF_EQ",	"IF_NOT_EQ",
        "IF_LESSEQ",	"IF_GREATEREQ", "IF_LESS",
        "IF_GREATER",	"CALL", "PARAM",
        "RETURN", "GETRETVAL",	"FUNCSTART",
        "FUNCEND", "JUMP", "TABLECREATE",	
        "TABLEGETELEM","TABLESETELEM"};

    struct quad * tempq = mainq;
    while(tempq!=NULL){
        printf("%d: %s ", tempq->quadno, t[tempq->op]);
        
        if(tempq->result!=NULL){
            if(tempq->result->sym!=NULL){
                printf("%s",tempq->result->sym->name);
            }else{
                    if(tempq->result->type==constint_e || tempq->result->type==intexpr_e){
                        printf("%d",tempq->result->intConst);
                    }else if(tempq->result->type==constfloat_e || tempq->result->type==floatexpr_e){
                        printf("%u",tempq->result->floatConst);
                    }else if(tempq->result->type==boolexpr_e || tempq->result->type==constbool_e){
                        printf("%d",tempq->result->boolConst);
                    }else if(tempq->result->type==conststring_e){
                        printf("%s",tempq->result->strConst);
                    }
                }
        }
        if(tempq->arg1!=NULL){
            if(tempq->arg1!=NULL){
            	printf(",");
                if(tempq->arg1->sym!=NULL){
                    printf("%s",tempq->arg1->sym->name);
                }else{
                    if(tempq->arg1->type==constint_e || tempq->arg1->type==intexpr_e){
                        printf("%d",tempq->arg1->intConst);
                    }else if(tempq->arg1->type==constfloat_e || tempq->arg1->type==floatexpr_e){
                        printf("%u",tempq->arg1->floatConst);
                    }else if(tempq->arg1->type==boolexpr_e || tempq->arg1->type==constbool_e){
                        printf("%d",tempq->arg1->boolConst);
                    }else if(tempq->arg1->type==conststring_e){
                        printf("%s",tempq->arg1->strConst);
                    }else {
                        printf("nil");
                    }
                }
            }
        }
         if(tempq->arg2!=NULL){
            if(tempq->arg2!=NULL){
            	printf(",");
                if(tempq->arg2->sym!=NULL){
                    printf("%s",tempq->arg2->sym->name);
                }else{
                    if(tempq->arg2->type==constint_e || tempq->arg2->type==intexpr_e){
                            printf("%d",tempq->arg2->intConst);
                    }else if(tempq->arg2->type==constfloat_e || tempq->arg2->type==floatexpr_e){
                        printf("%u",tempq->arg2->floatConst);
                    }else if(tempq->arg2->type==boolexpr_e || tempq->arg2->type==constbool_e){
                        printf("%d",tempq->arg2->boolConst);
                    }else if(tempq->arg2->type==conststring_e){
                        printf("%s",tempq->arg2->strConst);
                    }
                }
            }
        }
        if(tempq->label!=-1){
            if(strcmp(t[22],t[tempq->op])!=0) printf(",");
            printf("%d",tempq->label);
        }
        printf(" (line %d)\n",tempq->line);
        tempq=tempq->next;
    }

}


struct expr* copy_expr(struct expr* ex){
    if(ex==NULL) return NULL;
    struct expr* tmp = (struct expr*) malloc(sizeof(struct expr));
    tmp->type = ex->type ; 
   
    if(ex->sym) tmp->sym = ex->sym ; 
    else tmp->sym = NULL;
    if(ex->index) tmp->index = ex->index ;
    else tmp->index = NULL; 
    tmp->floatConst = ex->floatConst ; 
    tmp->intConst = ex->intConst ; 
    if(ex->strConst)tmp->strConst = strdup(ex->strConst) ;
    else tmp->strConst=NULL;
    tmp->boolConst = ex->boolConst ; 
    if(ex->next) tmp->next = ex->next ; 
    else tmp->next = NULL;
    return tmp ; 
}


// ----------------------------------------------------------------
//ARITHMETIC OPERATIONS
//returns 0 if they are the same type , -1 if they not .
int arith_compare_type(struct expr* ex1 , struct expr* ex2){
    if(ex1->type == programfunc_e || ex1->type == libraryfunc_e || ex1->type == var_e){
        ex1->type=intexpr_e;
    }
    if(ex2->type == programfunc_e || ex2->type == libraryfunc_e|| ex2->type == var_e){
        ex2->type=intexpr_e;
    }
    if ((ex1->type==constint_e && ex2->type == constint_e)||
    (ex1->type==intexpr_e && ex2->type == constint_e)||
    (ex1->type==constint_e && ex2->type == intexpr_e)||
    (ex1->type==intexpr_e && ex2->type == intexpr_e)){
        return INT;
    }else if((ex1->type==constint_e && ex2->type == constfloat_e)||
    (ex1->type==intexpr_e && ex2->type == constfloat_e)||
    (ex1->type==constint_e && ex2->type == floatexpr_e)||
    (ex1->type==intexpr_e && ex2->type == floatexpr_e)){
        return INT_FLOAT;
    }else if((ex1->type==constfloat_e && ex2->type == constint_e)||
    (ex1->type==constfloat_e && ex2->type == intexpr_e)||
    (ex1->type==floatexpr_e && ex2->type == constint_e)||
    (ex1->type==floatexpr_e && ex2->type == intexpr_e)){
        return FLOAT_INT;
    }else if((ex1->type==constfloat_e && ex2->type == constfloat_e)||
    (ex1->type==floatexpr_e && ex2->type == constfloat_e)||
    (ex1->type==constfloat_e && ex2->type == floatexpr_e)||
    (ex1->type==floatexpr_e && ex2->type == floatexpr_e)){
        return FLOAT;
    }else if ( ex1->type == boolexpr_e || ex1->type == constbool_e){
        if ( ex2->type == boolexpr_e || ex2->type == constbool_e){
            return BOOL;            
        }else{
            printf("CONFLICT! Expression with different types.\n");
            return -1;
            
        }           
    }else if ( ex2->type == assignexpr_e ||ex1->type == newtable_e || ex1->type == conststring_e || ex1->type == nil_e){
        printf("CONFLICT! Invalid expression .\n");
        return -1 ;
    }
    return -1 ; 
}

struct expr * arith_calc(char pr,struct expr * expr1,struct expr * expr2 , struct expr * res){
    if(res == NULL){
        return NULL;
    }
    if(expr1 == NULL){
        return NULL;
    }
    if(expr2 == NULL){
        return NULL;
    }

    if(res->type == floatexpr_e){
        float ar;
        float ar1 = expr1 -> floatConst + (float)(expr1 -> intConst);
        float ar2 = expr2 -> floatConst + (float)(expr2 -> intConst);
        if(pr == '+'){
            ar=ar1+ar2;
        }else if(pr == '-'){
             ar=ar1-ar2;
        }else if(pr == '*'){
             ar=ar1*ar2;
        }else if(pr == '/'){
            ar=ar1/ar2;
        }else if(pr == '%'){
            printf("ERROR : float module");
        }
        res->floatConst = ar;

    }
    if(res->type == intexpr_e){
        int ar;
        int ar1 = (int)(expr1 -> floatConst) + (expr1 -> intConst);
        int ar2 = (int)(expr2 -> floatConst) + (expr2 -> intConst);
        if(pr == '+'){
            ar=ar1+ar2;
        }else if(pr == '-'){
             ar=ar1-ar2;
        }else if(pr == '*'){
             ar=ar1*ar2;
        }else if(pr == '/'){
            ar=ar1/ar2;
        }else if(pr == '%'){
            ar = ar1 % ar2;
        }
        res->intConst = ar;
    }
    return res;
}


enum expr_t arith_ret_type(int com){
    if(com==-1||com==BOOL){
        return -1;
    }
    if(com == INT){
        return intexpr_e;
    }
    return floatexpr_e;
}
// ---------------------------------------------------------------------------------------
// Compare operations
struct expr * compare_calc(char * str , struct expr * ex1,struct expr * ex2 , struct expr * res ){
    if(res == NULL){
        return NULL;
    }
    if(ex1 == NULL){
        return NULL;
    }
    if(ex2 == NULL){
        return NULL;
    }

    if(ex1->type == programfunc_e || ex1->type == libraryfunc_e || ex1->type == var_e){
        ex1->type=ex2->type;
    }
    if(ex2->type == programfunc_e || ex2->type == libraryfunc_e|| ex1->type == var_e){
        ex2->type=ex1->type;
    }
    if(strcmp(str,"==")==0){
        int flag = compare_t(ex1,ex2);
        if(ex1->type == nil_e && ex2->type == nil_e){
            res->boolConst = 1;
            return res;
        }
        if(flag==1){
            if(ex1->type==floatexpr_e || ex1->type == constfloat_e){
                float ar1=ex1->floatConst;
                float ar2=ex2->floatConst;
                if(ar1==ar2){
                    res->boolConst = 1;
                }else{
                    res->boolConst = 0;
                }

            }else if(ex1->type==intexpr_e || ex1->type == constint_e){
                int ar1=ex1->intConst;
                int ar2=ex2->intConst;
                if(ar1==ar2){
                    res->boolConst = 1;
                }else{
                    res->boolConst = 0;
                }
            }else if(ex1->type==conststring_e){
                char * ar1=ex1->strConst;
                char * ar2=ex2->strConst;
                if(ar1==NULL || ar2==NULL){
                    res->boolConst = 0;
                }else if(strcmp(ar1,ar2)==0){
                    res->boolConst = 1;
                }else{
                    res->boolConst = 0;
                }
            }else if(ex1->type==boolexpr_e || ex1->type == constbool_e){
                int ar1=ex1->boolConst;
                int ar2=ex2->boolConst;
                if(ar1==ar2){
                    res->boolConst = 1;
                }else{
                    res->boolConst = 0;
                }
            }
            return res;
        }
        int ar1=-1;
        int ar2=-1;
        if(ex1->type == nil_e || ex2->type == nil_e){
            if(ex1->type == nil_e){
                ar1 = 0;
                make_boolean(ex2);
                ar2 = ex2->boolConst;
            }
            if(ex2->type == nil_e){
                ar2 = 0;
                make_boolean(ex1);
                ar1 = ex1->boolConst;
            }

            if(ar1==ar2){
                res->boolConst=1;
            }else{
                res->boolConst=0;
            }
            return res;
        }
        
        if(ex1->type == constbool_e || ex1->type == boolexpr_e){
            ar1=ex1->boolConst;    
            make_boolean(ex2);
            ar2=ex2->boolConst;
            if(ar1==ar2){
                res->boolConst=1;
            }else{
                res->boolConst=0;
            }
            return res;
        }
        if(ex2->type == constbool_e || ex2->type == boolexpr_e){
            ar2=ex2->boolConst;    
            make_boolean(ex1);
            ar1=ex1->boolConst;
            if(ar1==ar2){
                res->boolConst=1;
            }else{
                res->boolConst=0;
            }
            return res;
        }
        
            
        printf(" %d\n",ex2->type);   
        printf("ERROR : WRONG TYPES COMPARE1\n");
        return NULL;
       
        


    }else if(strcmp(str,"!=")==0){
        res=compare_calc("==" ,ex1,ex2 , res );
        if(res==NULL){
            return NULL;
        }
        res->boolConst=!(res->boolConst);
        return res;

    }else if(strcmp(str,"<=")==0){
    
    
        if(ex1->type!=intexpr_e && ex1->type!=constint_e && ex1->type!=floatexpr_e && ex1->type!=constfloat_e ){
            if(ex1->type!=var_e){
                printf("ERROR : WRONG TYPES COMPARE2\n");
                return NULL;
            }
        }
        if(ex2->type!=intexpr_e && ex2->type!=constint_e && ex2->type!=floatexpr_e && ex2->type!=constfloat_e ){
            if(ex2->type!=var_e){
                printf("ERROR : WRONG TYPES COMPARE3\n");
                return NULL;
            }
        }

        float ar1 = ex1->floatConst + (float)ex1->intConst;
        float ar2 = ex2->floatConst + (float)ex2->intConst;
        if(ar1<=ar2){
            res->boolConst=1;
        }else{
            res->boolConst=0;
        }
        return res;
    
    }else if(strcmp(str,">")==0){
        if(ex1->type!=intexpr_e && ex1->type!=constint_e && ex1->type!=floatexpr_e && ex1->type!=constfloat_e ){
            if(ex1->type!=var_e){
                printf("ERROR : WRONG TYPES COMPARE4\n");
                return NULL;
            }
        }
        if(ex2->type!=intexpr_e && ex2->type!=constint_e && ex2->type!=floatexpr_e && ex2->type!=constfloat_e ){
            if(ex2->type!=var_e){
                printf("ERROR : WRONG TYPES COMPARE5\n");
                return NULL;
            }
        }

        float ar1 = ex1->floatConst + (float)ex1->intConst;
        float ar2 = ex2->floatConst + (float)ex2->intConst;
        if(ar1>ar2){
            res->boolConst=1;
        }else{
            res->boolConst=0;
        }
        return res;

    }else if(strcmp(str,"<")==0){
        if(ex1->type!=intexpr_e && ex1->type!=constint_e && ex1->type!=floatexpr_e && ex1->type!=constfloat_e ){
            if(ex1->type!=var_e){
                printf("ERROR : WRONG TYPES COMPARE6\n");
                return NULL;
            }
        }
        if(ex2->type!=intexpr_e && ex2->type!=constint_e && ex2->type!=floatexpr_e && ex2->type!=constfloat_e ){
            if(ex2->type!=var_e){
                printf("ERROR : WRONG TYPES COMPARE7\n");
                return NULL;
            }
        }

        float ar1 = ex1->floatConst + (float)ex1->intConst;
        float ar2 = ex2->floatConst + (float)ex2->intConst;
        if(ar1<ar2){
            res->boolConst=1;
        }else{
            res->boolConst=0;
        }
        return res;
    }else if(strcmp(str,">=")==0){
        if(ex1->type!=intexpr_e && ex1->type!=constint_e && ex1->type!=floatexpr_e && ex1->type!=constfloat_e ){
            if(ex1->type!=var_e){
                printf("ERROR : WRONG TYPES COMPARE8\n");
                return NULL;
            }
        }
        if(ex2->type!=intexpr_e && ex2->type!=constint_e && ex2->type!=floatexpr_e && ex2->type!=constfloat_e ){
            if(ex2->type!=var_e){
                printf("ERROR : WRONG TYPES COMPARE9\n");
                return NULL;
            }
        }

        float ar1 = ex1->floatConst + (float)ex1->intConst;
        float ar2 = ex2->floatConst + (float)ex2->intConst;
        if(ar1>=ar2){
            res->boolConst=1;
        }else{
            res->boolConst=0;
        }
        return res;
    }


}

void make_boolean(struct expr* ex){
    if(ex->type==intexpr_e||ex->type==constint_e){
        if(ex->intConst!=0){
            ex->boolConst='1';
        }else{
            ex->boolConst='0';
        }
    }else if(ex->type==floatexpr_e||ex->type==constfloat_e){
        if(ex->floatConst!=0.0f){
            ex->boolConst='1';
        }else{
            ex->boolConst='0';
        }
    }else if(ex->type==conststring_e){
        if(strcmp(ex->strConst,"")!=0){
            ex->boolConst='1';
        }else{
            ex->boolConst='0';
        }
    }else if(ex->type==programfunc_e||ex->type==libraryfunc_e||ex->type==tableitem_e||ex->type==newtable_e){
        if(ex->floatConst!=0.0f){
            ex->boolConst='1';
        }else{
            ex->boolConst='0';
        }
    }
    return;
}


int compare_t(struct expr * ex1 , struct expr * ex2){
    if(ex1->type==ex2->type){
        return 1;
    }
    if( (ex1->type==intexpr_e && ex2->type == constint_e)||(ex1->type==constint_e && ex2->type == intexpr_e)){
        return 1;
    }    
    if( (ex1->type==floatexpr_e && ex2->type == constfloat_e)||(ex1->type==constfloat_e && ex2->type == floatexpr_e)){
        return 1;
    }
    if( (ex1->type==boolexpr_e && ex2->type == constbool_e)||(ex1->type==constbool_e && ex2->type == boolexpr_e)){
        return 1;
    }
    if(ex1->type==var_e || ex2->type==var_e){
        return 1;
    }
    return 0;
}

struct expr * log_calc(char * op , struct expr * ex1 , struct expr * ex2,struct expr * res){
    if(ex1==NULL){
        return NULL;
    }

    if(ex2==NULL){
        return NULL;
    }
    
    if(ex1->type!=boolexpr_e && ex1->type!=constbool_e){
        ex1->boolConst=non_boll_log_calc(ex1);
        // printf("ERROR : WRONG TYPE");
        // return NULL;
    }

    if(ex2->type!=boolexpr_e && ex2->type!=constbool_e){
        ex1->boolConst=non_boll_log_calc(ex1);
        // printf("ERROR : WRONG TYPE");
        // return NULL;
    }
    if(strcmp(op,"OR")==0){
        if(ex1->boolConst=='1'){
            res->boolConst='1';
            return res;
        }

        if(ex2->boolConst=='0'){
            res->boolConst='0';
            return res;    
        }
        res->boolConst='1';
        return res;
    }
    if(strcmp(op,"AND")==0){
        if(ex1->boolConst=='0'){
            res->boolConst='0';
            return res;
        }
        if(ex2->boolConst=='1'){
            res->boolConst='1';
            return res;    
        }
        res->boolConst='0';
        return res;
    }    
    return NULL;
}

int non_boll_log_calc(struct expr* ex){
    if(ex->type==intexpr_e||ex->type==constint_e){
        if(ex->intConst!=0){
            return 1;
        }
        return 0;
    }else if(ex->type==floatexpr_e||ex->type==constfloat_e){
        if(ex->floatConst!=0){
            return 1;
        }
        return 0;
    }else if(ex->type==newtable_e||ex->type==libraryfunc_e||ex->type==programfunc_e){
        return 1;
    }else if(ex->type==conststring_e){
        if(strcmp(ex->strConst,"")!=0){
            return 1;
        }
        return 0;
    }
        return 0;
}



void print_expr(){
    struct expr * temp = mainexp;
    while(temp!=NULL){
        if(temp->sym!=NULL){
            printf("%s  ",temp->sym->name);
        }
        printf("%d  ",temp->intConst);
        printf("%c\n",temp->boolConst);
        temp=temp->next;
    }
    return;
}

//Samos Stuff

struct expr *  insert_index(struct expr * table,struct expr * node){
    if(table==NULL){
        return NULL;
    }
    if(node==NULL){
        return NULL;
    }
    struct expr * temp = table->index;
    int i=0;
    if(temp==NULL){
        table->index = node;
        return table;
    }
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=node;
    return table;
}

struct quad * creat_q(struct expr * ex1 , struct expr * ex2){
    struct quad * q = (struct quad *)malloc(sizeof(struct quad));
    q->arg2=copy_expr(ex2);
    q->arg1=copy_expr(ex1);
    
    return q;
}

struct expr* add_e(struct expr * ex1 , struct expr * ex2){
    if(ex2==NULL){
        ex2=copy_expr(ex1);
        ex2->next=NULL;
        return ex2;
    }
    struct expr* temp=ex2;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=copy_expr(ex1);
    temp->next->next=NULL;
    return ex2;
}

struct expr* free_temp(struct expr* ex2){
    if(ex2==NULL){
        return NULL;
    }
    struct expr* prev=ex2;
    struct expr* curr=ex2;
    while(curr->next!=NULL){
        prev=curr;
        curr=curr->next;
    }
    if(prev==curr){
        free(curr);
        return NULL;
    }
    prev->next=NULL;
    free(curr);
    return ex2;
}

//-------------------------------------------------4175
int check_table(struct expr* tabl){ // returns -1 if something went wrong returns 0 if everything is good
    if(tabl->type==newtable_e) {
        return 0;
    }
    return -1 ; 
}

void fill_tabelem( struct expr* tabl , struct expr* elem ){ // na tsekaroume gt otan einai adeio to index to tmp exei skoupidia == segment...
    struct expr* tmp = tabl->index; 

    if ( tmp == NULL ){
        printf("Table is empty.\n");
        return;
    }else {
                        tmp->type = elem->type;
                        tmp->intConst = elem->intConst;
                        tmp->floatConst = elem->floatConst ;
                        tmp->boolConst = elem->boolConst ;
                        tmp->strConst = elem->strConst ;
                        tabl->index = tmp ; //-----------------------
                        return;
       
    }
}

struct expr* check_index(struct expr* tabl , char* name){
    struct expr* tmp = tabl->index; 
    struct expr* tmp2;
    struct expr* prev ;
    if ( tabl->index == NULL ){
            struct hashnode* ind = (struct hashnode*) malloc(sizeof(struct hashnode));
            struct expr* ex_ind = (struct expr*) malloc(sizeof(struct expr));
            ind->name = name ; 
            ex_ind->sym = ind ; 
            ex_ind->type = tableitem_e ; 
            ex_ind->next=NULL;
            tabl->index=ex_ind;
            return tabl->index;
    }else{
        if ( strcmp(tmp->sym->name,name) == 0 ){
            return tabl->index;
        }

    prev=tmp;
    tmp=tmp->next;
    while ( tmp != NULL ){
        if ( strcmp(tmp->sym->name,name) == 0 ){
            tmp2=tmp;
            prev->next=tmp->next;
            tmp->next=tabl->index;
            tabl->index=tmp2;/////dwhbcjwebcjwekbcjkwebcjkwebbcj
            return tabl->index;
        }
        prev = tmp ; 
        tmp = tmp->next; 
    }
    }
    struct hashnode* ind = (struct hashnode*) malloc(sizeof(struct hashnode));
    struct expr* ex_ind = (struct expr*) malloc(sizeof(struct expr));
    ind->name = name ; 
    ex_ind->sym = ind ; 
    ex_ind->type = tableitem_e ; 
    ex_ind->next = tabl->index;
    tabl->index = ex_ind ; 
     printf("else in check index %s\n" , tabl->index->sym->name);
    return tabl->index;
}


struct expr* find_index(struct expr* tabl , char* name){ // na tsekaroume gt otan einai adeio to index to tmp exei skoupidia == segment...
    struct expr* tmp = tabl->index; 
    if ( tmp == NULL ){
        printf("Table is empty.\n");
        return NULL;
    }else {
        while ( tmp != NULL){
             if (strcmp(tmp->sym->name,name) == 0 ){
                    return tmp ; 
             }else {
                    tmp = tmp->next;
             }      
        }
    }
     printf("Didn't find the index:%s in table:%s\n" , name , tabl->sym->name);
     return NULL ; 
}

struct expr* check_index2(struct expr* table , struct expr* elem){
    struct expr* tmp = table->index; 
    struct expr* tmp2;
    struct expr* prev ;
    int c = elem->type;

    if ( change_type(elem) == intexpr_e){ //  || c == constfloat_e || c == conststring_e || c == constbool_e ){
        if ( table->index == NULL ){
            struct hashnode* ind = (struct hashnode*) malloc(sizeof(struct hashnode));
            struct expr* ex_ind = (struct expr*) malloc(sizeof(struct expr));  
            char* n = malloc(sizeof(char)*999) ;  
            sprintf(n , "%d" , elem->intConst );
            ind->name = strdup(n) ; 
            ex_ind->sym = ind ; 
            ex_ind->type = tableitem_e ; 
            ex_ind->next=NULL;
            table->index=ex_ind;
            return table->index;
        }else{
            char* n = malloc(sizeof(char)*999) ;  
            sprintf(n , "%d" , elem->intConst );
            return check_index(table , n);
        }
    }else if (change_type(elem) == floatexpr_e){
        if ( table->index == NULL ){
            struct hashnode* ind = (struct hashnode*) malloc(sizeof(struct hashnode));
            struct expr* ex_ind = (struct expr*) malloc(sizeof(struct expr));  
            char* n = malloc(sizeof(char)*999) ;  
            sprintf(n , "%f" , elem->floatConst );
            ind->name = strdup(n) ; 
            ex_ind->sym = ind ; 
            ex_ind->type = tableitem_e ; 
            ex_ind->next=NULL;
            table->index=ex_ind;
            return table->index;
        }else{
            char* n = malloc(sizeof(char)*999) ;  
            sprintf(n , "%f" , elem->floatConst );
           return check_index(table , n);
        }
    }else if (change_type(elem) == boolexpr_e){
        if ( table->index == NULL ){
            struct hashnode* ind = (struct hashnode*) malloc(sizeof(struct hashnode));
            struct expr* ex_ind = (struct expr*) malloc(sizeof(struct expr));  
            char* n = malloc(sizeof(char)*999) ;  
            sprintf(n , "%d" , elem->boolConst );
            ind->name = strdup(n) ; 
            ex_ind->sym = ind ; 
            ex_ind->type = tableitem_e ; 
            ex_ind->next=NULL;
            table->index=ex_ind;
            return table->index;
        }else{
            char* n = malloc(sizeof(char)*999) ;  
            sprintf(n , "%d" , elem->boolConst );
            return check_index(table , n);
        }
    }else if ( elem->type == conststring_e){
         if ( table->index == NULL ){
            struct hashnode* ind = (struct hashnode*) malloc(sizeof(struct hashnode));
            struct expr* ex_ind = (struct expr*) malloc(sizeof(struct expr));  
            ind->name = strdup(elem->strConst) ; 
            ex_ind->sym = ind ; 
            ex_ind->type = tableitem_e ; 
            ex_ind->next=NULL;
            table->index=ex_ind;
            return table->index;
        }else{
           return check_index(table , strdup(elem->strConst));
        }
    }
}

struct expr* update_index (char* name , struct expr* in){
    struct expr * extemp=mainexp; 
    while(extemp!=NULL){
        if(strcmp(extemp->sym->name,name)==0){
            extemp->index = in ; 
            return extemp->index;
        }
        extemp=extemp->next;
    }
}