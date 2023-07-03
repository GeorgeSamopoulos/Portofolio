#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a.h"
#include "syntax_functions.h"
#include "intermediate.h"


//---------------------------------------------------------------------------------------------------------
int testarg(char* name , char* type , char* vision ,  int scope ){
    
    if(strcmp(vision,"formal")!=0){
        return 0;
    }
    
    struct scopenode * t = scopelist;
    struct hashnode *nodes = NULL ; 
    if(t==NULL){
        return 1;
    }
    // check for library functions collision 
    nodes = t->head ;
    while ( nodes != NULL ){
            if ( (strcmp(nodes->type, "library function") == 0 )&& (strcmp(nodes->name , name) == 0 ) ){
                //     printf("ERROR - LIBRARY FUNCTION'S NAME COLLISION WITH FORMAL VARIABLE'S NAME.\n");
                    return 0 ;
            }else {
                    nodes = nodes->snext ;
            }
    }
    while(t->scope!=scope){
        t=t->next;
        if(t==NULL){
            return 1;
        }
    }
    struct hashnode * st = t->head;
    
    
    while(st!=NULL){
        if((strcmp(name,st->name)==0)&&(st->active==1)){
            return 0;
        }
        st=st->snext;
    }
    return 1;
}
struct hashnode *search0( char* name){
    struct scopenode *scli ;
    struct hashnode* specificsc ;
    scli = scopelist ;
    if ( scli != NULL ){
        specificsc = scli->head ;
        while ( specificsc != NULL ){
            if ( strcmp(specificsc->name , name) == 0 && specificsc->active == 1){
                
                return specificsc ;
            }else {
                specificsc = specificsc->snext ;
            }
        }
    }
    return NULL ; //den brethike kati se global scope
}
//---------------------------------------------------------------------------------------------------------

struct hashnode *betfun(char* name ,  int scope){
    struct scopenode *scli ;
    struct hashnode* specificsc ;
    int i ;
    if ( scope != 0 ){
        scli = scopelist->next ;
        for ( i = 1 ; i < scope ; i++){
            if ( scli != NULL ){
                specificsc = scli->head ;
                while( specificsc != NULL){
                    if ( strcmp(specificsc->name , name) == 0 && (strcmp(specificsc->type , "user function") == 0 ||strcmp(specificsc->type , "library function") == 0)&& specificsc->active == 1){//check if userfunc or libfunc
                        //printf("CONFLICT VARIABLE-FUNCTION.\n");
                        return specificsc;
                    }else{
                    specificsc = specificsc->snext ;
                    }
                }
            }else{
                //printf("Error in case3 in LookUp\n");
                return NULL ; //error mporei na to bgaloume
            }
            scli=scli->next;
        }
    }
    return NULL ;
}
//---------------------------------------------------------------------------------------------------------
struct hashnode* betvar(char * name , int scope){
       struct scopenode * scli = scopelist;
       int flag = 1;
       int i;
       do{
               scli=scopelist;
               for(i=0;i<(scope-flag);i++){
                       scli=scli->next;
               }
               if(scli!=NULL && scli->scope!=0){
                       struct hashnode * node = scli->head;
                        while(node!=NULL){
                               if((strcmp(node->type , "variable")==0) && (strcmp(node->name,name)==0) && (node->active = 1)){
                                       return node;
                               }
                               node=node->snext;
                        }
               }
               flag++;
       }while(scope-flag>0);

        return NULL;

}
//---------------------------------------------------------------------------------------------------------
struct hashnode* samescope(char* name ,  int scope){
    struct scopenode *scli ;
    struct hashnode *specificsc ;
    int i ;
    scli=scopelist;
    if ( scli != NULL){
        scli = scli->next ; // prwth periptwsh den tsekarei to global scope .
        for ( i = 0 ; i < scope-1 ; i++){
            
            if ( scli != NULL){
                scli = scli->next ;
            }else{
                //printf("Error in case1-2 in LookUp\n");// if scope list is null in scope i , print error message .
                return NULL ; //error
            }
            
        }
        if ( scli != NULL ){
            specificsc = scli->head ;
            
            while( specificsc != NULL){//checking all the variables - functions in the same scope
                    if ( strcmp(specificsc->name , name) == 0 && specificsc->active == 1){
                        return specificsc;
                    }else{
                        specificsc = specificsc->snext ;
                    }
            }
           
        }
    }else {
        return NULL ;
    }
    return NULL;
}
//---------------------------------------------------------------------------------------------------------   

