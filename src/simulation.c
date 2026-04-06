#include <stdio.h>
#include "simulation.h"
#include "device.h"

float battery_capacity = 15000.0f;
float current_battery = 12000.0f;
float high_th = 75.0f, med_th = 50.0f, low_th = 25.0f;

int total_warnings = 0;
int mode_changes = 0;
int total_steps = 0;
float total_energy = 0.0f;

float charge_power = 0.0f;
int is_charging = 0;


int get_battery_mode() {
    float percent = (current_battery / battery_capacity) * 100.0f;
    static int current_mode = NORMAL_MODE;
    switch (current_mode) {
        case PERFORMANCE_MODE:
            if (percent < high_th - 5)
                current_mode = NORMAL_MODE;
            break;

        case NORMAL_MODE:
            if (percent >= high_th)
                current_mode = PERFORMANCE_MODE;
            else if (percent < low_th)
                current_mode = SAVE_MODE;
            break;

        case SAVE_MODE:
            if (percent > low_th + 10)
                current_mode = NORMAL_MODE;
            break;
    }

    return current_mode;
}

void auto_control() {
    int mode = get_battery_mode();
    static int last_mode = -1;

    if (mode != last_mode && total_steps > 0) {
        mode_changes++;
//======================DISPLAY DEVICE'S MODE========================================
        switch (mode)
        {
        case PERFORMANCE_MODE:
            printf("\n[MODE] Mode = Better Performance | Pin = %.1f%%\n", (current_battery / battery_capacity)*100);
            break;
        case NORMAL_MODE:
            printf("\n[MODE CHANGE] Mode = Better Battery | Pin = %.1f%%\n", (current_battery / battery_capacity)*100);
            break;
        case SAVE_MODE:
            printf("\n[MODE CHANGE] Mode = Save Battery | Pin = %.1f%%\n", (current_battery / battery_capacity)*100);
            break;
        }
        print_devices();
    }
    last_mode = mode;

    List_Device* p = head;
    while (p) {
        Device* d = &p->data;
        switch (mode) {
            case PERFORMANCE_MODE: d->status = 1; break;
            case NORMAL_MODE: d->status = (d->priority <= 3); break;
            case SAVE_MODE: d->status = d->essential; break;
        }
        p = p->next;
    }
}

void update_charging() {
    float percent = (current_battery / battery_capacity) * 100.0f;

    if (percent < 80.0f) {
        is_charging = 1;
        charge_power = 900.0f;   // hoặc đọc từ config
    } else if (percent > 95.5f) {
        is_charging = 0;
        charge_power = 0.0f;
    }
}

void simulate_step() {
    total_steps++;
    auto_control();

    update_charging();
    float total_power = get_total_power();
    float net_power = total_power - charge_power;
    current_battery -= net_power * 0.1f;

    if (current_battery > battery_capacity) current_battery = battery_capacity;
    if (current_battery < 0) current_battery = 0;

    total_energy += total_power * 0.1f;

    float percent = (current_battery / battery_capacity) * 100.0f;

    if (charge_power != 0) {
        printf("\nCharging!");
    } else printf("\nNot Charging!");
    printf("\n[STEP %d] Pin: %.1f%% | Power: %.1fW\n", total_steps, percent, total_power);

    if (percent < 15.0f || total_power > 3000.0f) {
        total_warnings++;
        printf("[WARNING] PIN YEU - CONG SUAT QUA CAO !\n");
    }
}