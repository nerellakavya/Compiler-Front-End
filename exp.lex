%{
#include <iostream>
#include<string.h>
#include<fstream>

using namespace std;
#define YY_DECL extern "C" int yylex()
#include "exp.h"
#include "y.tab.h" 
extern "C" ofstream flex_out; 

%}
%%
[ \t\n]         ;
[P][r][o][g][r][a][m]		{  yylval.sval = strdup(yytext); return PROGRAM;}
[v][o][i][d]			{ yylval.sval = strdup(yytext); return VOID;}
[i][f]				{ yylval.sval = strdup(yytext); return IF;}
[e][l][s][e]			{ yylval.sval = strdup(yytext); return ELSE;}
[f][o][r]			{ yylval.sval = strdup(yytext); return FOR;}
[b][r][e][a][k]			{ yylval.sval = strdup(yytext); return BREAK;}
[c][o][n][t][i][n][u][e] 	{ yylval.sval = strdup(yytext); return CONTINUE;}
[r][e][t][u][r][n] 		{ yylval.sval = strdup(yytext); return RETURN;}
[b][o][o][l][e][a][n]		{ flex_out << "BOOLEAN_DECLARATION" << endl; yylval.sval = strdup(yytext); return BOOLEAN;}
[c][a][l][l][o][u][t]		{ flex_out << "CALLOUT" << endl;  yylval.sval = strdup(yytext); return CALLOUT;}
[c][l][a][s][s]			{ flex_out << "CLASS" << endl;  yylval.sval = strdup(yytext); return CLASS;}
[f][a][l][s][e]			{ flex_out << "BOOLEAN: false" << endl; yylval.sval = strdup(yytext); return FALSE; }
[i][n][t]       { flex_out << "INT_DECLARATION" << endl; yylval.sval = strdup(yytext); return INTEGER; }
[t][r][u][e]    { flex_out << "BOOLEAN: true" << endl; yylval.sval = strdup(yytext); return TRUE; }
[a-zA-Z]+    { flex_out << "ID: " << yytext << endl; yylval.sval = strdup(yytext); return ID; }
[0-9]+          { flex_out << "INT: " << yytext << endl; yylval.ival = atoi(yytext); return INT; }
['][a-zA-Z][']        { flex_out << "CHARACTER: " << yytext << endl; yylval.sval = strdup(yytext); return CHAR;}
["][a-zA-Z0-9 ]+["]    { flex_out << "STRING: " << yytext << endl; yylval.sval = strdup(yytext); return STRING;}
[<][=]  { yylval.sval = strdup(yytext); return LE;}
[>][=]	{ yylval.sval = strdup(yytext); return GE;}
[=][=]  { yylval.sval = strdup(yytext); return EE;}
[!][=]  { yylval.sval = strdup(yytext); return NE;}
[&][&]  { yylval.sval = strdup(yytext); return AA;}
[|][|]  { yylval.sval = strdup(yytext); return OO;}
[=!></*+\-\[\]\(\)\{\};,%_~&|]    { return yytext[0];}
%%

