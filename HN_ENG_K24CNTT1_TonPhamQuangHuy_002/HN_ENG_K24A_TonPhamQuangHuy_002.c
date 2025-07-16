#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct activity {
    int id;
    char *type;
    int duration;
    int calories;
    char *date;
} act;

typedef struct linkedList {
    act data;
    struct linkedList *next;
} Node;

Node *createNode(int id, char type[], int duration, int calories, char date[]) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data.id = id;
    newNode->data.type = (char *) malloc(strlen(type) + 1);
    strcpy(newNode->data.type, type);
    newNode->data.duration = duration;
    newNode->data.calories = calories;
    newNode->data.date = (char *) malloc(strlen(date) + 1);
    strcpy(newNode->data.date, date);
    newNode->next = NULL;
    return newNode;
}

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("id: %d\ntype: %s\nduration: %d\ncalories: %d\ndate: %s\n", current->data.id, current->data.type,
               current->data.duration, current->data.calories, current->data.date);
        current = current->next;
    }
}

Node *addActivity() {
    int id, duration, calories;
    char type[100], date[100];
    printf("Nhap vao id cho hoat dong: ");
    scanf("%d", &id);
    fflush(stdin);
    printf("Nhap vao loai hoat dong: ");
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\n")] = '\0';
    printf("Nhap vao thoi luong hoat dong (phut): ");
    scanf("%d", &duration);
    printf("Nhap vao luong calories tieu thu: ");
    scanf("%d", &calories);
    fflush(stdin);
    printf("Nhap vao ngay hoat dong: ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';
    Node *node = createNode(id, type, duration, calories, date);
    return node;
}

Node *deleteActivity(Node *head, const int id) {
    Node *current = head;
    Node *prev = NULL;
    while (current != NULL) {
        if (current->data.id == id) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("\nXoa thanh cong\n");
            return head;
        }
        prev = current;
        current = current->next;
    }
}

void updateActivity(Node *head, int id) {
    Node *current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            fflush(stdin);
            printf("Nhap vao loai hoat dong moi: ");
            fgets(current->data.type, sizeof(current->data.type), stdin);
            current->data.type[strcspn(current->data.type, "\n")] = '\0';
            printf("Nhap vao thoi luong hoat dong (phut) moi: ");
            scanf("%d", &current->data.duration);
            printf("Nhap vao luong calories tieu thu moi: ");
            scanf("%d", &current->data.calories);
            fflush(stdin);
            printf("Nhap vao ngay hoat dong moi: ");
            fgets(current->data.date, sizeof(current->data.date), stdin);
            current->data.date[strcspn(current->data.date, "\n")] = '\0';
            break;
        }
        current = current->next;
    }
}

int totalCalories(Node *head) {
    int sum = 0;
    Node *current = head;
    while (current != NULL) {
        sum += current->data.calories;
    }
    return sum;
}

void sortIncreasing(Node *head) {
    for (Node *i = head; i->next != NULL; i = i->next) {
        for (Node *j = i->next; j != NULL; j = j->next) {
            if (i->data.calories > j->data.calories) {
                act temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void sortDecreasing(Node *head) {
    for (Node *i = head; i->next != NULL; i = i->next) {
        for (Node *j = i->next; j != NULL; j = j->next) {
            if (i->data.calories > j->data.calories) {
                act temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void findActivity(Node *head, char type[]) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->data.type, type)) {
            printf("id: %d\ntype: %s\nduration: %d\ncalories: %d\ndate: %s\n", current->data.id, current->data.type,
                   current->data.duration, current->data.calories, current->data.date);
            break;
        }
        current = current->next;
    }
}

int main() {
    Node *head = NULL;
    int choice;
    do {
        printf("1. Them hoat dong trong ngay\n");
        printf("2. Hien thi danh sach hoat dong\n");
        printf("3. Xoa hoat dong\n");
        printf("4. Cap nhat thong tin hoat dong\n");
        printf("5. Thong ke tong calories tieu thu trong ngay\n");
        printf("6. Sap xep hoat dong\n");
        printf("7. Tim kiem hoat dong\n");
        printf("8. Thoat chuong trinh\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                Node *newNode = addActivity();
                if (head == NULL) {
                    newNode->next = head;
                    head = newNode;
                } else {
                    Node *current = head;
                    head->next = newNode;
                }
                break;
            case 2:
                printList(head);
                break;
            case 3:
                int idDelete;
                printf("Nhap id hoat dong ban muon xoa: ");
                scanf("%d", &idDelete);
                head = deleteActivity(head, idDelete);
                printList(head);
                break;
            case 4:
                int idForUpdate;
                printf("Nhap id hoat dong ban muon cap nhat: ");
                scanf("%d", &idForUpdate);
                updateActivity(head, idForUpdate);
                printList(head);
                break;
            case 5:
                printf("Tong calories tieu thi la: %d", totalCalories(head));
                break;
            case 6:
                int choice2;
                printf("1. tang dan\n");
                printf("2. giam dan\n");
                printf("Nhap lua chon cua ban: ");
                scanf("%d", &choice2);
                switch (choice2) {
                    case 1:
                        sortIncreasing(head);
                        break;
                    case 2:
                        sortDecreasing(head);
                        break;
                }
                break;
            case 7:
                char find[100];
                printf("Nhap hoat dong ban muon tim kiem: ");
                fgets(find, 100, stdin);
                findActivity(head, find);
                break;
            case 8:
                printf("Thoat chuong trinh");
                break;
            default:
                printf("Lua chon khong hop le!");
                break;
        }
    } while (choice != 8);
    exit(0);
}
