#ifndef DEVICE_H
#define DEVICE_H

typedef struct {
    char id[50];
    char type[50];
    float consume;
    int priority;
    int essential;
    int status;
} Device;

typedef struct List_Device {
    Device data;
    struct List_Device* next;
} List_Device;

extern List_Device* head;
extern int device_count;

void add_device(Device d);
void input_device(Device *d) ;
void remove_device(const char* id);
void print_devices();
float get_total_power();
void free_list();

#endif