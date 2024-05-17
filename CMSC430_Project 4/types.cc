// Omoniyi Tomjones	
// CMSC 430 Compiler Theory and Design
// Project 4
// Spring 2024

// This file contains the bodies of the type checking functions

#include <string>
#include <vector>

using namespace std;

#include "types.h"
#include "listing.h"

void checkAssignment(Types lValue, Types rValue, string message) {
	if (lValue != MISMATCH && lValue != CHAR_TYPE && rValue != MISMATCH && lValue != rValue)
		appendError(GENERAL_SEMANTIC, "Type Mismatch on " + message);
}

void checkAssignmentList(Types lValue, Types rValue, string message) {
	if (lValue != INT_TYPE && rValue != INT_TYPE && lValue != rValue)
		appendError(GENERAL_SEMANTIC, "List Type Does Not Match " + message);
}

Types checkWhen(Types true_, Types false_) {
	if (true_ == MISMATCH || false_ == MISMATCH)
		return MISMATCH;
	if (true_ != false_)
		appendError(GENERAL_SEMANTIC, "When Types Mismatch ");
	return true_;
}

Types checkSwitch(Types case_, Types when, Types other) {
	if (case_ != INT_TYPE && case_ != CHAR_TYPE)
		appendError(GENERAL_SEMANTIC, "Switch Expression Not Integer or Character");
	return checkCases(when, other);
}

Types checkList(Types expressions_) {
	if (expressions_ == INT_TYPE)
		return MISMATCH;
		appendError(GENERAL_SEMANTIC, "List Element Types Do Not Match");
	return INT_TYPE;
}

Types checkFold(Types fold_) {
	if (fold_ != INT_TYPE)
		return MISMATCH;
		appendError(GENERAL_SEMANTIC, "Fold Requires A Numeric List");
	return INT_TYPE;
}

Types checkElsif (Types elsifs_) {
	if (elsifs_ != INT_TYPE)
		appendError(GENERAL_SEMANTIC, "If-Elsif-Else Type Mismatch");
	return INT_TYPE;
}

Types checkBody(Types primary_) {
	if (primary_ == INT_TYPE)
		return MISMATCH;
		appendError(GENERAL_SEMANTIC, "List Subscript Must Be Integer");
	return INT_TYPE;
}

Types checkCases(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == NONE || left == right)
		return right;
	appendError(GENERAL_SEMANTIC, "Case Types Mismatch");
	return MISMATCH;
}

Types checkArithmetic(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	if (left == CHAR_TYPE && right == INT_TYPE)
		return INT_TYPE;
	if (left == INT_TYPE && right == REAL_TYPE)
		return INT_TYPE;
	appendError(GENERAL_SEMANTIC, "Integer or Character Type Required");
	return MISMATCH;
}

Types checkProduct(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	if (left == CHAR_TYPE && right == INT_TYPE)
		return INT_TYPE;
	appendError(GENERAL_SEMANTIC, "Illegal Narrowing Variable Initialization");
	return MISMATCH;
}

Types checkPower (Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	if (left == CHAR_TYPE && right == INT_TYPE)
		return INT_TYPE;
	appendError(GENERAL_SEMANTIC, "Arithmetic Operator Requires Numeric Types");
	return MISMATCH;
}

Types checkRem(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	appendError(GENERAL_SEMANTIC, "Remainder Operator Requires Integer Operands");
	return MISMATCH;
}

Types checkCharacter(char c) {
    if (!isdigit(c))
        appendError(GENERAL_SEMANTIC, "Arithmetic Operator Requires Numeric Types");
	return INT_TYPE;
}

Types checkIf(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	appendError(GENERAL_SEMANTIC, "Character Literals Cannot be Compared to Numeric Expressions");
	return MISMATCH;
}
