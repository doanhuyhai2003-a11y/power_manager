#include <stdio.h>
#include "device.h"
#include "fileio.h"
#include "simulation.h"
#include "report.h"

void menu() {
    printf("\n===== MENU =====\n");
    printf("1. Hien thi thiet bi\n");
    printf("2. Them thiet bi\n");
    printf("3. Mo phong 1 buoc\n");
    printf("4. Mo phong n buoc\n");
    printf("5. Luu file\n");
    printf("6. Xuat report\n");
    printf("7. Xoa thiet bi\n");
    printf("0. Thoat\n");
}

int main() {
    load_devices_file("devices.txt");
    int choice;
    do {
        menu();
        printf("Chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_devices();
                break;

            case 2: {
                Device d;
                input_device(&d);
                add_device(d);
                //device_count++;
                break;
            }

            case 3:
                simulate_step();
                break;

            case 4: {
                int n;
                printf("Nhap n: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++)
                    simulate_step();
                break;
            }

            case 5:
                save_devices_file("devices.txt");
                break;

            case 6:
                export_report();
                break;
            case 7:
                char id[50];
                printf("Nhap ID can xoa: ");
                scanf("%s", id);
                remove_device(id);
                break;

            case 0:
                save_devices_file("devices.txt");
                printf("Thoat...\n");
                break;

            default:
                printf("Sai lua chon!\n");
        }

    } while (choice != 0);

    free_list();
    return 0;
}