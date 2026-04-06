#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

int get_json_value(const char *json, const char *key, char *result, int max_len) {
    char pattern[100];
    sprintf(pattern, "\"%s\"", key);
    char *pos = strstr(json, pattern);
    if (!pos) return 0;

    pos = strchr(pos, ':');
    if (!pos) return 0;
    pos++;

    while (*pos == ' ' || *pos == '\t' || *pos == '\"' || *pos == '\'') pos++;

    int i = 0;
    while (i < max_len-1 && *pos && *pos != '"' && *pos != ',' && *pos != '}' && *pos != '\n') {
        result[i++] = *pos++;
    }
    result[i] = '\0';

    while (i > 0 && (result[i-1] == ' ' || result[i-1] == '\t')) {
        result[--i] = '\0';
    }
    return (i > 0);
}

int parse_device(const char *line, Device *d) {
    char temp[100] = {0};
    memset(d, 0, sizeof(Device));

    if (!get_json_value(line, "id", d->id, 50)) return 0;
    if (!get_json_value(line, "type", d->type, 50)) return 0;

    if (get_json_value(line, "consume", temp, 100))
        d->consume = atof(temp);

    if (get_json_value(line, "priority", temp, 100))
        d->priority = atoi(temp);

    if (get_json_value(line, "essential", temp, 100))
        d->essential = atoi(temp);
    else
        d->essential = (d->priority <= 2) ? 1 : 0;

    if (get_json_value(line, "status", temp, 100))
        d->status = (strcmp(temp, "on") == 0 || atoi(temp) == 1);

    return 1;
}

void load_devices_file(const char* filename) {
    free_list();      // xóa danh sách cũ
    head = NULL;
    device_count = 0;
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Khong tim thay file %s\n", filename);
        printf("Vui long tao file devices.txt trong cung thu muc!\n");
        return;
    }

    char line[512];
    int line_num = 0;
    while (fgets(line, sizeof(line), f)) {
        line_num++;
        if (strlen(line) < 10) continue;

        Device d = {0};
        if (parse_device(line, &d)) {
            add_device(d);
            //device_count++;
        } else {
            printf("[DEBUG] Dong %d parse that bai: %s", line_num, line);
        }
    }
    fclose(f);
}

void save_devices_file(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) return;

    List_Device* p = head;
    while (p) {
        fprintf(f,
            "{\"id\":\"%s\",\"type\":\"%s\",\"consume\":%.1f,\"priority\":%d,\"essential\":%d,\"status\":\"%s\"}\n",
            p->data.id,
            p->data.type,
            p->data.consume,
            p->data.priority,
            p->data.essential,
            p->data.status ? "on" : "off"
        );
        p = p->next;
    }

    fclose(f);
    printf("Da luu devices.txt\n");
}