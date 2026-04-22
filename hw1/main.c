#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int isWhiteSpace(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

int main() {
    FILE *file = fopen(__FILE__, "r");
    if (file == NULL) {
        printf("無法開啟檔案\n");
        return 1;
    }

    int ch;
    char token[256];
    int i;

    while ((ch = fgetc(file)) != EOF) {
        /* 忽略空白 */
        if (isWhiteSpace((char)ch)) {
            continue;
        }

        /* 辨識 keyword 或 id */
        if (isLetter((char)ch)) {
            i = 0;
            token[i++] = (char)ch;

            while ((ch = fgetc(file)) != EOF) {
                if (isLetter((char)ch) || isDigit((char)ch) || ch == '_') {
                    token[i++] = (char)ch;
                } else {
                    ungetc(ch, file);
                    break;
                }
            }
            token[i] = '\0';

            if (strcmp(token, "int") == 0) {
                printf("%s: TYPE_TOKEN\n", token);
            } else if (strcmp(token, "main") == 0) {
                printf("%s: MAIN_TOKEN\n", token);
            } else if (strcmp(token, "if") == 0) {
                printf("%s: IF_TOKEN\n", token);
            } else if (strcmp(token, "else") == 0) {
                printf("%s: ELSE_TOKEN\n", token);
            } else if (strcmp(token, "while") == 0) {
                printf("%s: WHILE_TOKEN\n", token);
            } else {
                printf("%s: ID_TOKEN\n", token);
            }
        }

        /* 辨識數字 */
        else if (isDigit((char)ch)) {
            i = 0;
            token[i++] = (char)ch;

            while ((ch = fgetc(file)) != EOF) {
                if (isDigit((char)ch)) {
                    token[i++] = (char)ch;
                } else {
                    ungetc(ch, file);
                    break;
                }
            }
            token[i] = '\0';

            printf("%s: LITERAL_TOKEN\n", token);
        }

        /* 辨識符號 */
        else if (ch == '(') {
            printf("(: LEFTPAREN_TOKEN\n");
        } else if (ch == ')') {
            printf("): RIGHTPAREN_TOKEN\n");
        } else if (ch == '{') {
            printf("{: LEFTBRACE_TOKEN\n");
        } else if (ch == '}') {
            printf("}: RIGHTBRACE_TOKEN\n");
        } else if (ch == ';') {
            printf(";: SEMICOLON_TOKEN\n");
        } else if (ch == '+') {
            printf("+: PLUS_TOKEN\n");
        } else if (ch == '-') {
            printf("-: MINUS_TOKEN\n");
        } else if (ch == '=') {
            int next = fgetc(file);
            if (next == '=') {
                printf("==: EQUAL_TOKEN\n");
            } else {
                if (next != EOF) {
                    ungetc(next, file);
                }
                printf("=: ASSIGN_TOKEN\n");
            }
        } else if (ch == '>') {
            int next = fgetc(file);
            if (next == '=') {
                printf(">=: GREATEREQUAL_TOKEN\n");
            } else {
                if (next != EOF) {
                    ungetc(next, file);
                }
                printf(">: GREATER_TOKEN\n");
            }
        } else if (ch == '<') {
            int next = fgetc(file);
            if (next == '=') {
                printf("<=: LESSEQUAL_TOKEN\n");
            } else {
                if (next != EOF) {
                    ungetc(next, file);
                }
                printf("<: LESS_TOKEN\n");
            }
        }

        /* 其他不處理的字元 */
        else {
            printf("Lexical error: %c\n", ch);
        }
    }

    fclose(file);
    return 0;
}
