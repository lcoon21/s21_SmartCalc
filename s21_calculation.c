#include "s21_calculation.h"

lexeme readLexeme(char *lexem, int *iter) {
    lexeme result = {0};
    int i = *iter;
    if (lexem[i] == 'x') {
        result.type = X_LEXEME;
        result.priority = 0;
        result.value = 0;
        i++;
    } else if (lexem[i] == '+') {
        result.type = PLUS_LEXEME;
        result.priority = 1;
        result.value = 0;
        i++;
    } else if (lexem[i] == '-') {
        result.type = MINUS_LEXEME;
        result.priority = 1;
        result.value = 0;
        i++;
    } else if (lexem[i] == '/') {
        result.type = DIVIDE_LEXEME;
        result.priority = 2;
        result.value = 0;
        i++;
    } else if (lexem[i] == '*') {
        result.type = MULTIPLY_LEXEME;
        result.priority = 2;
        result.value = 0;
        i++;
    } else if (lexem[i] == '^') {
        result.type = POWER_LEXEME;
        result.priority = 3;
        result.value = 0;
        i++;
    } else if (lexem[i] == 'm' && lexem[i + 1] == 'o' && lexem[i + 2] == 'd') {
        result.type = MODULATE_LEXEME;
        result.priority = 2;
        result.value = 0;
        i += 3;
    } else if (lexem[i] == 'c' && lexem[i + 1] == 'o' && lexem[i + 2] == 's') {
        result.type = COS_LEXEME;
        result.priority = 5;
        result.value = 0;
        i += 3;
    } else if (lexem[i] == 's' && lexem[i + 1] == 'i' && lexem[i + 2] == 'n') {
        result.type = SIN_LEXEME;
        result.priority = 5;
        result.value = 0;
        i += 3;
    } else if (lexem[i] == 't' && lexem[i + 1] == 'a' && lexem[i + 2] == 'n') {
        result.type = TAN_LEXEME;
        result.priority = 5;
        result.value = 0;
        i += 3;
    } else if (lexem[i] == 'a' && lexem[i + 1] == 'c' && lexem[i + 2] == 'o' && lexem[i + 3] == 's') {
        result.type = ACOS_LEXEME;
        result.priority = 5;
        result.value = 0;
        i += 4;
    } else if (lexem[i] == 'a' && lexem[i + 1] == 's' && lexem[i + 2] == 'i' && lexem[i + 3] == 'n') {
        result.type = ASIN_LEXEME;
        result.priority = 5;
        result.value = 0;
        i += 4;
    } else if (lexem[i] == 'a' && lexem[i + 1] == 't' && lexem[i + 2] == 'a' && lexem[i + 3] == 'n') {
        result.type = ATAN_LEXEME;
        result.priority = 5;
        result.value = 0;
        i += 4;
    } else if (lexem[i] == 's' && lexem[i + 1] == 'q' && lexem[i + 2] == 'r' && lexem[i + 3] == 't') {
        result.type = SQRT_LEXEME;
        result.priority = 5;
        result.value = 0;
        i += 4;
    } else if (lexem[i] == 'l' && lexem[i + 1] == 'n') {
        result.type = LN_LEXEME;
        result.priority = 5;
        result.value = 0;
        i += 2;
    } else if (lexem[i] == 'l' && lexem[i + 1] == 'o' && lexem[i + 2] == 'g') {
        result.type = LOG_LEXEME;
        result.priority = 5;
        result.value = 0;
        i += 3;
    } else if (lexem[i] == '(') {
        result.type = LEFT_LEXEME;
        result.priority = -1;
        result.value = 0;
        i++;
    } else if (lexem[i] == ')') {
        result.type = RIGHT_LEXEME;
        result.priority = -1;
        result.value = 0;
        i++;
    }
    *iter = i;
    return result;
}

