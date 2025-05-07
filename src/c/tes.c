#include "tes.h"

// Initialize global variables
User users[MAX_USERS] = {
    {"nimonsslatte", "nimonatutgajah23", ROLE_MANAGER},
    {"Neroifa", "Neroifa123", ROLE_DOKTER},
    {"GRO", "NeroifaCantik", ROLE_PASIEN},
    {"nimonsganteng", "KelompokAmatGacor", ROLE_PASIEN}  // Added missing comma
};
int user_count = 4;
User* current_user = NULL;


const char* role_to_string(UserRole role) {
    switch(role) {
        case ROLE_MANAGER: return "Manager";
        case ROLE_DOKTER: return "Dokter";
        case ROLE_PASIEN: return "Pasien";
        default: return "Unknown";
    }
}


boolean is_alpha_string(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z'))) {
            return false;
        }
    }
    return true;
}


boolean is_username_unique(const char* username) {
    for (int i = 0; i < user_count; i++) {
        const char *a = users[i].username;
        const char *b = username;
       
        while (*a && *b) {
            char a_char = *a;
            char b_char = *b;
           
            // Case-insensitive comparison
            if (a_char >= 'A' && a_char <= 'Z') a_char += 32;
            if (b_char >= 'A' && b_char <= 'Z') b_char += 32;
           
            if (a_char != b_char) break;
           
            a++;
            b++;
        }
       
        if (*a == '\0' && *b == '\0') {
            return false;
        }
    }
    return true;
}


void generate_kode_unik(const char* username, char* kode_unik) {
    int len = strlen(username);
    int count = 1;
    int pos = 0;
   
    for (int i = 1; i <= len; i++) {
        if (i < len && username[i] == username[i-1]) {
            count++;
        } else {
            if (count > 1) {
                pos += sprintf(kode_unik + pos, "%d", count);
            }
            kode_unik[pos++] = username[i-1];
            count = 1;
        }
    }
    kode_unik[pos] = '\0';
}


void login_system() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
   
    printf("Masukan username: ");
    if (scanf("%49s", username) != 1) {  // Added input validation
        printf("Input tidak valid!\n");
        while (getchar() != '\n');  // Clear input buffer
        return;
    }
   
    printf("Masukan password: ");
    if (scanf("%49s", password) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
   
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                current_user = &users[i];
                printf("Selamat pagi %s %s!",
                       role_to_string(current_user->role),
                       current_user->username);
                if (current_user->role == ROLE_PASIEN) {
                    printf(" Ada keluhan apa ?\n");
                } else {
                    printf("\n");
                }
                return;
            } else {
                printf("Password salah untuk pengguna yang bernama %s!\n", username);
                return;
            }
        }
    }
   
    printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n", username);
}


void register_pasien() {
    if (current_user != NULL) {
        printf("Anda sudah login. Silakan logout terlebih dahulu.\n");
        return;
    }
   
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
   
    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
   
    if (!is_alpha_string(username)) {
        printf("Username hanya boleh berisi huruf!\n");
        return;
    }
   
    if (!is_username_unique(username)) {
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", username);
        return;
    }
   
    printf("Password: ");
    if (scanf("%49s", password) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
   
    if (user_count >= MAX_USERS) {
        printf("Kapasitas user penuh!\n");
        return;
    }
   
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    users[user_count].role = ROLE_PASIEN;
    user_count++;
   
    printf("Pasien %s berhasil ditambahkan!\n", username);
}


void logout_system() {
    if (current_user == NULL) {
        printf("Logout gagal!\n");
        printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout\n");
        return;
    }
   
    printf("Sampai jumpa %s!\n", current_user->username);
    current_user = NULL;
}


void lupa_password_system() {
    char username[USERNAME_LEN];
    char kode_unik_input[100];
    char kode_unik_asli[100];
    char password_baru[PASSWORD_LEN];
   
    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
   
    User* user = NULL;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            user = &users[i];
            break;
        }
    }
   
    if (user == NULL) {
        printf("Username tidak terdaftar!\n");
        return;
    }
   
    printf("Kode Unik: ");
    if (scanf("%99s", kode_unik_input) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
   
    generate_kode_unik(user->username, kode_unik_asli);
   
    if (strcmp(kode_unik_input, kode_unik_asli) != 0) {
        printf("Kode unik salah!\n");
        return;
    }
   
    printf("Halo %s %s, silakan daftarkan ulang password anda!\n",
           role_to_string(user->role), user->username);
    printf("Password Baru: ");
    if (scanf("%49s", password_baru) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
   
    strcpy(user->password, password_baru);
    printf("Password berhasil diubah!\n");
}


void help_system() {
    printf("\n=========== HELP ===========\n\n");
   
    if (current_user == NULL) {
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("REGISTER: Membuat akun baru\n");
    } else {
        printf("Halo %s %s. ", role_to_string(current_user->role), current_user->username);
       
        if (current_user->role == ROLE_DOKTER) {
            printf("Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n");
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("DIAGNOSIS: Melakukan diagnosis penyakit pasien berdasarkan kondisi tubuh pasien\n");
        } else if (current_user->role == ROLE_PASIEN) {
            printf("Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n");
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("DAFTAR_CHECKUP: Mendaftarkan diri untuk pemeriksaan dokter\n");
        } else if (current_user->role == ROLE_MANAGER) {
            printf("Kenapa kamu memanggil command HELP? Kan kamu manager, ");
            printf("tapi yasudahlah kamu pasti sedang kebingungan.\n");
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem\n");
        }
    }
   
    printf("\nFootnote: \n");
    printf("Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("Jangan lupa untuk memasukkan input yang valid\n");
}


void exit_system(const char* username) {
    char input[10];

    printf("\nApakah Anda mau keluar dari rumah sakit? (y/n)\n");

    while (1) {
        printf("Pilihan Anda: ");
        scanf("%s", input);

        if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) {
            printf("\n%s keluar dari Rumah Sakit,\nSampai jumpa!\n", username);
            exit(0);
        } else if (strcmp(input, "N") == 0 || strcmp(input, "n") == 0) {
            printf("\nKembali ke menu utama...\n");
            return;
        } else {
            printf("Tidak valid. Pilih Y atau N ya!\n");
        }
    }
}

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
            exit_system(current_user ? current_user->username : "User");
        } else {
            printf("Command tidak dikenali. Ketik HELP untuk bantuan.\n");
        }
    }
   
    return 0;
}
