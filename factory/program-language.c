#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VAR 100

typedef struct {
    char name[32];
    int value;
} Var;

Var vars[MAX_VAR];
int var_count = 0;

Var* get_var(const char* name) {
    for (int i = 0; i < var_count; i++)
        if (strcmp(vars[i].name, name) == 0)
            return &vars[i];
    if (var_count < MAX_VAR) {
        strcpy(vars[var_count].name, name);
        vars[var_count].value = 0;
        return &vars[var_count++];
    }
    return NULL;
}

char* next_token(char** code) {
    while (**code && isspace(**code)) (*code)++;
    if (**code == 0) return NULL;
    char* start = *code;
    while (**code && !isspace(**code)) (*code)++;
    if (**code) **code = 0, (*code)++;
    return start;
}

int parse_int(const char* token) { return atoi(token); }

int eval_expr(char* token1, char* op, char* token2) {
    int a = isalpha(token1[0]) ? get_var(token1)->value : parse_int(token1);
    int b = isalpha(token2[0]) ? get_var(token2)->value : parse_int(token2);
    if (strcmp(op, "+") == 0) return a + b;
    if (strcmp(op, "-") == 0) return a - b;
    if (strcmp(op, "*") == 0) return a * b;
    if (strcmp(op, "/") == 0) return a / b;
    return 0;
}

void exec_line(char* line) {
    char buf[256];
    strncpy(buf, line, sizeof(buf));
    buf[sizeof(buf)-1] = 0;
    char* code = buf;
    // char* code = line;
    char* token = next_token(&code);
    if (!token) return;

    if (strcmp(token, "let") == 0) {
        char* var_name = next_token(&code);
        next_token(&code); // skip "="
        char* val = next_token(&code);
        get_var(var_name)->value = isalpha(val[0]) ? get_var(val)->value : parse_int(val);
    } else if (strcmp(token, "print") == 0) {
        char* var_name = next_token(&code);
        printf("%d\n", get_var(var_name)->value);
    } else {
        char* token1 = token;
        char* op = next_token(&code);
        char* token2 = next_token(&code);
        int res = eval_expr(token1, op, token2);
        printf("%d\n", res);
    }
}

int main() {
    char* program[] = {
        "let x = 10",
        "let y = 20",
        "x + y",
        "let z = x",
        "z + 5",
        "print z",
        NULL
    };

    for (int i = 0; program[i]; i++)
        exec_line(program[i]);

    return 0;
}
