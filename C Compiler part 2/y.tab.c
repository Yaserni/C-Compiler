/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYSTYPE struct node*



typedef struct node{
	char* token;
	struct node *left;
	struct node *mid1;
	struct node *mid2;
	struct node *mid3;
	struct node *right;
	
} node;


typedef struct scope{

    struct scope* next_value;
    char* name;
    int is_function;
    char* type;
	char  func_args[50][50];
    
}scope;


typedef struct ns 
{
    struct ns *next;
    struct scope *sym ;
   
     int num;    
}ns;


void ifs_type(node* s,ns**head);
void return_st(node*,ns**,char*);
int sizeof_funcargs(char x[50][50]);
void set_theargs(node*,scope*);
void help1(scope*,char*,int);
void take_care_of_st (node*s,ns**head,node*);
scope* find_in_scope(char*,ns*);
void assig_check(node*,ns*);
void stcheck(node*tree,ns*head);
node* mknode(char* token,node* left,node* mid1,node* mid2,node* mid3, node* right);
void Printtree(node* tree,int tab);
int isTerminal(node* tree);
int AllChildTerminal(node* tree);
node* mkleaf(char* token);
node* mk1son(char* token,node* left);
node* mk2son(char* token,node* left,node* mid1);
node* mk3son(char* token,node* left,node* mid1,node* mid2);
node* mk4son(char* token,node* left,node* mid1,node* mid2,node* mid3);
void scantree(node*,ns**);
ns *pop(ns**);
void push(ns*,ns**);
void push_scope(scope*,ns*);
scope* find(char*,ns*);
void print_stack(ns*);
scope*make_scope(char*,int,char*);
void set_all_args(node*,ns*);
void set_all_vars(node*,ns*,ns*);
void take_care_of_body(node*,node*,ns**,node*);
void scanTree(node*,ns**);
scope *top(ns*);
char* checkexptype(node*,ns*);
int func_call_st(node*,ns*);
void loops_check(node*,ns**);
void takest2(node*,ns**);
int yyerror(/*const char *msg*/);

extern int yylex();
extern int yylineno;
extern char *yytext;
static int c=0;
node*tree;

#line 102 "y.tab.c"

