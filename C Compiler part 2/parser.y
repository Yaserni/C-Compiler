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
programe:code    {$$=mk1son(".CODE",$1);    ;tree=$$; };

code: functions_list  code {$$=mk2son(".code",$1,$2);} |main{$$=$1; } ;

main: FUNCTION VOID MAIN BP no_args EP SBLOCK body EBLOCK {$$=mk4son(".MAIN",mkleaf(".MAIN"),$5,mkleaf("(TYPE VOID)"),$8);};

functions_list: functions  {$$=$1;}
              | procedures  {$$=$1;}
              ;

procedures: FUNCTION VOID id BP p SBLOCK body EBLOCK  {  $$=mk4son(".procedures",$3,$5,mkleaf("(TYPE VOID)"),$7);};

functions: FUNCTION type id BP p SBLOCK body return_stmt EBLOCK {
						char a1[20]="(TYPE "; strcat(a1,$2->token);strcat(a1,")"); //printf("%s",a);
						$$=mknode(".FUNCTION",$3,$5,$2,$7,$8);} ;

no_args:{$$=mkleaf("(ARGS NONE)");};

exp: binary {$$ = $1;}
	| unairy{$$ = $1;};

return_stmt:RETURN exp SEMI { $$=mk1son("RETURNe",$2); } 
	    |  RETURN id BP EP SEMI {$$=mk1son("RETURNf",mk1son("FUNC_CALL",$2));}
	    |  RETURN id BP listof_exp EP SEMI  { $$=mk1son("RETURNf",mk2son("FUNC_CALL",$2,$4)); };

type: INT  {$$=mkleaf("INT");}
    | CHAR {$$=mkleaf("CHAR");}
    | REAL {$$=mkleaf("REAL");}
    |REALP {$$=mkleaf("REALP");}
    | INTP {$$=mkleaf("INTP");}
    | BOOL {$$=mkleaf("BOOL");}
    |CHARP {$$=mkleaf("CHARP");} 
    ; 
p:    m2 {$$=mk1son(".ARGS",$1);} 
    | EP {$$=mkleaf("(ARGS NONE)");}
	;
m2:   type co SEMI m2 {  $$=mk3son(".m2",$1,$2,$4);} 
	| type co EP  { $$=mk2son(".m2",$1,$2);} 
	 ;

co: id COMA co  {$$=mk2son(".co",$1,$3);} 
	| id {$$=$1; }
	;

body: fd {$$=mk1son(".BODY",$1);};


fd:	functions_list fd {$$=mk2son(".fd",$1,$2);} 
	|vd {$$=$1;}
	;

vd:   dec st {
   
   if($1!=NULL)$$=mk2son(".vd",$1,$2);
   else
     $$=mk1son(".vd",$2);
   

};


dec: dec_var {$$=$1;} | dec_string {$$=$1;} | {$$=NULL;};


dec_var: VAR type  dec_1 {
			  $$=mk2son(".VAR",$2,$3);};


dec_1: id COMA dec_1 {$$=mk2son(".dec_11",$1,$3);}
     | id SEMI dec {$$=mk2son(".dec_12",$1,$3);}
     | id EQ exp COMA dec_1  {$$=mk3son("=v1",$1,$5,$3);}
     | id EQ exp SEMI dec {$$=mk3son("=v2",$1,$5,$3);};


dec_string: STRING dec_2{$$=mk1son(".STRING",$2);};


dec_2: id BSI INT_NUM1 ESI COMA dec_2 {$$=mk2son(".dec_21",$1,$6);} 
     | id BSI INT_NUM1 ESI SEMI dec   {$$=mk2son(".dec_22",$1,$6);}
     | id BSI INT_NUM1 ESI EQ STRING_VAL COMA dec_2 {$$=mk2son("=s1",$1,$8);}
     | id BSI INT_NUM1 ESI EQ STRING_VAL SEMI dec  {$$=mk2son("=s2",$1,$8);};

st: assig st {$$=mk2son(".st",$1,$2);} 
    | SBLOCK code_block EBLOCK st  {$$=mk2son(".st",$2,$4);} 
    |IFS st  {$$=mk2son(".st",$1,$2);} 
    |loops st {$$=mk2son(".st",$1,$2);} 
    | func_call st  {$$=mk2son(".st",$1,$2);} 
    | {$$=NULL;};

num : INT_NUM1 {$$=mk1son("int",mkleaf(strdup(yytext)));}
	| INT_NUM2 {$$=mk1son("int",mkleaf(strdup(yytext)));}
	|REAL_NUM1 {$$=mk1son("real",mkleaf(strdup(yytext)));}
	|REAL_NUM2 {$$=mk1son("real",mkleaf(strdup(yytext)));}
	|REAL_NUM3 {$$=mk1son("real",mkleaf(strdup(yytext)));}
	|REAL_NUM4 {$$=mk1son("real",mkleaf(strdup(yytext)));};

