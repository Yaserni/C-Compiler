%{
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

node* mknode(char* token,node* left,node* mid1,node* mid2,node* mid3, node* right);
void Printtree(node* tree,int tab);
int isTerminal(node* tree);
int AllChildTerminal(node* tree);
node* mkleaf(char* token);
node* mk1son(char* token,node* left);
node* mk2son(char* token,node* left,node* mid1);
node* mk3son(char* token,node* left,node* mid1,node* mid2);
node* mk4son(char* token,node* left,node* mid1,node* mid2,node* mid3);

int yyerror(/*const char *msg*/);

extern int yylex();
extern int yylineno;
extern char *yytext;
static int c=0;


%}



%token ID FUNCTION INT CHAR SEMI COMA BP EP IF SBLOCK EBLOCK REAL REALP INTP BOOL CHARP EQ VAR INT_NUM1 INT_NUM2 REAL_NUM1 REAL_NUM2 REAL_NUM3
%token REAL_NUM4 STRING BSI ESI STRING_VAL OR PLUS MINUS MULT DIV EQEQ BIG BIGEQ SMALL SMALLEQ SHIFT NOTEQ NOT WHILE FOR DO RETURN AND VOID MAIN 	
%token N TRUE FALSE C_LITTER ABS 
%left MINUS PLUS SHIFT
%left MULT DIV
%left AND OR BIG BIGEQ SMALL SMALLEQ EQEQ NOTEQ 
%right NOT
//%type <node> code functions_list procedures functions exp return_stmt binary unairy p co body fd main vd dec dec_var dec_1 dec_2 st
%nonassoc IFX
%nonassoc ELSE
%%
programe:code    {$$=mk1son("CODE",$1);  Printtree($$,0);  printf("\nAccepted\n");};

code: functions_list  code {$$=mk2son("",$1,$2);} |main{$$=$1;} ;

main: FUNCTION VOID MAIN BP p SBLOCK body EBLOCK {$$=mk4son("FUNCTION",mkleaf("MAIN"),$5,mkleaf("(TYPE VOID)"),$7);};

functions_list: functions  {$$=$1;}
              | procedures  {$$=$1;}
              ;

procedures: FUNCTION VOID id BP p SBLOCK body EBLOCK  {  $$=mk4son("FUNCTION",$3,$5,mkleaf("(TYPE VOID)"),$7);};

functions: FUNCTION type id BP p SBLOCK body return_stmt EBLOCK {
						char a1[20]="(TYPE "; strcat(a1,$2->token);strcat(a1,")"); //printf("%s",a);
						$$=mknode("FUNCTION",$3,$5,mkleaf(a1),$7,$8);} ;


exp: 	binary {$$ = $1;}
	| unairy{$$ = $1;};

return_stmt:   RETURN exp SEMI { $$=mk1son("RETURN",$2); } 
	    |  RETURN id BP EP SEMI {$$=mk1son("RETURN",mk1son("FUNC_CALL",$2));}
	    |  RETURN id BP listof_exp EP SEMI  { $$=mk1son("RETURN",mk2son("FUNC_CALL",$2,$4)); };

type: INT  {$$=mkleaf("INT");}
    | CHAR {$$=mkleaf("CHAR");}
    | REAL {$$=mkleaf("REAL");}
    |REALP {$$=mkleaf("REALP");}
    | INTP {$$=mkleaf("INTP");}
    | BOOL {$$=mkleaf("BOOL");}
    |CHARP {$$=mkleaf("CHARP");} 
    ; 
p:    m2 {$$=mk1son("ARGS",$1);} 
    | EP {$$=mkleaf("(ARGS NONE)");}
	;
m2:       type co SEMI m2 {  $$=mk3son("",$1,$2,$4);} 
	| type co EP  { $$=mk2son("",$1,$2);} 
	 ;

co: id COMA co  {$$=mk2son("",$1,$3);} 
	| id {$$=$1;}
	;

body: fd {$$=mk1son("BODY",$1);};


fd:	functions_list fd {$$=mk2son("",$1,$2);} 
	|vd {$$=$1;}
	;

vd:   dec st {
if($1!=NULL)   $$=mk2son("VARIABLES",$1,$2);
else $$=mk2son("",$1,$2);
};


dec: dec_var {$$=$1;} | dec_string {$$=$1;} | {$$=NULL;};


dec_var: VAR type  dec_1 {
			  $$=mk2son("VAR",$2,$3);};


dec_1: id COMA dec_1 {$$=mk2son("",$1,$3);}
     | id SEMI dec {$$=mk2son("",$1,$3);}
     | id EQ exp COMA dec_1  {$$=mk3son("=",$1,$3,$5);}
     | id EQ exp SEMI dec {$$=mk2son("=",$1,$5);};


dec_string: STRING dec_2{$$=mk1son("STRING",$2);};


dec_2: id BSI INT_NUM1 ESI COMA dec_2 {$$=mk2son("",$1,$6);} 
     | id BSI INT_NUM1 ESI SEMI dec   {$$=mk2son("",$1,$6);}
     | id BSI INT_NUM1 ESI EQ STRING_VAL COMA dec_2 {$$=mk3son("=",$1,$5,$8);}
     | id BSI INT_NUM1 ESI EQ STRING_VAL SEMI dec  {$$=mk3son("=",$1,$6,$8);};

st: assig st {$$=mk2son("st",$1,$2);} 
    | SBLOCK code_block EBLOCK st  {$$=mk2son("st",$2,$4);} 
    |IFS st  {$$=mk2son("st",$1,$2);} 
    |loops st {$$=mk2son("st",$1,$2);} 
    | func_call st  {$$=mk2son("st",$1,$2);} 
    | {$$=NULL;};

