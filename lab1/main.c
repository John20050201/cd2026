#include <stdio.h>
#include <stdlib.h>

struct Node {
    unsigned char c;
    struct Node* next;
};

int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;

    FILE *file = fopen("main.c", "r");
    if (file == NULL) {
        printf("無法開啟檔案\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("記憶體配置失敗\n");
            fclose(file);
            return 1;
        }

        newNode->c = (unsigned char)ch;
        newNode->next = NULL;

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    fclose(file);

    struct Node* current = head;
    while (current != NULL) {
        if (current->c == '\n') {
            printf("'\\n'\n");
        } else if (current->c == '\r') {
            printf("'\\r'\n");
        } else if (current->c == '\t') {
            printf("'\\t'\n");
        } else if (current->c == ' ') {
            printf("' '\n");
        } else {
            printf("'%c'\n", current->c);
        }

        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
