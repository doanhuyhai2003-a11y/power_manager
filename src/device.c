#include "device.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List_Device* head = NULL;
int device_count = 0;

void add_device(Device d) {
    List_Device* node = (List_Device*)malloc(sizeof(List_Device));
    node->data = d;
    node->next = NULL;

    if (!head) head = node;
    else {
        List_Device* p = head;
        while (p->next) p = p->next;
        p->next = node;
    }
    device_count++;
}

void input_device(Device *d) {
    printf("Nhap ID: "); scanf("%s", d->id);
    printf("Nhap type: "); scanf("%s", d->type);
    printf("Nhap consume: "); scanf("%f", &d->consume);
    printf("Nhap priority: "); scanf("%d", &d->priority);
    printf("Nhap essential (0/1): "); scanf("%d", &d->essential);
    d->status = 1;
}

void remove_device(const char* id) {
    List_Device* p = head;
    List_Device* prev = NULL;

    while (p != NULL) {
        if (strcmp(p->data.id, id) == 0) {
            // Xóa node đầu
            if (prev == NULL) {
                head = p->next;
            } else {
                prev->next = p->next;
            }

            free(p);
            device_count--;

            printf("Da xoa thiet bi co ID = %s\n", id);
            return;
        }

        prev = p;
        p = p->next;
    }

    printf("Khong tim thay thiet bi co ID = %s\n", id);
}

void print_devices() {
    List_Device* p = head;
    printf("\n===== DANH SACH THIET BI (%d thiet bi) =====\n", device_count);
    while (p) {
        printf("ID: %-8s | Type: %-10s | Status: %s | Power: %7.1fW | Priority: %2d | Essential: %2d\n",
            p->data.id, p->data.type,
            p->data.status ? "ON" : "OFF",
            p->data.consume, p->data.priority, p->data.essential);
        p = p->next;
    }
}

float get_total_power() {
    float total = 0;
    List_Device* p = head;
    while (p) {
        if (p->data.status) total += p->data.consume;
        p = p->next;
    }
    return total;
}

void free_list() {
    List_Device* p = head;
    while (p) {
        List_Device* tmp = p;
        p = p->next;
        free(tmp);
    }
    head = NULL;
}