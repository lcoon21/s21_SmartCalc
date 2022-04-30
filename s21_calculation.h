#ifndef SRC_S21_CALCULATION_H_
#define SRC_S21_CALCULATION_H_

#include "s21_stack.h"

lexeme readLexeme(char *lexem, int *iter);

lexeme calculationSimple(double num1, double num2, int type);
lexeme calculationHarder(double num, int type);

double readStr(char* str, double x);
void mainLogic(lexeme **stackNum, lexeme **stackSim, lexeme this1, double x);
void vichislenie (lexeme **stackNum, lexeme **stackSim);
lexeme read_number(const char *input, int *j);

int check(char* str);

#ifdef DEBUG
void printformula(entity *input);
#endif

#endif  // SRC_S21_CALCULATION_H_