lexeme calculationSimple(double num1, double num2, int type) {
    lexeme result;
    result.priority = 0;
    result.type = NUMBER_LEXEME;
    if (type == PLUS_LEXEME) {
        result.value = num1 + num2;
    } else if (type == MINUS_LEXEME) {
        result.value = num1 - num2;
    } else if (type == DIVIDE_LEXEME) {
        result.value = num1 / num2;
    } else if (type == MULTIPLY_LEXEME) {
        result.value = num1 * num2;
    } else if (type == POWER_LEXEME) {
        result.value = pow(num1, num2);
    } else if (type == MODULATE_LEXEME) {
        result.value = fmod(num1, num2);
    }
    return result;
}

lexeme calculationHarder(double num, int type) {
    lexeme result;
    result.priority = 0;
    result.type = NUMBER_LEXEME;
    if (type == COS_LEXEME) {
        result.value = cos(num);
    } else if (type == SIN_LEXEME) {
        result.value = sin(num);
    } else if (type == TAN_LEXEME) {
        result.value = tan(num);
    } else if (type == ACOS_LEXEME) {
        result.value = acos(num);
    } else if (type == ASIN_LEXEME) {
        result.value = asin(num);
    } else if (type == ATAN_LEXEME) {
        result.value = atan(num);
    } else if (type == SQRT_LEXEME) {
        result.value = sqrt(num);
    } else if (type == LN_LEXEME) {
        result.value = log(num);
    } else if (type == LOG_LEXEME) {
        result.value = log10(num);
    }
    return result;
}


double readStr(char* str, double x) {
    lexeme *stackNum = NULL;
    lexeme *stackSim = NULL;
    int i = 0;
    if (str[0] == '-' || str[0] == '+') {
        push(&stackNum, 0, NUMBER_LEXEME, 0);  //запуш нолек если унарный минус
    }
    int length = strlen(str);
    while (i < length) {
        if (*(str + i) >= '0' && (*(str + i) <= '9' || *(str + i) == '.')) {
            lexeme num = read_number(str, &i);
            push(&stackNum, num.value, NUMBER_LEXEME, 0);
        } else {
            lexeme tmp = readLexeme(str, &i);
            if (i > 1 && *(str+i-2) == '(' && (tmp.type == MINUS_LEXEME || tmp.type == PLUS_LEXEME)) {
                push(&stackNum, 0, NUMBER_LEXEME, 0);
            }
            mainLogic(&stackNum, &stackSim, tmp, x);
        }
    }
    while (stackSim != NULL && stackNum != NULL) {
        vichislenie(&stackNum, &stackSim);
    }
    lexeme result = top(&stackNum);
    double resultt = result.value;
    pop(&stackNum);
    return resultt;
}

void mainLogic(lexeme **stackNum, lexeme **stackSim, lexeme this, double x) {
    lexeme topStack;

    if (*stackSim != NULL) {
        topStack = top(stackSim);
    } else {
       topStack.priority = -1;
    }
    if (this.type == X_LEXEME) {
        push(stackNum, x, NUMBER_LEXEME, 1);
    } else if (this.type == LEFT_LEXEME) {
        push(stackSim, 0, LEFT_LEXEME, -1);
    } else if (this.priority > topStack.priority && this.type != RIGHT_LEXEME) {
        push(stackSim, 0, this.type, this.priority);
    } else if (this.priority <= topStack.priority && this.type != RIGHT_LEXEME &&
    this.type != LEFT_LEXEME) {
        vichislenie(stackNum, stackSim);
        push(stackSim, this.value, this.type, this.priority);
    } else if (this.type == RIGHT_LEXEME) {
        while (stackSim && topSimType(stackSim) !=  LEFT_LEXEME) {
            vichislenie(stackNum, stackSim);
        }
        pop(stackSim);  // pop left skobka
    }
}