int LookUp( char* name , char* type , char* vision ,  int scope ){

    if (strcmp(vision,"::") == 0 ){
        struct hashnode* node0 = search0(name) ;
        if ( node0 != NULL ){
            if ( strcmp(type, "variable") == 0){
                if ( strcmp(node0->type , "user function") == 0 ||strcmp(node0->type , "library function") == 0 ){
                //     printf(" ERROR CONFLICT VAR-FUN IN SCOPE: %d\n" , node0->line);
                    return FUNVARCONF ;
                }
                return node0->scope;
            }else{
                if ( strcmp(node0->type , "variable") == 0){
                //     printf(" ERROR CONFLICT VAR-FUN IN SCOPE: %d\n" , node0->line);
                    return FUNVARCONF ;
                }
                return node0->scope;
            }
        }else{
            return NOTFOUND ;
        }
    }else if ( strcmp(vision,"local") == 0 ){
        struct hashnode *node0 = search0(name);
        if ( node0 != NULL){
            if ( strcmp(node0->type , "library function") == 0 ){
                // printf(" ERROR CONFLICT LIB-LOCAL VAR IN LINE: %d\n" , yylineno);
                return FUNVARCONF ;
            }
        }
        struct hashnode* nodeloc = samescope(name , scope);
        if ( nodeloc != NULL){
            if ( strcmp(nodeloc->type , "user function") == 0 ){//we have functiopn with same name before in the same scope
                // printf(" ERROR CONFLICT VAR-FUN IN SCOPE: %d\n" , nodeloc->line);
                return FUNVARCONF ;
            }else{
                return nodeloc->scope ;
            }
        }else{
            return NOTFOUND ;
        }
    }else if (strcmp (type , "variable") == 0 ) {
        struct hashnode* nodesame = samescope(name , scope);
        if ( nodesame != NULL ){
            return nodesame->scope ;
        }
        struct hashnode* nodebet = betvar(name , scope);
        if ( nodebet != NULL ){
            if ( strcmp(nodebet->type , "user function") == 0 ){
                // printf(" ERROR CONFLICT VAR-FUN IN SCOPE: %d\n" , nodebet->line);
                return FUNVARCONF ;
            }else if ( strcmp(nodebet->type , "variable") == 0 ){
                // printf(" ERROR CONFLICT VAR IN UPPER SCOPE: %d %d\n" , nodebet->line, yylineno);
                return UPPERSCOPEVAR;
            }
        }
        struct hashnode* node0 = search0(name);
        if ( node0 != NULL){
            if ( strcmp(node0->type , "user function") == 0 ||strcmp(node0->type , "library function") == 0 ){
                // printf(" 1.ERROR CONFLICT VAR-FUN IN SCOPE: %d\n" , node0->line);
                return FUNVARCONF ;
            }else{
                return node0->scope;
            }
        }
    }else if ( strcmp(type , "user function") == 0){
        struct hashnode* nodeloc = samescope(name , scope) ;
        if ( nodeloc != NULL ){
            if ( strcmp(nodeloc->type , "variable") == 0 ){
                if(nodeloc->space==formalarg){
                    return nodeloc->scope ;
                }
                // printf(" 2.ERROR CONFLICT VAR-FUN IN SCOPE: %d\n" , nodeloc->line);
                return FUNVARCONF ;
            }

            return nodeloc->scope ;
        }
        struct hashnode *nodebet = betfun(name , scope) ;
        if (nodebet != NULL ){

            return nodebet->scope ; //found
        }
        struct hashnode *node0 = search0(name);
        if ( node0 != NULL){
            if ( strcmp(node0->type , "variable") == 0 ){
                // printf("3. ERROR CONFLICT VAR-FUN IN SCOPE: %d\n" , node0->line);
                return FUNVARCONF ;
            }
            if ( strcmp(node0->type , "library function") == 0 ){
                // printf(" ERROR CONFLICT LIB-USER FUNC IN SCOPE: %d\n" , node0->line);
                return LIBRFOUND ;
            }
            return node0->scope ;
        }
    }
    if(strcmp(type,"library function")==0){
            return 0;
    }
    return NOTFOUND ;
}
//---------------------------------------------------------------------------------------------------------

