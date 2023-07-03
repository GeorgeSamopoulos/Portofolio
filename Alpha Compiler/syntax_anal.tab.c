
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "syntax_anal.y"

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



/* Line 189 of yacc.c  */
#line 173 "syntax_anal.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     STRING = 259,
     WHILE = 260,
     FOR = 261,
     IF = 262,
     ELSE = 263,
     FUNCTION = 264,
     RETURN = 265,
     BREAK = 266,
     CONT = 267,
     LOCAL = 268,
     TRUE = 269,
     FALSE = 270,
     NIL = 271,
     AND = 272,
     OR = 273,
     NOT = 274,
     PLUS = 275,
     MINUS = 276,
     ASSIGN = 277,
     MULTIPLY = 278,
     MODULE = 279,
     DIVIDE = 280,
     DECREASE = 281,
     INCREASE = 282,
     GREAT_EQUAL = 283,
     LESS_EQUAL = 284,
     GREATER = 285,
     LESS = 286,
     EQUAL = 287,
     NOTEQUAL = 288,
     L_C_BRACKET = 289,
     R_C_BRACKET = 290,
     L_S_BRACKET = 291,
     R_S_BRACKET = 292,
     L_PARENTH = 293,
     R_PARENTH = 294,
     COMA = 295,
     SEMICOLON = 296,
     COLON = 297,
     D_COLON = 298,
     DOT = 299,
     D_DOT = 300,
     OTHER = 301,
     INTCONST = 302,
     RCONST = 303
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 103 "syntax_anal.y"

char* stringValue;
int intValue;
float realValue;
struct expr* expressValue;



/* Line 214 of yacc.c  */
#line 266 "syntax_anal.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 278 "syntax_anal.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  61
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   543

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNRULES -- Number of states.  */
#define YYNSTATES  190

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    12,    14,    16,    19,
      22,    25,    26,    29,    31,    33,    35,    39,    43,    47,
      51,    55,    59,    63,    67,    71,    75,    79,    83,    87,
      89,    93,    96,    99,   102,   105,   108,   111,   113,   114,
     119,   121,   123,   125,   129,   131,   133,   136,   139,   141,
     145,   146,   152,   156,   161,   162,   168,   169,   173,   180,
     182,   184,   188,   194,   196,   200,   201,   202,   207,   208,
     213,   215,   219,   225,   226,   231,   234,   235,   236,   237,
     246,   247,   248,   256,   258,   260,   262,   264,   266,   268,
     270,   274,   275,   276,   277,   285,   286,   291,   292,   293,
     301,   302,   303,   304,   305,   306,   321,   323
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    51,    50,    -1,    -1,    53,    41,    -1,
      83,    -1,    87,    -1,    90,    -1,    96,    41,    -1,    11,
      41,    -1,    12,    41,    -1,    -1,    52,    73,    -1,    76,
      -1,    41,    -1,    55,    -1,    53,    20,    53,    -1,    53,
      21,    53,    -1,    53,    23,    53,    -1,    53,    24,    53,
      -1,    53,    25,    53,    -1,    53,    28,    53,    -1,    53,
      29,    53,    -1,    53,    30,    53,    -1,    53,    31,    53,
      -1,    53,    32,    53,    -1,    53,    33,    53,    -1,    53,
      17,    53,    -1,    53,    18,    53,    -1,    54,    -1,    38,
      53,    39,    -1,    21,    53,    -1,    19,    53,    -1,    27,
      58,    -1,    58,    27,    -1,    26,    58,    -1,    58,    26,
      -1,    57,    -1,    -1,    58,    56,    22,    53,    -1,    58,
      -1,    61,    -1,    68,    -1,    38,    76,    39,    -1,    81,
      -1,     3,    -1,    13,     3,    -1,    43,     3,    -1,    59,
      -1,    58,    44,     3,    -1,    -1,    58,    60,    36,    53,
      37,    -1,    61,    44,     3,    -1,    61,    36,    53,    37,
      -1,    -1,    61,    62,    38,    67,    39,    -1,    -1,    58,
      63,    64,    -1,    38,    76,    39,    38,    67,    39,    -1,
      65,    -1,    66,    -1,    38,    67,    39,    -1,    45,     3,
      38,    67,    39,    -1,    53,    -1,    67,    40,    53,    -1,
      -1,    -1,    36,    69,    67,    37,    -1,    -1,    36,    70,
      71,    37,    -1,    72,    -1,    71,    40,    72,    -1,    34,
      53,    42,    53,    35,    -1,    -1,    34,    74,    75,    35,
      -1,    75,    51,    -1,    -1,    -1,    -1,     9,     3,    77,
      38,    82,    39,    78,    73,    -1,    -1,    -1,     9,    38,
      79,    82,    39,    80,    73,    -1,    47,    -1,    48,    -1,
       4,    -1,    16,    -1,    14,    -1,    15,    -1,     3,    -1,
      82,    40,     3,    -1,    -1,    -1,    -1,     7,    84,    38,
      53,    39,    85,    51,    -1,    -1,    83,     8,    86,    51,
      -1,    -1,    -1,     5,    88,    38,    53,    39,    89,    51,
      -1,    -1,    -1,    -1,    -1,    -1,     6,    91,    38,    67,
      41,    92,    53,    93,    41,    94,    67,    39,    95,    51,
      -1,    10,    -1,    10,    53,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   175,   175,   176,   182,   189,   193,   196,   199,   206,
     216,   227,   227,   230,   233,   239,   244,   269,   294,   319,
     344,   369,   400,   432,   463,   494,   526,   559,   593,   626,
     635,   639,   667,   702,   807,   913,  1021,  1131,  1138,  1138,
    1301,  1386,  1390,  1395,  1399,  1406,  1416,  1425,  1436,  1444,
    1506,  1506,  1574,  1588,  1594,  1594,  1620,  1620,  1702,  1731,
    1734,  1741,  1746,  1751,  1778,  1812,  1818,  1818,  1854,  1854,
    1888,  1891,  1897,  1932,  1931,  1956,  1959,  1966,  1997,  1965,
    2035,  2059,  2034,  2096,  2105,  2114,  2122,  2130,  2139,  2150,
    2175,  2196,  2204,  2207,  2203,  2222,  2220,  2236,  2241,  2236,
    2263,  2266,  2270,  2276,  2279,  2262,  2299,  2308
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING", "WHILE", "FOR", "IF",
  "ELSE", "FUNCTION", "RETURN", "BREAK", "CONT", "LOCAL", "TRUE", "FALSE",
  "NIL", "AND", "OR", "NOT", "PLUS", "MINUS", "ASSIGN", "MULTIPLY",
  "MODULE", "DIVIDE", "DECREASE", "INCREASE", "GREAT_EQUAL", "LESS_EQUAL",
  "GREATER", "LESS", "EQUAL", "NOTEQUAL", "L_C_BRACKET", "R_C_BRACKET",
  "L_S_BRACKET", "R_S_BRACKET", "L_PARENTH", "R_PARENTH", "COMA",
  "SEMICOLON", "COLON", "D_COLON", "DOT", "D_DOT", "OTHER", "INTCONST",
  "RCONST", "$accept", "program", "stmt", "$@1", "expr", "term",
  "assignexpr", "$@2", "primary", "lvalue", "member", "$@3", "call", "$@4",
  "$@5", "callsuffix", "normcall", "methodcall", "elist", "objectdef",
  "$@6", "$@7", "indexed", "indexedelem", "block", "$@8", "insideblock",
  "funcdef", "$@9", "$@10", "$@11", "$@12", "const", "idlist", "ifstmt",
  "$@13", "$@14", "$@15", "whilestmt", "$@16", "$@17", "forstmt", "$@18",
  "$@19", "$@20", "$@21", "$@22", "returnstmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    52,    51,    51,    51,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    54,    54,    54,    54,    54,    56,    55,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    59,
      60,    59,    59,    59,    62,    61,    63,    61,    61,    64,
      64,    65,    66,    67,    67,    67,    69,    68,    70,    68,
      71,    71,    72,    74,    73,    75,    75,    77,    78,    76,
      79,    80,    76,    81,    81,    81,    81,    81,    81,    82,
      82,    82,    84,    85,    83,    86,    83,    88,    89,    87,
      91,    92,    93,    94,    95,    90,    96,    96
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     1,     1,     2,     2,
       2,     0,     2,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     0,     4,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       0,     5,     3,     4,     0,     5,     0,     3,     6,     1,
       1,     3,     5,     1,     3,     0,     0,     4,     0,     4,
       1,     3,     5,     0,     4,     2,     0,     0,     0,     8,
       0,     0,     7,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     0,     0,     7,     0,     4,     0,     0,     7,
       0,     0,     0,     0,     0,    14,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    45,    85,    97,   100,    92,     0,   106,     0,     0,
       0,    87,    88,    86,     0,     0,     0,     0,    66,     0,
      14,     0,    83,    84,     0,     3,     0,     0,    29,    15,
      37,    40,    48,    41,    42,    13,    44,     5,     6,     7,
       0,     0,     0,     0,    77,    80,   107,     9,    10,    46,
      32,    31,     0,    35,    54,    33,    65,     0,     0,     0,
      47,     1,     2,    73,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     4,    36,
      34,     0,     0,     0,     0,     0,     0,     0,    95,     8,
       0,    65,     0,     0,    91,     0,    63,     0,     0,     0,
      70,    30,    43,    76,    27,    28,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    49,     0,     0,
      65,     0,    57,    59,    60,     0,    52,    65,    11,     0,
       0,     0,    91,    89,     0,     0,    67,     0,     0,    69,
       0,    65,    11,    39,     0,     0,     0,    53,     0,    96,
      98,   101,    93,     0,    81,     0,    64,     0,    71,     0,
      74,    75,    51,    61,    65,    55,    11,     0,    11,    78,
       0,    90,     0,    58,     0,    99,   102,    94,     0,    82,
      72,    62,     0,    79,   103,    65,     0,   104,    11,   105
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    27,    28,    29,    82,    30,    31,
      32,    83,    33,    87,    84,   122,   123,   124,    97,    34,
      56,    57,    99,   100,    64,   103,   142,    35,    93,   178,
      94,   170,    36,   134,    37,    43,   168,   128,    38,    41,
     166,    39,    42,   167,   182,   185,   188,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -155
