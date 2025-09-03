#include "../header/cari_user.h"
//random

int binary_search (ListUser L, int targetElement, int size){
    int left = 0, right = size - 1;
    
    while (left <= right){
        int middle = (left + right) / 2;

        if (L.data[middle].idUser == targetElement) {
            return middle;
        }
        else if (L.data[middle].idUser < targetElement) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }
    return -1;
}

int sequential_username (ListUser L, char* targetName, int size){
    for (int i = 0; i < size; i++) {
        if (strcmp(L.data[i].username, targetName) == 0) {
            return i;
        }
    }
    return -1;
}

void search_penyakit (ListUser L, const char* targetPenyakit){
    int found = 0;
    printf("ID  | Nama             | Penyakit\n");
    printf("-----------------------------------\n");

    for (int i = 0; i < L.length; i++) {
        if (L.data[i].role == ROLE_PASIEN && L.data[i].dataPasien != NULL) {
            if (strcmp(L.data[i].dataPasien->penyakit, targetPenyakit) == 0) {
                printf("%-2d  | %-15s | %s\n", L.data[i].idUser, L.data[i].username, L.data[i].dataPasien->penyakit);
                found++;
            }
        }
    }

    if (found == 0) {
        printf("Tidak ditemukan pasien dengan penyakit \"%s\".\n", targetPenyakit);
    }
}

void cari_user (ListUser L){
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_MANAGER){
        printf ("ERROR: Hanya manajer yang bisa mencari user.\n");
        return;
    }
    
    int pilihan, idTarget, userIdx, len = L.length;
    char usernameTarget [USERNAME_LEN];
    printf ("\n+-----------------------------------------------+\n");
    printf("|                  CARI USER                    |\n");
    printf("+-----------------------------------------------+\n");
    printf ("Cari berdasarkan?\n1. ID\n2. Nama");
    while (1) {
        printf("\n>>> Pilihan: ");
        scanf("%d", &pilihan);
        if (pilihan == 1 || pilihan == 2) break;
        else printf("Pilihan harus 1 atau 2!\n");
    }

    if (pilihan == 1){
        printf("\n>>> Masukkan nomor ID user: ");
        scanf ("%d", &idTarget);
        userIdx = binary_search (L, idTarget, len);

        if (userIdx == -1){
            printf ("\nTidak ditemukan pengguna dengan ID user %d.\n", idTarget);
            return;
        }
    }
    else {
        printf("\n>>> Masukkan nama user: ");
        scanf (" %[^\n]", usernameTarget);
        userIdx = sequential_username(L, usernameTarget, L.length);

        if (userIdx == -1) {
        printf("\nTidak ditemukan pengguna dengan nama '%s'.\n", usernameTarget);
        return;
        }
    }

    User u = L.data[userIdx];

    if (u.role == ROLE_MANAGER) {
        printf("\nID/nama tersebut milik Manager dan tidak ditampilkan.\n");
        return;
    }
    else {
        const char *role_s = role_to_string(u.role);
        const char *penyakit = (u.role == ROLE_PASIEN && u.dataPasien != NULL) ? u.dataPasien->penyakit : "-";
        printf("ID  | Nama             | Role        | Penyakit\n");
        printf("-------------------------------------------------\n");
        printf("%-2d  | %-15s  | %-9s   | %s\n", u.idUser, u.username, role_s, penyakit);
    }
}