void vichislenie(lexeme **stackNum, lexeme **stackSim) {
    lexeme operator = pop(stackSim);
    lexeme value1;
    lexeme value2;
    if (operator.type > 8) {
        value2 = pop(stackNum);
    } else {
        value1 = pop(stackNum);
        value2 = pop(stackNum);
    }
    lexeme result;
    if (operator.type <= 8) {
        result = calculationSimple(value2.value, value1.value, operator.type);
    } else {
        result = calculationHarder(value2.value, operator.type);
    }
    push(stackNum, result.value, result.type, result.priority);
}

lexeme read_number(const char *input, int *j) {
    lexeme result = {0};
    int count = 1, flag = 0;
    int i = *j;
    for (; i < (int)strlen(input) &&
           ((input[i] >= 48 && input[i] <= 57) || input[i] == 46);
         i++) {
        result.type = NUMBER_LEXEME;
        if (input[i] == 46) {
            flag = 1;
            count = 10;
            i++;
        }
        if (flag) {
            int temp = input[i] - '0';
            double temp2 = (double)temp / count;
            result.value = result.value + temp2;
            count *= 10;
        } else {
            result.value = result.value * count;
            result.value = result.value + input[i] - '0';
            count = 10;
        }
        result.priority = 0;
    }
    *j = i;
    return result;
}

