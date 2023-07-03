
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "a.h"
#include "syntax_anal.tab.h"

extern struct alpha_token_t* ylval; 
int number=0;
struct alpha_token_t* token_list;
int  token_fill(struct alpha_token_t* ylval){
    struct alpha_token_t * temp_token_list= (struct alpha_token_t*) malloc(sizeof(struct alpha_token_t));

    temp_token_list->line=ylval->line;
    temp_token_list->num=ylval->num;
    temp_token_list->line=ylval->line;
    temp_token_list->num=ylval->num;
    temp_token_list->categ=strdup(ylval->categ);
    temp_token_list->id=strdup(ylval->id);
    temp_token_list->quote=strdup(ylval->quote);
    temp_token_list->type=strdup(ylval->type);
    temp_token_list->next = NULL;

    if(token_list==NULL){
        token_list = temp_token_list;
    }else{

        struct alpha_token_t* tmp = token_list;

        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=temp_token_list;

    }
    return 0;

}

%}
multi_comm 	"/*"
assign      "="
plus        "+"
minus       "-"
divide      "/"
multiply    "*"
module      "%"
equal       "=="
notequal    "!="
increase    "++"
decrease    "--"
greater     ">"
less        "<" 
great_equal ">="
less_equal  "<="
if_key      "if" 
else_key    "else" 
while_key   "while" 
for_key     "for" 
funct_key   "function" 
return_key  "return" 
break_key   "break" 
cont_key    "continue"
and_key     "and" 
not_key     "not" 
or_key      "or" 
local_key   "local" 
true_key    "true" 
false_key   "false" 
nil_key     "nil"
l_c_brack   "{" 
r_c_brack   "}"
l_s_brack   "[" 
r_s_brack   "]" 
l_parenth   "(" 
r_parenth   ")" 
semicol     ";" 
coma        "," 
colon       ":" 
d_colon     "::" 
dot         "." 
d_dot       ".."
id          [a-zA-Z][a-zA-Z_0-9]*
integer     [0-9]+
real        [0-9]+\.[0-9]+
string      \"((\\\")|[^\"])*\"
sl_comm 	"//"[^\n]*
other		\"|_|$|#|@|!|^|&
%option noyywrap yylineno

%%
"//"            {}
\n              { }
{multi_comm} 	{   
                    char c ;
                    char * categ = "COMMENT";
                    char * nest = "NESTED_COMMENT";
                    char * block = "BLOCK_COMMENT";
                    int line = yylineno;                            
                    int flag = 1;
                    int off = 0;
                    int prev_line=yylineno;
                    int * start = (int *)malloc(sizeof(int));
                    *(start + off)=line;
                    while(flag !=0){
                        c = input();
                        if(c==EOF){
                            printf("Error: Not closed comment in line %d\n", prev_line);
                          exit(0);  
                        }


                        if(c=='\n'){
                            line++;
                        }


                        if(c=='/'){
                            c=input();
                            if(c==EOF){
                                printf("Error: Not closed comment in line %d\n", prev_line);
                              exit(0);  
                            }    
                            if(c=='*'){
                                off++;
                                flag++;
                                start = (int *)realloc(start,sizeof(int) * (off + 1));
                                *(start+off)=line; 
                            }else {
                                unput(c);
                            }
                        }

                        if(c=='*'){
                            c=input();
                            if(c==EOF){
                                printf("Error: Not closed comment in line %d\n", prev_line);
                              exit(0);  
                            }    
                            if(c=='/'){
                                flag--;
                                number++;
                                ylval-> num = number;
                                ylval-> line = *(start + off);
                                int l1 = floor(log10(abs(*(start + off)))) + 1;
                                int l2 = floor(log10(abs(line))) + 1;
                                ylval-> quote = (char *)malloc(l1+l2+1);
                                sprintf(ylval-> quote, "%d-%d", *(start + off),line);
                                if(flag!=0){
                                    ylval->id=strdup(nest);
                                }else{
                                    ylval->id=strdup(block);
                                }
                                ylval->type = "<-enumerated";
                                ylval->categ = strdup(categ);
		                        token_fill (ylval);
                                off--;
                            }else {
                                unput(c);
                            }
                        }
                    }
                    free(start);

                }


{integer}       { 
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval-> id =strdup(yytext);
                    ylval->quote=strdup(yytext);
                    ylval->type = "<-integer";
                    ylval->categ = "INTCONST";
		            token_fill (ylval);
                    yylval.intValue = atoi(yytext);
                    return INTCONST;
                }
                    
{real}          {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval-> id =strdup(yytext);
                    ylval->quote=strdup(yytext);
                    ylval->type = "<-real";
                    ylval->categ = "REAL";
		            token_fill (ylval);
                    yylval.realValue = atof(yytext);
                    return RCONST;                
                }
{assign}        {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval-> id ="ASSIGN";
                    ylval->quote=strdup(yytext);
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return ASSIGN;
                  }

{plus}          {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="PLUS";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return PLUS;
                }

{minus}         {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="MINUS";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return MINUS;
                  }

{multiply}      {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext); 
                    ylval-> id ="MULTIPLY";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return MULTIPLY;
                }

{divide}        {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="DIVIDE";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return DIVIDE;
                }

{module}        {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="MODULE";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return MODULE;
                }

{equal}         {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="EQUAL";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return EQUAL;
                }

{notequal}      {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="NOT_EQUAL";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return NOTEQUAL;
                }

{increase}      {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="PLUS_PLUS";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return INCREASE;
                }

{decrease}      {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="MINUS_MINUS";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return DECREASE;
                }


{greater}       {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="GREATER";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return GREATER;
                }