#if ! defined(YYSTYPE) && ! defined(YYSTYPE_IS_DECLARED)
/* Default: YYSTYPE is the semantic value type. */
typedef int YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define ID 257
#define FUNCTION 258
#define INT 259
#define CHAR 260
#define SEMI 261
#define COMA 262
#define BP 263
#define EP 264
#define IF 265
#define SBLOCK 266
#define EBLOCK 267
#define REAL 268
#define REALP 269
#define INTP 270
#define BOOL 271
#define CHARP 272
#define EQ 273
#define VAR 274
#define INT_NUM1 275
#define INT_NUM2 276
#define REAL_NUM1 277
#define REAL_NUM2 278
#define REAL_NUM3 279
#define REAL_NUM4 280
#define STRING 281
#define BSI 282
#define ESI 283
#define STRING_VAL 284
#define OR 285
#define PLUS 286
#define MINUS 287
#define MULT 288
#define DIV 289
#define EQEQ 290
#define BIG 291
#define BIGEQ 292
#define SMALL 293
#define SMALLEQ 294
#define SHIFT 295
#define NOTEQ 296
#define NOT 297
#define WHILE 298
#define FOR 299
#define DO 300
#define RETURN 301
#define AND 302
#define VOID 303
#define MAIN 304
#define N 305
#define TRUE 306
#define FALSE 307
#define C_LITTER 308
#define ABS 309
#define IFX 310
#define ELSE 311
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    3,    2,    2,    7,    6,    4,   12,
   12,   11,   11,   11,   10,   10,   10,   10,   10,   10,
   10,    9,    9,   16,   16,   17,   17,    5,   18,   18,
   19,   20,   20,   20,   22,   24,   24,   24,   24,   23,
   25,   25,   25,   25,   21,   21,   21,   21,   21,   21,
   31,   31,   31,   31,   31,   31,   26,   26,   26,   13,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   14,   14,   14,   14,   30,   30,   15,   15,   27,
   28,   28,   28,   28,   28,   33,   33,   32,   32,   32,
   32,   29,   29,   29,   29,   29,   29,   34,   35,    8,
};
static const YYINT yylen[] = {                            2,
    1,    2,    1,    9,    1,    1,    8,    9,    0,    1,
    1,    3,    5,    6,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    4,    3,    3,    1,    1,    2,    1,
    2,    1,    1,    0,    3,    3,    3,    5,    5,    2,
    6,    6,    8,    8,    2,    4,    2,    2,    2,    0,
    1,    1,    1,    1,    1,    1,    4,    7,    5,    3,
    3,    3,    3,    3,    3,    3,    3,    1,    3,    1,
    3,    3,    3,    3,    1,    1,    1,    1,    3,    1,
    4,    2,    2,    2,    2,    7,    6,    3,    1,    2,
    7,    5,   12,    9,    7,    1,    0,    1,    1,    1,
    1,    7,    5,   11,   11,    9,    9,    3,    3,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    1,    0,    3,    5,    6,   15,   16,   17,
   18,   19,   20,   21,    0,    0,    2,  110,    0,    0,
    0,    9,    0,    0,    0,   23,    0,    0,   22,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   28,   30,    0,   32,   33,    0,    0,   25,    0,
    0,    0,    0,    0,   40,   29,    7,    0,    0,    0,
    0,    0,    0,    0,   31,    0,    0,    0,    0,   26,
   24,    0,    0,    4,    0,   35,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   45,   47,   48,   49,
    0,   51,   52,   53,   54,   55,   56,   80,    0,    0,
    0,    0,   75,   77,   78,   76,    0,    0,    0,   10,
   11,   68,    8,    0,    0,    0,    0,    0,    0,   90,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   83,    0,    0,    0,   12,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   37,   36,    0,    0,    0,   46,    0,    0,
    0,    0,    0,    0,    0,    0,   57,    0,   69,   79,
    0,    0,    0,    0,   64,    0,    0,    0,    0,   65,
   72,   73,   66,   74,   67,   71,    0,    0,    0,    0,
    0,    0,   98,   99,  101,  100,    0,   59,    0,  103,
  108,    0,    0,    0,    0,    0,    0,    0,   13,    0,
    0,   81,   39,   38,   42,   41,    0,    0,    0,    0,
    0,    0,    0,   87,    0,    0,   88,   14,    0,    0,
    0,   95,  102,    0,    0,    0,   86,   58,   44,   43,
    0,    0,    0,    0,    0,   94,    0,    0,  106,  107,
    0,    0,    0,   96,    0,  104,  105,   93,
};
static const YYINT yydgoto[] = {                          2,
    3,   40,    5,   25,   41,    6,    7,  118,   27,   28,
   73,  172,  110,  111,  173,   29,   34,   42,   43,   79,
   65,   45,   46,   76,   55,   66,   80,   67,   68,   69,
  112,  197,  255,  126,  127,
};
static const YYINT yysindex[] = {                      -232,
   82,    0,    0, -232,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -246, -237,    0,    0, -230, -220,
 -215,    0,  558,  558, -209,    0, -203, -237,    0, -187,
 -181, -239, -171, -156, -239, -239,   96,  564, -237, -239,
 -152,    0,    0,  -63,    0,    0, -237,  564,    0, -184,
 -127, -237, -237, -157,    0,    0,    0, -122, -251, -237,
 -120, -116, -118, -206,    0,  -63,  -63,  -63,  -63,    0,
    0,   24, -115,    0, -212,    0, -117,   24,  -63, -114,
 -113,   24, -240, -251,   24,   24,    0,    0,    0,    0,
   24,    0,    0,    0,    0,    0,    0,    0,   24,   24,
   24,   24,    0,    0,    0,    0, -237, -238,  212,    0,
    0,    0,    0, -251, -237,   24, -111, -119,  357,    0,
  -63,   24,  375,  564, -112,  -99,  -96,  -93, -236,  231,
  468,  393,  519,   32,  519,    0, -133,  -46,   24,    0,
   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,
   24,   24,    0,    0,  153, -179,  118,    0,  249,  124,
 -237,   24,   24,   24, -109,  -11,    0,  -94,    0,    0,
  -84,  339,  -82,  486,    0,  519,  519,   32,   32,    0,
    0,    0,    0,    0,    0,    0, -251, -237, -251, -237,
 -104, -251,    0,    0,    0,    0, -128,    0, -251,    0,
    0,  504,  267,  285,  -78,  -77,  -74,   24,    0,   24,
  -70,    0,    0,    0,    0,    0, -165,  -75, -144,  -71,
 -237, -237,   24,    0,  -68,  303,    0,    0, -251, -237,
 -110,    0,    0,  -67,  -66,  411,    0,    0,    0,    0,
  168,  -61,  171,  -53, -251,    0, -251, -251,    0,    0,
 -184,  -55,  -54,    0,  -51,    0,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  121, -154,    0,  104,  121,    0,    0,    0,  -79,
    0,    0,    0, -245,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  121,    0,
    0,    0,    0,    0,    0, -245, -245, -245, -245,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -245,    0,
    0,    0,    0,  121,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  321,    0,    0,
    0,    0,    0,  -79,    0,    0,    0,  189,    0,    0,
 -245,    0,    0,    0,    0,    0,    0,    0,  321,    0,
    0,    0,   76,  201,  110,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -64,    0,    0,    0,  458,  463,  429,  447,    0,
    0,    0,    0,    0,    0,    0,  -79,    0,  -79,    0,
    0,  121,    0,    0,    0,    0,  -10,    0,  121,    0,
    0, -145,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -79,    0,
   48,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -79,    0,  121,  121,    0,    0,
  -43,    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  210,   62,    0,    0,   88,    0,    0,  -15,  203,    3,
  -12,  -13,    0,    0, -150,  192,  196,  204,    0,  -30,
  102,    0,    0, -107, -183, -148,  -81, -142, -129, -121,
    0, -139,    0,    0, -147,
};
#define YYTABLESIZE 836
static const YYINT yytable[] = {                         20,
   21,   44,  128,   16,   44,   44,  216,  154,  193,   44,
   18,  193,   33,  201,  194,  207,   18,  194,   37,   18,
  200,   50,   38,   54,  138,    1,  166,  195,   64,   39,
  195,   33,   22,  124,   38,  196,   20,   75,  196,   16,
   53,   39,   23,  139,   81,  139,  240,   24,  114,  115,
   64,   64,   64,   64,   31,   50,  108,   19,  109,  227,
  116,    4,   32,   64,  119,    4,   85,  125,  123,  129,
  193,  130,  131,  234,  235,   86,  194,  132,   35,  232,
  214,  189,  190,  153,   36,  133,  134,  135,  136,  195,
   47,  137,  193,  191,  193,  229,  230,  196,  194,   75,
  194,  246,  155,  249,   48,   64,   27,   49,  159,   27,
  218,  195,   18,  195,   57,  109,   72,  220,  109,  196,
   58,  196,   50,   51,   77,  174,  161,  175,  176,  177,
  178,  179,  180,  181,  182,  183,  184,  185,  186,   74,
   78,   64,   82,   60,   64,  125,   83,   84,  202,  203,
  204,  113,  121,   61,   62,   63,  213,  117,  215,  122,
  162,  163,  139,  251,  164,  252,  253,   87,   88,   89,
   90,  156,   75,  165,   54,  170,  209,   34,  208,  217,
  120,  211,  219,  224,  223,   34,   34,   34,  205,  225,
  228,  231,  237,   18,  226,  233,  242,  243,  239,   89,
  241,   58,   59,   64,  247,  125,  125,  250,   34,  236,
   18,  256,  257,   17,   54,  258,   91,  171,   34,   34,
   34,   34,  158,   97,   60,   64,   30,   64,   92,   93,
   94,   95,   96,   97,   61,   62,   63,   98,  254,   71,
   99,  100,   70,   56,    0,   18,   92,    0,  101,    0,
  102,   91,  206,    0,   92,   92,   92,    0,  103,  104,
  105,  106,  107,   92,   93,   94,   95,   96,   97,    0,
    0,    0,   98,    0,    0,   99,  100,   92,    0,    0,
   18,    0,    0,  101,    0,  102,   91,   92,   92,   92,
   92,    0,    0,  103,  104,  105,  106,  107,   92,   93,
   94,   95,   96,   97,   91,    0,    0,   98,    0,    0,
   99,  100,   91,   91,   91,    0,  141,    0,  101,    0,
  102,  146,  147,  148,  149,  150,    0,  151,  103,  104,
  105,  106,  107,  152,    0,   91,   84,   84,    0,   84,
    8,    9,    0,    0,    0,   91,   91,   91,   91,   10,
   11,   12,   13,   14,    8,    9,    0,    0,   84,    0,
   34,   84,   84,   10,   11,   12,   13,   14,   34,   34,
   85,   85,    0,   85,   18,    0,    0,   34,    0,    0,
   18,    0,   58,  192,   15,   34,   34,   34,   58,  199,
    0,   34,   85,    0,    0,   85,   85,    0,   52,    0,
    0,   34,   34,   34,   34,   60,    0,    0,   34,    0,
    0,   60,    0,  187,  188,   61,   62,   63,   34,   34,
   34,   61,   62,   63,   18,    0,    0,   18,    0,    0,
    0,    0,   58,  245,    0,   58,  248,  141,  142,  143,
  144,  145,  146,  147,  148,  149,  150,    0,  151,   70,
   70,    0,   70,    0,  152,   60,    0,    0,   60,    0,
    0,   82,   82,    0,   82,   61,   62,   63,   61,   62,
   63,   70,  140,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   82,   70,    0,   82,   82,   82,   82,
   70,  167,    0,    0,    0,    0,  141,  142,  143,  144,
  145,  146,  147,  148,  149,  150,    0,  151,    0,  198,
    0,    0,    0,  152,    0,  141,  142,  143,  144,  145,
  146,  147,  148,  149,  150,    0,  151,  221,    0,    0,
    0,    0,  152,  141,  142,  143,  144,  145,  146,  147,
  148,  149,  150,    0,  151,  222,    0,    0,    0,    0,
  152,  141,  142,  143,  144,  145,  146,  147,  148,  149,
  150,    0,  151,  238,    0,    0,    0,    0,  152,  141,
  142,  143,  144,  145,  146,  147,  148,  149,  150,    0,
  151,   70,    0,    0,    0,    0,  152,  141,  142,  143,
  144,  145,  146,  147,  148,  149,  150,    0,  151,    0,
  210,    0,    0,    0,  152,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,    0,   70,    0,    0,    0,
  157,    0,   70,  141,  142,  143,  144,  145,  146,  147,
  148,  149,  150,    0,  151,    0,    0,    0,  160,    0,
  152,  141,  142,  143,  144,  145,  146,  147,  148,  149,
  150,    0,  151,    0,    0,    0,  169,    0,  152,  141,
  142,  143,  144,  145,  146,  147,  148,  149,  150,    0,
  151,    0,    0,    0,  244,    0,  152,  141,  142,  143,
  144,  145,  146,  147,  148,  149,  150,    0,  151,   60,
   60,    0,   60,    0,  152,  141,  142,  143,  144,  145,
  146,  147,  148,  149,  150,    0,  151,   63,   63,    0,
   63,   60,  152,    0,   60,   60,   60,   60,   61,   61,
    0,   61,    0,   62,   62,    0,   62,    0,    0,   63,
    0,    0,   63,   63,   63,   63,    0,    0,    0,    0,
   61,    0,    0,   61,   61,   62,    0,    0,   62,   62,
  168,    0,  141,  142,  143,  144,  145,  146,  147,  148,
  149,  150,    0,  151,    0,    0,    0,    0,  212,  152,
  141,  142,  143,  144,  145,  146,  147,  148,  149,  150,
    0,  151,    0,    0,    0,    0,    0,  152,  141,  142,
  143,  144,  145,  146,  147,  148,  149,  150,    0,  151,
    0,    0,    0,  141,    0,  152,  144,  145,  146,  147,
  148,  149,  150,    0,  151,    0,    8,    9,    0,    0,
  152,   26,    8,    9,    0,   10,   11,   12,   13,   14,
    0,   10,   11,   12,   13,   14,
};
static const YYINT yycheck[] = {                         15,
   16,   32,   84,    1,   35,   36,  190,  115,  157,   40,
  257,  160,   28,  161,  157,  166,  257,  160,  258,  257,
  160,  267,  274,   39,  263,  258,  263,  157,   44,  281,
  160,   47,  263,  274,  274,  157,   52,   53,  160,   37,
   38,  281,  263,  282,   60,  282,  230,  263,  261,  262,
   66,   67,   68,   69,  264,  301,   72,  304,   72,  210,
  273,    0,  266,   79,   78,    4,  273,   83,   82,   85,
  219,   85,   86,  221,  222,  282,  219,   91,  266,  219,
  188,  261,  262,  114,  266,   99,  100,  101,  102,  219,
  262,  107,  241,  273,  243,  261,  262,  219,  241,  115,
  243,  241,  116,  243,  261,  121,  261,  264,  122,  264,
  192,  241,  257,  243,  267,  261,  301,  199,  264,  241,
  265,  243,   35,   36,  282,  139,  124,  141,  142,  143,
  144,  145,  146,  147,  148,  149,  150,  151,  152,  267,
  263,  157,  263,  288,  160,  161,  263,  266,  162,  163,
  164,  267,  267,  298,  299,  300,  187,  275,  189,  273,
  273,  261,  282,  245,  261,  247,  248,   66,   67,   68,
   69,  283,  188,  267,  190,  309,  261,  257,  273,  284,
   79,  264,  311,  261,  263,  265,  266,  267,  298,  264,
  261,  267,  261,  257,  208,  267,  264,  264,  229,  264,
  311,  265,  266,  219,  266,  221,  222,  261,  288,  223,
  257,  267,  267,    4,  230,  267,  263,  264,  298,  299,
  300,  301,  121,  267,  288,  241,   24,  243,  275,  276,
  277,  278,  279,  280,  298,  299,  300,  284,  251,   48,
  287,  288,   47,   40,   -1,  257,  257,   -1,  295,   -1,
  297,  263,  264,   -1,  265,  266,  267,   -1,  305,  306,
  307,  308,  309,  275,  276,  277,  278,  279,  280,   -1,
   -1,   -1,  284,   -1,   -1,  287,  288,  288,   -1,   -1,
  257,   -1,   -1,  295,   -1,  297,  263,  298,  299,  300,
  301,   -1,   -1,  305,  306,  307,  308,  309,  275,  276,
  277,  278,  279,  280,  257,   -1,   -1,  284,   -1,   -1,
  287,  288,  265,  266,  267,   -1,  285,   -1,  295,   -1,
  297,  290,  291,  292,  293,  294,   -1,  296,  305,  306,
  307,  308,  309,  302,   -1,  288,  261,  262,   -1,  264,
  259,  260,   -1,   -1,   -1,  298,  299,  300,  301,  268,
  269,  270,  271,  272,  259,  260,   -1,   -1,  283,   -1,
  257,  286,  287,  268,  269,  270,  271,  272,  265,  266,
  261,  262,   -1,  264,  257,   -1,   -1,  257,   -1,   -1,
  257,   -1,  265,  266,  303,  265,  266,  267,  265,  266,
   -1,  288,  283,   -1,   -1,  286,  287,   -1,  303,   -1,
   -1,  298,  299,  300,  301,  288,   -1,   -1,  288,   -1,
   -1,  288,   -1,  261,  262,  298,  299,  300,  298,  299,
  300,  298,  299,  300,  257,   -1,   -1,  257,   -1,   -1,
   -1,   -1,  265,  266,   -1,  265,  266,  285,  286,  287,
  288,  289,  290,  291,  292,  293,  294,   -1,  296,  261,
  262,   -1,  264,   -1,  302,  288,   -1,   -1,  288,   -1,
   -1,  261,  262,   -1,  264,  298,  299,  300,  298,  299,
  300,  283,  261,  285,  286,  287,  288,  289,  290,  291,
  292,  293,  294,  283,  296,   -1,  286,  287,  288,  289,
  302,  261,   -1,   -1,   -1,   -1,  285,  286,  287,  288,
  289,  290,  291,  292,  293,  294,   -1,  296,   -1,  261,
   -1,   -1,   -1,  302,   -1,  285,  286,  287,  288,  289,
  290,  291,  292,  293,  294,   -1,  296,  261,   -1,   -1,
   -1,   -1,  302,  285,  286,  287,  288,  289,  290,  291,
  292,  293,  294,   -1,  296,  261,   -1,   -1,   -1,   -1,
  302,  285,  286,  287,  288,  289,  290,  291,  292,  293,
  294,   -1,  296,  261,   -1,   -1,   -1,   -1,  302,  285,
  286,  287,  288,  289,  290,  291,  292,  293,  294,   -1,
  296,  261,   -1,   -1,   -1,   -1,  302,  285,  286,  287,
  288,  289,  290,  291,  292,  293,  294,   -1,  296,   -1,
  262,   -1,   -1,   -1,  302,  285,  286,  287,  288,  289,
  290,  291,  292,  293,  294,   -1,  296,   -1,   -1,   -1,
  264,   -1,  302,  285,  286,  287,  288,  289,  290,  291,
  292,  293,  294,   -1,  296,   -1,   -1,   -1,  264,   -1,
  302,  285,  286,  287,  288,  289,  290,  291,  292,  293,
  294,   -1,  296,   -1,   -1,   -1,  264,   -1,  302,  285,
  286,  287,  288,  289,  290,  291,  292,  293,  294,   -1,
  296,   -1,   -1,   -1,  264,   -1,  302,  285,  286,  287,
  288,  289,  290,  291,  292,  293,  294,   -1,  296,  261,
  262,   -1,  264,   -1,  302,  285,  286,  287,  288,  289,
  290,  291,  292,  293,  294,   -1,  296,  261,  262,   -1,
  264,  283,  302,   -1,  286,  287,  288,  289,  261,  262,
   -1,  264,   -1,  261,  262,   -1,  264,   -1,   -1,  283,
   -1,   -1,  286,  287,  288,  289,   -1,   -1,   -1,   -1,
  283,   -1,   -1,  286,  287,  283,   -1,   -1,  286,  287,
  283,   -1,  285,  286,  287,  288,  289,  290,  291,  292,
  293,  294,   -1,  296,   -1,   -1,   -1,   -1,  283,  302,
  285,  286,  287,  288,  289,  290,  291,  292,  293,  294,
   -1,  296,   -1,   -1,   -1,   -1,   -1,  302,  285,  286,
  287,  288,  289,  290,  291,  292,  293,  294,   -1,  296,
   -1,   -1,   -1,  285,   -1,  302,  288,  289,  290,  291,
  292,  293,  294,   -1,  296,   -1,  259,  260,   -1,   -1,
  302,  264,  259,  260,   -1,  268,  269,  270,  271,  272,
   -1,  268,  269,  270,  271,  272,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 311
#define YYUNDFTOKEN 349
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ID","FUNCTION","INT","CHAR",
"SEMI","COMA","BP","EP","IF","SBLOCK","EBLOCK","REAL","REALP","INTP","BOOL",
"CHARP","EQ","VAR","INT_NUM1","INT_NUM2","REAL_NUM1","REAL_NUM2","REAL_NUM3",
"REAL_NUM4","STRING","BSI","ESI","STRING_VAL","OR","PLUS","MINUS","MULT","DIV",
"EQEQ","BIG","BIGEQ","SMALL","SMALLEQ","SHIFT","NOTEQ","NOT","WHILE","FOR","DO",
"RETURN","AND","VOID","MAIN","N","TRUE","FALSE","C_LITTER","ABS","IFX","ELSE",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : programe",
"programe : code",
"code : functions_list code",
"code : main",
"main : FUNCTION VOID MAIN BP no_args EP SBLOCK body EBLOCK",
"functions_list : functions",
"functions_list : procedures",
"procedures : FUNCTION VOID id BP p SBLOCK body EBLOCK",
"functions : FUNCTION type id BP p SBLOCK body return_stmt EBLOCK",
"no_args :",
"exp : binary",
"exp : unairy",
"return_stmt : RETURN exp SEMI",
"return_stmt : RETURN id BP EP SEMI",
"return_stmt : RETURN id BP listof_exp EP SEMI",
"type : INT",
"type : CHAR",
"type : REAL",
"type : REALP",
"type : INTP",
"type : BOOL",
"type : CHARP",
"p : m2",
"p : EP",
"m2 : type co SEMI m2",
"m2 : type co EP",
"co : id COMA co",
"co : id",
"body : fd",
"fd : functions_list fd",
"fd : vd",
"vd : dec st",
"dec : dec_var",
"dec : dec_string",
"dec :",
"dec_var : VAR type dec_1",
"dec_1 : id COMA dec_1",
"dec_1 : id SEMI dec",
"dec_1 : id EQ exp COMA dec_1",
"dec_1 : id EQ exp SEMI dec",
"dec_string : STRING dec_2",
"dec_2 : id BSI INT_NUM1 ESI COMA dec_2",
"dec_2 : id BSI INT_NUM1 ESI SEMI dec",
"dec_2 : id BSI INT_NUM1 ESI EQ STRING_VAL COMA dec_2",
"dec_2 : id BSI INT_NUM1 ESI EQ STRING_VAL SEMI dec",
"st : assig st",
"st : SBLOCK code_block EBLOCK st",
"st : IFS st",
"st : loops st",
"st : func_call st",
"st :",
"num : INT_NUM1",
"num : INT_NUM2",
"num : REAL_NUM1",
"num : REAL_NUM2",
"num : REAL_NUM3",
"num : REAL_NUM4",
"assig : id EQ exp SEMI",
"assig : id BSI exp ESI EQ exp SEMI",
"assig : MULT id EQ exp SEMI",
"binary : exp MULT exp",
"binary : exp PLUS exp",
"binary : exp MINUS exp",
"binary : exp DIV exp",
"binary : exp OR exp",
"binary : exp EQEQ exp",
"binary : exp SMALL exp",
"binary : exp NOTEQ exp",
"binary : num",
"binary : BP exp EP",
"binary : id",
"binary : exp AND exp",
"binary : exp BIG exp",
"binary : exp BIGEQ exp",
"binary : exp SMALLEQ exp",
"binary : N",
"binary : C_LITTER",
"binary : TRUE",
"binary : FALSE",
"binary : ABS id ABS",
"binary : STRING_VAL",
"binary : id BSI exp ESI",
"unairy : MULT exp",
"unairy : NOT exp",
"unairy : MINUS exp",
"unairy : SHIFT exp",
"func_call : id EQ id BP listof_exp EP SEMI",
"func_call : id EQ id BP EP SEMI",
"listof_exp : exp COMA listof_exp",
"listof_exp : exp",
"code_block : dec st",
"IFS : IF BP exp EP SBLOCK code_block EBLOCK",
"IFS : IF BP exp EP st2",
"IFS : IF BP exp EP SBLOCK code_block EBLOCK ELSE SBLOCK code_block rt EBLOCK",
"IFS : IF BP exp EP SBLOCK code_block EBLOCK ELSE st2",
"IFS : IF BP exp EP st2 ELSE st2",
"rt : return_stmt",
"rt :",
"st2 : assig",
"st2 : IFS",
"st2 : func_call",
"st2 : loops",
"loops : WHILE BP exp EP SBLOCK code_block EBLOCK",
"loops : WHILE BP exp EP st2",
"loops : FOR BP dec_loops SEMI exp SEMI assig_loops EP SBLOCK code_block EBLOCK",
"loops : FOR BP assig_loops SEMI exp SEMI assig_loops EP SBLOCK code_block EBLOCK",
"loops : FOR BP assig_loops SEMI exp SEMI assig_loops EP st2",
"loops : DO SBLOCK code_block EBLOCK WHILE BP exp EP SEMI",
"dec_loops : VAR type assig_loops",
"assig_loops : id EQ exp",
"id : ID",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 296 "parser.y"
#include "lex.yy.c"
int main()
{
 #ifdef YYDEBUG
  yydebug = 1;
  #endif
 ns*global=(ns*)malloc(sizeof(ns));
  
  yyparse();
 // scantree(tree,&global) ;
 printf("--------------------\n\n");
 printf("this  printf for debug reson \n");
  scanTree(tree,&global);
  printf("--------------------------\n\n");
  printf("this  printf for debug reson \n");
  print_stack(global);
  printf("--------------------------\n\n");

	//Printtree(tree,0);

 return 1;
}

node* mknode(char* token,node* left,node* mid1,node* mid2,node* mid3, node* right){
	node *newnode = (node*)malloc(sizeof(node));
   	//char *newstr = (char*)malloc(sizeof(token)+1);
   	//strcpy (newstr, token);
    newnode->token = token;//newstr;
	newnode->left=left;
	newnode->mid1=mid1;
	newnode->mid2=mid2;
	newnode->mid3=mid3;
	newnode->right=right;
	return newnode;
}
node* mkleaf(char* token)
{
	return mknode(token,NULL,NULL,NULL,NULL,NULL);
}
node* mk1son(char* token,node* left)
{
	return mknode(token,left,NULL,NULL,NULL,NULL);
}
node* mk2son(char* token,node* left,node* mid1)
{
	return mknode(token,left,mid1,NULL,NULL,NULL);
}
node* mk3son(char* token,node* left,node* mid1,node* mid2)
{
	return mknode(token,left,mid1,mid2,NULL,NULL);
}
node* mk4son(char* token,node* left,node* mid1,node* mid2,node* mid3)
{
	return mknode(token,left,mid1,mid2,mid3,NULL);
}



int isLeaf(node* tree){
	
	if(tree){
		return (tree->left == NULL) && (tree->mid1 == NULL) && (tree->mid2 == NULL) && (tree->mid3 == NULL) && (tree->right == NULL);
	}
	return 1;
}

int AllChildTerminal(node* tree){
	if(tree->left){
		if(isLeaf(tree->left)){
			if(tree->mid1){
				if(isLeaf(tree->mid1)){
					if(tree->mid2){
						if(isLeaf(tree->mid2)){
							if(tree->right){
								return isLeaf(tree->right);
							}else{
								return 1;
							}
						}else{
							return 0;
						}
					}else{
						return 1;
					}
				}else{
					return 0;
				}
			}else{
				return 1;
			}
		}else{
			return 0;
		}
	}else{
		return 1;
	}
}
			

void Printtree(node* tree,int tab){
	if(isLeaf(tree)){
		printf(" %s",tree->token);
		return;
	}
	
	if(strcmp("st",tree->token) && strcmp("VARIABLES",tree->token)){
		for(int i=0;i<tab;i++)
			printf("    ");
		printf("(%s",tree->token);
		
	}
	else{
		tab--;
	}
	
	if(tree->left){
		if(!isLeaf(tree->left) )
			printf("\n");

		Printtree(tree->left,tab+1);	
	}
				
	if(tree->mid1){
		if(!isLeaf(tree->mid1))
			printf("\n");	
		Printtree(tree->mid1,tab+1);

	}
				
	if(tree->mid2 ){
		if(!isLeaf(tree->mid2))
			printf("\n");
		Printtree(tree->mid2,tab+1);

	}
	if(tree->mid3 ){
		if(!isLeaf(tree->mid3))
			printf("\n");
		Printtree(tree->mid3,tab+1);

	}
				
	if(tree->right){
		if(!isLeaf(tree->right))
			printf("\n");
		Printtree(tree->right,tab+1);
	}
	
	if(strcmp("FUNCTION",tree->token) && strcmp("st",tree->token) || AllChildTerminal(tree)){
		if(!isLeaf(tree->left) || !isLeaf(tree->mid1) || !isLeaf(tree->mid2) || !isLeaf(tree->mid3) || !isLeaf(tree->right)){
			printf("\n");
			for(int i=0;i<tab;i++)
				printf("    ");
			printf(")");
		}else{
			printf(")\n");
			for(int i=0;i<tab;i++)
				printf("    ");
		}	
	}
	
}



void scanTree(node*tree,ns**head)
{
     node*temp=tree;
	 node *temp2=NULL;
	 if(strcmp(temp->token,".CODE")==0)
	 {
		 temp=temp->left;
	//	 printf("you in the ritght way \n");
		 if(strcmp(temp->token,".code")==0)
		 {
			 //temp=temp->left;
	//		 printf("you in the right way \n");
			  while(strcmp(temp->token,".MAIN")!=0)
			  {
	//			  printf("%s \n",temp->left->token);
				  temp2=temp->left;
				  //here i take care of for all function above the main (global function)
                      if(strcmp(temp2->token,".FUNCTION")==0)
					  {
						  
						 node*help=temp2;
					     scope*x=make_scope(help->left->token,1,help->mid2->token);
                    if(find_in_scope(temp2->left->token,*head)!=NULL)
				   { 
	//				 printf("error %s alredy declerd\n",x->name );
					  exit(0);
					    
				   }
						
						
						if(strcmp(help->mid1->token,".ARGS")==0)
					  	{
	//				 		  printf("in set args \n");
							 set_theargs(help->mid1,x);
			  			}   
						  push_scope(x,*head);
					      
						  
						   

						 //return_st(temp2->right,head,help->mid2->token); 
						  
						  take_care_of_body(temp2->mid3,temp2->mid1,head,temp2);
					     
						 
					  
					  }
					 
					 if(strcmp(temp2->token,".procedures")==0)
		           	 {
                  		node*help=temp2;
                 		scope*x=make_scope(help->left->token,1,"VOID");
						 
						 if(find_in_scope(temp2->left->token,*head)!=NULL)
				   		{ 
						 	printf("error %s alredy declerd\n",x->name );
					  		exit(0);
					    
				   		}
						
						
						
						
						if(strcmp(help->mid1->token,".ARGS")==0)
					  	{
					 		set_theargs(help->mid1,x);
			  			}
               			
						
						push_scope(x,*head);
						take_care_of_body(temp2->mid3,temp2->mid1,head,NULL);
		    	  	}
  //                 printf(" maybe herer 1 \n");
			      if(temp->mid1!=NULL)
				   	  {
						  temp=temp->mid1;
				      }
					  
			  
//			       printf(" maybe herer 2 \n");
			  }
			 
			 if(strcmp(temp->token,".MAIN")==0)
			  {
				  
				  
                 
				  scope*x=make_scope("MAIN",1,"VOID");
               	 
				  push_scope(x,*head);
				 
				  take_care_of_body(temp->mid3,temp->mid1,head,NULL);
                 

			  }
			

            
		 
		 
		 
		 }
		
		else if(strcmp(temp->token,".MAIN")==0)
			  {
				  
				 // node*p=mkleaf("(ARGS NONE)");
//				  printf("in first main \n");
				  //node*help=temp->left;
                 
				  scope*x=make_scope("MAIN",1,"VOID");
               	 
				  push_scope(x,*head);
				 
				  take_care_of_body(temp->mid3,temp->mid1,head,NULL);
                 

			  }


	 }

}

void take_care_of_body(node*body,node*p,ns**head,node*h)
{
    //printf("in take car of body %s \n",body->left->token);
//	printf("in body \n");
	ns*t=(ns*)malloc(sizeof(ns));
	t->next=NULL;
    t->sym=NULL;
	push(t,head);
	
	if(strcmp(p->token,".ARGS")==0)
	{ 
//		printf("in p \n");
		 set_all_args(p,t);

	}
    
  if(strcmp(body->left->token,".vd")==0)
  {
       	
		// printf("in .vd \n");
		node*temp=body->left;
		if(temp->left==NULL)
        {
           take_care_of_st(NULL,head,h);
		}  
		  
		else if(strcmp(temp->left->token,".VAR")==0 || strcmp(temp->left->token,".STRING")==0)
		  {
			  set_all_vars(temp->left,t,*head);
		      take_care_of_st(temp->mid1,head,h);
		  }
		 else if(strcmp(temp->left->token,".st")==0)
		 {
              take_care_of_st(temp->left,head,h);
		 }
		  
		  
           return;
	  }
   
  
   
   
   if(strcmp(body->left->token,".fd")==0)
  {
     // printf("in fd \n");
	  node*temp=body->left;
	  
	  while(strcmp(temp->token,".vd")!=0)
	  {
		  // printf("2\n");
		   if( strcmp(temp->left->token,".FUNCTION")==0)
			{
				
			 node*help=temp->left;
			 scope*x=make_scope(help->left->token,1,help->mid2->token);
			 
			  if(find_in_scope(help->left->token,*head)!=NULL)
				   { 
					 printf("error %s alredy declerd\n",x->name );
					  exit(0);
					    
				   }
			 
			 
			 
			 
			 if(strcmp(help->mid1->token,".ARGS")==0)
			  {
					 set_theargs(help->mid1,x);
			  }
             push_scope(x,t);
		//	 printf("3\n");
			 //return_st(help->right,head,help->mid2->token);
			 take_care_of_body(help->mid3,help->mid1,head,temp->left);
		//	 printf("4\n");
			}
			
			else if(strcmp(temp->left->token,".procedures")==0)
		       {
					node*help=temp->left;
             		scope*x=make_scope(help->left->token,1,"VOID");
					

			  if(find_in_scope(help->left->token,*head)!=NULL)
				   { 
					 printf("error %s alredy declerd\n",x->name );
					  exit(0);
					    
				   }


					if(strcmp(help->mid1->token,".ARGS")==0)
					{
					 set_theargs(help->mid1,x);
					}
        			push_scope(x,t);
					
					take_care_of_body(help->mid3,help->mid1,head,NULL);
		       }

          
		  // printf("5\n");
		  
		   if(temp->mid1!=NULL)
		   {
		      temp=temp->mid1;
			  //printf("%s\n",temp->token);
           }
		
	  }
	 



	 
	  if(strcmp(temp->token,".vd")==0)
	  {
         
		 if(temp->left==NULL)
            {
                take_care_of_st(NULL,head,h);
			}  
		  
		  else if(strcmp(temp->left->token,".VAR")==0 || strcmp(temp->left->token,".STRING")==0)
		  {
			  set_all_vars(temp->left,t,*head);
		      take_care_of_st(temp->mid1,head,h);
		  }
		  else if( strcmp(temp->left->token,".st")==0)
		  {
                   take_care_of_st(temp->left,head,h);
		  }
		  
		  
           return;
	  }


  
  
  
  }
  
  
  


}

void set_all_args(node*p,ns*t)
{
    node*temp=p->left;
	node*temp1=temp;
	char* old;
	while(1)
	{
           if(strcmp(temp->token,".m2")==0)
		   {
			   old=temp->left->token;
			   temp1=temp->mid1;
		   }
		   
		   if(strcmp(temp1->token,".co")==0)
		   {
                node*help=temp1;
			    while(1)
				{
				  scope *x=make_scope(help->left->token,0,old);
                  if(find_in_scope(help->left->token,t)!=NULL)
                   {
					   printf("error %s alrdey dec \n",help->left->token);
						exit(0);
				   }				  
				  
				  push_scope(x,t);
                  
				  if(strcmp(help->mid1->token,".co")==0)
				  {
                        help=help->mid1;

				  }
				  
				  else{
					  	scope *x=make_scope(help->mid1->token,0,old);
                    
					 	if(find_in_scope(help->mid1->token,t)!=NULL)
                      	{
					   		printf("error %s alrdey dec \n",help->mid1->token);
                         	exit(0); 
				       	}
					
					push_scope(x,t);
					break;


				  }
			   
			   
			   }

		   }
		   
			else{
                  scope*x=make_scope(temp->mid1->token,0,old);
				 // printf("%s \n",temp->mid1->token);
				  
				  if(find_in_scope(temp->mid1->token,t)!=NULL)
                   {
					   printf("error %s alrdey dec \n",temp->mid1->token);
						exit(0);
				   }
				  push_scope(x,t);

			}
			
           
		   if(temp->mid2!=NULL){
                temp=temp->mid2;
		   }
		   else{
			   break;
		   }       
	        
	}


}

scope* find (char* name,ns*head_stack)
{
  
 ns*temp=NULL;
 scope*temp1=NULL;    
 temp=head_stack; 

 while(temp!=NULL){
    temp1=temp->sym; 
   while(temp1!=NULL){  
        if(strcmp(name,temp1->name)==0)
              return temp1;  
        temp1=temp1->next_value;
     }
   temp=temp->next;
}
  return NULL;
}



void push(ns *x,ns **head_stack )
{
       ns*temp=(*head_stack);
       *head_stack = x;
       (*head_stack)->next=temp;       

}



ns* pop(ns**head)
{
      ns *temp=(*head);
      *head=temp->next;    
      temp->next=NULL;
	  return temp; 
}


void push_scope(scope* x,ns*t)
{
        
          if(t->sym==NULL)
           {
               t->sym=x;
           
           }	
           else{

        scope*temp=t->sym;
	while(temp->next_value!=NULL)
       {
            temp=temp->next_value;
       }
     
      temp->next_value=x;

     }				


	 

}

void print_stack(ns*head)
{
  
   ns*temp=head;
   scope*temp1=NULL;
     int c=0;
    while(temp!=NULL){
       temp1=temp->sym;
	   printf(" the num is %d : \n",c);
		 c++;
	   while( temp1!=NULL){

		  
		   printf(" %s  %s  %d   \n",temp1->type,temp1->name,temp1->is_function);
		   
		   if(temp1->is_function ==1 && sizeof_funcargs(temp1->func_args)>0)
		   {
		   	printf("the args of %s is \n",temp1->name);
		    for(int i=0;i<sizeof_funcargs(temp1->func_args);i++)
			  printf("%s\n",temp1->func_args[i]);
		   }
		   temp1=temp1->next_value;
		   
	   }
         
        temp=temp->next;
	}


}

scope* make_scope(char*name,int a,char*type)
{
      scope*x=(scope*)malloc(sizeof(scope));
       x->name=name;
       x->is_function=a;
       x->type=type;
          
       return x;
}




void set_all_vars(node*help,ns*a,ns*head)
{
     
	 
	 	  node*temp2=help;
	  char*old;
	  while(1)
        {
           
			 if(strcmp(temp2->token,".STRING")==0)
             {
                  old="STRING";
                  temp2=temp2->left;
             }
            
             
			if(strcmp(temp2->token,".dec_21")==0 || strcmp(temp2->token,"=s1")==0)
               {

                  scope *x=make_scope(temp2->left->token,0,"STRING");
                   if(find_in_scope(x->name,a)!=NULL)
				   { 
					 printf("error %s alredy declerd\n",x->name );
					  exit(0);
					    
				   }
				  push_scope(x,a);
                  

               }
                if(strcmp(temp2->token,".dec_22")==0 || strcmp(temp2->token,"=s2")==0 ) 
               {

                  scope *x=make_scope(temp2->left->token,0,"STRING");
                  if((find_in_scope(x->name,a)!=NULL))
				   { 
					 printf("error %s alredy declerd\n",x->name );
					  exit(0);
					    
				   }
				  push_scope(x,a);
                  
                  if(temp2->mid1==NULL)
				  {
                         break;
                  }
				  

               }

			   
               if(strcmp(temp2->token,".VAR")==0){
                  
		          old=temp2->left->token;
                  temp2=temp2->mid1;
				  
                  


		       }
           if(strcmp(temp2->token,".dec_11")==0)
           {
               scope *x=make_scope(temp2->left->token,0,old);
               if((find_in_scope(x->name,a)!=NULL))
				   { 
					 printf("error %s alredy declerd\n",x->name );
					  exit(0);
					    
				   }
			  push_scope(x,a);

          

           }
           if(strcmp(temp2->token,".dec_12")==0)
           {
               
              scope *x=make_scope(temp2->left->token,0,old);
               if((find_in_scope(x->name,a)!=NULL))
				   { 
					 printf("error %s alredy declerd\n",x->name );
					 exit(0);
					    
				   }
			  push_scope(x,a);
              
                  if(temp2->mid1==NULL)
				  {
                         break;
                   }
				


           }

		   
		   if(strcmp(temp2->token,"=v1")==0)
		   {
              if((strcmp(old,"CHARP")==0 || strcmp(old,"INTP")==0 || strcmp(old,"REALP")==0 )&& strcmp(temp2->mid2->token,"NULL")==0)
			  {
                   
//				   printf("in null check 1");
				    
					
                           

			  }

			  else if(strcmp(old,checkexptype(temp2->mid2,head))!=0)
		        { 
					printf("unmatch type 1\n");
					exit(0);

				}
			   
			   scope *x=make_scope(temp2->left->token,0,old);
               if((find_in_scope(x->name,a)!=NULL))
				   { 
					 printf("error %s alredy declerd\n",x->name );
					 exit(0);
					    
				   }
			  push_scope(x,a);



		   }
		   if(strcmp(temp2->token,"=v2")==0)
            { 
				if((strcmp(old,"CHARP")==0 || strcmp(old,"INTP")==0 || strcmp(old,"REALP")==0) && strcmp(temp2->mid2->token,"NULL")==0)
			  {
                   
	//			   printf("in null check \n");
				    
                           

			  }
				
				else if(strcmp(old,checkexptype(temp2->mid2,head))!=0)
		        { 
					
					printf("unmatch type 2 \n");
	//				printf("%s , %s  \n",old,checkexptype(temp2->mid2,head));
					exit(0);

				}
				
			   scope *x=make_scope(temp2->left->token,0,old);
               if((find_in_scope(x->name,a)!=NULL))
				   { 
					 printf("error %s alredy declerd\n",x->name );
					 exit(0);
					    
				   }
			    push_scope(x,a);
              
                  if(temp2->mid1==NULL)
				  {
                         break;
                   }
			
			  


			}

		   


           
           temp2=temp2->mid1;


        }


 //printf("exit set var \n");

}


void take_care_of_bodyst(node*temp,ns**head)
{
    
	ns*t=(ns*)malloc(sizeof(ns));
	t->next=NULL;
    t->sym=NULL;
	push(t,head);
	
	
	if(temp->left==NULL)
     {
         take_care_of_st(NULL,head,NULL);
	 }  
		  
	else if(strcmp(temp->left->token,".VAR")==0 || strcmp(temp->left->token,".STRING")==0)
	{
			  set_all_vars(temp->left,t,*head);
		      take_care_of_st(temp->mid1,head,NULL);
	}
	
	else if(strcmp(temp->left->token,".st")==0)
	{
            take_care_of_st(temp->left,head,NULL);
	}
		  
		  
    return;
}



int yyerror()
{
   printf("Unaccepted \nline %d \n unexpected: %s",yylineno,yytext);
  return 0;
}


scope* top(ns* head)
{
	return head->sym;
}


char* checkexptype(node* exp,ns* head)
{
//	printf("in checkexptype\n");
	
	if(!strcmp(exp->token,"TRUE") || !strcmp(exp->token,"FALSE"))
		return "BOOL";

	if(!strcmp(exp->token,"int"))
		return "INT";
	
	if(!strcmp(exp->token,"real"))
	{
		printf("in if of exp \n");
		return "REAL";

	}	
	if(!strcmp(exp->token,"NULL"))
		return "NULL";

	if(!strcmp(exp->token,"id"))
	{
		scope* x = find(exp->left->token,head);
		if(x==NULL)
		{
			printf("%s undeclared 2\n",exp->left->token);
			exit(0);
		}
		else return x->type;
	}

	if(!strcmp(exp->token,"at"))//line 196 
	{
		scope* x = find(exp->left->token,head);
		if(x==NULL)
		{
			printf("%s undeclared3\n",exp->left->token);
			exit(0);
		}
		if(strcmp(x->type,"STRING")==0)
			return "CHAR";
		else
		{
			printf("the type of the %s is not string \n",x->name);
			exit(0);
		}
	}

	if(!strcmp(exp->token,"str"))
	{
		return "STRING";
	}

	if(!strcmp(exp->token,"ABS"))//line 196 
	{
		scope* x = find(exp->left->token,head);
		if(x==NULL)
		{
			printf("%s undeclared 1\n",exp->token);
			exit(0);
		}
		if(strcmp(x->type,"STRING")==0)
			return "INT";
		else
		{
			printf("the type of the %s is not string \n",x->name);
			exit(0);
		}
	}


	if(!strcmp(exp->token,"char"))
		return "CHAR";


	if((!strcmp(exp->token,"*")||!strcmp(exp->token,"-")||!strcmp(exp->token,"!")||!strcmp(exp->token,"&"))&& exp->mid1==NULL)
	{//unary expression
		if(!strcmp(exp->token,"*"))
		{
			char* left=checkexptype(exp->left,head);
			if(strcmp(left,"CHARP") && strcmp(left,"INTP") && strcmp(left,"REALP"))
			{
				printf("incompatible type , unexpected %s type \n",left);
				exit(0);
			}
			else {
			   if(strcmp(left,"CHARP")==0)
			        return "CHAR";
			   
			   if(strcmp(left,"INTP")==0)
			        return "INT";
			   if(strcmp(left,"REALP")==0)
			        return "REAL";
               			   
				
			}
		
		}
		if(!strcmp(exp->token,"&"))
		{
			char* left=checkexptype(exp->left,head);
			if(strcmp(left,"CHAR") && strcmp(left,"INT") && strcmp(left,"REAL"))
			{
				printf("incompatible type , unexpected %s type \n",left);
				exit(0);
			}
			else
			 {
			   if(strcmp(left,"CHAR")==0)
			        return "CHARP";
			   
			   if(strcmp(left,"INT")==0)
			        return "INTP";
			   if(strcmp(left,"REAL")==0)
			        return "REALP";
               			   
				
			}
		
		}
		if(!strcmp(exp->token,"!"))   
		{
				char* left=checkexptype(exp->left,head);
			if(strcmp(left,"BOOL"))
			{
				printf("incompatible type , unexpected %s type \n",left);
				exit(0);
			}
			else return left;
		}
		
		

	}
	
	
	if(strcmp(exp->token,"()")==0)
		return checkexptype(exp->left,head);
	
if(!strcmp(exp->token,"*")||!strcmp(exp->token,"-")||!strcmp(exp->token,"+")||!strcmp(exp->token,"/"))
	{//binary expression
		
		char* left=checkexptype(exp->left,head);
		char* right=checkexptype(exp->mid1,head);
		
		if(!strcmp(left,"INT") && !strcmp(right,"INT"))
			return "INT";
		else {
			if((!strcmp(left,"INT") && !strcmp(right,"REAL")) ||(!strcmp(left,"REAL")&&!strcmp(left,"REAL")) ||(!strcmp(right,"INT")&&!strcmp(left,"REAL")))
				return "REAL";
			else{
				if((!strcmp(left,"INTP")&&!strcmp(right,"INT"))||(!strcmp(left,"CHARP")&&!strcmp(right,"INT"))||(!strcmp(left,"REALP")&&!strcmp(right,"INT")))
					return left;
				if((!strcmp(right,"INTP")&&!strcmp(left,"INT"))||(!strcmp(right,"CHARP")&&!strcmp(left,"INT"))||(!strcmp(right,"REALP")&&!strcmp(left,"INT")))
					return right;
				else{
					printf(" 1 error incompatible type %s  %s \n",right,left);
					exit(0);
				}
			}
		}
	}
	if((exp->token,"==")||!strcmp(exp->token,"!="))
	{
		char* left=checkexptype(exp->left,head);
		char* right=checkexptype(exp->mid1,head);
		
		//printf(" left %s  right %s \n",left,right);
		if(strcmp(left,right)==0)
			return "BOOL";
		else
		{
			printf(" error cannot compare two diffirent types \n");
			

			exit(0);
		}
	}
	if(!strcmp(exp->token,"<")||!strcmp(exp->token,">")||!strcmp(exp->token,">=")||!strcmp(exp->token,"<="))
	{
		char* left=checkexptype(exp->left,head);
		char* right=checkexptype(exp->mid1,head);
		if((!strcmp(left,"INT")&&!strcmp(right,"REAL")) || (!strcmp(left,"INT")&&!strcmp(right,"INT")) ||(!strcmp(left,"REAL")&&!strcmp(left,"REAL")) ||(!strcmp(right,"INT")&&!strcmp(left,"REAL")))
			return "BOOL";
		else
		{
			printf("error, illegal to compare between %s and %s \n",left,right);
			exit(0);
		}
	}
	if(!strcmp(exp->token,"&&")||!strcmp(exp->token,"||"))
	{//comparing operations 
		char* left=checkexptype(exp->left,head);
		char* right=checkexptype(exp->mid1,head);
		if(!strcmp(left,"BOOL") && strcmp(right,"BOOL"))
		{
			return "BOOL";
		}
	}
  
  
   



  

}






void assig_check(node*z,ns*head)
{
   
  
   
    scope* x=find(z->left->token,head);
				
		
		if(x==NULL)
		{
		   printf(" %s is undec  \n", z->left->token);
		   exit(0);
		}
   
if(x->is_function==1)
{
   printf(" %s is not variable  \n", z->left->token);
		   exit(0);


}



   if(strcmp(z->token,"=")==0)
    {
         
	     
        char* s=checkexptype(z->mid1,head);
        
          if(strcmp(s,x->type)!=0)
		  {
			  printf("the type of the  var is unmatch to value \n");
			  exit(0);
		  }
    
	
	}
	
	if(strcmp(z->token,"=s")==0)
	{
	    
		
		if(strcmp(x->type,"STRING")!=0)
		{
			
			printf("the %s must be string \n",x->name);
			exit(0);
		}    
		
		
		char*s=checkexptype(z->mid1,head);
		
		if(strcmp(s,"INT")!=0)
		{
             printf("index must be int \n");
			 exit(0);

		}
		 
		 s=checkexptype(z->mid2,head);
		 if(strcmp(s,"CHAR")!=0)
		 {
			 printf("in string you can only assim char \n");
			 exit(0);
		 }


	
	}


	if(strcmp(z->token,"=*")==0)
	{
        char *s=checkexptype(z->mid1,head);
		
		if(strcmp(x->type,"INTP")==0)
		{
                 
			 if(strcmp(s,"INT")!=0)
			 {
                 printf("error : the value of the exp not match to type of the var \n");
				 exit(0);
			 }
			return;

		}
        if(strcmp(x->type,"CHARP")==0)
        {
			if(strcmp(s,"CHAR")!=0)
			 {
                 printf("error : the value of the exp not match to type of the var \n");
				 exit(0);
			 }
			return;
        }

		if(strcmp(x->type,"REALP")==0)
        {
			if(strcmp(s,"REAL")!=0)
			 {
                 printf("error : the value of the exp not match to type of the var \n");
				 exit(0);
			 }

			return;
		}
		else  
		{
              printf("error %s is not pointer",x->name);
			  exit(0);


		}


	}



}

scope* find_in_scope(char*x,ns*head)
{
    scope*temp=head->sym;
	while(temp!=NULL)
	{
         if(strcmp(x,temp->name)==0)
		    return temp;
		temp=temp->next_value;

	}
	

   return NULL;

} 

void take_care_of_st (node*s,ns**head,node*h)
{
      if(s==NULL)
	  { 
	if(h!=NULL)
		 {
			 return_st(h->right,head,h->mid2->token);
		    
		 
		 }
		 
		 
		 pop(head);
		 return ;

	  }
	  
	  
	  node*temp=s;
	  
	  
	  while(temp!=NULL)
	  {
		
		if(strcmp(temp->left->token,"=")==0 || strcmp(temp->left->token,"=s")==0 || strcmp(temp->left->token,"=*")==0 )
        {
			assig_check(temp->left,*head);
		}
		
		if(strcmp(temp->left->token,".FUNC_CALL")==0)
		{
			func_call_st(temp->left,*head);
		}
		
		if(strcmp(temp->left->token,".BLOCK")==0)
		{
			 take_care_of_bodyst(temp->left,head);
		}
		
		if(strcmp(temp->left->token,"IF1")==0 || strcmp(temp->left->token,"IF2")==0 || strcmp(temp->left->token,"IF-ELSE1")==0 || strcmp(temp->left->token,"IF-ELSE2")==0 || strcmp(temp->left->token,"IF-ELSE3")==0)
		{
			 
		      ifs_type(temp->left,head);	 
			  
		}    

		if(strcmp(temp->left->token,"FOR")==0 || strcmp(temp->left->token,"FOR1")==0 || strcmp(temp->left->token,"FOR2")==0 || strcmp(temp->left->token,"WHILE")==0 || strcmp(temp->left->token,"WHILE1")==0 ||  strcmp(temp->left->token,"DO_WHILE")==0  )	
        {
           loops_check(temp->left,head);

		} 

	  
		    temp=temp->mid1;

			  
	  
	  }

	  
	  
	  if(temp==NULL)
	  {
          		   if(h!=NULL)
		 {
			 return_st(h->right,head,h->mid2->token);
		   
		 
		 }
		  
		  pop(head);
		  return;

	  }
    




}



int func_call_st(node*f,ns*head)
{
    
	
     printf("in func call \n");
	 char* var=f->left->token;
	 char* func=f->mid1->token;
	 printf("func name %s \n",func);
	 scope*x=find(func,head);
	 scope*y=find(var,head);
	 int c=0;
	
	if( x==NULL)
	    {
			printf("error %s is undec \n",func);
			exit(0);
		} 
		if(y==NULL)
		{
			printf("error %s is undec \n",var);
			exit(0);

		}
	
	
	
	
	
	
	if(y->is_function==1)
	{
			printf("error %s is NOT FUNC \n",func);
			exit(0);

	}
	
	
	
	 // if func and var  declerd 
	
	 
		//if func have args we check if the args are same type and num
		if(f->mid2!=NULL)
		{ 
			node*help=f->mid2;
			
			while(strcmp(help->token,"..vd")==0)
			{
                
				char*m=checkexptype(help->left,head);
				
				
				if(strcmp(m,x->func_args[c])!=0)
				{
                    
					  printf("error the args not math unexpexted type %s ",m);
					  exit(0);
				}
				
				
				if(help->mid1!=NULL)
				{
					help=help->mid1;
				}
				else
				  break;
				

			  c++;
			
			}
			if(c+1!=sizeof_funcargs(x->func_args))
			   {
				  
				  c++;
				   printf("num of args not math \n");
			       exit(0);
			   }

		}
    	// if func dont have args;
		else{
                if(sizeof_funcargs(x->func_args)!=0)
				{		 
				 printf("number of args not match \n");
			     exit(0);
			 }
		}

		//type of var and func is same
		if(strcmp(x->type,y->type)!=0)
		{
            printf("type of var and type of func not match \n");
			exit(0);
		}
		






}

void help1(scope *x1 ,char*x,int c)
{
     int size=strlen(x);
	 int i=0;
	 for( i=0;i<size;i++)
	 {
        x1->func_args[c][i]=x[i];

	 }     
    x1->func_args[c][i]='\0';

}



void set_theargs(node*p,scope* x)
{
   int c=0;
   node*temp=p->left;
   node*temp1;
	char* old;
	while(1)
	{
           if(strcmp(temp->token,".m2")==0)
		   {
			   old=temp->left->token;
			   temp1=temp->mid1;
		   }
		  
		   if(strcmp(temp1->token,".co")==0)
		   {
                	node*help=temp1;
			    	while(1)
				{
				   help1(x,old,c);
				    c++;
				  if(strcmp(help->mid1->token,".co")==0)
				  {
                        help=help->mid1;

				  }
				  else{
					   help1(x,old,c);
					   break;


				  }
			   
			   
			   }

		   }
		   
			else{
                  //scope*x=make_scope(temp->token,0,old);
				  //push_scope(x,t);
                  
				  help1(x,old,c);
			
			}
			
           
		   if(temp->mid2!=NULL){
                temp=temp->mid2;
		   }
		   else{
			   break;
		   }       
	        
	}




}

int sizeof_funcargs(char x [50][50])
{
    int i=0;
	int c=0;
	for( i;i<50;i++)
	{
		if(strlen(x[i])!=0)
		{
		  
		   c++;
		   
		}
	}
    return c;




}


void ifs_type(node* s,ns**head)
{
  node* temp=s;

    if(strcmp(temp->token,"IF1")==0)
	{
		char*s=checkexptype(temp->left,*head);
		if(strcmp(s,"BOOL")!=0)
		{ 
			 printf("error : the exp of if must be bool \n");
			 exit(0);
		}
       take_care_of_bodyst(temp->mid1,head);
	}
	if(strcmp(temp->token,"IF2")==0)
	{
		char*s=checkexptype(temp->left,*head);
		if(strcmp(s,"BOOL")!=0)
		{ 
			 printf("error : the exp of if must be bool \n");
			 exit(0);
		}
       takest2(temp->mid1,head);
	}

	if(strcmp(temp->token,"IF-ELSE1")==0)
	{
		char*s=checkexptype(temp->left,*head);
		if(strcmp(s,"BOOL")!=0)
		{ 
			 printf("error : the exp of if must be bool \n");
			 exit(0);
		}
       take_care_of_bodyst(temp->mid1,head);
	   take_care_of_bodyst(temp->mid2,head);
	}

	if(strcmp(temp->token,"IF-ELSE2")==0)
	{
		char*s=checkexptype(temp->left,*head);
		if(strcmp(s,"BOOL")!=0)
		{ 
			 printf("error : the exp of if must be bool \n");
			 exit(0);
		}
       take_care_of_bodyst(temp->mid1,head);
	   takest2(temp->mid2,head);
	
	
	}


	if(strcmp(temp->token,"IF-ELSE3")==0)
	{
		char*s=checkexptype(temp->left,*head);
		if(strcmp(s,"BOOL")!=0)
		{ 
			 printf("error : the exp of if must be bool \n");
			 exit(0);
		}
       takest2(temp->mid1,head);
	   takest2(temp->mid2,head);
	
	
	}
}

void return_st(node*temp,ns**head,char*type)
{
       

  if(strcmp(temp->token,"RETURNe")==0)
    { 
	 	
		 if(strcmp(type,checkexptype(temp->left,*head))!=0)
	     {
				printf("error  return  unmatch the function type \n");
				exit(0);
	    }
	}
	if(strcmp(temp->token,"RETURNf")==0)	
	{	
		
		node*c=temp->left->left;
		scope *x=find(c->token,*head);
		char* t=x->type;
		
		if(strcmp(type,t)!=0)
        {
               printf("error type of return unmatch the function \n");
			   exit(0);       
		   
		}
        
		take_care_of_st(temp->left,head,NULL);
	 
	}					  


   
}

void loops_check(node*temp,ns**head)
{
     
	 if(strcmp(temp->token,"WHILE1")==0)
	 {
		 char* type =checkexptype(temp->left,*head);
         if(strcmp(type,"BOOL")!=0)
		 {
			 printf("error: the type of the exp in while is not bool \n");
			 exit(0);
		 }
		 take_care_of_bodyst(temp->mid1,head);

	 }
	  if(strcmp(temp->token,"WHILE")==0)
	 {
		 char* type =checkexptype(temp->left,*head);
         if(strcmp(type,"BOOL")!=0)
		 {
			 printf("error: the type of the exp in while is not bool \n");
			 exit(0);
		 }
		 takest2(temp->mid1,head);

	 }

	 if(strcmp(temp->token,"FOR1")==0)
	 {
		 char* type =checkexptype(temp->mid1,*head);
		 if(strcmp(type,"BOOL")!=0)
		 {
			 printf("error: the type of the exp in for is not bool \n");
			exit(0);
		 }
		 assig_check(temp->mid2,*head);
		 take_care_of_bodyst(temp->mid3,head);

	 }
	 if(strcmp(temp->token,"FOR2")==0)
	 {
		 char* type =checkexptype(temp->mid1,*head);
		 if(strcmp(type,"BOOL")!=0)
		 {
			 printf("error: the type of the exp in for is not bool \n");
			exit(0);
		 }
		 assig_check(temp->left,*head);
		 assig_check(temp->mid2,*head);
		 take_care_of_bodyst(temp->mid3,head);

	 }
	 if(strcmp(temp->token,"DO_WHILE")==0)
	 {
		 char* type =checkexptype(temp->mid1,*head);
		 if(strcmp(type,"BOOL")!=0)
		 {
			 printf("error: the type of the exp in for is not bool \n");
			exit(0);
		 }
		 take_care_of_bodyst(temp->left,head);

	 }

	  if(strcmp(temp->token,"FOR")==0)
	 {
		 char* type =checkexptype(temp->mid1,*head);
         if(strcmp(type,"BOOL")!=0)
		 {
			 printf("error: the type of the exp in while is not bool \n");
			 exit(0);
		 }
		 assig_check(temp->left,*head);
		 assig_check(temp->mid2,*head);
		 takest2(temp->mid3,head);

	 }






}

void  takest2(node*temp,ns**head)
{

   
      if(strcmp(temp->token,"=")==0 || strcmp(temp->token,"=s")==0 || strcmp(temp->token,"=*")==0 )
        {
			assig_check(temp,*head);
		}
		
		if(strcmp(temp->token,".FUNC_CALL")==0)
		{
			func_call_st(temp,*head);
		}
		
		if(strcmp(temp->token,".BLOCK")==0)
		{
			 take_care_of_bodyst(temp,head);
		}
		
		if(strcmp(temp->token,"IF1")==0 || strcmp(temp->token,"IF2")==0 || strcmp(temp->token,"IF-ELSE1")==0 || strcmp(temp->token,"IF-ELSE2")==0 || strcmp(temp->token,"IF-ELSE3")==0)
		{
			 
		      ifs_type(temp,head);	 
			  
		}    

		if(strcmp(temp->token,"FOR")==0 || strcmp(temp->token,"FOR1")==0 || strcmp(temp->token,"FOR2")==0 || strcmp(temp->token,"WHILE")==0 || strcmp(temp->token,"WHILE1")==0 ||  strcmp(temp->token,"DO_WHILE")==0  )	
        {
           loops_check(temp,head);

		}


}
#line 2375 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 97 "parser.y"
	{yyval=mk1son(".CODE",yystack.l_mark[0]);    ;tree=yyval; }
break;
case 2:
#line 99 "parser.y"
	{yyval=mk2son(".code",yystack.l_mark[-1],yystack.l_mark[0]);}
break;
case 3:
#line 99 "parser.y"
	{yyval=yystack.l_mark[0]; }
break;
case 4:
#line 101 "parser.y"
	{yyval=mk4son(".MAIN",mkleaf(".MAIN"),yystack.l_mark[-4],mkleaf("(TYPE VOID)"),yystack.l_mark[-1]);}
break;
case 5:
#line 103 "parser.y"
	{yyval=yystack.l_mark[0];}
break;
case 6:
#line 104 "parser.y"
	{yyval=yystack.l_mark[0];}
break;
case 7:
#line 107 "parser.y"
	{  yyval=mk4son(".procedures",yystack.l_mark[-5],yystack.l_mark[-3],mkleaf("(TYPE VOID)"),yystack.l_mark[-1]);printf("procedures\n");}
break;
case 8:
#line 109 "parser.y"
	{
						char a1[20]="(TYPE "; strcat(a1,yystack.l_mark[-7]->token);strcat(a1,")"); /*printf("%s",a);*/
						yyval=mknode(".FUNCTION",yystack.l_mark[-6],yystack.l_mark[-4],yystack.l_mark[-7],yystack.l_mark[-2],yystack.l_mark[-1]);printf("functions\n");}
break;
case 9:
#line 113 "parser.y"
	{yyval=mkleaf("(ARGS NONE)");printf("p 2 \n");}
break;
case 10:
#line 115 "parser.y"
	{yyval = yystack.l_mark[0];printf("exp_binary\n");}
break;
case 11:
#line 116 "parser.y"
	{yyval = yystack.l_mark[0];printf("exp_unairt\n");}
break;
case 12:
#line 118 "parser.y"
	{ yyval=mk1son("RETURNe",yystack.l_mark[-1]);printf("return_stmt1\n"); }
break;
case 13:
#line 119 "parser.y"
	{yyval=mk1son("RETURNf",mk1son("FUNC_CALL",yystack.l_mark[-3]));printf("return_stmt2\n");}
break;
case 14:
#line 120 "parser.y"
	{ yyval=mk1son("RETURNf",mk2son("FUNC_CALL",yystack.l_mark[-4],yystack.l_mark[-2])); printf("return_stmt3\n");}
break;
case 15:
#line 122 "parser.y"
	{yyval=mkleaf("INT");}
break;
case 16:
#line 123 "parser.y"
	{yyval=mkleaf("CHAR");}
break;
case 17:
#line 124 "parser.y"
	{yyval=mkleaf("REAL");}
break;
case 18:
#line 125 "parser.y"
	{yyval=mkleaf("REALP");}
break;
case 19:
#line 126 "parser.y"
	{yyval=mkleaf("INTP");}
break;
case 20:
#line 127 "parser.y"
	{yyval=mkleaf("BOOL");}
break;
case 21:
#line 128 "parser.y"
	{yyval=mkleaf("CHARP");}
break;
case 22:
#line 130 "parser.y"
	{yyval=mk1son(".ARGS",yystack.l_mark[0]);printf("p 1 \n");}
break;
case 23:
#line 131 "parser.y"
	{yyval=mkleaf("(ARGS NONE)");printf("p 2 \n");}
break;
case 24:
#line 133 "parser.y"
	{  yyval=mk3son(".m2",yystack.l_mark[-3],yystack.l_mark[-2],yystack.l_mark[0]);printf("m2 1 \n");}
break;
case 25:
#line 134 "parser.y"
	{ yyval=mk2son(".m2",yystack.l_mark[-2],yystack.l_mark[-1]);printf("m2 2 \n");}
break;
case 26:
#line 137 "parser.y"
	{yyval=mk2son(".co",yystack.l_mark[-2],yystack.l_mark[0]);printf("co 1 \n");}
break;
case 27:
#line 138 "parser.y"
	{yyval=yystack.l_mark[0]; printf("co 2 \n");}
break;
case 28:
#line 141 "parser.y"
	{yyval=mk1son(".BODY",yystack.l_mark[0]);printf("body 1 \n");}
break;
case 29:
#line 144 "parser.y"
	{yyval=mk2son(".fd",yystack.l_mark[-1],yystack.l_mark[0]);printf("fd 1 \n");}
break;
case 30:
#line 145 "parser.y"
	{yyval=yystack.l_mark[0];printf("fd 2 \n");}
break;
case 31:
#line 148 "parser.y"
	{
   
   if(yystack.l_mark[-1]!=NULL)yyval=mk2son(".vd",yystack.l_mark[-1],yystack.l_mark[0]);
   else
     yyval=mk1son(".vd",yystack.l_mark[0]);
   

}
break;
case 32:
#line 158 "parser.y"
	{yyval=yystack.l_mark[0];}
break;
case 33:
#line 158 "parser.y"
	{yyval=yystack.l_mark[0];}
break;
case 34:
#line 158 "parser.y"
	{yyval=NULL;}
break;
case 35:
#line 161 "parser.y"
	{
			  yyval=mk2son(".VAR",yystack.l_mark[-1],yystack.l_mark[0]);}
break;
case 36:
#line 165 "parser.y"
	{yyval=mk2son(".dec_11",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 37:
#line 166 "parser.y"
	{yyval=mk2son(".dec_12",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 38:
#line 167 "parser.y"
	{yyval=mk3son("=v1",yystack.l_mark[-4],yystack.l_mark[0],yystack.l_mark[-2]);}
break;
case 39:
#line 168 "parser.y"
	{yyval=mk3son("=v2",yystack.l_mark[-4],yystack.l_mark[0],yystack.l_mark[-2]);}
break;
case 40:
#line 171 "parser.y"
	{yyval=mk1son(".STRING",yystack.l_mark[0]);}
break;
case 41:
#line 174 "parser.y"
	{yyval=mk2son(".dec_21",yystack.l_mark[-5],yystack.l_mark[0]);}
break;
case 42:
#line 175 "parser.y"
	{yyval=mk2son(".dec_22",yystack.l_mark[-5],yystack.l_mark[0]);}
break;
case 43:
#line 176 "parser.y"
	{yyval=mk2son("=s1",yystack.l_mark[-7],yystack.l_mark[0]);}
break;
case 44:
#line 177 "parser.y"
	{yyval=mk2son("=s2",yystack.l_mark[-7],yystack.l_mark[0]);}
break;
case 45:
#line 179 "parser.y"
	{yyval=mk2son(".st",yystack.l_mark[-1],yystack.l_mark[0]);}
break;
case 46:
#line 180 "parser.y"
	{yyval=mk2son(".st",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 47:
#line 181 "parser.y"
	{yyval=mk2son(".st",yystack.l_mark[-1],yystack.l_mark[0]);}
break;
case 48:
#line 182 "parser.y"
	{yyval=mk2son(".st",yystack.l_mark[-1],yystack.l_mark[0]);}
break;
case 49:
#line 183 "parser.y"
	{yyval=mk2son(".st",yystack.l_mark[-1],yystack.l_mark[0]);}
break;
case 50:
#line 184 "parser.y"
	{yyval=NULL;}
break;
case 51:
#line 186 "parser.y"
	{yyval=mk1son("int",mkleaf(strdup(yytext)));}
break;
case 52:
#line 187 "parser.y"
	{yyval=mk1son("int",mkleaf(strdup(yytext)));}
break;
case 53:
#line 188 "parser.y"
	{yyval=mk1son("real",mkleaf(strdup(yytext)));}
break;
case 54:
#line 189 "parser.y"
	{yyval=mk1son("real",mkleaf(strdup(yytext)));}
break;
case 55:
#line 190 "parser.y"
	{yyval=mk1son("real",mkleaf(strdup(yytext)));}
break;
case 56:
#line 191 "parser.y"
	{yyval=mk1son("real",mkleaf(strdup(yytext)));}
break;
case 57:
#line 193 "parser.y"
	{yyval=mk2son("=",yystack.l_mark[-3],yystack.l_mark[-1]); printf("using the is role var \n") ;}
break;
case 58:
#line 194 "parser.y"
	{yyval=mk3son("=s",yystack.l_mark[-6],yystack.l_mark[-4],yystack.l_mark[-1]); printf("using string assig \n");}
break;
case 59:
#line 195 "parser.y"
	{yyval=mk2son("=*",yystack.l_mark[-3],yystack.l_mark[-1]);}
break;
case 60:
#line 197 "parser.y"
	{yyval=mk2son("*",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 61:
#line 198 "parser.y"
	{yyval=mk2son("+",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 62:
#line 199 "parser.y"
	{yyval=mk2son("-",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 63:
#line 200 "parser.y"
	{yyval=mk2son("/",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 64:
#line 201 "parser.y"
	{yyval=mk2son("||",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 65:
#line 202 "parser.y"
	{yyval=mk2son("==",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 66:
#line 203 "parser.y"
	{yyval=mk2son("<",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 67:
#line 204 "parser.y"
	{yyval=mk2son("!=",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 68:
#line 205 "parser.y"
	{yyval=yystack.l_mark[0];}
break;
case 69:
#line 206 "parser.y"
	{yyval=mk1son("()",yystack.l_mark[-1]);}
break;
case 70:
#line 207 "parser.y"
	{yyval=mk1son("id",yystack.l_mark[0]);printf("in id  of  exp yacc \n");}
break;
case 71:
#line 208 "parser.y"
	{yyval=mk2son("&&",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 72:
#line 209 "parser.y"
	{yyval=mk2son(">",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 73:
#line 210 "parser.y"
	{yyval=mk2son(">=",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 74:
#line 211 "parser.y"
	{yyval=mk2son("<=",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 75:
#line 212 "parser.y"
	{yyval=mkleaf("NULL");}
break;
case 76:
#line 213 "parser.y"
	{yyval=mk1son("char",mkleaf(strdup(yytext)));}
break;
case 77:
#line 214 "parser.y"
	{yyval=mkleaf("TRUE");}
break;
case 78:
#line 215 "parser.y"
	{yyval=mkleaf("FALSE");}
break;
case 79:
#line 216 "parser.y"
	{char a[25]="length("; strcat(a,yystack.l_mark[-1]->token);strcat(a,")");yyval=mk1son("ABS",yystack.l_mark[-1]);}
break;
case 80:
#line 217 "parser.y"
	{yyval=mk1son("str",mkleaf(strdup(yytext)));}
break;
case 81:
#line 218 "parser.y"
	{yyval=mk2son("at",yystack.l_mark[-3],yystack.l_mark[-1]);}
break;
case 82:
#line 224 "parser.y"
	{ yyval=mk1son("*",yystack.l_mark[0]);}
break;
case 83:
#line 225 "parser.y"
	{ yyval=mk1son("!",yystack.l_mark[0]);}
break;
case 84:
#line 226 "parser.y"
	{ yyval=mk1son("-",yystack.l_mark[0]);}
break;
case 85:
#line 227 "parser.y"
	{ yyval=mk1son("&",yystack.l_mark[0]);}
break;
case 86:
#line 229 "parser.y"
	{ yyval=mk3son(".FUNC_CALL",yystack.l_mark[-6],yystack.l_mark[-4],yystack.l_mark[-2]);}
break;
case 87:
#line 230 "parser.y"
	{ yyval=mk2son(".FUNC_CALL",yystack.l_mark[-5],yystack.l_mark[-3]);}
break;
case 88:
#line 232 "parser.y"
	{ yyval=mk2son("..vd",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 89:
#line 233 "parser.y"
	{ yyval=mk1son("..vd",yystack.l_mark[0]);}
break;
case 90:
#line 235 "parser.y"
	{if(yystack.l_mark[-1]!=NULL) yyval=mk2son(".BLOCK",yystack.l_mark[-1],yystack.l_mark[0]);
		      else yyval=mk1son(".BLOCK",yystack.l_mark[0]);	}
break;
case 91:
#line 240 "parser.y"
	{
							
						yyval=mk2son("IF1",yystack.l_mark[-4],yystack.l_mark[-1]);
												
					}
break;
case 92:
#line 246 "parser.y"
	{
						
						yyval=mk2son("IF2",yystack.l_mark[-2],yystack.l_mark[0]);
						}
break;
case 93:
#line 252 "parser.y"
	{
					
						yyval=mk3son("IF-ELSE1",yystack.l_mark[-9],yystack.l_mark[-6],yystack.l_mark[-2]);
						
						}
break;
case 94:
#line 258 "parser.y"
	{ 
						
						yyval=mk3son("IF-ELSE2",yystack.l_mark[-6],yystack.l_mark[-3],yystack.l_mark[0]);
						
						}
break;
case 95:
#line 264 "parser.y"
	{ 
						
						yyval=mk3son("IF-ELSE3",yystack.l_mark[-4],yystack.l_mark[-2],yystack.l_mark[0]);
						
						}
break;
case 96:
#line 272 "parser.y"
	{yyval=yystack.l_mark[0];}
break;
case 97:
#line 272 "parser.y"
	{yyval=NULL;}
break;
case 98:
#line 274 "parser.y"
	{yyval=yystack.l_mark[0];}
break;
case 99:
#line 275 "parser.y"
	{yyval=yystack.l_mark[0];}
break;
case 100:
#line 276 "parser.y"
	{yyval=yystack.l_mark[0];}
break;
case 101:
#line 277 "parser.y"
	{yyval=yystack.l_mark[0];}
break;
case 102:
#line 280 "parser.y"
	{yyval=mk2son("WHILE1",yystack.l_mark[-4],yystack.l_mark[-1]);}
break;
case 103:
#line 281 "parser.y"
	{yyval=mk2son("WHILE",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 104:
#line 282 "parser.y"
	{yyval=mk4son("FOR1",yystack.l_mark[-8],yystack.l_mark[-6],yystack.l_mark[-4],yystack.l_mark[-1]);}
break;
case 105:
#line 283 "parser.y"
	{yyval=mk4son("FOR2",yystack.l_mark[-8],yystack.l_mark[-6],yystack.l_mark[-4],yystack.l_mark[-1]);}
break;
case 106:
#line 284 "parser.y"
	{yyval=mk4son("FOR",yystack.l_mark[-6],yystack.l_mark[-4],yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 107:
#line 285 "parser.y"
	{yyval=mk2son("DO-WHILE",yystack.l_mark[-6],yystack.l_mark[-2]);}
break;
case 108:
#line 290 "parser.y"
	{char s[20]="VAR "; /*strcat(s,$1->token) */;  yyval=mk1son(s,yystack.l_mark[0]);}
break;
case 109:
#line 291 "parser.y"
	{yyval=mk2son("=",yystack.l_mark[-2],yystack.l_mark[0]);}
break;
case 110:
#line 293 "parser.y"
	{yyval=mkleaf(strdup(yytext));}
break;
#line 3047 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
