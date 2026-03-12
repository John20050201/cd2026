#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義 Linked-list 的 Node
struct Node {
    unsigned char c;
    int count;
    struct Node* next;
};

int main() {
    // 加分題：使用指標陣列將搜尋時間複雜度降為 O(1)
    // 陣列大小為 256，涵蓋所有 ASCII 字元，初始為 NULL
    struct Node* lookupTable[256] = {NULL};
    
    struct Node* head = NULL;
    struct Node* tail = NULL;

    // 讀取自己本身的程式碼檔案 (__FILE__ 會被替換為當前原始碼檔名)
    FILE *file = fopen(__FILE__, "r");
    if (file == NULL) {
        printf("無法開啟檔案\n");
        return 1;
    }

    int ch;
    // 逐字元讀取，直到檔案結束
    while ((ch = fgetc(file)) != EOF) {
        unsigned char uc = (unsigned char)ch;

        if (lookupTable[uc] == NULL) {
            // 若為新字元，建立新的 node 並加入 linked-list
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->c = uc;
            newNode->count = 1;
            newNode->next = NULL;

            if (head == NULL) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            // 將新建立的 node 記憶體位置存入 lookupTable
            lookupTable[uc] = newNode;
        } else {
            // 若字元已存在，透過 lookupTable 以 O(1) 複雜度找到 node 並將數量加一
            lookupTable[uc]->count++;
        }
    }
    fclose(file);

    // 輸出結果
    struct Node* current = head;
    while (current != NULL) {
        // 處理特殊字元的印出格式，避免版面亂掉 (依簡報要求自行決定紀錄方式)
        if (current->c == '\n') {
            printf("\\n:%d\n", current->count);
        } else if (current->c == '\r') {
            printf("\\r:%d\n", current->count);
        } else if (current->c == '\t') {
            printf("\\t:%d\n", current->count);
        } else if (current->c == ' ') {
            printf("space:%d\n", current->count);
        } else {
            printf("%c:%d\n", current->c, current->count);
        }
        
        // 釋放記憶體順便切換到下一個
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
