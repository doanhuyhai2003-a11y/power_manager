#include <stdio.h>
#include "simulation.h"
#include "device.h"
#include "report.h"

void export_report() {
    FILE* f = fopen("report.txt", "w");
    if (!f) return;

    Device* max_dev = NULL;
    List_Device* p = head;
    while (p) {
        if (!max_dev || p->data.consume > max_dev->consume)
            max_dev = &p->data;
        p = p->next;
    }

    fprintf(f, "===== BAO CAO TONG KET =====\n");
    fprintf(f, "Tong thoi gian mo phong: %d phut (%.1f gio)\n", total_steps * 6, total_steps * 0.1f);
    fprintf(f, "Steps: %d\n", total_steps);
    fprintf(f, "Energy: %.2f Wh\n", total_energy);
    fprintf(f, "Mode changes: %d\n", mode_changes);
    fprintf(f, "Warnings: %d\n", total_warnings);
    if (max_dev)
        fprintf(f, "Max device: %s (%s) %.1fW\n", max_dev->type, max_dev->id, max_dev->consume);

    fclose(f);
    printf("\nDa xuat report.txt\n");
}