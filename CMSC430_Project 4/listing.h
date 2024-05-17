// Omoniyi Tomjones	
// CMSC 430 Compiler Theory and Design
// Project 4
// Spring 2024


// This file contains the function prototypes for the functions that produce the 
// compilation listing

enum ErrorCategories {LEXICAL, SYNTAX, GENERAL_SEMANTIC, DUPLICATE_IDENTIFIER,
	UNDECLARED};

void firstLine();
void nextLine();
int lastLine();
void appendError(ErrorCategories errorCategory, string message);

