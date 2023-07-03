%{
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include "a.h"
        #include "syntax_functions.h"
        #include "intermediate.h"
        #include "finalcode.h"

        #define NOTFOUND -1
        #define FUNVARCONF -2
        #define LIBRFOUND -3
        #define UPPERSCOPEVAR -4

        int yyerror(char* yaccProvidedMessage);

        struct alpha_token_t* ylval;
        extern int yylex();
        extern int yylineno;
        extern char* yytext;
        extern FILE* yyin;
        struct hashnode* terms=NULL;
        struct hashnode* callnode=NULL;
        int n;
        int sizescope=-1;
        struct scopenode * scopelist;
        char fun_name[20]="@";
        int rf=0;
        int fun_name_num=1;
        int from_member=0;
        int if_block=0;
        int while_block=0;
        int for_block=0;
        int function_block=0;
        int scope_count = 0;
        int simple_block=1;
        int dd=0;
        struct expr* temp_as;
        struct expr* temp_expr;
        struct expr* temp_table;
        struct expr* tables_temp;
        char* temp_name;
        int quad_count=1;
        struct quad* table_stack;
        struct expr* true_expr;
        struct expr* false_expr;
        struct expr* one_expr;
        struct quad* if_jump;
        struct quad* if_else;
        struct quad* else_jump;
        struct quad* while_jump;
        struct quad* break_jump;
        struct quad* for_jump;
        struct quad* function_jump;
        struct quad* return_jump;
        struct quad* fun_name_quad;
        struct quad* elist_list;
        struct quad* true_quad;
        struct quad* false_quad;
        int    loop;
        struct jump_stack* else_jump_list;
        struct jump_stack* if_jump_list;
        struct jump_stack* while_jump_list;
        struct jump_stack* for_true_jump_list;
        struct jump_stack* for_false_jump_list;
        struct bcr_stack* break_jump_list;
        struct jump_stack* function_jump_list;
        struct bcr_stack* return_jump_list;
        struct jump_stack* fun_name_quad_list;
        struct jump_stack* true_list;
        struct jump_stack* false_list;
        struct loop* loop_jump_list;
        struct loop* increment_jump_list;
        int call_flag=0;
        int object_flag=0;
        int from_table = 0 ;
        char* tabname;
        int tabtype = -1 ;
        int tabnum ; 
        float tabfl ; 
        char tabbool ; 
        char* tabst ; 
        int checking ; 
        struct expr* tabmem ; 
        struct expr* tabnode;
        struct expr* tmp_e ; 
        int flagN = 0 ;
        int programf=0;
        int formalf=0;
        struct local_flag* local_f=NULL;
        struct local_flag* formal_f=NULL;
        struct bcr_stack* tmp_ret_stack=NULL;
        struct bcr_stack* tmp_bcr_stack=NULL;
        struct hashnode* assign_ins=NULL;
        struct expr* formalarg_list=NULL;
        struct expr* dummy=NULL;

%}
%error-verbose

%start program

%union {
char* stringValue;
int intValue;
float realValue;
struct expr* expressValue;
}


/*
Terminal symbols
*/

// identifier
%token <stringValue> ID
// string
%token <stringValue> STRING
//words
%token <stringValue> WHILE FOR IF ELSE FUNCTION RETURN BREAK CONT LOCAL TRUE FALSE NIL
//logical operators
%token <stringValue> AND OR NOT 
//arithmetical operators
%token <stringValue> PLUS MINUS ASSIGN MULTIPLY MODULE DIVIDE DECREASE INCREASE
//compare operators
%token <stringValue> GREAT_EQUAL LESS_EQUAL GREATER LESS EQUAL NOTEQUAL
// parenthesis
%token <stringValue> L_C_BRACKET R_C_BRACKET L_S_BRACKET R_S_BRACKET L_PARENTH R_PARENTH
// operands
%token <stringValue> COMA SEMICOLON COLON D_COLON DOT D_DOT OTHER
//integer
%token <intValue> INTCONST
//float
%token <realValue> RCONST

/*
Non-terminal symbols
*/
%type <stringValue> stmt
%type <expressValue> expr
%type <expressValue> term
%type <expressValue> assignexpr
%type <expressValue> primary
%type <expressValue> lvalue
%type <expressValue> member
%type <expressValue> call
%type <stringValue> callsuffix
%type <stringValue> normcall
%type <stringValue> methodcall
%type <stringValue> elist
%type <expressValue> objectdef
%type <stringValue> indexed
%type <stringValue> indexedelem
%type <stringValue> block
%type <expressValue> funcdef
%type <stringValue> idlist
%type <stringValue> ifstmt
%type <stringValue> whilestmt
%type <stringValue> forstmt
%type <stringValue> returnstmt
%type <stringValue> insideblock
%type <expressValue> const
%right ASSIGN
%left OR
%left AND
%nonassoc EQUAL NOTEQUAL
%nonassoc GREAT_EQUAL LESS_EQUAL GREATER LESS 
%left PLUS MINUS
%left MULTIPLY MODULE DIVIDE
%right NOT DECREASE INCREASE
%left DOT D_DOT
%left R_C_BRACKET L_S_BRACKET
%left L_PARENTH R_PARENTH
%%
program: stmt program  
        |       {
			//printf("Program end\n");
		}
        ;


stmt: expr SEMICOLON {
			temp_as=NULL;
                        //  tabmem = NULL;
                          flagN = 0 ;
                        //reset_var_name();
                        //printf("expression; -->statement\n");
		}
    | ifstmt    {
                        if_else=NULL;
                        //printf("if statement -->statement\n");
		}
    | whilestmt {
                        //printf("while loop-->statement\n");
		}
    | forstmt   {
                        //printf("for loop-->statement\n");
		}
    | returnstmt SEMICOLON
                {
                        if(function_block==0){
                                printf("ERROR!Return outside function in line %d\n",yylineno);
                        }
			//printf("return statement;-->statement\n");
		}
    | BREAK SEMICOLON 
                {
                        if(if_block==0 && for_block==0 && while_block==0){
                                printf("ERROR!Break outside loop in line %d\n",yylineno);
                        }else{
                                break_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                                push_jump_stack(break_jump,&(break_jump_list->head));
                        }
			// printf("break-->statement\n");
		}
    | CONT SEMICOLON
                {
                        if(if_block==0 && for_block==0 && while_block==0){
                                printf("ERROR!Continue outside loop in line %d\n",yylineno);
                        }else if(for_block==1){
                                emit(jump,NULL,NULL,NULL,increment_jump_list->num,yylineno);
                        }else if(while_block==1){
                                emit(jump,NULL,NULL,NULL,loop_jump_list->num,yylineno);
                        }
			// printf("continue;-->statement\n");
		}
    | {simple_block=1;} block     { simple_block=1;
			// printf("block-->statement\n");
		}
    | funcdef   {
			// printf("function definition-->statement\n");
		}
    |SEMICOLON  {
			// printf(";-->statement\n");
		}
    ;