assig: id EQ exp SEMI  {$$=mk2son("=",$1,$3);  ;} 
	| id BSI exp ESI EQ exp SEMI {$$=mk3son("=s",$1,$3,$6);} 
	| MULT id EQ exp SEMI  {$$=mk2son("=*",$2,$4);}  ;

binary : exp MULT exp  {$$=mk2son("*",$1,$3);}
	| exp PLUS exp {$$=mk2son("+",$1,$3);}
	| exp MINUS exp {$$=mk2son("-",$1,$3);}
	|exp DIV exp    {$$=mk2son("/",$1,$3);}
	| exp OR exp    {$$=mk2son("||",$1,$3);}
	| exp EQEQ exp  {$$=mk2son("==",$1,$3);}
	| exp SMALL exp {$$=mk2son("<",$1,$3);}
    | exp NOTEQ  exp {$$=mk2son("!=",$1,$3);}
    | num {$$=$1;}
    | BP exp EP {$$=mk1son("()",$2);}
    |id {$$=mk1son("id",$1);}
        |exp AND exp {$$=mk2son("&&",$1,$3);}
        |exp BIG exp{$$=mk2son(">",$1,$3);}
        |exp BIGEQ exp{$$=mk2son(">=",$1,$3);}
        |exp SMALLEQ exp {$$=mk2son("<=",$1,$3);}
        |N {$$=mkleaf("NULL");}
        |C_LITTER  {$$=mk1son("char",mkleaf(strdup(yytext)));}
	|TRUE  {$$=mkleaf("TRUE");}
	|FALSE  {$$=mkleaf("FALSE");}
        |ABS id ABS {char a[25]="length("; strcat(a,$2->token);strcat(a,")");$$=mk1son("ABS",$2);}
        |STRING_VAL  {$$=mk1son("str",mkleaf(strdup(yytext)));}
        |id BSI exp ESI {$$=mk2son("at",$1,$3);}
       ;




unairy: MULT exp { $$=mk1son("*",$2);}
      | NOT exp { $$=mk1son("!",$2);}
      | MINUS exp { $$=mk1son("-",$2);}
      | SHIFT exp { $$=mk1son("&",$2);};

func_call: id EQ id BP listof_exp EP SEMI { $$=mk3son(".FUNC_CALL",$1,$3,$5);}  
         | id EQ id BP EP SEMI { $$=mk2son(".FUNC_CALL",$1,$3);}    ;  

listof_exp: exp COMA listof_exp{ $$=mk2son("..vd",$1,$3);}
          | exp { $$=mk1son("..vd",$1);}  ;

code_block:  dec st  {if($1!=NULL) $$=mk2son(".BLOCK",$1,$2);
		      else $$=mk1son(".BLOCK",$2);	}; 


IFS:				IF BP exp EP SBLOCK code_block  EBLOCK  %prec IFX 
					{
							
						$$=mk2son("IF1",$3,$6);
												
					}
					| IF BP exp EP st2 %prec IFX
						{
						
						$$=mk2son("IF2",$3,$5);
						}
					
					| IF BP exp EP SBLOCK code_block EBLOCK ELSE SBLOCK code_block rt EBLOCK
						{
					
						$$=mk3son("IF-ELSE1",$3,$6,$10);
						
						}
					| IF BP exp EP SBLOCK code_block  EBLOCK ELSE st2
						{ 
						
						$$=mk3son("IF-ELSE2",$3,$6,$9);
						
						}
					| IF BP exp EP st2 ELSE st2
						{ 
						
						$$=mk3son("IF-ELSE3",$3,$5,$7);
						
						}
						
						;

rt: return_stmt {$$=$1;}| {$$=NULL;};

st2:assig {$$=$1;}
    | IFS {$$=$1;}
    |func_call{$$=$1;}
    |loops{$$=$1;}
    ;

loops: 		 WHILE BP exp EP SBLOCK code_block EBLOCK {$$=mk2son("WHILE1",$3,$6);}
			| WHILE BP exp EP st2 {$$=mk2son("WHILE",$3,$5);}
			| FOR BP dec_loops SEMI exp SEMI assig_loops EP SBLOCK code_block EBLOCK    {$$=mk4son("FOR1",$3,$5,$7,$10);}
			| FOR BP assig_loops SEMI exp SEMI assig_loops EP SBLOCK code_block EBLOCK  {$$=mk4son("FOR2",$3,$5,$7,$10);}
			| FOR BP assig_loops SEMI exp SEMI assig_loops EP st2 {$$=mk4son("FOR",$3,$5,$7,$9);}
			| DO SBLOCK code_block EBLOCK WHILE BP exp EP SEMI  {$$=mk2son("DO-WHILE",$3,$7);} ;

			;


dec_loops:VAR type assig_loops {char s[20]="VAR "; /*strcat(s,$1->token) */;  $$=mk1son(s,$3);}; //-----------------------------------
assig_loops:id EQ exp {$$=mk2son("=",$1,$3);};

id: ID {$$=mkleaf(strdup(yytext));};

%%
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