{less}          {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="LESS";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return LESS;
                }

{great_equal}   {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="GREAT_EQUAL";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return GREAT_EQUAL;
                }

{less_equal}    {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="LESS_EQUAL";
                    ylval->type = "<-enumerated";
                    ylval->categ = "OPERATOR";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return LESS_EQUAL;
                }
                  
{if_key}        {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="IF";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return IF;
                }
{else_key}      {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="ELSE";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return ELSE;
                    }
{while_key}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="WHILE";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return WHILE;
                }
{for_key}       {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="FOR";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return FOR;
                }
{funct_key}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="FUNCTION";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return FUNCTION;
                }
{return_key}    {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="RETURN";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return RETURN;
                }
{break_key}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="BREAK";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return BREAK;
                }
{cont_key}      {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="IF";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return CONT;
                }
{and_key}       {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="AND";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return AND;
                }
{not_key}       {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="NOT";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return NOT;
                }
{or_key}        {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="OR";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return OR;
                }
{local_key}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="LOCAL";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return LOCAL;
                } 
{true_key}      {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="TRUE";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return TRUE;
                }
{false_key}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="FALSE";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return FALSE;
                } 
{nil_key}       {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="NIL";
                    ylval->type = "<-enumerated";
                    ylval->categ = "KEYWORD";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return NIL;
                }
{l_c_brack}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="LEFT_BRACE";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return L_C_BRACKET;
                }
{r_c_brack}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="RIGHT_BRACE";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return R_C_BRACKET;
                }
{l_s_brack}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="LEFT_BRACKET";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return L_S_BRACKET;
                }
{r_s_brack}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="RIGHT_BRACKET";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return R_S_BRACKET;
                } 
{l_parenth}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="LEFT_PARENTHESIS";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return L_PARENTH;
                } 
{r_parenth}     {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="RIGHT_PARENTHESIS";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return R_PARENTH;
                }
{semicol}       {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="SEMICOLON";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return SEMICOLON;
                }
{coma}          {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="COMA";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return COMA;
                }
{colon}         {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="COLON";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return COLON;
                } 
{d_colon}       {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="DOUBLE_COLON";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return D_COLON;
                } 
{dot}           {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="DOT";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return DOT;
                }
{d_dot}         {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id ="DOUBLE_DOT";
                    ylval->type = "<-enumerated";
                    ylval->categ = "PUNCTUATION";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return D_DOT;
                }

{id}            {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    ylval->quote=strdup(yytext);
                    ylval-> id =strdup(yytext);
                    ylval->type = "<-char *";
                    ylval->categ = "ID";
		            token_fill (ylval);
                    yylval.stringValue = strdup(yytext);
                    return ID;
                }

{string}        {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    char * q = strdup(yytext);
                    char * q1 =(char *) malloc(strlen(q)+1);
                    int i=0;
                    int j=0;
                    while(*(q+i) != '\0'){
                        if(*(q+i)=='\\'){
                            i++;
                            if(*(q+i)=='n'){
                                *(q1+j)='\n';
                            }else if(*(q+i)=='t'){
                                *(q1+j)='\t';
                            }else if(*(q+i)=='\\'){
                                *(q1+j)='\\';
                            }else if(*(q+i)=='a'){
                                *(q1+j)='\a';
                            }else if(*(q+i)=='b'){
                                *(q1+j)='\b';
                            }else if(*(q+i)=='e'){
                                *(q1+j)='\e';
                            }else if(*(q+i)=='f'){
                                *(q1+j)='\f';
                            }else if(*(q+i)=='r'){
                                *(q1+j)='\r';
                            }else if(*(q+i)=='v'){
                                *(q1+j)='\v';
                            }else if(*(q+i)=='\''){
                                *(q1+j)='\'';
                            }else if(*(q+i)=='\"'){
                                if(*(q+i+1)!='\0'){
                                    *(q1+j)='\"';
                                }else{
                                    printf("Invalid string in line %d\n",yylineno);
                                    exit(0);
                                }
                            }else if(*(q+i)=='\?'){
                                *(q1+j)='\?';
                            }else{
                                printf("Error: Not valid escape character in line %d\n", yylineno);
                                exit(1);
                            }
                        }else{
                            *(q1+j)=*(q+i);
                        }
                        i++;
                        j++;
                    }
                    *(q1+j)='\0';
                    ylval->quote=strdup(q1);
                    ylval->categ = "STRING";
                    ylval-> id =strdup(yytext);
                    ylval->type = "<-char *";
		            token_fill (ylval);
                    yylval.stringValue = strdup(q1);
                    free(q1);
                    return STRING;
                }

{sl_comm}       {
                    number++;
                    ylval-> num = number;
                    ylval-> line = yylineno;
                    char * q = (char *) malloc  (strlen (yytext)-2);	
                    int i , j=2;
                    for(i=0;i<(strlen (yytext)-3);i++){
                        *(q+i)=*(yytext+j);
                        j++;
                    }
                    *(q+i)='\0';
                    ylval->quote=strdup(q);
                    ylval-> id ="LINE_COMMENT";
                    ylval->type = "<-enumerated";
                    ylval->categ = "COMMENT";
		            token_fill (ylval);
                }
{other}		{printf("Invalid token in line %d\n",yylineno);exit(0);}
%%

// int main(int argc , char** argv){
//         if (argc > 1){
//                 if (!(yyin = fopen(argv[1],"r"))){
//                         fprintf(stderr,"Cannot read file: %s\n",argv[1]);
//                         return 1 ; 
//                 }
//         }else {
//                 yyin = stdin ;
//         }

//         yylex();
//         fclose(yyin);
//         return 0 ;
// }
