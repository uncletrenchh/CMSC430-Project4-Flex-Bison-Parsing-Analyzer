// Omoniyi Tomjones	
// CMSC 430 Compiler Theory and Design
// Project 4
// Spring 2024

// This file contains type definitions and the function
// prototypes for the type checking functions

typedef char* CharPtr;

enum Types {MISMATCH, INT_TYPE, CHAR_TYPE, REAL_TYPE, NONE};

void checkAssignment(Types lValue, Types rValue, string message);
void checkAssignmentList(Types lValue, Types rValue, string message);
Types checkWhen(Types true_, Types false_);
Types checkSwitch(Types case_, Types when, Types other);
Types checkCases(Types left, Types right);
Types checkArithmetic(Types left, Types right);
Types checkList(Types expressions_);
Types checkBody(Types primary_);
Types checkIf(Types left, Types right);
Types checkPower (Types left, Types right);
Types checkCharacter(char c);
Types checkRem(Types left, Types right);
Types checkElsif (Types elsifs_);
Types checkFold(Types fold_);
Types checkProduct(Types left, Types right);