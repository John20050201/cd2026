#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

CharNode *create_node(char ch, int index) {
    CharNode *new_node = (CharNode *)malloc(sizeof(CharNode));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->ch = ch;
    new_node->index = index;
    new_node->next = NULL;
    return new_node;
}

void append_node(CharNode **head, CharNode **tail, char ch, int index) {
    CharNode *new_node = create_node(ch, index);
    if (new_node == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(1);
    }

    if (*head == NULL) {
        *head = new_node;
        *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

int scan_file_to_list(const char *filename, CharNode **head, CharNode **tail, int *total_chars) {
    FILE *fp;
    int c;
    int index = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        return 0;
    }

    while ((c = fgetc(fp)) != EOF) {
        append_node(head, tail, (char)c, index);
        index++;
    }

    fclose(fp);
    *total_chars = index;
    return 1;
}

void print_visible_char(char ch) {
    if (ch == '\n') {
        printf("'\\n'");
    } else if (ch == '\t') {
        printf("'\\t'");
    } else if (ch == ' ') {
        printf("' '");
    } else {
        printf("'%c'", ch);
    }
}

void print_list(const CharNode *head) {
    const CharNode *current = head;

    printf("===== Scanner Output (from linked list) =====\n");
    while (current != NULL) {
        printf("[%d] ", current->index);
        print_visible_char(current->ch);
        printf("\n");
        current = current->next;
    }
}

void free_list(CharNode *head) {
    CharNode *current = head;
    CharNode *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}