void cari_pasien (ListUser L){
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_MANAGER){
        printf ("\nERROR: Hanya manajer yang bisa mencari pasien.\n");
        return;
    }
    
    int pilihan, idTarget, userIdx, len = L.length;
    char usernameTarget [USERNAME_LEN], penyakitTarget [USERNAME_LEN];
    printf ("\n+-----------------------------------------------+\n");
    printf("|                  CARI PASIEN                  |\n");
    printf("+-----------------------------------------------+\n");
    printf ("Cari berdasarkan?\n1. ID\n2. Nama\n3. Penyakit");
    while (1) {
        printf("\n>>> Pilihan: ");
        scanf("%d", &pilihan);
        if (pilihan == 1 || pilihan == 2 || pilihan == 3) break;
        else printf("Pilihan harus 1, 2, atau 3!\n");
    }

    if (pilihan == 1){
        printf("\n>>> Masukkan nomor ID pasien: ");
        scanf ("%d", &idTarget);
        userIdx = binary_search (L, idTarget, len);

        if (userIdx == -1){
            printf ("\nTidak ditemukan pasien dengan ID %d.\n", idTarget);
            return;
        } 
        else{
            User u = L.data[userIdx];

            if (u.role == ROLE_MANAGER) {
                printf("\nID tersebut milik Manager dan tidak ditampilkan.\n");
                return;
            }
            else if (u.role != ROLE_PASIEN) {
                printf("\nUser ditemukan, tetapi bukan seorang pasien.\n");
                return;
            }
            else {
                const char *role_s = role_to_string(u.role);
                const char *penyakit = (u.role == ROLE_PASIEN && u.dataPasien != NULL) ? u.dataPasien->penyakit : "-";
                printf("ID  | Nama             | Penyakit\n");
                printf("-----------------------------------\n");
                printf("%-2d  | %-15s  | %s\n", u.idUser,u.username, penyakit);
            }
        }
    }
    else if (pilihan == 2) {
        printf("\n>>> Masukkan nama pasien: ");
        scanf (" %[^\n]", usernameTarget);
        userIdx = sequential_username(L, usernameTarget, L.length);

        if (userIdx == -1) {
            printf("\nTidak ditemukan pasien dengan nama '%s'.\n", usernameTarget);
            return;
        }
        else {
            User u = L.data[userIdx];

            if (u.role == ROLE_MANAGER) {
                printf("\nNama tersebut milik Manager dan tidak ditampilkan.\n");
                return;
            }
            else if (u.role != ROLE_PASIEN) {
                printf("\nUser ditemukan, tetapi bukan seorang pasien.\n");
                return;
            }
            else {
                const char *role_s = role_to_string(u.role);
                const char *penyakit = (u.role == ROLE_PASIEN && u.dataPasien != NULL) ? u.dataPasien->penyakit : "-";
                printf("ID  | Nama             | Penyakit\n");
                printf("-----------------------------------\n");
                printf("%-2d  | %-15s  | %s\n", u.idUser,u.username, penyakit);
            }
        }
    }
    else {
        printf("\n>>> Masukkan nama penyakit: ");
        scanf (" %[^\n]", penyakitTarget);
        search_penyakit(L, penyakitTarget);
    }
}

void cari_dokter(ListUser L){
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    if (currUser->role != ROLE_MANAGER){
        printf ("\nERROR: Hanya manajer yang bisa mencari dokter.\n");
        return;
    }

    int pilihan, idTarget, userIdx, len = L.length;
    char usernameTarget [USERNAME_LEN];
    printf ("\n+-----------------------------------------------+\n");
    printf("|                  CARI DOKTER                  |\n");
    printf("+-----------------------------------------------+\n");
    printf ("Cari berdasarkan?\n1. ID\n2. Nama");
    while (1) {
        printf("\n>>> Pilihan: ");
        scanf("%d", &pilihan);
        if (pilihan == 1 || pilihan == 2) break;
        else printf("Pilihan harus 1 atau 2!\n");
    }

    if (pilihan == 1){
        printf("\n>>> Masukkan nomor ID dokter: ");
        scanf ("%d", &idTarget);
        userIdx = binary_search (L, idTarget, len);

        if (userIdx == -1){
            printf ("\nTidak ditemukan dokter dengan ID %d.\n", idTarget);
            return;
        }
    }
    else {
        printf("\n>>> Masukkan nama dokter: ");
        scanf (" %[^\n]", usernameTarget);
        userIdx = sequential_username(L, usernameTarget, L.length);

        if (userIdx == -1) {
        printf("\nTidak ditemukan dokter dengan nama '%s'.\n", usernameTarget);
        return;
        }
    }

    User u = L.data[userIdx];

    if (u.role == ROLE_MANAGER) {
        printf("\nID tersebut milik Manager dan tidak ditampilkan.\n");
        return;
    }
    else if (u.role != ROLE_DOKTER) {
        printf("\nUser ditemukan, tetapi bukan seorang dokter.\n");
        return;
    }
    else {
        const char *role_s = role_to_string(u.role);
        printf("ID  | Nama             \n");
        printf("-------------------------\n");
        printf("%-2d  | %-15s\n", u.idUser, u.username);
    }

}