void hide(int curr_scope){
    struct scopenode *last = scopelist ;
    struct hashnode *sc ;
    if ( last != NULL){
        while (last->scope!=curr_scope){//search for last scope node with pointer to list 
            last = last->next ;
            if(last==NULL){
                    break;
            }
        }
        if(last==NULL){
                return;
        }
        sc = last->head ;
        while ( sc != NULL ){
            sc->active = 0 ;
            sc = sc->snext ;
        }
    }else{
        printf("Error in Hide.\n");
    }
}
//---------------------------------------------------------------------------------------------------------

void print_elements(){
	
	struct scopenode * s = scopelist;
	while(s!=NULL){
		printf("----------------------------SCOPE %d----------------------------------\n",s->scope);
		struct hashnode * t = s->head;
		while(t!=NULL){
                        if(strcmp(t->vision,"local")==0 || strcmp(t->vision,"formal")==0){
			        printf("\"%s\" [%s %s] (line %d) (scope %d) (active %d) (space %d) (offset %d)\n",t->name,t->vision, t->type,t->line,t->scope,t->active,t->space,t->offset);
                        }else{
			        printf("\"%s\" [%s] (line %d) (scope %d) (active %d) (space %d) (offset %d)\n",t->name,t->type,t->line,t->scope,t->active,t->space,t->offset);
                        }
			t=t->snext;
		}
		s=s->next;
	}
	
}

//---------------------------------------------------------------------------------------------------------

void add_scope(struct hashnode * node){
	
	int i = node -> scope ;
	
	if(sizescope==-1){
		sizescope++;
		scopelist = (struct scopenode *) malloc (sizeof(struct scopenode));
		scopelist -> scope = i;
		scopelist -> next = NULL;
		scopelist -> head = node;
		
		return; 	
	}
	if(sizescope < i){
	
		struct scopenode * s = (struct scopenode *) malloc (sizeof(struct scopenode));
		s -> scope = i;
		s -> next = NULL;
		s -> head = node;
		
		struct scopenode * t = scopelist;
		while(t->next!=NULL){
			t=t->next;
		}
		t->next=s;
		sizescope++;
		return ;
	}else{
		
		struct scopenode * t = scopelist;
		while(i!=t->scope){
			t=t->next;
		}
		
		struct hashnode * t1=t->head;
	
		
		while(t1->snext!=NULL){
			t1=t1->snext;
		}
		t1->snext=node;
		
		return;
	}
	
}

//---------------------------------------------------------------------------------------------------------

struct hashnode * insert_node(int scope ,int line , char * type ,char * name,char * vision){
	struct hashnode * n = (struct hashnode *) malloc (sizeof(struct hashnode));
	n->line = line;
	n->scope = scope;
    n->active = 1 ; // ta eew balei ola ena gia na tsekarw tin hide !!!
	n->type = strdup(type);
	n->name = strdup(name);
        n->vision=strdup(vision);
	n->snext=NULL;

	add_scope(n);
    return n;
}
//---------------------------------------------------------------------------------------------------------

void init(){
	scopelist = NULL;
	insert_node(0,0,"library function","print","-");
	insert_node(0,0,"library function","input","-");
	insert_node(0,0,"library function","objectmemberkeys","-");
	insert_node(0,0,"library function","objecttotalmembers","-");
	insert_node(0,0,"library function","objectcopy","-");
	insert_node(0,0,"library function","totalarguments","-");
	insert_node(0,0,"library function","argument","-");
	insert_node(0,0,"library function","typeof","-");
	insert_node(0,0,"library function","strtonum","-");
	insert_node(0,0,"library function","sqrt","-");
	insert_node(0,0,"library function","cos","-");
	insert_node(0,0,"library function","sin","-");
  
}