expr: assignexpr 
                        {
                                $$=$1;
                                // printf("Assign expression -->expression\n");
                        }
        | expr PLUS expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                temp_expr->type = arith_ret_type(arith_compare_type($1,$3));
                                temp_expr=arith_calc('+',$1,$3,temp_expr);
                                $$=copy_expr(temp_expr);
                                emit(add,$1,$3,$$,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
        | expr MINUS expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                temp_expr->type = arith_ret_type(arith_compare_type($1,$3));
                                temp_expr=arith_calc('-',$1,$3,temp_expr);
                                $$=copy_expr(temp_expr);
                                emit(sub,$1,$3,$$,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
         | expr MULTIPLY expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                temp_expr->type = arith_ret_type(arith_compare_type($1,$3));
                                temp_expr=arith_calc('*',$1,$3,temp_expr);
                                $$=copy_expr(temp_expr);
                                emit(mul,$1,$3,$$,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
        | expr MODULE expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                temp_expr->type = arith_ret_type(arith_compare_type($1,$3));
                                temp_expr=arith_calc('%',$1,$3,temp_expr);
                                $$=copy_expr(temp_expr);
                                emit(mod,$1,$3,$$,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
         | expr DIVIDE expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                temp_expr->type = arith_ret_type(arith_compare_type($1,$3));
                                temp_expr=arith_calc('/',$1,$3,temp_expr);
                                $$=copy_expr(temp_expr);
                                emit(divide,$1,$3,$$,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
        | expr GREAT_EQUAL expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc(">=",$1,$3,temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc(">=",$1,$3,temp_expr);
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                $$=copy_expr(temp_expr);
                                emit(if_greatereq,$1,$3,NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                emit(assign,true_expr,NULL,temp_expr,-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
         | expr LESS_EQUAL expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("<=",$1,$3,temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("<=",$1,$3,temp_expr);
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                $$=copy_expr(temp_expr);
                                emit(if_lesseq,$1,$3,NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                               // printf("%d\n",true_expr->type);
                                emit(assign,true_expr,NULL,temp_expr,-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
        | expr GREATER expr 
                        {       temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc(">",$1,$3,temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc(">",$1,$3,temp_expr);
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                $$=copy_expr(temp_expr);
                                emit(if_greater,$1,$3,NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                //printf("%d\n",true_expr->type);
                                emit(assign,true_expr,NULL,temp_expr,-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
         | expr LESS expr 
                        {       temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("<",$1,$3,temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("<",$1,$3,temp_expr);
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                $$=copy_expr(temp_expr);
                                emit(if_less,$1,$3,NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                //printf("%d\n",true_expr->type);
                                emit(assign,true_expr,NULL,copy_expr(temp_expr),-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
        | expr EQUAL expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("==",$1,$3,temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("==",$1,$3,temp_expr);
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                $$=copy_expr(temp_expr);
                                emit(if_eq,$1,$3,NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                //printf("%d\n",true_expr->type);
                                emit(assign,true_expr,NULL,temp_expr,-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
         | expr NOTEQUAL expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("!=",$1,$3,temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("!=",$1,$3,temp_expr);
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                $$=copy_expr(temp_expr);
                                emit(if_not_eq,$1,$3,NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                //printf("%d\n",true_expr->type);
                                emit(assign,true_expr,NULL,temp_expr,-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);

                                // printf("expression %s expression -->expression\n",$2);
                        }
        | expr AND expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=(struct expr *)log_calc("AND",$1,$3,temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=(struct expr *)log_calc("AND",$1,$3,temp_expr);
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                $$=copy_expr(temp_expr);
                                
                                // emit(if_eq,NULL,true_expr,$<expressValue>4,quad_count+2,yylineno);
                                // emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                // emit(assign,NULL,true_expr,$<expressValue>$,-1,yylineno);
                                // pop_jump_stack(&false_list)->label=quad_count+1;
                                // emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                // emit(assign,NULL,false_expr,$<expressValue>$,-1,yylineno);
                                emit(and,$1,$3,$$,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
         | expr OR expr 
                        {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=(struct expr *)log_calc("OR",$1,$3,temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=(struct expr *)log_calc("OR",$1,$3,temp_expr);
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                $$=copy_expr(temp_expr);
                                // emit(if_eq,NULL,true_expr,$<expressValue>4,quad_count+2,yylineno);
                                // emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                // pop_jump_stack(&true_list)->label=quad_count;
                                // emit(assign,NULL,true_expr,$<expressValue>$,-1,yylineno);
                                // emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                // emit(assign,NULL,false_expr,$<expressValue>$,-1,yylineno);
                                emit(or,$1,$3,$$,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        }
        | term      {
                                $$=$1;
                                // printf("term-->expression\n");
                        }
        ;




term: L_PARENTH expr R_PARENTH {
                        $$=$2;
			// printf("(expression)-->term\n");
                }
    | MINUS expr{
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_expr->type = $2->type;
                                temp_expr->intConst= (-1)*$2->intConst;
                                temp_expr->floatConst= (-1)*$2->floatConst;
                        }else{
                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                temp_expr->type = $2->type;
                                temp_expr->intConst= (-1)*$2->intConst;
                                temp_expr->floatConst= (-1)*$2->floatConst;
                                if(function_block!=0){
                                        temp_expr->sym->space=functionlocal;
                                        temp_expr->sym->offset=local_f->num;
                                        local_f->num++;
                                }else{
                                        temp_expr->sym->space=programvar;
                                        temp_expr->sym->offset=programf;
                                        programf++;
                                }
                                fillExp(copy_expr(temp_expr));
                        }
                        $$=copy_expr(temp_expr);
                        emit(uminus,$2,NULL,$$,-1,yylineno);
			// printf("-expression-->term\n");
                }
    | NOT expr {
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_expr->type = boolexpr_e;
                                if($2->type!=boolexpr_e && $2->type!=constbool_e){
                                        printf("ERROR : WRONG TYPE");
                                }else{
                                        temp_expr->boolConst=!($2->boolConst);
                                }
                        }else{
                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                temp_expr->type = boolexpr_e;
                                if($2->type!=boolexpr_e && $2->type!=constbool_e){
                                        temp_expr->boolConst=!non_boll_log_calc($2);
                                }else{
                                        temp_expr->boolConst=!($2->boolConst);
                                }
                                if(function_block!=0){
                                        temp_expr->sym->space=functionlocal;
                                        temp_expr->sym->offset=local_f->num;
                                        local_f->num++;
                                }else{
                                        temp_expr->sym->space=programvar;
                                        temp_expr->sym->offset=programf;
                                        programf++;
                                }
                                fillExp(copy_expr(temp_expr));
                        }
                        $$=copy_expr(temp_expr);
                        emit(not,$2,NULL,$$,-1,yylineno);
                        // $$=$2;
                        // printf("not expression -->term\n");
                }
    | INCREASE lvalue {
			if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",$2->sym->name,terms->line);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else{
                                        $2=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $2->type;
                                                $2->intConst++;
                                                temp_expr->intConst= $2->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $2->type;
                                                $2->intConst++;
                                                temp_expr->intConst= $2->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        $$=copy_expr(temp_expr);
                                        emit(add,$2,one_expr,$2,-1,yylineno);
                                        emit(assign,$2,NULL,$$,-1,yylineno); 
                                }
                        }else{
                                n=LookUp($2->sym->name,$2->sym->type,$2->sym->vision,$2->sym->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",$2->sym->name,yylineno);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $2->index->type;
                                                $2->index->intConst++;
                                                temp_expr->intConst= $2->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $2->index->type;
                                                $2->index->intConst++;
                                                temp_expr->intConst= $2->index->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        $$=copy_expr(temp_expr);
                                        emit(tablegetelem,$2,$2->index,$$,-1,yylineno); 
                                        emit(add,$$,one_expr,$$,-1,yylineno);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $2->index->type;
                                                $2->intConst++;
                                                temp_expr->intConst= $2->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $2->index->type;
                                                $2->intConst++;
                                                temp_expr->intConst= $2->index->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        emit(assign,copy_expr(temp_expr),NULL,$$,-1,yylineno); 
                                        $$ = copy_expr($2);
                                }
                                from_member=0;
                        
                        }
                         //printf("++value-->term\n");
                }
    | lvalue INCREASE {
                        if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",$1->sym->name,yylineno);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else{
                                        $1=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $1->type;
                                                $1->intConst++;
                                                temp_expr->intConst= $1->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $1->type;
                                                $1->intConst++;
                                                temp_expr->intConst= $1->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        $$=copy_expr(temp_expr);
                                        emit(assign,$1,NULL,$$,-1,yylineno); 
                                        emit(add,$1,one_expr,$1,-1,yylineno);
                                }
                        }else{
                                n=LookUp($1->sym->name,$1->sym->type,$1->sym->vision,$1->sym->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",$1->sym->name,yylineno);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $1->index->type;
                                                $1->index->intConst++;
                                                temp_expr->intConst= $1->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $1->index->type;
                                                $1->index->intConst++;
                                                temp_expr->intConst= $1->index->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        $$=copy_expr(temp_expr);
                                        emit(tablegetelem,$1,$1->index,$$,-1,yylineno); 
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $1->index->type;
                                                $1->intConst++;
                                                temp_expr->intConst= $1->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $1->index->type;
                                                $1->intConst++;
                                                temp_expr->intConst= $1->index->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        emit(assign,$$,NULL,copy_expr(temp_expr),-1,yylineno);
                                        emit(add,$$,one_expr,$$,-1,yylineno); 
                                        emit(tablesetelem,$1,$1->index,$$,-1,yylineno); 
                                        $$ = copy_expr($1);
                                }
                                from_member=0;
                        
                        }
			// printf("value++-->term\n");
                }
    | DECREASE lvalue {
                        if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",$2->sym->name,yylineno);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                        $2=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $2->type;
                                                $2->intConst--;
                                                temp_expr->intConst= $2->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $2->type;
                                                $2->intConst--;
                                                temp_expr->intConst= $2->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        $$=copy_expr(temp_expr);
                                        emit(sub,$2,one_expr,$2,-1,yylineno);
                                        emit(assign,$2,NULL,$$,-1,yylineno); 
                                }
                        }else{
                                n=LookUp($2->sym->name,$2->sym->type,$2->sym->vision,$2->sym->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",$2->sym->name,yylineno);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $2->index->type;
                                                $2->index->intConst--;
                                                temp_expr->intConst= $2->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $2->index->type;
                                                $2->index->intConst--;
                                                temp_expr->intConst= $2->index->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        $$=copy_expr(temp_expr);
                                        emit(tablegetelem,$2,$2->index,$$,-1,yylineno); 
                                        emit(sub,$$,one_expr,$$,-1,yylineno);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $2->index->type;
                                                $2->intConst++;
                                                temp_expr->intConst= $2->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $2->index->type;
                                                $2->intConst++;
                                                temp_expr->intConst= $2->index->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        emit(assign,copy_expr(temp_expr),NULL,$$,-1,yylineno); 
                                        $$ = copy_expr($2);
                                }
                                from_member=0;
                        }
			//  printf("--value-->term\n");
                }
    | lvalue DECREASE {
                        if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",$1->sym->name,yylineno);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                        $1=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $1->type;
                                                $1->intConst++;
                                                temp_expr->intConst= $1->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $1->type;
                                                $1->intConst++;
                                                temp_expr->intConst= $1->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        $$=copy_expr(temp_expr);
                                        emit(assign,$1,NULL,$$,-1,yylineno); 
                                        emit(sub,$1,one_expr,$1,-1,yylineno);
                                }
                        }else{
                                n=LookUp($1->sym->name,$1->sym->type,$1->sym->vision,$1->sym->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",$1->sym->name,yylineno);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $1->index->type;
                                                $1->index->intConst--;
                                                temp_expr->intConst= $1->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $1->index->type;
                                                $1->index->intConst--;
                                                temp_expr->intConst= $1->index->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        $$=copy_expr(temp_expr);
                                        emit(tablegetelem,$1,$1->index,$$,-1,yylineno); 
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = $1->index->type;
                                                $1->intConst--;
                                                temp_expr->intConst= $1->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = $1->index->type;
                                                $1->intConst--;
                                                temp_expr->intConst= $1->index->intConst;
                                                if(function_block!=0){
                                                        temp_expr->sym->space=functionlocal;
                                                        temp_expr->sym->offset=local_f->num;
                                                        local_f->num++;
                                                }else{
                                                        temp_expr->sym->space=programvar;
                                                        temp_expr->sym->offset=programf;
                                                        programf++;
                                                }
                                                fillExp(copy_expr(temp_expr));
                                        } 
                                        emit(assign,$$,NULL,copy_expr(temp_expr),-1,yylineno);
                                        emit(sub,$$,one_expr,$$,-1,yylineno); 
                                        emit(tablesetelem,$1,$1->index,$$,-1,yylineno); 
                                        $$ = copy_expr($1);
                                }
                                from_member=0;

                        }
			// printf("value---->term\n");
                }
    | primary {
                        $$=$1;
                        // printf("primary-->term\n");
                }
    ;


assignexpr: lvalue {
                        if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(strcmp(terms->vision,"::")==0){
                                        if(n==-1){
                                                printf("ERROR! Variable %s not found in global scope in line %d\n",terms->name,terms->line);
                                        }else if(n==-2){
                                                //printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                                $1=copy_expr(find_expr(terms->name , "user function" , terms->vision ,  terms->scope));
                                        }else{
                                                $1=copy_expr(find_expr(terms->name , terms->type , terms->vision ,  terms->scope));
                                        }
                                }else if(n==-1){
                                        temp_expr = (struct expr*) malloc(sizeof(struct expr));
                                        temp_expr->sym = insert_node(terms->scope,terms->line,terms->type,terms->name,terms->vision);
                                        assign_ins= temp_expr->sym;
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        temp_expr->strConst=NULL;
                                        //fillExp(copy_expr(temp_expr));
                                        $1=copy_expr(temp_expr);
                                }else if(n==-2){
                                        //printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                        $1=copy_expr(find_expr(terms->name , "user function" , terms->vision ,  terms->scope));
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                        $1=copy_expr(find_expr(terms->name , terms->type , terms->vision ,  terms->scope));
                                }
                                //IF NOT FOUND INSERT
                        }else{
                                from_member=0;//mporei na fugei
                        }
                }
        ASSIGN expr {
                if($4->type==newtable_e && flagN == 0 ){
                        struct expr * tsym=copy_expr($1);
                        $1=copy_expr($4);
                        $1->type=change_type($4);
                        $1->sym=tsym->sym;
                        fillExp(copy_expr($1));
                        emit(assign , copy_expr($4) , NULL , $1, -1, yylineno);
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_expr->type=change_type($1);
                        }else{
                                temp_expr->type=change_type($1);
                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                temp_expr->strConst=NULL;
                                if(function_block!=0){
                                        temp_expr->sym->space=functionlocal;
                                        temp_expr->sym->offset=local_f->num;
                                        local_f->num++;
                                }else{
                                        temp_expr->sym->space=programvar;
                                        temp_expr->sym->offset=programf;
                                        programf++;
                                }
                                fillExp(copy_expr(temp_expr));
                        }
                        emit(assign , $1 , NULL , copy_expr(temp_expr), -1, yylineno);
                        $$=copy_expr(temp_expr);
                }else if ($1->type == newtable_e && flagN == 1 ){
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=find_expr(temp_name,"variable","-",scope_count);
                                temp_expr->type=change_type($1);
                        }else{
                                temp_expr->type=change_type($1);
                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                temp_expr->strConst=NULL;
                                if(function_block!=0){
                                        temp_expr->sym->space=functionlocal;
                                        temp_expr->sym->offset=local_f->num;
                                        local_f->num++;
                                }else{
                                        temp_expr->sym->space=programvar;
                                        temp_expr->sym->offset=programf;
                                        programf++;
                                }
                                fillExp(copy_expr(temp_expr));
                        }
                        if (tabmem != NULL && tabmem->next != NULL && ($4->type == newtable_e || $4->type == tableitem_e)){
                                if ( $4->type == tableitem_e){
                                        emit(tablesetelem,tabmem->next->index,$4,tabmem->next,-1,yylineno);
                                //}else if ($4->type == newtable_e){
                                      //  emit(tablesetelem,tabmem->index,$4,tabmem,-1,yylineno);
                                }
                                fill_tabelem(tabmem, tabmem->next );
                                emit(tablegetelem, $1, $1->index, copy_expr(temp_expr),-1,yylineno);
                                temp_expr->type = newtable_e;
                                temp_expr->strConst=NULL;
                                $$ = copy_expr(temp_expr);
                        }else if (tabtype == -1 ) {
                                fill_tabelem($1, $4 );
                                emit(tablesetelem,$1->index,$4,$1,-1,yylineno);
                                emit(tablegetelem, $1, $1->index, copy_expr(temp_expr),-1,yylineno);
                                $$ = copy_expr(temp_expr);       
                        }
                        else{
                                fill_tabelem(copy_expr($1), copy_expr($4));
                                emit(tablesetelem,tabmem->index,$4,tabmem,-1,yylineno);
                                emit(tablegetelem, tabmem, tabmem->index, copy_expr(temp_expr),-1,yylineno);   
                                $$ = copy_expr(temp_expr);
                        }

                        tabmem = tabmem->next;
                        from_member = 0 ;
                        tabtype = -1 ; 
                        $1->index =  update_index($1->sym->name , $1->index) ; 

                }else if ( $4->type != newtable_e && flagN == 0 ){
                        if(from_member==0){
                                if($4->type==2) assign_ins->type="user function";
                                $1->type=change_type($4);
                                $1->intConst=$4->intConst;
                                $1->floatConst=$4->floatConst;
                                if($4->strConst) $1->strConst=strdup($4->strConst);
                                else $1->strConst=NULL;
                                $1->boolConst=$4->boolConst;
                                fillExp(copy_expr($1));
                                emit(assign , copy_expr($4) , NULL , $1, -1, yylineno);
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type=change_type($1);
                                }else{
                                        temp_expr->type=change_type($1);
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->strConst=NULL;
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                emit(assign , $1 , NULL , temp_expr, -1, yylineno);
                                $$=copy_expr(temp_expr);
                        }
                }
                // printf("lvalue=expression-->assignexpr\n");
        };


primary: lvalue {
			if(from_member==0){

                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(n==-1||n==-2||n==-4){
                                        terms->type="user function";
                                        n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                        if(n==-1){
                                                if(object_flag>=1 && rf==0){
                                                        temp_expr = (struct expr*) malloc(sizeof(struct expr));
                                                        temp_expr->sym=insert_node(terms->scope,yylineno,"variable",terms->name,terms->vision);
                                                        $$=copy_expr(temp_expr);
                                                        
                                                }else{
                                                        printf("ERROR! Undeclared variable in line %d\n",yylineno);
                                                }
                                        }else if(n==-2){
                                                printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                        }else if(n==-4){
                                                if(simple_block==0){
                                                        printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                                }
                                        }else if(n==-3){
                                            if(call_flag==1 || (object_flag>=1 && rf==1)){ 
                                              temp_expr = (struct expr*) malloc(sizeof(struct expr));
                                              temp_expr->type=libraryfunc_e;
                                              temp_expr->sym=search0(terms->name);
                                              $$=copy_expr(temp_expr);
                                            }else{
                                                    printf("ERROR CONFLICT LIB-FUN IN LINEEEE: %d\n",terms->line);
                                            }
                                        }else{
                                                $1=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                                $$=copy_expr($1);
                                        }
                                }else{
                                        $1=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                        $$=copy_expr($1);
                                }
                        }else if ( from_member == 1){
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=find_expr(temp_name,"variable","-",scope_count);
                                        temp_expr->type=$1->index->type;
                                        temp_expr->intConst=$1->index->intConst;
                                        temp_expr->floatConst=$1->index->floatConst;
                                        if($1->index->strConst) temp_expr->strConst=strdup($1->index->strConst);
                                }else{
                                        temp_expr->type=change_type($1);
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type=$1->index->type;
                                        temp_expr->intConst=$1->index->intConst;
                                        temp_expr->floatConst=$1->index->floatConst;
                                        if($1->index->strConst) temp_expr->strConst=strdup($1->index->strConst);
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                if ( tabtype == -1 ){
                                        emit(tablegetelem,$1,$1->index,copy_expr(temp_expr),-1,yylineno);//edw na tsekarw
                                        $$ = copy_expr(temp_expr);
                                }else{
                                        emit(tablegetelem,tabmem,tabmem->index,copy_expr(temp_expr),-1,yylineno);
                                        $$ = copy_expr(temp_expr);
                                }
                                if ( tabmem != NULL && tabmem->next != NULL){
                                        from_member = 1 ;
                                }else{
                                        from_member=0;
                                }
                        }
                        if(object_flag>=1 && rf==0){
                            rf=1;
                        }
                        // printf("value-->primary\n");
                }
        | call {
                        $$=$1;
                        // printf("call-->primary\n");
                }
        | objectdef {
                        object_flag--;
                        $$=$1;
			// printf("object definition-->primary\n");
                }
        | L_PARENTH funcdef R_PARENTH {
			$$=$2;
                        // printf("(function definition)-->primary\n");
                }
        | const {
                        $$=$1;
                        // printf("const-->primary\n");
                }
        ;


lvalue: ID              {
                                terms->name=strdup($1);
                                terms->type=NULL;
                                terms->line=yylineno;
                                terms->vision="-";
                                terms->scope=scope_count;
                                from_member=0;
                                // printf("identifier-->lvalue\n");

		        }
        |LOCAL ID       {
                                terms->name=strdup($2);
                                terms->type="variable";
                                terms->line=yylineno;
                                terms->vision="local";
                                terms->scope=scope_count;
                                from_member=0;
			        // printf("local identifier-->lvalue\n");
                        }
        | D_COLON ID    {
                                terms->name=strdup($2);
                                terms->type=NULL;
                                terms->line=yylineno;
                                terms->vision="::";
                                terms->scope=scope_count;
                                terms->snext=NULL;
                                from_member=0;
                                $$=$2;
	        		// printf("::identifier-->lvalue\n");
                }
        |member {       
                        from_member=1;
                        $$=$1;
			//printf("member-->lvalue\n");
                }
        ;


member: lvalue DOT ID {
                        if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(n==-1){
                                        //printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                                        temp_expr->type=newtable_e;
                                        temp_expr->strConst=NULL;
                                        temp_expr->sym=insert_node(terms->scope,terms->line,terms->type,terms->name,terms->vision);
                                        temp_expr->index=NULL;
                                        fillExp(copy_expr(temp_expr));
                                        $1=copy_expr(temp_expr);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                       temp_expr=find_expr(terms->name,"variable","-",scope_count);
                                       temp_expr->type = newtable_e;
                                       $1 = copy_expr(temp_expr); 

                                }
                        }else{
                                from_member=0;
                        }
                        // terms->name=(char*) malloc(sizeof($3)+1);
                        // terms->name[0]='.';
                        // strcat(&(terms->name[1]),$3);
                        // terms->type="variable";
                        // terms->line=yylineno;
                        // terms->vision="-";
                        // terms->scope=scope_count;
                        // n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                        // if(n==-1){
                        //         insert_node(terms->scope,terms->line,terms->type,terms->name,terms->vision);
                        // }
                        checking = check_table($1) ; 
                        if ( checking == -1 ){
                                printf("ERROR variable %s isn't newtable_e.\n" , $1->sym->name);
                        }else{
                               
                                if ( tabmem == NULL ){
                                        tabname = strdup($3) ;
                                        $1->index = check_index($1,tabname);
                                        tabmem = copy_expr($1);
                                }else{ 
                                        tabname = strdup($3) ;
                                        $1->index = check_index($1 , tabname);
                                        tabnode = copy_expr($1);
                                        tabnode->next = tabmem;
                                        tabmem = tabnode;       
                                }
                                tabtype = -1;
                                flagN = 1 ;
                                $$ = copy_expr($1) ; 
                               // printf("value.identifier-->member\n");
                        }

                }
        |lvalue {
			if(from_member==0){
                                printf ("ok\n");
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                 printf ("ok\n");
                                if(n==-1){
                                        //printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                                        temp_expr->type=newtable_e;
                                        temp_expr->sym=insert_node(terms->scope,terms->line,terms->type,terms->name,terms->vision);
                                        temp_expr->index=NULL;
                                        temp_expr->strConst=NULL;
                                        fillExp(copy_expr(temp_expr));
                                        $1=copy_expr(temp_expr);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                       temp_expr=find_expr(terms->name,"variable","-",scope_count);
                                       temp_expr->type = newtable_e;
                                       $1 = copy_expr(temp_expr); 
                                }
                        }else{
                                from_member=0;
                        }
                }
        L_S_BRACKET expr R_S_BRACKET {
                        checking = check_table($1) ; 
                        if ( checking == -1 ){
                                printf("ERROR variable %s isn't newtable_e.\n" , $1->sym->name);
                        }else{
                              
                                tabtype = $4->type;
                               // if ( tabtype == 9 ){
                                  //      tabnum = $4->intConst ; 
                                   //     printf("check-int :%d \n" , $4->intConst);
                                //}else if ( tabtype == 10 ){
                                      //  tabfl = $4->floatConst;
                                      //  printf("check-float : %f \n", $4->floatConst);
                             //   }else if ( tabtype == 11){
                                      //  tabbool = $4->boolConst ;
                                      //  printf("check-bool  : %c \n", $4->boolConst); 
                             //   }else if ( tabtype == 12){ // gia kapoio logo den gemizei to strConst sto expr 
                                   //     tabst = $4->strConst;
                                      //   printf("check-string  : %s \n", $4->strConst);
                               // }else {
                                      //  tabname = $4->sym->name;
                            //    }
                                 if ( tabmem == NULL ){
                                        $1->index = check_index2($1,$4);
                                        tabmem = copy_expr($1);
                                }else{ 
                                        $1->index = check_index2($1 , $4);
                                        tabnode = copy_expr($1);
                                        tabnode->next = tabmem;
                                        tabmem = tabnode;     
                                }
                                tabtype =tabmem->index->type; 
                                 $$ = copy_expr($1) ; 
                        }

                        flagN = 1 ;
                        // printf("value[expresion]-->member\n");
                }
        |call DOT ID{
			// terms->name=(char*) malloc(sizeof($3)+1);
                        // terms->name[0]='.';
                        // strcat(&(terms->name[1]),$3);
                        // terms->type="variable";
                        // terms->line=yylineno;
                        // terms->vision="-";
                        // terms->scope=scope_count;
                        // n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                        // if(n==-1){
                        //         insert_node(terms->scope,terms->line,terms->type,terms->name,terms->vision);
                        // }
                        // printf("call.identifier-->member\n");
                }
        |call L_S_BRACKET expr R_S_BRACKET {
			// printf("call[expression]-->member\n");
                }
        ;


call:   call {call_flag=1;} L_PARENTH elist R_PARENTH {
			// printf("(elist)-->call\n");
                        // emit_elist_quads(&elist_list);
                        emit(call,NULL,NULL,copy_expr($1),-1,yylineno);
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_expr->type=var_e;
                        }else{
                                temp_expr->type=var_e;
                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                if(function_block!=0){
                                        temp_expr->sym->space=functionlocal;
                                        temp_expr->sym->offset=local_f->num;
                                        local_f->num++;
                                }else{
                                        temp_expr->sym->space=programvar;
                                        temp_expr->sym->offset=programf;
                                        programf++;
                                }
                                fillExp(copy_expr(temp_expr));
                        }
                        emit(getretval,NULL,NULL,copy_expr(temp_expr),-1,yylineno);
                        $$=copy_expr(temp_expr);
                }
        |lvalue {
			callnode->name=strdup(terms->name);
                        callnode->vision=strdup(terms->vision);
                        callnode->scope=terms->scope;
                        callnode->line=terms->line;
                        call_flag=1;
                        if(from_member==0){
                                if(strcmp(callnode->name,"print")==0||strcmp(callnode->name,"input")==0||strcmp(callnode->name,"objectmemberkeys")==0||
                                        strcmp(callnode->name,"objecttotalmembers")==0||strcmp(callnode->name,"objectcopy")==0||strcmp(callnode->name,"totalarguments")==0||
                                        strcmp(callnode->name,"argument")==0||strcmp(callnode->name,"typeof")==0||strcmp(callnode->name,"strtonum")==0||
                                        strcmp(callnode->name,"sqrt")==0||strcmp(callnode->name,"cos")==0||strcmp(callnode->name,"sin")==0){
                                        
                                        callnode->type="library function";
                                }else if(dd==1){
                                        callnode->type="variable";
                                        dd=0;
                                }else{
                                        callnode->type="user function";
                                }
                                if(strcmp(callnode->vision,"local")==0){
                                        printf("Error! Local prefix in function call in line %d",yylineno);
                                }else{
                                        n=LookUp(callnode->name,callnode->type,callnode->vision,callnode->scope);
                                        if(n==-1){
                                                printf("ERROR! %s not found\n",callnode->name);
                                        }else if(n==-2){
                                                printf("ERROR! %s VAR-FUN CONFLICT\n",callnode->name);
                                        }else if(n==-3){
                                                printf("%d %s\n",callnode->line,callnode->type);
                                        }else if(n==-4){
                                                if(simple_block==0){
                                                        printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                                }
                                        }
                                }
                                // emit_elist_quads(&elist_list);
                                
                        }else{
                                from_member=0;
                        }
                }
        callsuffix {
                        if(from_member==0){
                                if(strcmp($1,"print")==0||strcmp($1,"input")==0||strcmp($1,"objectmemberkeys")==0||
                                        strcmp($1,"objecttotalmembers")==0||strcmp($1,"objectcopy")==0||strcmp($1,"totalarguments")==0||
                                        strcmp($1,"argument")==0||strcmp($1,"typeof")==0||strcmp($1,"strtonum")==0||
                                        strcmp($1,"sqrt")==0||strcmp($1,"cos")==0||strcmp($1,"sin")==0){
                                                temp_expr=(struct expr*) malloc(sizeof(struct expr));
                                                temp_expr->type=libraryfunc_e;
                                                temp_expr->sym=(struct hashnode*) malloc(sizeof(struct hashnode));
                                                temp_expr->sym->name=strdup($1);
                                }else{
                                        temp_expr=copy_expr(find_expr($1,"user function","-",scope_count));
                                }
                                temp_expr->strConst=NULL;
                                emit(call,NULL,NULL,copy_expr(temp_expr),-1,yylineno);
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type=var_e;
                                }else{
                                        temp_expr->type=var_e;
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        if(function_block!=0){
                                                temp_expr->sym->space=functionlocal;
                                                temp_expr->sym->offset=local_f->num;
                                                local_f->num++;
                                        }else{
                                                temp_expr->sym->space=programvar;
                                                temp_expr->sym->offset=programf;
                                                programf++;
                                        }
                                        fillExp(copy_expr(temp_expr));
                                }
                                emit(getretval,NULL,NULL,copy_expr(temp_expr),-1,yylineno);
                                $$=copy_expr(temp_expr);
                        }else{
                                from_member=0;
                        }
                        // printf("callsuffix-->call\n");
                }
        | L_PARENTH funcdef R_PARENTH L_PARENTH elist R_PARENTH {
                        // emit_elist_quads(&elist_list);
			emit(call,NULL,NULL,copy_expr($2),-1,yylineno);
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_expr->type=change_type($2);
                        }else{
                                temp_expr->type=change_type($2);
                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                if(function_block!=0){
                                        temp_expr->sym->space=functionlocal;
                                        temp_expr->sym->offset=local_f->num;
                                        local_f->num++;
                                }else{
                                        temp_expr->sym->space=programvar;
                                        temp_expr->sym->offset=programf;
                                        programf++;
                                }
                                fillExp(copy_expr(temp_expr));
                        }
                        emit(getretval,NULL,NULL,copy_expr(temp_expr),-1,yylineno);
                        $$=copy_expr(temp_expr);
                        // printf("(function definition)(elist)\n");
                }
        ;


callsuffix: normcall {
			// printf("normcall-->callsuffix\n");
                }
        |methodcall {
			dd=1;
                        // printf("methodcall-->callsuffix\n");
                }
        ;


normcall: L_PARENTH elist R_PARENTH {
			// printf("(elist)-->normcall\n");
                }
        ;

methodcall: D_DOT ID L_PARENTH elist R_PARENTH {
			// printf("..identifier(elist)-->methodcall\n");
                } //equivalent to lvalue.id(lvalue, elist) 
        ;

elist:  expr {
                        // printf("expression-->elist\n");
                        if(call_flag==1){
                                emit(param,NULL,NULL,copy_expr($1),-1,yylineno);
                                // fill_elist_quads(param,copy_expr($1),yylineno,&elist_list);
                        }else if(object_flag>=1){
                                struct expr* temp=tables_temp;
                                while(temp->next!=NULL){
                                        temp=temp->next;
                                }
                                temp_table=temp;
                                temp_table->intConst=0;
                                struct expr * t = (struct expr *) malloc (sizeof(struct expr));
                                //t=copy_expr($1);
                                t->sym=(struct hashnode *)malloc(sizeof(struct hashnode));
                                t->sym->name=(char*)malloc(sizeof(999999));
                                sprintf(t->sym->name,"%d",temp_table->intConst);
                                //itoa(temp_table->intConst,t->sym->name,10);
                                table_stack=creat_q(copy_expr(t),copy_expr($1));
                                table_stack->result=copy_expr(temp_table);
                                temp_table->index=NULL;
                                temp_table->index=add_e(copy_expr($1),temp_table->index);
                                emit(tablesetelem,table_stack->arg1,table_stack->arg2,table_stack->result,-1,yylineno);
                                temp_table->intConst++;
                        }
        		//printf("expression-->elist\n");
                }
        | elist COMA expr {
			// printf("elist,expression->elist\n");
                        if(call_flag==1){
                                emit(param,NULL,NULL,copy_expr($3),-1,yylineno);
                                // fill_elist_quads(param,copy_expr($3),yylineno,&elist_list);
                        }
                        else if(object_flag>=1){
                                struct expr* temp=tables_temp;
                                while(temp->next!=NULL){
                                        temp=temp->next;
                                }
                                temp_table=temp;
                                struct expr * t = (struct expr *) malloc (sizeof(struct expr));
                                t=copy_expr($3);
                                t->sym=(struct hashnode *)malloc(sizeof(struct hashnode));
                                t->sym->name=(char*)malloc(sizeof(999999));
                                if(function_block!=0){
                                        t->sym->space=functionlocal;
                                        t->sym->offset=local_f->num;
                                        local_f->num++;
                                }else{
                                        t->sym->space=programvar;
                                        t->sym->offset=programf;
                                        programf++;
                                }
                                sprintf(t->sym->name,"%d",temp_table->intConst);
                                //itoa(temp_table->intConst,t->sym->name,10);
                                table_stack=creat_q(copy_expr(t),copy_expr($3));
                                table_stack->result=copy_expr(temp_table);
                                temp_table->index=add_e(copy_expr($3),temp_table->index);
                                emit(tablesetelem,table_stack->arg1,table_stack->arg2,table_stack->result,-1,yylineno);
                                temp_table->intConst++;
                        }
                }
        |       {
                        // printf("empty elist-->elist\n");
                }
        ;


objectdef:  L_S_BRACKET {
                        object_flag++;
                        rf=1;
                        temp_name=var_name();
                        temp_table=(struct expr *)malloc(sizeof(struct expr));
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_table=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_table->strConst=NULL;
                                temp_table->next=NULL;
                                temp_table->type=newtable_e;
                        }else{
                                temp_table->type=newtable_e;
                                temp_table->sym = insert_node(scope_count,yylineno,"variable",strdup(temp_name),"-");
                                temp_table->strConst=NULL;
                                temp_table->next=NULL;
                                if(function_block!=0){
                                        temp_table->sym->space=functionlocal;
                                        temp_table->sym->offset=local_f->num;
                                        local_f->num++;
                                }else{
                                        temp_table->sym->space=programvar;
                                        temp_table->sym->offset=programf;
                                        programf++;
                                }
                                fillExp(copy_expr(temp_table));
                        }
                        tables_temp=add_e(temp_table,tables_temp);
                        temp_table->intConst=0;
                        temp_table->strConst=NULL;
                        emit(tablecreate,NULL,NULL,temp_table,-1,yylineno);
        }elist R_S_BRACKET {
                        $$=copy_expr(temp_table);
                        tables_temp=free_temp(tables_temp);
                }
                
        | L_S_BRACKET{
                        object_flag++;
                        rf=0;
                        temp_name=var_name();
                        temp_table=(struct expr *)malloc(sizeof(struct expr));
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_table=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_table->type=newtable_e;
                        }else{
                                temp_table->type=newtable_e;
                                temp_table->sym = insert_node(scope_count,yylineno,"variable",strdup(temp_name),"-");
                                if(function_block!=0){
                                        temp_table->sym->space=functionlocal;
                                        temp_table->sym->offset=local_f->num;
                                        local_f->num++;
                                }else{
                                        temp_table->sym->space=programvar;
                                        temp_table->sym->offset=programf;
                                        programf++;
                                }
                                fillExp(copy_expr(temp_table));
                        }
                        tables_temp=add_e(temp_table,tables_temp);
                        temp_table->intConst=0;
                        emit(tablecreate,NULL,NULL,temp_table,-1,yylineno);
        } indexed R_S_BRACKET {
                        $$=copy_expr(temp_table);
                        tables_temp=free_temp(tables_temp);
                                
                }
        ;


indexed:  indexedelem {
			// printf("indexedelem-->indexed\n");
                }
        | indexed COMA indexedelem {
			// printf("indexed,indexedelem->indexed\n");
                } 
        ;


indexedelem:  L_C_BRACKET expr COLON expr R_C_BRACKET {
                        rf=1;
                        struct expr* temp=tables_temp;
                        while(temp->next!=NULL){
                                temp=temp->next;
                        }
                        temp_table=temp;
                        if($2->type==constint_e){
                                $2->sym=(struct hashnode *)malloc(sizeof(struct hashnode));
                                $2->sym->name=(char*)malloc(sizeof(999999));
                                sprintf($2->sym->name,"%d",temp_table->intConst);
                                //itoa($2->intConst,$2->sym->name,10);
                        }else if($2->type==conststring_e){
                                $2->sym=(struct hashnode *)malloc(sizeof(struct hashnode));
                                $2->sym->name=strdup($2->strConst);
                        }else if($2->type<8){
        
                        }
                        
                        $2->type=$4->type;
                        $2->intConst=$4->intConst;
                        $2->floatConst=$4->floatConst;
                        $2->boolConst=$4->boolConst;
                        if($4->strConst) $2->strConst=strdup($4->strConst);
                        else $2->strConst=NULL;
                        table_stack=creat_q(copy_expr($2),copy_expr($4));
                        table_stack->result=copy_expr(temp_table);
                        temp_table->index=add_e(copy_expr($4),temp_table->index);
                        emit(tablesetelem,table_stack->arg1,table_stack->arg2,table_stack->result,-1,yylineno);
                      
                        // printf("{expression:expression}\n");
                };


block:  L_C_BRACKET 
                 {       
                        if(if_block==0 && while_block==0 && for_block==0){
                                scope_count++;

                                // printf("INCREASE SCOPE %d %d\n",scope_count,yylineno);
                        }
                }
        insideblock R_C_BRACKET 
                {       
			if(if_block==0 && while_block==0 && for_block==0){
                                hide(scope_count);
                                scope_count--;
                                // printf("DECREASE SCOPE %d %d\n",scope_count,yylineno);
                        }
                        if(function_block!=scope_count){
                                simple_block=1;
                        }else{
                                simple_block=0;
                        }
                        // printf("{insideblock}-->block %d\n",yylineno);
                }
        ;


insideblock: insideblock stmt {
			// printf("stmt stmt ....-->insideblock\n");
                }
        |       {
                        // printf("empty insideblock-->insideblock\n");
                }
        ;


funcdef:  FUNCTION ID 
                {
                        simple_block=0;
                        function_block++;
                        push_bcr_stack(&return_jump_list);
                        terms->name=strdup($2);
                        terms->type="user function";
                        terms->vision="-";
                        terms->line=yylineno;
                        terms->scope=scope_count;
                        n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                        if(n==-1||(n>=0 && n!=terms->scope)){
                                temp_expr=(struct expr*) malloc(sizeof(struct expr));
                                temp_expr->type=programfunc_e;
                                temp_expr->sym=insert_node(terms->scope,terms->line,terms->type,terms->name,terms->vision);
                                temp_expr->strConst=NULL;
                                fillExp(copy_expr(temp_expr));
                                function_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                                push_jump_stack(function_jump,&function_jump_list);
                                fun_name_quad = emit(funcstart,NULL,NULL,copy_expr(temp_expr),-1,yylineno);
                                push_jump_stack(fun_name_quad,&fun_name_quad_list);
                        }else if(n==terms->scope){
                                printf("ERROR! Function definition conflict of %s in same scope in line %d\n",terms->name,terms->line);
                        }else if(n==-2){
                                printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                        }else if(n==-3){
                                printf("ERROR CONFLICT FUN-LIBFUN IN LINE: %d\n",terms->line);
                        }
                        formalf=0;
                        //IF NOT FOUND INSERT
			// printf("function identifier (idlist){stmts}-->funcdef\n");
                }
        L_PARENTH idlist R_PARENTH {
                        push_local(0,&local_f);
                        push_local(formalf,&formal_f);
                        printf("%d:%d\n",formalf,formal_f->num);
                }
                block {
                        function_block--;
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=programfunc_e;
                        temp_expr->sym=pop_jump_stack(&fun_name_quad_list)->result->sym;
                        temp_expr->strConst=NULL;
                        temp_expr->sym->formal_num=formal_f->num;
                        printf("%s %d:%d\n",$2, formalf,formal_f->num);
                        pop_local(&formal_f);
                        temp_expr->sym->local_num=local_f->num;
                        pop_local(&local_f);
                        if(function_block==0){
                                temp_expr->sym->space=programvar;
                                temp_expr->sym->offset=programf;
                                programf++;
                        }else{
                                temp_expr->sym->space=functionlocal;
                                temp_expr->sym->offset=local_f->num;
                                local_f->num++;
                        }
                        pop_jump_stack(&function_jump_list)->label=quad_count+1;
                        if(return_jump_list!=NULL){
                                tmp_ret_stack = pop_bcr_stack(&return_jump_list);
                                while(tmp_ret_stack->head!=NULL){
                                        tmp_ret_stack->head->jump->label=quad_count;
                                        tmp_ret_stack->head = tmp_ret_stack->head->next;
                                }
                        } 
                        emit(funcend,NULL,NULL,copy_expr(temp_expr),-1,yylineno);
                        $$=copy_expr(temp_expr);
			// printf("function identifier (idlist){stmts}-->funcdef\n");
                }
        | FUNCTION L_PARENTH 
                {
                        function_block++;
                        push_bcr_stack(&return_jump_list);
                        char tmp[15];
                        sprintf(tmp,"@%d",fun_name_num);
                        terms->name=strdup(tmp);
                        terms->type="user function";
                        terms->vision="-";
                        terms->line=yylineno;
                        terms->scope=scope_count; 
                        fun_name_num++;
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=programfunc_e;
                        temp_expr->sym=insert_node(terms->scope,terms->line,terms->type,terms->name,terms->vision);
                        temp_expr->strConst=NULL;
                        fillExp(copy_expr(temp_expr));
                        function_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                        push_jump_stack(function_jump,&function_jump_list);
                        fun_name_quad = emit(funcstart,NULL,NULL,copy_expr(temp_expr),-1,yylineno);
                        push_jump_stack(fun_name_quad,&fun_name_quad_list);
                        formalf=0;
                        //INSERT
			// printf("function (idlist){stmts}-->funcdef\n");
                }
        idlist R_PARENTH {
                        push_local(0,&local_f);
                        push_local(formalf,&formal_f);
                }
                block {
                        function_block--;
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=programfunc_e;
                        temp_expr->sym=pop_jump_stack(&fun_name_quad_list)->result->sym;
                        temp_expr->strConst=NULL;
                        temp_expr->sym->formal_num=formal_f->num;
                        pop_local(&formal_f);
                        temp_expr->sym->local_num=local_f->num;
                        pop_local(&local_f);
                        if(function_block==0){
                                temp_expr->sym->space=programvar;
                                temp_expr->sym->offset=programf;
                                programf++;
                        }else{
                                temp_expr->sym->space=functionlocal;
                                temp_expr->sym->offset=local_f->num;
                                local_f->num++;
                        }
                        pop_jump_stack(&function_jump_list)->label=quad_count+1;
                        if(return_jump_list!=NULL){
                                tmp_ret_stack = pop_bcr_stack(&return_jump_list);
                                while(tmp_ret_stack->head!=NULL){
                                        tmp_ret_stack->head->jump->label=quad_count;
                                        tmp_ret_stack->head = tmp_ret_stack->head->next;
                                }
                        } 
                        emit(funcend,NULL,NULL,copy_expr(temp_expr),-1,yylineno);
                        $$=copy_expr(temp_expr);
			// printf("function (idlist){stmts}-->funcdef\n");
                };


const:  INTCONST {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=constint_e;
                        temp_expr->intConst=(float) $1;
                        temp_expr->strConst=NULL;
                        temp_expr->sym=NULL;
                        $$=copy_expr(temp_expr);
                        // printf("integer-->const\n");
                }
        | RCONST {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=constfloat_e;
                        temp_expr->floatConst=$1;
                        temp_expr->strConst=NULL;
                        temp_expr->sym=NULL;
                        $$=copy_expr(temp_expr);
			// printf("float-->const\n");
                }
        | STRING {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=conststring_e;
                        temp_expr->strConst=strdup($1);
                        temp_expr->sym=NULL;
                        $$=copy_expr(temp_expr);
			// printf("string-->const\n");
                }
        | NIL {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=nil_e;
                        temp_expr->strConst="nil";
                        temp_expr->sym=NULL;
                        $$=copy_expr(temp_expr);
			// printf("nill-->const\n");
                }
        | TRUE {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=constbool_e;
                        temp_expr->boolConst=1;
                        temp_expr->strConst=NULL;
                        temp_expr->sym=NULL;
                        $$=copy_expr(temp_expr);
			// printf("true-->const\n");
                }
        | FALSE {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=constbool_e;
                        temp_expr->boolConst=0;
                        temp_expr->strConst=NULL;
                        temp_expr->sym=NULL;
                        $$=copy_expr(temp_expr);
			// printf("false-->const\n");
                };


idlist:  ID {           

                        formalf=0;
                        terms->name=strdup($1);
                        terms->type="variable";
                        terms->vision= "formal";
                        terms->scope=scope_count+1; 
                        terms->line=yylineno;
                        n = testarg(terms->name, terms->type, terms->vision,  terms->scope);
                        if(n==1){
                                temp_expr=(struct expr*) malloc(sizeof(struct expr));
                                temp_expr->type=var_e;
                                temp_expr->sym=insert_node(terms->scope,terms->line,terms->type,terms->name,terms->vision);
                                temp_expr->strConst=NULL;
                                temp_expr->sym->space= formalarg;
                                temp_expr->sym->offset= formalf;
                                formalf++;
                                fillExp(copy_expr(temp_expr));
                        }else{
                                printf("ERROR! Conflict in formal argument %s in line %d\n",terms->name,terms->line);
                        }
                        // lookup typika orismata sto scope_count+1
			//insert an den yparxei allios error
                        // printf("identifier for idlist-->idlist\n");
                }
        | idlist COMA ID  {
                        terms->name=strdup($3);
                        terms->type="variable";
                        terms->vision= "formal";
                        terms->scope=scope_count+1; 
                        terms->line=yylineno;
                        n = testarg(terms->name, terms->type, terms->vision,  terms->scope);
                        if(n==1){
                             temp_expr=(struct expr*) malloc(sizeof(struct expr));
                                temp_expr->type=var_e;
                                temp_expr->sym=insert_node(terms->scope,terms->line,terms->type,terms->name,terms->vision);
                                temp_expr->strConst=NULL;
                                temp_expr->sym->space= formalarg;
                                temp_expr->sym->offset= formalf;
                                formalf++;
                                fillExp(copy_expr(temp_expr));
                        }else{
                                printf("ERROR! Conflict in formal argument %s in line %d\n",terms->name,terms->line);
                        }
			// printf("idenitfier,identifier-->idlist\n");
                }
        | {
                        formalf=0;
                        // printf("empty idlist-->idlist\n");
                }
        ;


ifstmt:  IF 
                {
                        if_block++; 
                }
        L_PARENTH expr R_PARENTH {
                        // printf("%s\n",$3);
                        emit(if_eq,$4,true_expr,NULL,quad_count+2,yylineno);
                        if_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                        push_jump_stack(if_jump,&if_jump_list);
                }
        stmt         
                {
			// printf("if(expression) stmt-->ifstmt\n");
                        if_block--;
                        if_else=pop_jump_stack(&if_jump_list);
                        if_else->label=quad_count;
                }
        |ifstmt 
        ELSE 
                {
                        if_block++;
                        if(if_else!=NULL) if_else->label=quad_count+1;
                        else_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                        push_jump_stack(else_jump,&else_jump_list);
                }
        stmt 
                {
			if_block--;
                        pop_jump_stack(&else_jump_list)->label=quad_count;
                        // printf("if(expression) stmt else stmt-->ifstmt\n");
                }; 


whilestmt:  WHILE {
                        while_block++;
                        push(quad_count,&loop_jump_list);
                        push_bcr_stack(&break_jump_list);
                } 
        L_PARENTH expr R_PARENTH {
                        emit(if_eq,$4,true_expr,NULL,quad_count+2,yylineno);
                        while_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                        push_jump_stack(while_jump,&while_jump_list);
                }
        stmt {
                        while_block--;
                        pop_jump_stack(&while_jump_list)->label=quad_count+1;
                        if(break_jump_list!=NULL){
                                tmp_bcr_stack = pop_bcr_stack(&break_jump_list);
                                while(tmp_bcr_stack->head!=NULL){
                                        tmp_bcr_stack->head->jump->label=quad_count+1;
                                        tmp_bcr_stack->head = tmp_bcr_stack->head->next;
                                }
                        } 
                        //pop_jump_stack(&break_jump_list)->label=quad_count+1;
                        emit(jump,NULL,NULL,NULL,pop(&loop_jump_list),yylineno);
			// printf("while(expression) stmt-->whilestmt\n");
                };


forstmt:  FOR 
                {
                        for_block++;
                } 
        L_PARENTH elist SEMICOLON {
                        push(quad_count,&loop_jump_list);
                        push_bcr_stack(&break_jump_list);
                }
        expr    {
                        for_jump=emit(if_eq,$7,true_expr,NULL,quad_count+2,yylineno);
                        push_jump_stack(for_jump,&for_true_jump_list);
                        for_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                        push_jump_stack(for_jump,&for_false_jump_list);
                }
        SEMICOLON {
                push(quad_count,&increment_jump_list);
        }
        elist R_PARENTH {
                        pop_jump_stack(&for_true_jump_list)->label=quad_count+1;
                        emit(jump,NULL,NULL,NULL,pop(&loop_jump_list),yylineno);
                } 
        stmt {
                        for_block--;
                        pop_jump_stack(&for_false_jump_list)->label=quad_count+1;
                        // EDWW
                        if(break_jump_list!=NULL){
                                tmp_bcr_stack = pop_bcr_stack(&break_jump_list);
                                while(tmp_bcr_stack->head!=NULL){
                                        tmp_bcr_stack->head->jump->label=quad_count+1;
                                        tmp_bcr_stack->head = tmp_bcr_stack->head->next;
                                }
                        } 
                        emit(jump,NULL,NULL,NULL,pop(&increment_jump_list),yylineno);
			// printf("for(elist;expression;elist) stmt-->forstmt\n");
                }
        ;

returnstmt: RETURN {
                        if(function_block>=1){
                                emit(ret,NULL,NULL,NULL,-1,yylineno);
                                return_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                                //EDWWWW
                                push_jump_stack(return_jump,&(return_jump_list->head));
                        }
                        // printf("return-->returnstmt\n");
                }
        | RETURN expr {
                        if(function_block>=1){
                                emit(ret,NULL,NULL,copy_expr($2),-1,yylineno);
                                return_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                                // EDWWW
                                // if(return_jump_list->head==NULL){
                                //         return_jump_list->head = (struct jump_stack*) malloc(sizeof(struct jump_stack));
                                //         return_jump_list->head->next=NULL;
                                // } 
                                push_jump_stack(return_jump,&(return_jump_list->head));
                        }
                        // printf("return expression-->returnstmt\n");
                };


%%
int yyerror (char * YaccProvidedMessage)
{	
	if ((strstr(YaccProvidedMessage,"$end")))
		printf("Unexpected reach of the EOF.\n");
	else
		printf("%s -- in line %d\n ",YaccProvidedMessage,yylineno);
	return 0;
}

//---------------------------------------------------------------------------------------------------------
int main(int argc , char** argv){
        ylval = (struct alpha_token_t*) malloc(sizeof(struct alpha_token_t)); 
        terms=(struct hashnode*) malloc(sizeof(struct hashnode));
        true_expr= (struct expr*) malloc(sizeof(struct expr));
        true_expr->type=constbool_e;
        true_expr->sym=NULL;
        true_expr->strConst=NULL;
        true_expr->boolConst=1;
        false_expr= (struct expr*) malloc(sizeof(struct expr));
        false_expr->type=constbool_e;
        false_expr->sym=NULL;
        false_expr->strConst=NULL;
        false_expr->boolConst=0;
        one_expr= (struct expr*) malloc(sizeof(struct expr));
        one_expr->type=constint_e;
        one_expr->sym=NULL;
        one_expr->strConst=NULL;
        one_expr->intConst=1;
        callnode=(struct hashnode*) malloc(sizeof(struct hashnode));
        tabmem = (struct expr*) malloc(sizeof(struct expr));
        tabnode = (struct expr*) malloc(sizeof(struct expr));
        tmp_e = (struct expr*) malloc(sizeof(struct expr));
        tabmem = NULL;
        if (argc > 1){
                if (!(yyin = fopen(argv[1],"r"))){
                        fprintf(stderr,"Cannot read file: %s\n",argv[1]);
                        return 1 ; 
                }
        }else {
                yyin = stdin ;
        }
        // FILE* quadfile;
	// if(!(quadfile=fopen("quads.txt","w"))){
	// 	quadfile=stdout;
	// }
        init();
        yyparse();
        print_elements();
	printf("----------------------------------------END------------------------------------------\n");
        print_quads();
        printf("end quads\n");
        gen();
        // print_in();
        //print_expr();
        // printf("%d\n",programf);
        create_bin(programf);
        read_binfile();
        fclose(yyin);
        return 0 ;
}