num : INT_NUM1 {$$=mkleaf(strdup(yytext));}
	| INT_NUM2 {$$=mkleaf(strdup(yytext));}
	|REAL_NUM1 {$$=mkleaf(strdup(yytext));}
	|REAL_NUM2 {$$=mkleaf(strdup(yytext));}
	|REAL_NUM3 {$$=mkleaf(strdup(yytext));}
	|REAL_NUM4 {$$=mkleaf(strdup(yytext));};

assig: id EQ exp SEMI  {$$=mk2son("=",$1,$3);} 
	| id BSI exp ESI EQ exp SEMI {$$=mk2son("=",$1,$6);} 
	| MULT id EQ exp SEMI  {$$=mk2son("=",$2,$4);}  ;

binary : exp MULT exp  {$$=mk2son("*",$1,$3);}
	| exp PLUS exp {$$=mk2son("+",$1,$3);}
	| exp MINUS exp {$$=mk2son("-",$1,$3);}
	|exp DIV exp    {$$=mk2son("/",$1,$3);}
	| exp OR exp    {$$=mk2son("||",$1,$3);}
	| exp EQEQ exp  {$$=mk2son("==",$1,$3);}
	| exp SMALL exp {$$=mk2son("<",$1,$3);}
        | num {$$=$1;}
        | BP exp EP {$$=mk1son("()",$2);}
        |id {$$=$1;}
        |exp AND exp {$$=mk2son("&&",$1,$3);}
        |exp BIG exp{$$=mk2son(">",$1,$3);}
        |exp BIGEQ exp{$$=mk2son(">=",$1,$3);}
        |exp SMALLEQ exp {$$=mk2son("<=",$1,$3);}
        |N {$$=mkleaf("NULL");}
        |C_LITTER  {$$=mkleaf(strdup(yytext));}
	|TRUE  {$$=mkleaf("TRUE");}
	|FALSE  {$$=mkleaf("FALSE");}
        |ABS id ABS {char a[25]="length("; strcat(a,$2->token);strcat(a,")");$$=mkleaf(a);}
        |STRING_VAL  {$$=mkleaf(strdup(yytext));}
        ;




unairy: MULT exp { $$=mk1son("*",$2);}
      | NOT exp { $$=mk1son("!",$2);}
      | MINUS exp { $$=mk1son("-",$2);}
      | SHIFT exp { $$=mk1son("&",$2);};

func_call: id EQ id BP listof_exp EP SEMI { $$=mk2son("FUNC_CALL",$1,$5);}  
         | id EQ id BP EP SEMI { $$=mk1son("FUNC_CALL",$1);}    ;  

listof_exp: exp COMA listof_exp{ $$=mk2son("",$1,$3);}
          | exp { $$=mk1son("",$1);}  ;

code_block:  dec st  {if($2!=NULL) $$=mk2son("BLOCK",$1,$2);
		      else $$=mk1son("BLOCK",$1);	}; 


IFS:					IF BP exp EP SBLOCK code_block rt EBLOCK  %prec IFX 
					{
							
						$$=mk2son("IF",$3,$6);
												
					}
					| IF BP exp EP st2 %prec IFX
						{
						
						$$=mk2son("IF",$3,$5);
						}
					
					| IF BP exp EP SBLOCK code_block rt EBLOCK ELSE SBLOCK code_block rt EBLOCK
						{
					
						$$=mk3son("IF-ELSE",$3,$6,$10);
						
						}
					| IF BP exp EP SBLOCK code_block rt EBLOCK ELSE st2
						{ 
						
						$$=mk3son("IF-ELSE",$3,$6,$9);
						
						}
					| IF BP exp EP st2 ELSE st2
						{ 
						
						$$=mk3son("IF-ELSE",$3,$5,$7);
						
						}
						
						;

rt: return_stmt {$$=$1;}| {$$=NULL;};

st2:assig {$$=$1;}
    | IFS {$$=$1;}
    |func_call{$$=$1;}
    |loops{$$=$1;}
    ;

loops: 			WHILE BP exp EP SBLOCK code_block EBLOCK {$$=mk2son("WHILE",$3,$6);}
			| WHILE BP exp EP st2 {$$=mk2son("WHILE",$3,$5);}
			| FOR BP dec_loops SEMI exp SEMI assig_loops EP SBLOCK code_block EBLOCK    {$$=mk4son("FOR",$3,$5,$7,$10);}
			| FOR BP assig_loops SEMI exp SEMI assig_loops EP SBLOCK code_block EBLOCK  {$$=mknode("FOR",$3,$5,$7,$9,$10);}
			| FOR BP assig_loops SEMI exp SEMI assig_loops EP st2 {$$=mk4son("FOR",$3,$5,$7,$9);}
			| DO SBLOCK code_block EBLOCK WHILE BP exp EP SEMI  {$$=mk2son("DO-WHILE",$3,$7);} ;

			;


dec_loops:VAR type assig_loops {char s[20]="VAR "; strcat(s,$1->token);  $$=mk1son(s,$3);}; //-----------------------------------
assig_loops:id EQ exp {$$=mk2son("=",$1,$3);};

id: ID {$$=mkleaf(strdup(yytext));};

%%
#include "lex.yy.c"
int main()
{
 #ifdef YYDEBUG
  yydebug = 1;
  #endif
 return yyparse();
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

int yyerror()
{
  printf("Unaccepted \nline %d \n unexpected: %s",yylineno,yytext);
  return 0;
}