int check(char* str) {
    int res = 1, cnt = 0, scob = 0;
    while (cnt != (int)strlen(str)) {
        if (str[cnt] == 'x' && cnt != 0 && cnt != (int)strlen(str)) {
            if (str[cnt-1] == ')' || str[cnt+1] == '(' || (str[cnt-1] <= '9' && str[cnt-1] >= '0')
            || (str[cnt+1] <= '9' && str[cnt+1] >= '0')
            || str[cnt+1] == 's' || str[cnt+1] == 'c' || str[cnt+1] == 't' || str[cnt+1] == 'a' ||
            str[cnt+1] == 'l' || str[cnt+1] == 'm'
            || str[cnt+1] == 'i' || str[cnt+1] == 'o' || str[cnt+1] == 'q' || str[cnt+1] == 'n') {
                res = 0;
            }
        }
        if (str[cnt] == '.') {
            if (cnt == 0 || cnt == (int)strlen(str) - 1) {
                res = 0;
            } else {
                if ((str[cnt-1] >= '9' && str[cnt-1] <= '0') || (str[cnt+1] >= '9' && str[cnt+1] <= '0')) {
                    res = 0;
                }
            }
        } else if (str[cnt] == '+' || str[cnt] == '-' || str[cnt] == '*' || str[cnt] == '/' ||
        str[cnt] == '^') {
            if (cnt == 0) {
                if (str[cnt] != '-') {
                    res = 0;
                } else if (str[cnt] == '-' && str[cnt + 1] <= '0' && str[cnt + 1] >= '9') {
                    res = 0;
                } else if (cnt == (int)strlen(str) - 1) {
                    res = 0;
                } else {
                    if ((str[cnt-1] != ')' && str[cnt-1] > '9' && str[cnt-1] < '0') ||
                    (str[cnt+1] < '0' && str[cnt+1] > '9') || str[cnt+1] == 'm' ||
                    str[cnt+1] == '+' || str[cnt+1] == '-' || str[cnt+1] == '*' || str[cnt+1] == '/'
                    || str[cnt+1] == '^') {
                        res = 0;
                    }
                }
            }
        } else if (str[cnt] == ')') {
            scob -= 1;
            if (scob == -1) {
                res = 0;
            }
            if (cnt != 0) {
                if (str[cnt-1] == '+' || str[cnt-1] == '/' || str[cnt-1] == '*' || str[cnt-1] == '-' ||
                str[cnt-1] == '^' || str[cnt-1] == '(') {
                    res = 0;
                }
                if ((str[cnt+1] == 's' && str[cnt+2] == 'i' && str[cnt+3] == 'n') ||
                (str[cnt+1] == 'c' && str[cnt+2] == 'o' && str[cnt+3] == 's') ||
                (str[cnt+1] == 't' && str[cnt+2] == 'a' && str[cnt+3] == 'n')
                || (str[cnt+1] == 'a' && str[cnt+2] == 's' && str[cnt+3] == 'i' && str[cnt+4] == 'n') ||
                (str[cnt+1] == 'a' && str[cnt+2] == 'c' && str[cnt+3] == 'o' && str[cnt+4] == 's') ||
                (str[cnt+1] == 'l' && str[cnt+2] == 'n') ||
                (str[cnt+1] == 'l' && str[cnt+2] == 'o' && str[cnt+3] == 'g') ||
                (str[cnt+1] == 'a' && str[cnt+2] == 't' && str[cnt+3] == 'a' && str[cnt+4] == 'n') ||
                (str[cnt+1] == 's' && str[cnt+2] == 'q' && str[cnt+3] == 'r' && str[cnt+4] == 't') ||
                (str[cnt+1] == 'm' && str[cnt+2] == 'o' && str[cnt+3] == 'd')) {
                    res = 0;
                }
            } else {
                res = 0;
            }
        } else if (str[cnt] == '(') {
            scob += 1;
            if (cnt != (int)strlen(str) - 1) {
                if (str[cnt+1] == '+' || str[cnt+1] == '/' || str[cnt+1] == '*' ||
                str[cnt+1] == '^' || str[cnt+1] == ')') {
                    res = 0;
                }
                if (str[cnt-1] <= '9' && str[cnt-1] >= '0') {
                    res = 0;
                }
            } else {
                res = 0;
            }
        } else if ((str[cnt] == 's' && str[cnt+1] == 'i' && str[cnt+2] == 'n') ||
                (str[cnt] == 'c' && str[cnt+1] == 'o' && str[cnt+2] == 's') ||
                (str[cnt] == 't' && str[cnt+1] == 'a' && str[cnt+2] == 'n')
                || (str[cnt] == 'a' && str[cnt+1] == 's' && str[cnt+2] == 'i' && str[cnt+3] == 'n') ||
                (str[cnt] == 'a' && str[cnt+1] == 'c' && str[cnt+2] == 'o' && str[cnt+3] == 's') ||
                (str[cnt] == 'l' && str[cnt+1] == 'n') ||
                (str[cnt] == 'l' && str[cnt+1] == 'o' && str[cnt+2] == 'g') ||
                (str[cnt] == 'a' && str[cnt+1] == 't' && str[cnt+2] == 'a' && str[cnt+3] == 'n') ||
                (str[cnt] == 's' && str[cnt+1] == 'q' && str[cnt+2] == 'r' && str[cnt+3] == 't')) {
            if ((cnt != 0 && str[cnt-1] == ')') || (str[cnt-1] <= '9' && str[cnt-1] >= '0')) {
                res = 0;
            }
        } else if (str[cnt] == 'm' && str[cnt+1] == 'o' && str[cnt+2] == 'd') {
            if ((cnt == 0 && str[cnt] == 'm') || (str[cnt] == 'd' && cnt == (int)strlen(str)-1)) {
                res = 0;
            } else if (cnt != 0 && str[cnt] == 'm' && (str[cnt-1] == '(' || str[cnt-1] == '+' ||
            str[cnt-1] == '/' || str[cnt-1] == '*' || str[cnt-1] == '-' || str[cnt-1] == '^')) {
                res = 0;
            } else if (cnt != (int)strlen(str) - 1 && str[cnt] == 'd'  && (str[cnt + 1] == '+' ||
            str[cnt + 1] == '/' || str[cnt + 1] == '*' || str[cnt + 1] == '-' || str[cnt + 1] == '^')) {
                res = 0;
            }
        }
        cnt++;
    }
    if (scob != 0) {
        res = 0;
    }
    return res;
}
