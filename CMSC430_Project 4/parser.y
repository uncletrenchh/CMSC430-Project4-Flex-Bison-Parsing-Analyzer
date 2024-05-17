/* Omoniyi Tomjones	
   CMSC 430 Compiler Theory and Design
   Project 4
   Spring 2024
   
   Project 4 Parser with semantic actions for static semantic errors */

%{
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "types.h"
#include "listing.h"
#include "symbols.h"

int yylex();
Types find(Symbols<Types>& table, CharPtr identifier, string tableName);
void yyerror(const char* message);

Symbols<Types> scalars;
Symbols<Types> lists;

%}

%define parse.error verbose

%union {
	double value;
	CharPtr iden;
	Types type;
}

%token <iden> IDENTIFIER

%token <type> INT_LITERAL CHAR_LITERAL REAL_LITERAL

%token ADDOP MULOP RELOP ANDOP ARROW EXPOP NOTOP REMOP

%token BEGIN_ CASE CHARACTER ELSE END ENDSWITCH FUNCTION INTEGER IS LIST OF OTHERS
	RETURNS SWITCH WHEN REAL IF ELSIF THEN ENDIF LEFT FOLD ENDFOLD

%type <type> list expressions body type statement_ statement cases case expression
	term primary elsifs condition relation

%%

function:	
	function_header optional_variable body ;
	
function_header:	
	FUNCTION IDENTIFIER RETURNS type ';' ;

type:
	REAL {$$ = REAL_TYPE;} |
	INTEGER {$$ = INT_TYPE;} |
	CHARACTER {$$ = CHAR_TYPE; } ;
	
optional_variable:
	variable |
	variable optional_variable |
	%empty ;
    
variable:	
	IDENTIFIER ':' type IS statement ';' {checkAssignment($3, $5, "Variable Initialization"); scalars.insert($1, $3);} |
	IDENTIFIER ':' LIST OF type IS list ';' {checkAssignmentList($5, $7, "Element Types"); checkList($7); lists.insert($1, $5);}; 

list:
	'(' expressions ')' {$$ = $2;};

expressions:
	expressions ',' expression {$$ = checkList($1);} |
	expression ',' expression ',' expression |
	primary |
	expression ;

body:
	BEGIN_ statement_ END ';' {$$ = $2;} ;
    
statement_:
	statement ';' |
	error ';' {$$ = MISMATCH;} ;
	
statement:
	expression |
	FOLD LEFT ADDOP expression ENDFOLD {$$ = $4; } |
	WHEN condition ',' expression ':' expression 
		{$$ = checkWhen($4, $6);} |
	SWITCH expression IS cases OTHERS ARROW statement ';' ENDSWITCH 
		{$$ = checkSwitch($2, $4, $7);} |
	IF condition elsif ENDIF {$$ = $2;} ;

cases:
	cases case {$$ = checkCases($1, $2);} |
	%empty {$$ = NONE;} ;
	
case:
	CASE INT_LITERAL ARROW statement ';' {$$ = $4;} ;

elsif:
	elsifs elsif |
	%empty;

elsifs:
	THEN statement_ {$$ = checkElsif($2); } |
	ELSE statement_ {$$ = checkElsif($2);} |
	ELSIF condition THEN statement_ {$$ = checkElsif($4);} ;

condition:
	condition ANDOP relation |
	relation ;

relation:
	'(' condition')' {$$ = $2;} |
	expression RELOP expression {$$ = checkIf($1, $3);} ;
	
expression:
	NOTOP expression {$$ = checkCharacter($$); } |
	expression ADDOP term {$$ = checkArithmetic($1, $3);} |
	'(' expressions ')' {checkFold($2);} |
	term ;

term:
	term REMOP primary {$$ = checkRem ($1, $3);} |
	term EXPOP primary {$$ = checkPower($1, $3);} |
	term MULOP primary {$$ = checkProduct($1, $3);} |
	primary ;

primary:
	
	'(' expression ')' {$$ = $2;} |
	INT_LITERAL | 
	REAL_LITERAL |
	CHAR_LITERAL |
	IDENTIFIER '(' expression ')' {$$ = find(lists, $1, "List"); checkBody($3);} |
	IDENTIFIER  {$$ = find(scalars, $1, "Scalar");} ;

%%

Types find(Symbols<Types>& table, CharPtr identifier, string tableName) {
	Types type;
	if (!table.find(identifier, type)) {
		appendError(UNDECLARED, tableName + " " + identifier);
		return MISMATCH;
	}
	return type;
}

void yyerror(const char* message) {
	appendError(SYNTAX, message);
}

int main(int argc, char *argv[]) {
	firstLine();
	yyparse();
	lastLine();
	return 0;
} 
