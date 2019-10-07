%{
#include <cstdio>
#include <climits>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include "exp.h"

using namespace std;

list<pgm *> root_list;
int line_num = 1;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

ofstream flex_out, bison_out, xml_out;
 
void yyerror(const char *s);
%}

%union {
	bool boolean;
	int ival; 
	char c; 
	char *sval;
	exp_node *expnode;
	list<exp_node *> *expnodelist;
	list<statement *> *stmts;
	list<calloutArgs *> *calloutargs;
	calloutArgs *cst;
	statement *st;
	pgm *prog;
}

%error-verbose

%token SNAZZLE TYPE

%token <sval> PROGRAM
%token <sval> VOID
%token <ival> INT
%token <sval> BOOLEAN
%token <sval> CALLOUT
%token <sval> CLASS
%token <sval> FALSE
%token <sval> TRUE
%token <sval> INTEGER
%token <sval> STRING
%token <sval> ID
%token <sval> IF
%token <sval> ELSE
%token <sval> CONTINUE
%token <sval> BREAK
%token <sval> FOR
%token <sval> RETURN
%token <c> CHAR
%token <sval> GE
%token <sval> LE
%token <sval> EE
%token <sval> NE
%token <sval> AA
%token <sval> OO
%type <expnode> exp
%type <expnode> t0
%type <expnode> t1
%type <expnode> t2
%type <expnode> t3
%type <expnode> t4
%type <expnodelist> exps
%type <stmts> body_lines
%type <prog> block
%type <calloutargs> callout_args
%type <cst> callout_arg
%type <st> body_line

%%

program:
	CLASS PROGRAM '{' field_decl '}' { bison_out << "PROGRAM ENCOUNTERED" << endl; }
	;
field_decl:
	type_lines		
	;
type_lines:
	type_lines type_line
     	|  type_line 		
	;
type_line:
	INTEGER IDS ';' // { bison_out << "INT DECLARATION ENCOUNTERED. ID=" << $2 << endl; update_decl_table($2, "integer", 0);}
	| INTEGER ID '[' INT ']' ';' { bison_out << "INT DECLARATION ENCOUNTERED. ID=" << $2 << " SIZE=" << $4 << endl;  update_decl_table($2, "integer", $4);}
	| BOOLEAN ID ';' { bison_out << "BOOLEAN DECLARATION ENCOUNTERED. ID=" << $2 << endl;  update_decl_table($2, "boolean", 0);}
	| BOOLEAN ID '[' INT ']' ';'	{ bison_out << "BOOLEAN DECLARATION ENCOUNTERED. ID=" << $2 << " SIZE=" << $4 << endl; update_decl_table($2, "boolean", $4); }
	| INTEGER ID '(' ')' block 		{ root_list.push_back($5); }
	| INTEGER ID '(' params ')' block 	{ root_list.push_back($6); }
	| BOOLEAN ID '(' ')' block		{ root_list.push_back($5); }
	| BOOLEAN ID '(' params ')' block	{ root_list.push_back($6); }
	| VOID ID '(' ')' block 		{ root_list.push_back($5); }
	| VOID ID '(' params ')' block 		{ root_list.push_back($6); }
	;
IDS:
   IDS ',' ID    { update_decl_table($3, "integer", 0); }
   | ID		{ update_decl_table($1, "integer", 0); }
   ;							

params:
      param ',' params		
      | param
      ;
param:
     INTEGER ID
     | BOOLEAN ID
     ;
block:
     '{' var_lines body_lines '}' { bison_out << "BLOCK ENCOUNTERED" << endl; $$ = new pgm($3);}
      ;
var_lines:
	var_lines var_line
	|
	;
var_line:
	INTEGER IDS ';' // { bison_out << "INT DECLARATION ENCOUNTERED. ID=" << $2 << endl; update_decl_table($2, "integer", 0);}
        | BOOLEAN ID ';' { bison_out << "BOOLEAN DECLARATION ENCOUNTERED. ID=" << $2 << endl;  update_decl_table($2, "boolean", 0);}
	;

//statement_decl:
//	body_lines
//	;
body_lines:
	body_lines body_line {
              $$ = $1;
              $1->push_back($2);
            }
//	| body_line 
	| { $$ = new list<statement *>(); }
	;
body_line:
	ID '=' exp ';' { $$ = new assignment_stmt1($1, $3); }
	| ID '[' exp ']' '=' exp ';' {  $$ = new assignment_stmt($1, $3, $6); }			