static const yytype_int16 yypact[] =
{
     132,  -155,  -155,  -155,  -155,  -155,     1,   296,   -36,   -20,
      30,  -155,  -155,  -155,   296,   296,     0,     0,     2,   260,
    -155,    51,  -155,  -155,    52,   132,    39,   328,  -155,  -155,
    -155,    -4,  -155,     6,  -155,  -155,  -155,    82,  -155,  -155,
      57,    54,    72,    78,  -155,  -155,   453,  -155,  -155,  -155,
    -155,   -14,   108,   -19,   -30,   -19,   296,    85,   347,    83,
    -155,  -155,  -155,  -155,  -155,   296,   296,   296,   296,   296,
     296,   296,   296,   296,   296,   296,   296,   296,  -155,  -155,
    -155,   118,   101,    88,   -18,   296,   122,    89,  -155,  -155,
     296,   296,   296,    90,   123,    92,   453,    -9,   296,     8,
    -155,  -155,    91,  -155,   484,   470,   -14,   -14,  -155,  -155,
    -155,   512,   512,   512,   512,   498,   498,  -155,   296,   296,
     296,   129,  -155,  -155,  -155,   398,  -155,   296,   224,   364,
      16,   381,   123,  -155,     7,    91,  -155,   296,    76,  -155,
      85,   296,   178,   453,   416,    32,    95,  -155,    37,  -155,
    -155,  -155,  -155,    40,  -155,   137,   453,   296,  -155,    42,
    -155,  -155,  -155,  -155,   296,  -155,   224,   296,   224,  -155,
      39,  -155,   434,  -155,    47,  -155,   453,  -155,    39,  -155,
    -155,  -155,   111,  -155,  -155,   296,    49,  -155,   224,  -155
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,   124,  -113,  -155,    -7,  -155,  -155,  -155,  -155,    86,
    -155,  -155,    98,  -155,  -155,  -155,  -155,  -155,   -90,  -155,
    -155,  -155,  -155,    14,  -154,  -155,  -155,   -17,  -155,  -155,
    -155,  -155,  -155,    23,  -155,  -155,  -155,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -69
static const yytype_int16 yytable[] =
{
      46,   130,    59,     1,    44,    47,    85,    50,    51,    69,
      70,    71,    58,    10,    86,   149,   179,   -50,   -38,   -56,
     120,    48,    79,    80,   183,    81,   -56,   121,   136,   161,
     145,   137,   -50,    49,   -56,    95,   -68,   148,    52,    45,
      81,   -56,    85,    21,   -54,   139,   154,   155,   140,    96,
      86,   159,    61,   175,    60,   177,   137,   151,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   163,   137,    63,   174,   189,   165,   137,   125,   169,
     155,   173,   137,   129,    96,   131,   181,   137,   187,   137,
      88,   138,    90,    65,    66,   186,    67,    68,    89,    69,
      70,    71,    53,    55,    72,    73,    74,    75,    76,    77,
      91,   143,   144,    96,    54,    54,    92,     6,   157,    98,
      96,   117,   102,   118,   119,   126,   133,   127,   132,   141,
     156,   135,   146,   164,    96,     1,     2,     3,     4,     5,
     171,     6,     7,     8,     9,    10,    11,    12,    13,    62,
     172,    14,   184,    15,   158,   153,     0,    96,    16,    17,
     176,     0,     0,     0,     0,     0,   -11,     0,    18,     0,
      19,     0,     0,    20,     0,    21,     0,     0,    96,    22,
      23,     1,     2,     3,     4,     5,     0,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,    14,     0,    15,
       0,     0,     0,     0,    16,    17,     0,     0,     0,     0,
       0,     0,     0,   160,    18,     0,    19,     0,     0,    20,
       0,    21,     0,     0,     0,    22,    23,     1,     2,     3,
       4,     5,     0,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,    14,     0,    15,     0,     0,     0,     0,
      16,    17,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,    19,     1,     2,    20,     0,    21,     0,     6,
       0,    22,    23,    10,    11,    12,    13,     0,     0,    14,
       0,    15,     0,     0,     0,     0,    16,    17,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,    19,     1,
       2,     0,     0,    21,     0,     0,     0,    22,    23,    10,
      11,    12,    13,     0,     0,    14,     0,    15,     0,     0,
       0,     0,    16,    17,     0,     0,     0,     0,     0,     0,
       0,     0,    18,     0,    19,     0,     0,     0,     0,    21,
       0,     0,     0,    22,    23,    65,    66,     0,    67,    68,
       0,    69,    70,    71,     0,     0,    72,    73,    74,    75,
      76,    77,     0,     0,    65,    66,     0,    67,    68,    78,
      69,    70,    71,     0,     0,    72,    73,    74,    75,    76,
      77,    65,    66,     0,    67,    68,   101,    69,    70,    71,
       0,     0,    72,    73,    74,    75,    76,    77,    65,    66,
       0,    67,    68,   150,    69,    70,    71,     0,     0,    72,
      73,    74,    75,    76,    77,    65,    66,     0,    67,    68,
     152,    69,    70,    71,     0,     0,    72,    73,    74,    75,
      76,    77,     0,    65,    66,   147,    67,    68,     0,    69,
      70,    71,     0,     0,    72,    73,    74,    75,    76,    77,
       0,    65,    66,   162,    67,    68,     0,    69,    70,    71,
       0,     0,    72,    73,    74,    75,    76,    77,     0,   180,
      65,    66,     0,    67,    68,     0,    69,    70,    71,     0,
       0,    72,    73,    74,    75,    76,    77,    65,     0,     0,
      67,    68,     0,    69,    70,    71,     0,     0,    72,    73,
      74,    75,    76,    77,    67,    68,     0,    69,    70,    71,
       0,     0,    72,    73,    74,    75,    76,    77,    67,    68,
       0,    69,    70,    71,     0,     0,    72,    73,    74,    75,
     -69,   -69,    67,    68,     0,    69,    70,    71,     0,     0,
     -69,   -69,   -69,   -69
};

static const yytype_int16 yycheck[] =
{
       7,    91,    19,     3,     3,    41,    36,    14,    15,    23,
      24,    25,    19,    13,    44,   128,   170,    36,    22,    38,
      38,    41,    26,    27,   178,    44,    45,    45,    37,   142,
     120,    40,    36,     3,    38,    52,    34,   127,    38,    38,
      44,    45,    36,    43,    38,    37,    39,    40,    40,    56,
      44,   141,     0,   166,     3,   168,    40,    41,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    39,    40,    34,   164,   188,    39,    40,    85,    39,
      40,    39,    40,    90,    91,    92,    39,    40,    39,    40,
       8,    98,    38,    17,    18,   185,    20,    21,    41,    23,
      24,    25,    16,    17,    28,    29,    30,    31,    32,    33,
      38,   118,   119,   120,    16,    17,    38,     9,    42,    34,
     127,     3,    39,    22,    36,     3,     3,    38,    38,    38,
     137,    39,     3,    38,   141,     3,     4,     5,     6,     7,
       3,     9,    10,    11,    12,    13,    14,    15,    16,    25,
     157,    19,    41,    21,   140,   132,    -1,   164,    26,    27,
     167,    -1,    -1,    -1,    -1,    -1,    34,    -1,    36,    -1,
      38,    -1,    -1,    41,    -1,    43,    -1,    -1,   185,    47,
      48,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    19,    -1,    21,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    -1,    38,    -1,    -1,    41,
      -1,    43,    -1,    -1,    -1,    47,    48,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    19,    -1,    21,    -1,    -1,    -1,    -1,
      26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    38,     3,     4,    41,    -1,    43,    -1,     9,
      -1,    47,    48,    13,    14,    15,    16,    -1,    -1,    19,
      -1,    21,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    38,     3,
       4,    -1,    -1,    43,    -1,    -1,    -1,    47,    48,    13,
      14,    15,    16,    -1,    -1,    19,    -1,    21,    -1,    -1,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    38,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    47,    48,    17,    18,    -1,    20,    21,
      -1,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    -1,    17,    18,    -1,    20,    21,    41,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    17,    18,    -1,    20,    21,    39,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    17,    18,
      -1,    20,    21,    39,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    17,    18,    -1,    20,    21,
      39,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    17,    18,    37,    20,    21,    -1,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    17,    18,    37,    20,    21,    -1,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      17,    18,    -1,    20,    21,    -1,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    17,    -1,    -1,
      20,    21,    -1,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    20,    21,    -1,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    20,    21,
      -1,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    20,    21,    -1,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    14,    15,    16,    19,    21,    26,    27,    36,    38,
      41,    43,    47,    48,    50,    51,    52,    53,    54,    55,
      57,    58,    59,    61,    68,    76,    81,    83,    87,    90,
      96,    88,    91,    84,     3,    38,    53,    41,    41,     3,
      53,    53,    38,    58,    61,    58,    69,    70,    53,    76,
       3,     0,    50,    34,    73,    17,    18,    20,    21,    23,
      24,    25,    28,    29,    30,    31,    32,    33,    41,    26,
      27,    44,    56,    60,    63,    36,    44,    62,     8,    41,
      38,    38,    38,    77,    79,    76,    53,    67,    34,    71,
      72,    39,    39,    74,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,     3,    22,    36,
      38,    45,    64,    65,    66,    53,     3,    38,    86,    53,
      67,    53,    38,     3,    82,    39,    37,    40,    53,    37,
      40,    38,    75,    53,    53,    67,     3,    37,    67,    51,
      39,    41,    39,    82,    39,    40,    53,    42,    72,    67,
      35,    51,    37,    39,    38,    39,    89,    92,    85,    39,
      80,     3,    53,    39,    67,    51,    53,    51,    78,    73,
      35,    39,    93,    73,    41,    94,    67,    39,    95,    51
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1455 of yacc.c  */
#line 176 "syntax_anal.y"
    {
			//printf("Program end\n");
		;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 182 "syntax_anal.y"
    {
			temp_as=NULL;
                        //  tabmem = NULL;
                          flagN = 0 ;
                        //reset_var_name();
                        //printf("expression; -->statement\n");
		;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 189 "syntax_anal.y"
    {
                        if_else=NULL;
                        //printf("if statement -->statement\n");
		;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 193 "syntax_anal.y"
    {
                        //printf("while loop-->statement\n");
		;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 196 "syntax_anal.y"
    {
                        //printf("for loop-->statement\n");
		;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 200 "syntax_anal.y"
    {
                        if(function_block==0){
                                printf("ERROR!Return outside function in line %d\n",yylineno);
                        }
			//printf("return statement;-->statement\n");
		;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 207 "syntax_anal.y"
    {
                        if(if_block==0 && for_block==0 && while_block==0){
                                printf("ERROR!Break outside loop in line %d\n",yylineno);
                        }else{
                                break_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                                push_jump_stack(break_jump,&(break_jump_list->head));
                        }
			// printf("break-->statement\n");
		;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 217 "syntax_anal.y"
    {
                        if(if_block==0 && for_block==0 && while_block==0){
                                printf("ERROR!Continue outside loop in line %d\n",yylineno);
                        }else if(for_block==1){
                                emit(jump,NULL,NULL,NULL,increment_jump_list->num,yylineno);
                        }else if(while_block==1){
                                emit(jump,NULL,NULL,NULL,loop_jump_list->num,yylineno);
                        }
			// printf("continue;-->statement\n");
		;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 227 "syntax_anal.y"
    {simple_block=1;;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 227 "syntax_anal.y"
    { simple_block=1;
			// printf("block-->statement\n");
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 230 "syntax_anal.y"
    {
			// printf("function definition-->statement\n");
		;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 233 "syntax_anal.y"
    {
			// printf(";-->statement\n");
		;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 240 "syntax_anal.y"
    {
                                (yyval.expressValue)=(yyvsp[(1) - (1)].expressValue);
                                // printf("Assign expression -->expression\n");
                        ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 245 "syntax_anal.y"
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
                                temp_expr->type = arith_ret_type(arith_compare_type((yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue)));
                                temp_expr=arith_calc('+',(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(add,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),(yyval.expressValue),-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 270 "syntax_anal.y"
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
                                temp_expr->type = arith_ret_type(arith_compare_type((yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue)));
                                temp_expr=arith_calc('-',(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(sub,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),(yyval.expressValue),-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 295 "syntax_anal.y"
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
                                temp_expr->type = arith_ret_type(arith_compare_type((yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue)));
                                temp_expr=arith_calc('*',(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(mul,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),(yyval.expressValue),-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 320 "syntax_anal.y"
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
                                temp_expr->type = arith_ret_type(arith_compare_type((yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue)));
                                temp_expr=arith_calc('%',(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(mod,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),(yyval.expressValue),-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 345 "syntax_anal.y"
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
                                temp_expr->type = arith_ret_type(arith_compare_type((yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue)));
                                temp_expr=arith_calc('/',(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(divide,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),(yyval.expressValue),-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 370 "syntax_anal.y"
    {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc(">=",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc(">=",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
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
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(if_greatereq,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                emit(assign,true_expr,NULL,temp_expr,-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 401 "syntax_anal.y"
    {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("<=",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("<=",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
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
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(if_lesseq,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                               // printf("%d\n",true_expr->type);
                                emit(assign,true_expr,NULL,temp_expr,-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 433 "syntax_anal.y"
    {       temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc(">",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc(">",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
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
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(if_greater,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                //printf("%d\n",true_expr->type);
                                emit(assign,true_expr,NULL,temp_expr,-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 464 "syntax_anal.y"
    {       temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("<",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("<",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
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
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(if_less,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                //printf("%d\n",true_expr->type);
                                emit(assign,true_expr,NULL,copy_expr(temp_expr),-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 495 "syntax_anal.y"
    {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("==",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("==",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
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
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(if_eq,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                //printf("%d\n",true_expr->type);
                                emit(assign,true_expr,NULL,temp_expr,-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 527 "syntax_anal.y"
    {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("!=",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=compare_calc("!=",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
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
                                (yyval.expressValue)=copy_expr(temp_expr);
                                emit(if_not_eq,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),NULL,quad_count+2,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                //printf("%d\n",true_expr->type);
                                emit(assign,true_expr,NULL,temp_expr,-1,yylineno);
                                emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                emit(assign,false_expr,NULL,temp_expr,-1,yylineno);

                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 560 "syntax_anal.y"
    {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=(struct expr *)log_calc("AND",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=(struct expr *)log_calc("AND",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
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
                                (yyval.expressValue)=copy_expr(temp_expr);
                                
                                // emit(if_eq,NULL,true_expr,$<expressValue>4,quad_count+2,yylineno);
                                // emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                // emit(assign,NULL,true_expr,$<expressValue>$,-1,yylineno);
                                // pop_jump_stack(&false_list)->label=quad_count+1;
                                // emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                // emit(assign,NULL,false_expr,$<expressValue>$,-1,yylineno);
                                emit(and,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),(yyval.expressValue),-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 594 "syntax_anal.y"
    {
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=(struct expr *)log_calc("OR",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
                                }else{
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type = boolexpr_e;
                                        temp_expr=(struct expr *)log_calc("OR",(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),temp_expr);
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
                                (yyval.expressValue)=copy_expr(temp_expr);
                                // emit(if_eq,NULL,true_expr,$<expressValue>4,quad_count+2,yylineno);
                                // emit(jump,NULL,NULL,NULL,quad_count+3,yylineno);
                                // pop_jump_stack(&true_list)->label=quad_count;
                                // emit(assign,NULL,true_expr,$<expressValue>$,-1,yylineno);
                                // emit(jump,NULL,NULL,NULL,quad_count+2,yylineno);
                                // emit(assign,NULL,false_expr,$<expressValue>$,-1,yylineno);
                                emit(or,(yyvsp[(1) - (3)].expressValue),(yyvsp[(3) - (3)].expressValue),(yyval.expressValue),-1,yylineno);
                                // printf("expression %s expression -->expression\n",$2);
                        ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 626 "syntax_anal.y"
    {
                                (yyval.expressValue)=(yyvsp[(1) - (1)].expressValue);
                                // printf("term-->expression\n");
                        ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 635 "syntax_anal.y"
    {
                        (yyval.expressValue)=(yyvsp[(2) - (3)].expressValue);
			// printf("(expression)-->term\n");
                ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 639 "syntax_anal.y"
    {
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->type;
                                temp_expr->intConst= (-1)*(yyvsp[(2) - (2)].expressValue)->intConst;
                                temp_expr->floatConst= (-1)*(yyvsp[(2) - (2)].expressValue)->floatConst;
                        }else{
                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->type;
                                temp_expr->intConst= (-1)*(yyvsp[(2) - (2)].expressValue)->intConst;
                                temp_expr->floatConst= (-1)*(yyvsp[(2) - (2)].expressValue)->floatConst;
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
                        (yyval.expressValue)=copy_expr(temp_expr);
                        emit(uminus,(yyvsp[(2) - (2)].expressValue),NULL,(yyval.expressValue),-1,yylineno);
			// printf("-expression-->term\n");
                ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 667 "syntax_anal.y"
    {
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_expr->type = boolexpr_e;
                                if((yyvsp[(2) - (2)].expressValue)->type!=boolexpr_e && (yyvsp[(2) - (2)].expressValue)->type!=constbool_e){
                                        printf("ERROR : WRONG TYPE");
                                }else{
                                        temp_expr->boolConst=!((yyvsp[(2) - (2)].expressValue)->boolConst);
                                }
                        }else{
                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                temp_expr->type = boolexpr_e;
                                if((yyvsp[(2) - (2)].expressValue)->type!=boolexpr_e && (yyvsp[(2) - (2)].expressValue)->type!=constbool_e){
                                        temp_expr->boolConst=!non_boll_log_calc((yyvsp[(2) - (2)].expressValue));
                                }else{
                                        temp_expr->boolConst=!((yyvsp[(2) - (2)].expressValue)->boolConst);
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
                        (yyval.expressValue)=copy_expr(temp_expr);
                        emit(not,(yyvsp[(2) - (2)].expressValue),NULL,(yyval.expressValue),-1,yylineno);
                        // $$=$2;
                        // printf("not expression -->term\n");
                ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 702 "syntax_anal.y"
    {
			if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",(yyvsp[(2) - (2)].expressValue)->sym->name,terms->line);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else{
                                        (yyvsp[(2) - (2)].expressValue)=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->type;
                                                (yyvsp[(2) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->type;
                                                (yyvsp[(2) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->intConst;
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
                                        (yyval.expressValue)=copy_expr(temp_expr);
                                        emit(add,(yyvsp[(2) - (2)].expressValue),one_expr,(yyvsp[(2) - (2)].expressValue),-1,yylineno);
                                        emit(assign,(yyvsp[(2) - (2)].expressValue),NULL,(yyval.expressValue),-1,yylineno); 
                                }
                        }else{
                                n=LookUp((yyvsp[(2) - (2)].expressValue)->sym->name,(yyvsp[(2) - (2)].expressValue)->sym->type,(yyvsp[(2) - (2)].expressValue)->sym->vision,(yyvsp[(2) - (2)].expressValue)->sym->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",(yyvsp[(2) - (2)].expressValue)->sym->name,yylineno);
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
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->index->type;
                                                (yyvsp[(2) - (2)].expressValue)->index->intConst++;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->index->type;
                                                (yyvsp[(2) - (2)].expressValue)->index->intConst++;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->index->intConst;
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
                                        (yyval.expressValue)=copy_expr(temp_expr);
                                        emit(tablegetelem,(yyvsp[(2) - (2)].expressValue),(yyvsp[(2) - (2)].expressValue)->index,(yyval.expressValue),-1,yylineno); 
                                        emit(add,(yyval.expressValue),one_expr,(yyval.expressValue),-1,yylineno);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->index->type;
                                                (yyvsp[(2) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->index->type;
                                                (yyvsp[(2) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->index->intConst;
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
                                        emit(assign,copy_expr(temp_expr),NULL,(yyval.expressValue),-1,yylineno); 
                                        (yyval.expressValue) = copy_expr((yyvsp[(2) - (2)].expressValue));
                                }
                                from_member=0;
                        
                        }
                         //printf("++value-->term\n");
                ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 807 "syntax_anal.y"
    {
                        if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",(yyvsp[(1) - (2)].expressValue)->sym->name,yylineno);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else{
                                        (yyvsp[(1) - (2)].expressValue)=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->type;
                                                (yyvsp[(1) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->type;
                                                (yyvsp[(1) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->intConst;
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
                                        (yyval.expressValue)=copy_expr(temp_expr);
                                        emit(assign,(yyvsp[(1) - (2)].expressValue),NULL,(yyval.expressValue),-1,yylineno); 
                                        emit(add,(yyvsp[(1) - (2)].expressValue),one_expr,(yyvsp[(1) - (2)].expressValue),-1,yylineno);
                                }
                        }else{
                                n=LookUp((yyvsp[(1) - (2)].expressValue)->sym->name,(yyvsp[(1) - (2)].expressValue)->sym->type,(yyvsp[(1) - (2)].expressValue)->sym->vision,(yyvsp[(1) - (2)].expressValue)->sym->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",(yyvsp[(1) - (2)].expressValue)->sym->name,yylineno);
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
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->index->type;
                                                (yyvsp[(1) - (2)].expressValue)->index->intConst++;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->index->type;
                                                (yyvsp[(1) - (2)].expressValue)->index->intConst++;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->index->intConst;
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
                                        (yyval.expressValue)=copy_expr(temp_expr);
                                        emit(tablegetelem,(yyvsp[(1) - (2)].expressValue),(yyvsp[(1) - (2)].expressValue)->index,(yyval.expressValue),-1,yylineno); 
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->index->type;
                                                (yyvsp[(1) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->index->type;
                                                (yyvsp[(1) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->index->intConst;
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
                                        emit(assign,(yyval.expressValue),NULL,copy_expr(temp_expr),-1,yylineno);
                                        emit(add,(yyval.expressValue),one_expr,(yyval.expressValue),-1,yylineno); 
                                        emit(tablesetelem,(yyvsp[(1) - (2)].expressValue),(yyvsp[(1) - (2)].expressValue)->index,(yyval.expressValue),-1,yylineno); 
                                        (yyval.expressValue) = copy_expr((yyvsp[(1) - (2)].expressValue));
                                }
                                from_member=0;
                        
                        }
			// printf("value++-->term\n");
                ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 913 "syntax_anal.y"
    {
                        if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",(yyvsp[(2) - (2)].expressValue)->sym->name,yylineno);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                        (yyvsp[(2) - (2)].expressValue)=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->type;
                                                (yyvsp[(2) - (2)].expressValue)->intConst--;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->type;
                                                (yyvsp[(2) - (2)].expressValue)->intConst--;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->intConst;
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
                                        (yyval.expressValue)=copy_expr(temp_expr);
                                        emit(sub,(yyvsp[(2) - (2)].expressValue),one_expr,(yyvsp[(2) - (2)].expressValue),-1,yylineno);
                                        emit(assign,(yyvsp[(2) - (2)].expressValue),NULL,(yyval.expressValue),-1,yylineno); 
                                }
                        }else{
                                n=LookUp((yyvsp[(2) - (2)].expressValue)->sym->name,(yyvsp[(2) - (2)].expressValue)->sym->type,(yyvsp[(2) - (2)].expressValue)->sym->vision,(yyvsp[(2) - (2)].expressValue)->sym->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",(yyvsp[(2) - (2)].expressValue)->sym->name,yylineno);
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
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->index->type;
                                                (yyvsp[(2) - (2)].expressValue)->index->intConst--;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->index->type;
                                                (yyvsp[(2) - (2)].expressValue)->index->intConst--;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->index->intConst;
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
                                        (yyval.expressValue)=copy_expr(temp_expr);
                                        emit(tablegetelem,(yyvsp[(2) - (2)].expressValue),(yyvsp[(2) - (2)].expressValue)->index,(yyval.expressValue),-1,yylineno); 
                                        emit(sub,(yyval.expressValue),one_expr,(yyval.expressValue),-1,yylineno);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->index->type;
                                                (yyvsp[(2) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(2) - (2)].expressValue)->index->type;
                                                (yyvsp[(2) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(2) - (2)].expressValue)->index->intConst;
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
                                        emit(assign,copy_expr(temp_expr),NULL,(yyval.expressValue),-1,yylineno); 
                                        (yyval.expressValue) = copy_expr((yyvsp[(2) - (2)].expressValue));
                                }
                                from_member=0;
                        }
			//  printf("--value-->term\n");
                ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 1021 "syntax_anal.y"
    {
                        if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",(yyvsp[(1) - (2)].expressValue)->sym->name,yylineno);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                        (yyvsp[(1) - (2)].expressValue)=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->type;
                                                (yyvsp[(1) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->type;
                                                (yyvsp[(1) - (2)].expressValue)->intConst++;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->intConst;
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
                                        (yyval.expressValue)=copy_expr(temp_expr);
                                        emit(assign,(yyvsp[(1) - (2)].expressValue),NULL,(yyval.expressValue),-1,yylineno); 
                                        emit(sub,(yyvsp[(1) - (2)].expressValue),one_expr,(yyvsp[(1) - (2)].expressValue),-1,yylineno);
                                }
                        }else{
                                n=LookUp((yyvsp[(1) - (2)].expressValue)->sym->name,(yyvsp[(1) - (2)].expressValue)->sym->type,(yyvsp[(1) - (2)].expressValue)->sym->vision,(yyvsp[(1) - (2)].expressValue)->sym->scope);
                                if(n==-1){
                                        printf("ERROR! Undeclared variable %s in line %d\n",(yyvsp[(1) - (2)].expressValue)->sym->name,yylineno);
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
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->index->type;
                                                (yyvsp[(1) - (2)].expressValue)->index->intConst--;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->index->type;
                                                (yyvsp[(1) - (2)].expressValue)->index->intConst--;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->index->intConst;
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
                                        (yyval.expressValue)=copy_expr(temp_expr);
                                        emit(tablegetelem,(yyvsp[(1) - (2)].expressValue),(yyvsp[(1) - (2)].expressValue)->index,(yyval.expressValue),-1,yylineno); 
                                        temp_name=var_name();
                                        n=LookUp(temp_name,"variable","-",scope_count);
                                        if(n>=0){
                                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->index->type;
                                                (yyvsp[(1) - (2)].expressValue)->intConst--;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->index->intConst;
                                        }else{
                                                temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                                temp_expr->type = (yyvsp[(1) - (2)].expressValue)->index->type;
                                                (yyvsp[(1) - (2)].expressValue)->intConst--;
                                                temp_expr->intConst= (yyvsp[(1) - (2)].expressValue)->index->intConst;
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
                                        emit(assign,(yyval.expressValue),NULL,copy_expr(temp_expr),-1,yylineno);
                                        emit(sub,(yyval.expressValue),one_expr,(yyval.expressValue),-1,yylineno); 
                                        emit(tablesetelem,(yyvsp[(1) - (2)].expressValue),(yyvsp[(1) - (2)].expressValue)->index,(yyval.expressValue),-1,yylineno); 
                                        (yyval.expressValue) = copy_expr((yyvsp[(1) - (2)].expressValue));
                                }
                                from_member=0;

                        }
			// printf("value---->term\n");
                ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 1131 "syntax_anal.y"
    {
                        (yyval.expressValue)=(yyvsp[(1) - (1)].expressValue);
                        // printf("primary-->term\n");
                ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 1138 "syntax_anal.y"
    {
                        if(from_member==0){
                                terms->type="variable";
                                n=LookUp(terms->name,terms->type,terms->vision,terms->scope);
                                if(strcmp(terms->vision,"::")==0){
                                        if(n==-1){
                                                printf("ERROR! Variable %s not found in global scope in line %d\n",terms->name,terms->line);
                                        }else if(n==-2){
                                                //printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                                (yyvsp[(1) - (1)].expressValue)=copy_expr(find_expr(terms->name , "user function" , terms->vision ,  terms->scope));
                                        }else{
                                                (yyvsp[(1) - (1)].expressValue)=copy_expr(find_expr(terms->name , terms->type , terms->vision ,  terms->scope));
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
                                        (yyvsp[(1) - (1)].expressValue)=copy_expr(temp_expr);
                                }else if(n==-2){
                                        //printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                        (yyvsp[(1) - (1)].expressValue)=copy_expr(find_expr(terms->name , "user function" , terms->vision ,  terms->scope));
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                        (yyvsp[(1) - (1)].expressValue)=copy_expr(find_expr(terms->name , terms->type , terms->vision ,  terms->scope));
                                }
                                //IF NOT FOUND INSERT
                        }else{
                                from_member=0;//mporei na fugei
                        }
                ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 1182 "syntax_anal.y"
    {
                if((yyvsp[(4) - (4)].expressValue)->type==newtable_e && flagN == 0 ){
                        struct expr * tsym=copy_expr((yyvsp[(1) - (4)].expressValue));
                        (yyvsp[(1) - (4)].expressValue)=copy_expr((yyvsp[(4) - (4)].expressValue));
                        (yyvsp[(1) - (4)].expressValue)->type=change_type((yyvsp[(4) - (4)].expressValue));
                        (yyvsp[(1) - (4)].expressValue)->sym=tsym->sym;
                        fillExp(copy_expr((yyvsp[(1) - (4)].expressValue)));
                        emit(assign , copy_expr((yyvsp[(4) - (4)].expressValue)) , NULL , (yyvsp[(1) - (4)].expressValue), -1, yylineno);
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_expr->type=change_type((yyvsp[(1) - (4)].expressValue));
                        }else{
                                temp_expr->type=change_type((yyvsp[(1) - (4)].expressValue));
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
                        emit(assign , (yyvsp[(1) - (4)].expressValue) , NULL , copy_expr(temp_expr), -1, yylineno);
                        (yyval.expressValue)=copy_expr(temp_expr);
                }else if ((yyvsp[(1) - (4)].expressValue)->type == newtable_e && flagN == 1 ){
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=find_expr(temp_name,"variable","-",scope_count);
                                temp_expr->type=change_type((yyvsp[(1) - (4)].expressValue));
                        }else{
                                temp_expr->type=change_type((yyvsp[(1) - (4)].expressValue));
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
                        if (tabmem != NULL && tabmem->next != NULL && ((yyvsp[(4) - (4)].expressValue)->type == newtable_e || (yyvsp[(4) - (4)].expressValue)->type == tableitem_e)){
                                if ( (yyvsp[(4) - (4)].expressValue)->type == tableitem_e){
                                        emit(tablesetelem,tabmem->next->index,(yyvsp[(4) - (4)].expressValue),tabmem->next,-1,yylineno);
                                //}else if ($4->type == newtable_e){
                                      //  emit(tablesetelem,tabmem->index,$4,tabmem,-1,yylineno);
                                }
                                fill_tabelem(tabmem, tabmem->next );
                                emit(tablegetelem, (yyvsp[(1) - (4)].expressValue), (yyvsp[(1) - (4)].expressValue)->index, copy_expr(temp_expr),-1,yylineno);
                                temp_expr->type = newtable_e;
                                temp_expr->strConst=NULL;
                                (yyval.expressValue) = copy_expr(temp_expr);
                        }else if (tabtype == -1 ) {
                                fill_tabelem((yyvsp[(1) - (4)].expressValue), (yyvsp[(4) - (4)].expressValue) );
                                emit(tablesetelem,(yyvsp[(1) - (4)].expressValue)->index,(yyvsp[(4) - (4)].expressValue),(yyvsp[(1) - (4)].expressValue),-1,yylineno);
                                emit(tablegetelem, (yyvsp[(1) - (4)].expressValue), (yyvsp[(1) - (4)].expressValue)->index, copy_expr(temp_expr),-1,yylineno);
                                (yyval.expressValue) = copy_expr(temp_expr);       
                        }
                        else{
                                fill_tabelem(copy_expr((yyvsp[(1) - (4)].expressValue)), copy_expr((yyvsp[(4) - (4)].expressValue)));
                                emit(tablesetelem,tabmem->index,(yyvsp[(4) - (4)].expressValue),tabmem,-1,yylineno);
                                emit(tablegetelem, tabmem, tabmem->index, copy_expr(temp_expr),-1,yylineno);   
                                (yyval.expressValue) = copy_expr(temp_expr);
                        }

                        tabmem = tabmem->next;
                        from_member = 0 ;
                        tabtype = -1 ; 
                        (yyvsp[(1) - (4)].expressValue)->index =  update_index((yyvsp[(1) - (4)].expressValue)->sym->name , (yyvsp[(1) - (4)].expressValue)->index) ; 

                }else if ( (yyvsp[(4) - (4)].expressValue)->type != newtable_e && flagN == 0 ){
                        if(from_member==0){
                                if((yyvsp[(4) - (4)].expressValue)->type==2) assign_ins->type="user function";
                                (yyvsp[(1) - (4)].expressValue)->type=change_type((yyvsp[(4) - (4)].expressValue));
                                (yyvsp[(1) - (4)].expressValue)->intConst=(yyvsp[(4) - (4)].expressValue)->intConst;
                                (yyvsp[(1) - (4)].expressValue)->floatConst=(yyvsp[(4) - (4)].expressValue)->floatConst;
                                if((yyvsp[(4) - (4)].expressValue)->strConst) (yyvsp[(1) - (4)].expressValue)->strConst=strdup((yyvsp[(4) - (4)].expressValue)->strConst);
                                else (yyvsp[(1) - (4)].expressValue)->strConst=NULL;
                                (yyvsp[(1) - (4)].expressValue)->boolConst=(yyvsp[(4) - (4)].expressValue)->boolConst;
                                fillExp(copy_expr((yyvsp[(1) - (4)].expressValue)));
                                emit(assign , copy_expr((yyvsp[(4) - (4)].expressValue)) , NULL , (yyvsp[(1) - (4)].expressValue), -1, yylineno);
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                        temp_expr->type=change_type((yyvsp[(1) - (4)].expressValue));
                                }else{
                                        temp_expr->type=change_type((yyvsp[(1) - (4)].expressValue));
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
                                emit(assign , (yyvsp[(1) - (4)].expressValue) , NULL , temp_expr, -1, yylineno);
                                (yyval.expressValue)=copy_expr(temp_expr);
                        }
                }
                // printf("lvalue=expression-->assignexpr\n");
        ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 1301 "syntax_anal.y"
    {
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
                                                        (yyval.expressValue)=copy_expr(temp_expr);
                                                        
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
                                              (yyval.expressValue)=copy_expr(temp_expr);
                                            }else{
                                                    printf("ERROR CONFLICT LIB-FUN IN LINEEEE: %d\n",terms->line);
                                            }
                                        }else{
                                                (yyvsp[(1) - (1)].expressValue)=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                                (yyval.expressValue)=copy_expr((yyvsp[(1) - (1)].expressValue));
                                        }
                                }else{
                                        (yyvsp[(1) - (1)].expressValue)=find_expr(terms->name , terms->type , terms->vision ,  terms->scope);
                                        (yyval.expressValue)=copy_expr((yyvsp[(1) - (1)].expressValue));
                                }
                        }else if ( from_member == 1){
                                temp_name=var_name();
                                n=LookUp(temp_name,"variable","-",scope_count);
                                if(n>=0){
                                        temp_expr=find_expr(temp_name,"variable","-",scope_count);
                                        temp_expr->type=(yyvsp[(1) - (1)].expressValue)->index->type;
                                        temp_expr->intConst=(yyvsp[(1) - (1)].expressValue)->index->intConst;
                                        temp_expr->floatConst=(yyvsp[(1) - (1)].expressValue)->index->floatConst;
                                        if((yyvsp[(1) - (1)].expressValue)->index->strConst) temp_expr->strConst=strdup((yyvsp[(1) - (1)].expressValue)->index->strConst);
                                }else{
                                        temp_expr->type=change_type((yyvsp[(1) - (1)].expressValue));
                                        temp_expr->sym = insert_node(scope_count,yylineno,"variable",temp_name,"-");
                                        temp_expr->type=(yyvsp[(1) - (1)].expressValue)->index->type;
                                        temp_expr->intConst=(yyvsp[(1) - (1)].expressValue)->index->intConst;
                                        temp_expr->floatConst=(yyvsp[(1) - (1)].expressValue)->index->floatConst;
                                        if((yyvsp[(1) - (1)].expressValue)->index->strConst) temp_expr->strConst=strdup((yyvsp[(1) - (1)].expressValue)->index->strConst);
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
                                        emit(tablegetelem,(yyvsp[(1) - (1)].expressValue),(yyvsp[(1) - (1)].expressValue)->index,copy_expr(temp_expr),-1,yylineno);//edw na tsekarw
                                        (yyval.expressValue) = copy_expr(temp_expr);
                                }else{
                                        emit(tablegetelem,tabmem,tabmem->index,copy_expr(temp_expr),-1,yylineno);
                                        (yyval.expressValue) = copy_expr(temp_expr);
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
                ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 1386 "syntax_anal.y"
    {
                        (yyval.expressValue)=(yyvsp[(1) - (1)].expressValue);
                        // printf("call-->primary\n");
                ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 1390 "syntax_anal.y"
    {
                        object_flag--;
                        (yyval.expressValue)=(yyvsp[(1) - (1)].expressValue);
			// printf("object definition-->primary\n");
                ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 1395 "syntax_anal.y"
    {
			(yyval.expressValue)=(yyvsp[(2) - (3)].expressValue);
                        // printf("(function definition)-->primary\n");
                ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 1399 "syntax_anal.y"
    {
                        (yyval.expressValue)=(yyvsp[(1) - (1)].expressValue);
                        // printf("const-->primary\n");
                ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 1406 "syntax_anal.y"
    {
                                terms->name=strdup((yyvsp[(1) - (1)].stringValue));
                                terms->type=NULL;
                                terms->line=yylineno;
                                terms->vision="-";
                                terms->scope=scope_count;
                                from_member=0;
                                // printf("identifier-->lvalue\n");

		        ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 1416 "syntax_anal.y"
    {
                                terms->name=strdup((yyvsp[(2) - (2)].stringValue));
                                terms->type="variable";
                                terms->line=yylineno;
                                terms->vision="local";
                                terms->scope=scope_count;
                                from_member=0;
			        // printf("local identifier-->lvalue\n");
                        ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 1425 "syntax_anal.y"
    {
                                terms->name=strdup((yyvsp[(2) - (2)].stringValue));
                                terms->type=NULL;
                                terms->line=yylineno;
                                terms->vision="::";
                                terms->scope=scope_count;
                                terms->snext=NULL;
                                from_member=0;
                                (yyval.expressValue)=(yyvsp[(2) - (2)].stringValue);
	        		// printf("::identifier-->lvalue\n");
                ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 1436 "syntax_anal.y"
    {       
                        from_member=1;
                        (yyval.expressValue)=(yyvsp[(1) - (1)].expressValue);
			//printf("member-->lvalue\n");
                ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 1444 "syntax_anal.y"
    {
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
                                        (yyvsp[(1) - (3)].expressValue)=copy_expr(temp_expr);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                       temp_expr=find_expr(terms->name,"variable","-",scope_count);
                                       temp_expr->type = newtable_e;
                                       (yyvsp[(1) - (3)].expressValue) = copy_expr(temp_expr); 

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
                        checking = check_table((yyvsp[(1) - (3)].expressValue)) ; 
                        if ( checking == -1 ){
                                printf("ERROR variable %s isn't newtable_e.\n" , (yyvsp[(1) - (3)].expressValue)->sym->name);
                        }else{
                               
                                if ( tabmem == NULL ){
                                        tabname = strdup((yyvsp[(3) - (3)].stringValue)) ;
                                        (yyvsp[(1) - (3)].expressValue)->index = check_index((yyvsp[(1) - (3)].expressValue),tabname);
                                        tabmem = copy_expr((yyvsp[(1) - (3)].expressValue));
                                }else{ 
                                        tabname = strdup((yyvsp[(3) - (3)].stringValue)) ;
                                        (yyvsp[(1) - (3)].expressValue)->index = check_index((yyvsp[(1) - (3)].expressValue) , tabname);
                                        tabnode = copy_expr((yyvsp[(1) - (3)].expressValue));
                                        tabnode->next = tabmem;
                                        tabmem = tabnode;       
                                }
                                tabtype = -1;
                                flagN = 1 ;
                                (yyval.expressValue) = copy_expr((yyvsp[(1) - (3)].expressValue)) ; 
                               // printf("value.identifier-->member\n");
                        }

                ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 1506 "syntax_anal.y"
    {
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
                                        (yyvsp[(1) - (1)].expressValue)=copy_expr(temp_expr);
                                }else if(n==-2){
                                        printf("ERROR CONFLICT VAR-FUN IN LINE: %d\n",terms->line);
                                }else if(n==-4){
                                        if(simple_block==0){
                                                printf("ERROR CONFLICT VAR IN UPPER SCOPE: %d\n",terms->line);                
                                        }
                                }else{
                                       temp_expr=find_expr(terms->name,"variable","-",scope_count);
                                       temp_expr->type = newtable_e;
                                       (yyvsp[(1) - (1)].expressValue) = copy_expr(temp_expr); 
                                }
                        }else{
                                from_member=0;
                        }
                ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 1536 "syntax_anal.y"
    {
                        checking = check_table((yyvsp[(1) - (5)].expressValue)) ; 
                        if ( checking == -1 ){
                                printf("ERROR variable %s isn't newtable_e.\n" , (yyvsp[(1) - (5)].expressValue)->sym->name);
                        }else{
                              
                                tabtype = (yyvsp[(4) - (5)].expressValue)->type;
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
                                        (yyvsp[(1) - (5)].expressValue)->index = check_index2((yyvsp[(1) - (5)].expressValue),(yyvsp[(4) - (5)].expressValue));
                                        tabmem = copy_expr((yyvsp[(1) - (5)].expressValue));
                                }else{ 
                                        (yyvsp[(1) - (5)].expressValue)->index = check_index2((yyvsp[(1) - (5)].expressValue) , (yyvsp[(4) - (5)].expressValue));
                                        tabnode = copy_expr((yyvsp[(1) - (5)].expressValue));
                                        tabnode->next = tabmem;
                                        tabmem = tabnode;     
                                }
                                tabtype =tabmem->index->type; 
                                 (yyval.expressValue) = copy_expr((yyvsp[(1) - (5)].expressValue)) ; 
                        }

                        flagN = 1 ;
                        // printf("value[expresion]-->member\n");
                ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 1574 "syntax_anal.y"
    {
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
                ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1588 "syntax_anal.y"
    {
			// printf("call[expression]-->member\n");
                ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1594 "syntax_anal.y"
    {call_flag=1;;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 1594 "syntax_anal.y"
    {
			// printf("(elist)-->call\n");
                        // emit_elist_quads(&elist_list);
                        emit(call,NULL,NULL,copy_expr((yyvsp[(1) - (5)].expressValue)),-1,yylineno);
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
                        (yyval.expressValue)=copy_expr(temp_expr);
                ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 1620 "syntax_anal.y"
    {
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
                ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 1661 "syntax_anal.y"
    {
                        if(from_member==0){
                                if(strcmp((yyvsp[(1) - (3)].expressValue),"print")==0||strcmp((yyvsp[(1) - (3)].expressValue),"input")==0||strcmp((yyvsp[(1) - (3)].expressValue),"objectmemberkeys")==0||
                                        strcmp((yyvsp[(1) - (3)].expressValue),"objecttotalmembers")==0||strcmp((yyvsp[(1) - (3)].expressValue),"objectcopy")==0||strcmp((yyvsp[(1) - (3)].expressValue),"totalarguments")==0||
                                        strcmp((yyvsp[(1) - (3)].expressValue),"argument")==0||strcmp((yyvsp[(1) - (3)].expressValue),"typeof")==0||strcmp((yyvsp[(1) - (3)].expressValue),"strtonum")==0||
                                        strcmp((yyvsp[(1) - (3)].expressValue),"sqrt")==0||strcmp((yyvsp[(1) - (3)].expressValue),"cos")==0||strcmp((yyvsp[(1) - (3)].expressValue),"sin")==0){
                                                temp_expr=(struct expr*) malloc(sizeof(struct expr));
                                                temp_expr->type=libraryfunc_e;
                                                temp_expr->sym=(struct hashnode*) malloc(sizeof(struct hashnode));
                                                temp_expr->sym->name=strdup((yyvsp[(1) - (3)].expressValue));
                                }else{
                                        temp_expr=copy_expr(find_expr((yyvsp[(1) - (3)].expressValue),"user function","-",scope_count));
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
                                (yyval.expressValue)=copy_expr(temp_expr);
                        }else{
                                from_member=0;
                        }
                        // printf("callsuffix-->call\n");
                ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 1702 "syntax_anal.y"
    {
                        // emit_elist_quads(&elist_list);
			emit(call,NULL,NULL,copy_expr((yyvsp[(2) - (6)].expressValue)),-1,yylineno);
                        temp_name=var_name();
                        n=LookUp(temp_name,"variable","-",scope_count);
                        if(n>=0){
                                temp_expr=copy_expr(find_expr(temp_name,"variable","-",scope_count));
                                temp_expr->type=change_type((yyvsp[(2) - (6)].expressValue));
                        }else{
                                temp_expr->type=change_type((yyvsp[(2) - (6)].expressValue));
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
                        (yyval.expressValue)=copy_expr(temp_expr);
                        // printf("(function definition)(elist)\n");
                ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 1731 "syntax_anal.y"
    {
			// printf("normcall-->callsuffix\n");
                ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1734 "syntax_anal.y"
    {
			dd=1;
                        // printf("methodcall-->callsuffix\n");
                ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1741 "syntax_anal.y"
    {
			// printf("(elist)-->normcall\n");
                ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1746 "syntax_anal.y"
    {
			// printf("..identifier(elist)-->methodcall\n");
                ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1751 "syntax_anal.y"
    {
                        // printf("expression-->elist\n");
                        if(call_flag==1){
                                emit(param,NULL,NULL,copy_expr((yyvsp[(1) - (1)].expressValue)),-1,yylineno);
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
                                table_stack=creat_q(copy_expr(t),copy_expr((yyvsp[(1) - (1)].expressValue)));
                                table_stack->result=copy_expr(temp_table);
                                temp_table->index=NULL;
                                temp_table->index=add_e(copy_expr((yyvsp[(1) - (1)].expressValue)),temp_table->index);
                                emit(tablesetelem,table_stack->arg1,table_stack->arg2,table_stack->result,-1,yylineno);
                                temp_table->intConst++;
                        }
        		//printf("expression-->elist\n");
                ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1778 "syntax_anal.y"
    {
			// printf("elist,expression->elist\n");
                        if(call_flag==1){
                                emit(param,NULL,NULL,copy_expr((yyvsp[(3) - (3)].expressValue)),-1,yylineno);
                                // fill_elist_quads(param,copy_expr($3),yylineno,&elist_list);
                        }
                        else if(object_flag>=1){
                                struct expr* temp=tables_temp;
                                while(temp->next!=NULL){
                                        temp=temp->next;
                                }
                                temp_table=temp;
                                struct expr * t = (struct expr *) malloc (sizeof(struct expr));
                                t=copy_expr((yyvsp[(3) - (3)].expressValue));
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
                                table_stack=creat_q(copy_expr(t),copy_expr((yyvsp[(3) - (3)].expressValue)));
                                table_stack->result=copy_expr(temp_table);
                                temp_table->index=add_e(copy_expr((yyvsp[(3) - (3)].expressValue)),temp_table->index);
                                emit(tablesetelem,table_stack->arg1,table_stack->arg2,table_stack->result,-1,yylineno);
                                temp_table->intConst++;
                        }
                ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1812 "syntax_anal.y"
    {
                        // printf("empty elist-->elist\n");
                ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1818 "syntax_anal.y"
    {
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
        ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1849 "syntax_anal.y"
    {
                        (yyval.expressValue)=copy_expr(temp_table);
                        tables_temp=free_temp(tables_temp);
                ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1854 "syntax_anal.y"
    {
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
        ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1880 "syntax_anal.y"
    {
                        (yyval.expressValue)=copy_expr(temp_table);
                        tables_temp=free_temp(tables_temp);
                                
                ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1888 "syntax_anal.y"
    {
			// printf("indexedelem-->indexed\n");
                ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1891 "syntax_anal.y"
    {
			// printf("indexed,indexedelem->indexed\n");
                ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1897 "syntax_anal.y"
    {
                        rf=1;
                        struct expr* temp=tables_temp;
                        while(temp->next!=NULL){
                                temp=temp->next;
                        }
                        temp_table=temp;
                        if((yyvsp[(2) - (5)].expressValue)->type==constint_e){
                                (yyvsp[(2) - (5)].expressValue)->sym=(struct hashnode *)malloc(sizeof(struct hashnode));
                                (yyvsp[(2) - (5)].expressValue)->sym->name=(char*)malloc(sizeof(999999));
                                sprintf((yyvsp[(2) - (5)].expressValue)->sym->name,"%d",temp_table->intConst);
                                //itoa($2->intConst,$2->sym->name,10);
                        }else if((yyvsp[(2) - (5)].expressValue)->type==conststring_e){
                                (yyvsp[(2) - (5)].expressValue)->sym=(struct hashnode *)malloc(sizeof(struct hashnode));
                                (yyvsp[(2) - (5)].expressValue)->sym->name=strdup((yyvsp[(2) - (5)].expressValue)->strConst);
                        }else if((yyvsp[(2) - (5)].expressValue)->type<8){
        
                        }
                        
                        (yyvsp[(2) - (5)].expressValue)->type=(yyvsp[(4) - (5)].expressValue)->type;
                        (yyvsp[(2) - (5)].expressValue)->intConst=(yyvsp[(4) - (5)].expressValue)->intConst;
                        (yyvsp[(2) - (5)].expressValue)->floatConst=(yyvsp[(4) - (5)].expressValue)->floatConst;
                        (yyvsp[(2) - (5)].expressValue)->boolConst=(yyvsp[(4) - (5)].expressValue)->boolConst;
                        if((yyvsp[(4) - (5)].expressValue)->strConst) (yyvsp[(2) - (5)].expressValue)->strConst=strdup((yyvsp[(4) - (5)].expressValue)->strConst);
                        else (yyvsp[(2) - (5)].expressValue)->strConst=NULL;
                        table_stack=creat_q(copy_expr((yyvsp[(2) - (5)].expressValue)),copy_expr((yyvsp[(4) - (5)].expressValue)));
                        table_stack->result=copy_expr(temp_table);
                        temp_table->index=add_e(copy_expr((yyvsp[(4) - (5)].expressValue)),temp_table->index);
                        emit(tablesetelem,table_stack->arg1,table_stack->arg2,table_stack->result,-1,yylineno);
                      
                        // printf("{expression:expression}\n");
                ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1932 "syntax_anal.y"
    {       
                        if(if_block==0 && while_block==0 && for_block==0){
                                scope_count++;

                                // printf("INCREASE SCOPE %d %d\n",scope_count,yylineno);
                        }
                ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1940 "syntax_anal.y"
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
                ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1956 "syntax_anal.y"
    {
			// printf("stmt stmt ....-->insideblock\n");
                ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1959 "syntax_anal.y"
    {
                        // printf("empty insideblock-->insideblock\n");
                ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1966 "syntax_anal.y"
    {
                        simple_block=0;
                        function_block++;
                        push_bcr_stack(&return_jump_list);
                        terms->name=strdup((yyvsp[(2) - (2)].stringValue));
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
                ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1997 "syntax_anal.y"
    {
                        push_local(0,&local_f);
                        push_local(formalf,&formal_f);
                        printf("%d:%d\n",formalf,formal_f->num);
                ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 2002 "syntax_anal.y"
    {
                        function_block--;
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=programfunc_e;
                        temp_expr->sym=pop_jump_stack(&fun_name_quad_list)->result->sym;
                        temp_expr->strConst=NULL;
                        temp_expr->sym->formal_num=formal_f->num;
                        printf("%s %d:%d\n",(yyvsp[(2) - (8)].stringValue), formalf,formal_f->num);
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
                        (yyval.expressValue)=copy_expr(temp_expr);
			// printf("function identifier (idlist){stmts}-->funcdef\n");
                ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 2035 "syntax_anal.y"
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
                ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 2059 "syntax_anal.y"
    {
                        push_local(0,&local_f);
                        push_local(formalf,&formal_f);
                ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 2063 "syntax_anal.y"
    {
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
                        (yyval.expressValue)=copy_expr(temp_expr);
			// printf("function (idlist){stmts}-->funcdef\n");
                ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 2096 "syntax_anal.y"
    {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=constint_e;
                        temp_expr->intConst=(float) (yyvsp[(1) - (1)].intValue);
                        temp_expr->strConst=NULL;
                        temp_expr->sym=NULL;
                        (yyval.expressValue)=copy_expr(temp_expr);
                        // printf("integer-->const\n");
                ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 2105 "syntax_anal.y"
    {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=constfloat_e;
                        temp_expr->floatConst=(yyvsp[(1) - (1)].realValue);
                        temp_expr->strConst=NULL;
                        temp_expr->sym=NULL;
                        (yyval.expressValue)=copy_expr(temp_expr);
			// printf("float-->const\n");
                ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 2114 "syntax_anal.y"
    {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=conststring_e;
                        temp_expr->strConst=strdup((yyvsp[(1) - (1)].stringValue));
                        temp_expr->sym=NULL;
                        (yyval.expressValue)=copy_expr(temp_expr);
			// printf("string-->const\n");
                ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 2122 "syntax_anal.y"
    {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=nil_e;
                        temp_expr->strConst="nil";
                        temp_expr->sym=NULL;
                        (yyval.expressValue)=copy_expr(temp_expr);
			// printf("nill-->const\n");
                ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 2130 "syntax_anal.y"
    {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=constbool_e;
                        temp_expr->boolConst=1;
                        temp_expr->strConst=NULL;
                        temp_expr->sym=NULL;
                        (yyval.expressValue)=copy_expr(temp_expr);
			// printf("true-->const\n");
                ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 2139 "syntax_anal.y"
    {
                        temp_expr=(struct expr*) malloc(sizeof(struct expr));
                        temp_expr->type=constbool_e;
                        temp_expr->boolConst=0;
                        temp_expr->strConst=NULL;
                        temp_expr->sym=NULL;
                        (yyval.expressValue)=copy_expr(temp_expr);
			// printf("false-->const\n");
                ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 2150 "syntax_anal.y"
    {           

                        formalf=0;
                        terms->name=strdup((yyvsp[(1) - (1)].stringValue));
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
                ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 2175 "syntax_anal.y"
    {
                        terms->name=strdup((yyvsp[(3) - (3)].stringValue));
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
                ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 2196 "syntax_anal.y"
    {
                        formalf=0;
                        // printf("empty idlist-->idlist\n");
                ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 2204 "syntax_anal.y"
    {
                        if_block++; 
                ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 2207 "syntax_anal.y"
    {
                        // printf("%s\n",$3);
                        emit(if_eq,(yyvsp[(4) - (5)].expressValue),true_expr,NULL,quad_count+2,yylineno);
                        if_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                        push_jump_stack(if_jump,&if_jump_list);
                ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 2214 "syntax_anal.y"
    {
			// printf("if(expression) stmt-->ifstmt\n");
                        if_block--;
                        if_else=pop_jump_stack(&if_jump_list);
                        if_else->label=quad_count;
                ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 2222 "syntax_anal.y"
    {
                        if_block++;
                        if(if_else!=NULL) if_else->label=quad_count+1;
                        else_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                        push_jump_stack(else_jump,&else_jump_list);
                ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 2229 "syntax_anal.y"
    {
			if_block--;
                        pop_jump_stack(&else_jump_list)->label=quad_count;
                        // printf("if(expression) stmt else stmt-->ifstmt\n");
                ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 2236 "syntax_anal.y"
    {
                        while_block++;
                        push(quad_count,&loop_jump_list);
                        push_bcr_stack(&break_jump_list);
                ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 2241 "syntax_anal.y"
    {
                        emit(if_eq,(yyvsp[(4) - (5)].expressValue),true_expr,NULL,quad_count+2,yylineno);
                        while_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                        push_jump_stack(while_jump,&while_jump_list);
                ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 2246 "syntax_anal.y"
    {
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
                ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 2263 "syntax_anal.y"
    {
                        for_block++;
                ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 2266 "syntax_anal.y"
    {
                        push(quad_count,&loop_jump_list);
                        push_bcr_stack(&break_jump_list);
                ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 2270 "syntax_anal.y"
    {
                        for_jump=emit(if_eq,(yyvsp[(7) - (7)].expressValue),true_expr,NULL,quad_count+2,yylineno);
                        push_jump_stack(for_jump,&for_true_jump_list);
                        for_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                        push_jump_stack(for_jump,&for_false_jump_list);
                ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 2276 "syntax_anal.y"
    {
                push(quad_count,&increment_jump_list);
        ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 2279 "syntax_anal.y"
    {
                        pop_jump_stack(&for_true_jump_list)->label=quad_count+1;
                        emit(jump,NULL,NULL,NULL,pop(&loop_jump_list),yylineno);
                ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 2283 "syntax_anal.y"
    {
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
                ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 2299 "syntax_anal.y"
    {
                        if(function_block>=1){
                                emit(ret,NULL,NULL,NULL,-1,yylineno);
                                return_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                                //EDWWWW
                                push_jump_stack(return_jump,&(return_jump_list->head));
                        }
                        // printf("return-->returnstmt\n");
                ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 2308 "syntax_anal.y"
    {
                        if(function_block>=1){
                                emit(ret,NULL,NULL,copy_expr((yyvsp[(2) - (2)].expressValue)),-1,yylineno);
                                return_jump=emit(jump,NULL,NULL,NULL,-1,yylineno);
                                // EDWWW
                                // if(return_jump_list->head==NULL){
                                //         return_jump_list->head = (struct jump_stack*) malloc(sizeof(struct jump_stack));
                                //         return_jump_list->head->next=NULL;
                                // } 
                                push_jump_stack(return_jump,&(return_jump_list->head));
                        }
                        // printf("return expression-->returnstmt\n");
                ;}
    break;



/* Line 1455 of yacc.c  */
#line 4404 "syntax_anal.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 2323 "syntax_anal.y"

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


