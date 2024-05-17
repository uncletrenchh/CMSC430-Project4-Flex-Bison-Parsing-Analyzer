/* Omoniyi Tomjones	
   CMSC 430 Compiler Theory and Design
   Project 4
   Spring 2024 /*

/* This file contains flex input file */

%{
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

#include "types.h"
#include "listing.h"
#include "tokens.h"

%}

%option noyywrap

ws		[ \t\r]+
comment		"\/\/".*\n|"\-\-".*\n
line		[\n]
hex     ([a-fA-F0-9]+)|(\#[a-fA-F0-9]+)|(\'[a-fA-F0-9]'+)|([a-fA-F])
id		[A-Za-z]([A-Za-z0-9])*
digit		[0-9]|'[0-9]'
dec		{digit}+
char		'.'
real    ({digit}+\.{digit}*|\.{digit}+|\d+\.{digit}*)([eE][+-]?{digit}+)?
punc		[\(\),:;]
%%

{ws}		{ ECHO; }
{comment}	{ ECHO; nextLine(); }
{line}		{ ECHO; nextLine(); }
"+"		{ ECHO; return(ADDOP); }
"-"		{ ECHO; return(ADDOP); }
"*"		{ ECHO; return(MULOP); }
"&"		{ ECHO; return(ANDOP); }
"<"		{ ECHO; return(RELOP); }
"=>"		{ ECHO; return(ARROW); }
"~"      { ECHO; return(NOTOP); }
"^"      { ECHO; return(EXPOP); }
"%"      { ECHO; return(REMOP); }
"="      { ECHO; return(RELOP); }
begin		{ ECHO; return(BEGIN_); }
case		{ ECHO; return(CASE); }
character	{ ECHO; return(CHARACTER); }
end		{ ECHO; return(END); }
endswitch	{ ECHO; return(ENDSWITCH); }
function	{ ECHO; return(FUNCTION); }
integer		{ ECHO; return(INTEGER); }
is		{ ECHO; return(IS); }
list		{ ECHO; return(LIST); }
of		{ ECHO; return(OF); }
if    { ECHO; return(IF); }
else  { ECHO; return(ELSE); }
elsif { ECHO; return(ELSIF); }
then  { THEN; return(THEN); }
endif { ECHO; return(ENDIF); }
real  { ECHO; return(REAL); }
others		{ ECHO; return(OTHERS); }
returns		{ ECHO; return(RETURNS); }
switch		{ ECHO; return(SWITCH); }
when		{ ECHO; return(WHEN); }
fold     { ECHO; return(FOLD); }
endfold     { ECHO; return(ENDFOLD); }
left     { ECHO; return(LEFT); }

{id}		{ ECHO; yylval.iden = (CharPtr)malloc(yyleng + 1); 
			strcpy(yylval.iden, yytext); return(IDENTIFIER);}

{dec}		{ ECHO; yylval.type = INT_TYPE; return(INT_LITERAL); }
{hex}		{ ECHO; char hex_str[yyleng + 3]; sprintf(hex_str, "0x%s", yytext); 
yylval.value = strtol(hex_str, NULL, 16); yylval.type = CHAR_TYPE; return(INT_LITERAL); }
{char}		{ ECHO; yylval.type = CHAR_TYPE; return(CHAR_LITERAL); }
{real}		{ ECHO; yylval.value = atof(yytext); yylval.type = REAL_TYPE; return(REAL_LITERAL); }
{punc}		{ ECHO; return(yytext[0]); }
.		{ ECHO; appendError(LEXICAL, yytext); }
%%