//	| ID '(' ')' ';'	{ $$ = new method_call_stmt($1); }
	| ID '(' exps ')' ';'	{ $$ = new method_call_stmt1($1, $3);}
	| CALLOUT '(' STRING ')' ';' 	{ $$ = new callout_stmt($3); bison_out << "CALLOUT TO " << $3 << "ENCOUNTERED" << endl;}
       	| CALLOUT '(' STRING ',' callout_args ')' ';'	{ $$ = new callout_stmt1($3, $5); bison_out << "CALLOUT TO "<< $3 << " ENCOUNTERED" << endl; }
	| IF '(' exp ')' block 		{ $$ = new if_stmt($3, $5); }
	| IF '(' exp ')' block ELSE block	{ $$ = new if_else_stmt($3, $5, $7); }
	| FOR ID '=' exp ',' exp block	{ $$ = new for_stmt($2, $4, $6, $7); }
	| RETURN ';'		{ $$ = new ret_stmt(); }
	| RETURN exp ';'	{ $$ = new ret_exp_stmt($2); }
	| BREAK ';'		{ $$ = new break_stmt(); }
	| CONTINUE ';'		{ $$ = new continue_stmt(); }
	| block			{ $$ = new block_stmt($1); }
	;
exps: 
    exp ',' exps	{ $$ = $3; $3->push_back($1); }	
    | exp{$$ = new list<exp_node *>(); $$->push_back($1); }		
    ;

callout_args:
	callout_args ',' callout_arg{
		$$ = $1;
		$1->push_back($3);	
	}
	| {$$ = new list<calloutArgs *>();}
	;
callout_arg:
	exp { $$ = new calloutEXP($1); }
	| STRING { $$ = new calloutSTR($1); }
	;
exp:
	exp '<' t0 { bison_out << "LESS THAN ENCOUTERED" << endl;  $$ = new lesser_node($1, $3); }
	| exp '>' t0 { bison_out << "GREATER THAN ENCOUNTERED" << endl;  $$ = new greater_node($1, $3); }
	| exp LE t0 { bison_out << "GREATER THAN ENCOUNTERED" << endl;  $$ = new lesser_equal_node($1, $3); }
	| exp GE t0 { bison_out << "GREATER THAN ENCOUNTERED" << endl;  $$ = new greater_equal_node($1, $3); }
	| exp AA t0 { bison_out << "GREATER THAN ENCOUNTERED" << endl;  $$ = new and_node($1, $3); }
	| exp OO t0 { bison_out << "GREATER THAN ENCOUNTERED" << endl;  $$ = new or_node($1, $3); }
	| exp NE t0 { bison_out << "GREATER THAN ENCOUNTERED" << endl;  $$ = new equal_node($1, $3); }
	| exp EE t0 { bison_out << "GREATER THAN ENCOUNTERED" << endl;  $$ = new not_equal_node($1, $3); }
	| t0
	;
t0:
	t0 '+' t1 { bison_out << "ADDITION ENCOUNTERED" << endl;  $$ = new plus_node($1, $3); }
	| t0 '-' t1 { bison_out << "SUBTRACTION ENCOUNTERED" << endl;  $$ = new minus_node($1, $3);}
	| t1
	;
t1:
	 t1 '*' t2 { bison_out << "MULTIPLICATION ENCOUNTERED" << endl;  $$ = new times_node($1, $3); }
 	| t1 '/' t2 { bison_out << "DIVISION ENCOUNTERED" << endl;  $$ = new divide_node($1, $3); }
	| t1 '%' t2 { bison_out << "MOD ENCOUNTERED" << endl;  $$ = new mod_node($1, $3); }
	| t2
	;
t2:
	 '!' t3 { $$ = new not_node($2); }
	| t3
	;
t3:
	 '-' t4 { $$ = new unary_minus_node($2); }
	| t4
	;
t4:
	 INT	{ bison_out << "INT ENCOUNTERED=" << $1 << endl; $$ = new int_node($1); }
	| BOOLEAN { bison_out << "BOOLEAN ENCOUNTERED=" << $1 << endl; $$ = new boolean_node($1); } 
	| CHAR { bison_out << "CHAR ENCOUNTERED=" << $1 << endl; $$ = new char_node($1);}
	| ID	{ bison_out << "LOCATION ENCOUNTERED=" << $1 << endl; $$ = new id_node($1); }
	| ID '[' exp ']' { bison_out << "LOCATION ENCOUNTERED=" << $1 << endl; $$ = new ids_node($1, $3); }
	;
%%

int main(int argc, char** argv) {
	FILE *myfile = fopen(argv[1], "r");
	if (!myfile) {
		cout << "I can't open " << argv[1] << "!" << endl;
		return -1;
	}
	yyin = myfile;

	flex_out.open("flex_output.txt");
	bison_out.open("bison_output.txt");
	xml_out.open("output.xml");
//	do {
		yyparse();
//	} while (!feof(yyin));
	list<pgm *>::iterator it = root_list.begin();
	while(it!=root_list.end())
	{
		(*it)->evaluate();
		it++;
	}
	return 0;
}

void yyerror(const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	exit(-1);
}

