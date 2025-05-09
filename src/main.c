#include <stdio.h>
#include "user.h"
#include "auth/login.h"
#include "auth/register.h"
#include "auth/logout.h"
#include "auth/lupa_password.h"
#include "help.h"

User users[MAX_USERS] = {
    {"nimonsslatte", "nimonatutgajah23", ROLE_MANAGER},
    {"Neroifa", "Neroifa123", ROLE_DOKTER},
    {"GRO", "NeroifaCantik", ROLE_PASIEN},
    {"nimonsganteng", "KelompokAmatGacor", ROLE_PASIEN}
};
int user_count = 4;
User* current_user = NULL;

int main() {
    char command[20];
    
    while(1) {
        printf("\n>>> ");
        if (scanf("%19s", command) != 1) {
            printf("Input tidak valid!\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (strcmp(command, "LOGIN") == 0) {
            login_system();
        } else if (strcmp(command, "REGISTER") == 0) {
            register_pasien();
        } else if (strcmp(command, "LOGOUT") == 0) {
            logout_system();
        } else if (strcmp(command, "LUPA_PASSWORD") == 0) {
            lupa_password_system();
        } else if (strcmp(command, "HELP") == 0) {
            help_system();
        } else if (strcmp(command, "EXIT") == 0) {
            break;
        } else {
            printf("Command tidak dikenali. Ketik HELP untuk bantuan.\n");
        }
    }
    
    return 0;
}
