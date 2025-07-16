#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graphicAction {
    char action[100];
    char timestamp[100];
} Node;

typedef struct action {
    Node *data;
    int top;
    int cap;
} stack;

Node *createNode() {
    Node *node = (Node*)malloc(sizeof(Node));
    return node;
};

stack *createStack(int capacity) {
    stack *s = (stack*)malloc(sizeof(stack));
    s->top = -1;
    s->cap = capacity;
}

void push(stack *s, char action[], char timestamp[]) {
    if (s->top == s->top - 1) {
        printf("Ngan xap da day");
        return;
    }
    s->top++;
    strcpy(s->data[s->top].timestamp, timestamp);
    strcpy(s->data[s->top].action, action);
};

Node *addDraw(stack *s) {
    char action[100], timestamp[100];
    printf("Nhap hoat dong cua ban: ");
    fgets(action, 100, stdin);
    action[strcspn(action, "\n")] = '\0';
    printf("Nhap thoi luong cua ban: ");
    fgets(timestamp, 100, stdin);
    timestamp[strcspn(timestamp, "\n")] = '\0';
    push(s, action, timestamp);
}

char* pop(stack *s) {
    if (s->top == -1) {
        printf("Ngan xep trong");
        exit(0);
    }
    s->top--;
    return s->data[s->top].action;
}

void printList (stack *s) {
    for (int i = 0 ; i < s->top; i++) {
        printf("action: %s\ntimestamp: %s\n", s->data[i].action, s->data[i].timestamp);
    }
}
int main() {
    Node *head = NULL;
    int capacity = 10;
    stack *undo = createStack(capacity);
    stack *redo = createStack(capacity);
    int choice;
    do {
        printf("1. Draw\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Print\n");
        printf("Thoat chuong trinh");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                addDraw(undo);
                break;
            case 2:
                printf("%s\n", pop(undo));

                break;
            case 3:

                break;
            case 4:
                printList(undo);
                break;
            case 5:
                printf("Thoat chuong trinh");
                break;
            default:
                printf("Lua chon khong hop le!");
                break;
        }
    } while (choice != 5);
    exit(0);
}
