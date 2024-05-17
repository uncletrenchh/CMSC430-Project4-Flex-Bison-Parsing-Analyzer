// Omoniyi Tomjones	
// CMSC 430 Compiler Theory and Design
// Project 4
// Spring 2024

// This file contains the bodies of the functions that produces the 
// compilation listing

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

#include "listing.h"

static int lineNumber;
static int lexicalErrors;
static int syntaxErrors;
static int semanticErrors;
static vector<string> errors;

static void displayErrors();

void firstLine() {
	lexicalErrors = 0;
	syntaxErrors = 0;
	semanticErrors = 0;
	lineNumber = 1;
	printf("\n%4d  ",lineNumber);
}

void nextLine() {
	displayErrors();
	lineNumber++;
	printf("%4d  ",lineNumber);
}

int lastLine() {
	printf("\r");
	displayErrors();
	printf("     \n");
	int totalErrors = lexicalErrors + syntaxErrors + semanticErrors;
	if (totalErrors > 0)
	{
		printf("Lexical Errors %d\n", lexicalErrors);
		printf("Syntax Errors %d\n", syntaxErrors);
		printf("Semantic Errors %d\n", semanticErrors);

	}
	else
		printf("Compiled Successfully\n\n");
	return totalErrors;
}
    
void appendError(ErrorCategories errorCategory, string message) {
	string messages[] = { "Lexical Error, Invalid Character ", 
	"Syntax Error, U", "Semantic Error, ",
	"Semantic Error, Duplicate ", 
	"Semantic Error, Undeclared " };

	switch (errorCategory) {
		case LEXICAL:
			lexicalErrors++;
			break;
		case SYNTAX:
			message = message.substr(15);
			syntaxErrors++;
			break;
		case GENERAL_SEMANTIC:
		case DUPLICATE_IDENTIFIER:
		case UNDECLARED:
			semanticErrors++;
			break;
    }
	errors.push_back(messages[errorCategory] + message);
}

void displayErrors() {
	for (int i = 0; i < errors.size(); i++)
		printf("%s\n", errors[i].c_str());
	errors.clear();
}
