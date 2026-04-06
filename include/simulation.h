#ifndef SIMULATION_H
#define SIMULATION_H

typedef enum {
    PERFORMANCE_MODE = 3,
    NORMAL_MODE = 2,
    SAVE_MODE = 1
} mode_change_t;

extern float battery_capacity;
extern float current_battery;
extern float high_th, med_th, low_th;

extern int total_warnings;
extern int mode_changes;
extern int total_steps;
extern float total_energy;

extern float charge_power;
extern int is_charging;

void simulate_step();
void update_charging();
int get_battery_mode();
void auto_control();

#endif