
#define NOTFOUND -1
#define FUNVARCONF -2
#define LIBRFOUND -3
#define UPPERSCOPEVAR -4

extern int sizescope;
extern struct scopenode * scopelist;


// --------------
// | scopenodes |
// --------------
//       0      -------> hashnode0 -------> hashnode1 -------> hashnode2 ...
//       |    
//       1      -------> hashnode0 -------> hashnode1 -------> hashnode2 ...
//       |     
//       2      -------> hashnode0 -------> hashnode1 -------> hashnode2 ...
//       |
//       3      -------> hashnode0 -------> hashnode1 -------> hashnode2 ...
//      ...

enum space_t{
    programvar,
    functionlocal,
    formalarg,
};

struct hashnode{
        int scope ;  // scope of var or funct
        int line ;	// line
        int active ; // shows if node is active 
        char * type ; //  type of node (user function, lib function, variable etc)
        char * name ; // name of var
        char* vision ; // local or formal etc.
        enum space_t space;
        int offset;
        int taddress;
        int formal_num;
        int local_num;
        struct hashnode * snext ; // next pointer in scope list
};

struct scopenode {
        int scope ; 
        struct scopenode * next ; 
        struct hashnode * head ; 
};

// checks for validity of a formal argument
int testarg(char*, char*, char*,  int); 

// checks for validity of a var in global scope
struct hashnode *search0( char*);

// checks for validity of a function in the scope between the current and the global
struct hashnode *betfun(char*,  int);

// checks for validity of a variable in the scope between the current and the global
struct hashnode* betvar(char*, int);

// checks for validity of a variable in the current scope 
struct hashnode* samescope(char*,  int);

// checks for validity of a variable or function in the symbol table 
int LookUp( char*, char*, char*,  int);

// disables variables and function after exit from a block
void hide(int);

// print the elements put in the symbol table
void print_elements();

// add new scopenode in the scopelist
void add_scope(struct hashnode*);

// inserts new element in the symbol table
struct hashnode * insert_node(int, int, char*, char*, char*);

// initializes symbol table with library functions
void init(void);
