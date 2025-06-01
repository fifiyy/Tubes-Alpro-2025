#include "../header/lihat_user.h"

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
    return c;
}

int compare_nama(char *a, char *b) {
    int i = 0;
    while (a[i] && b[i]) {
        char ca = to_lower(a[i]);
        char cb = to_lower(b[i]);
        if (ca != cb) return (ca < cb) ? -1 : 1;
        i++;
    }
    if (a[i] == b[i]) return 0;
    return a[i] ? 1 : -1;
}

void sort_user (ListUser L, int idx[], int len, int id, int asc){
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            int cmp;
            if (id) {
                cmp = (L.data[idx[j]].idUser - L.data[idx[j+1]].idUser);
            } else {
                cmp = compare_nama(L.data[idx[j]].username, L.data[idx[j+1]].username);
            }

            if ((asc && cmp > 0) || (!asc && cmp < 0)) {
                int tmp = idx[j];
                idx[j] = idx[j+1];
                idx[j+1] = tmp;
            }
        }
    }
}

void print_user (ListUser L, int idx [], int len, int view){
    // view: 0 = semua user, 1 = berdasarkan pasien, 2 = berdasarkan dokter
    if (view == 0){
        printf("ID  | Nama             | Role        | Penyakit\n");
        printf("-------------------------------------------------\n");
        for (int i = 0; i < len; i++) {
            int id = idx[i];
            if (L.data[id].role == ROLE_MANAGER) continue;  // Skip manager
            const char *role_s = role_to_string(L.data[id].role);
            const char *penyakit = (L.data[id].role == ROLE_PASIEN && L.data[id].dataPasien != NULL) 
            ? L.data[id].dataPasien->penyakit : "-";
            printf("%-2d  | %-15s  | %-9s   | %s\n", L.data[id].idUser, L.data[id].username, role_s, penyakit);
        }
    }
    else if (view == 1){
        printf("ID  | Nama             | Penyakit\n");
        printf("-----------------------------------\n");
        for (int i = 0; i < len; i++) {
            int id = idx[i];
            if (L.data[id].role == ROLE_MANAGER) continue;  // Skip manager
            const char *role_s = role_to_string(L.data[id].role);
            const char *penyakit = (L.data[id].role == ROLE_PASIEN && L.data[id].dataPasien != NULL) 
            ? L.data[id].dataPasien->penyakit : "-";
            if (L.data[id].role == ROLE_PASIEN) printf("%-2d  | %-15s  | %s\n", L.data[id].idUser, L.data[id].username, penyakit);
        }
    }
    else if (view == 2){
        printf("ID  | Nama             \n");
        printf("-------------------------\n");
        for (int i = 0; i < len; i++) {
            int id = idx[i];
            if (L.data[id].role == ROLE_MANAGER) continue;  // Skip manager
            const char *role_s = role_to_string(L.data[id].role);
            if (L.data[id].role == ROLE_DOKTER) printf("%-2d  | %-15s\n", L.data[id].idUser, L.data[id].username);
        }
    }
}

void lihat_user (ListUser L) {
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_MANAGER){
        printf ("nERROR: Hanya manajer yang bisa melihat user.\n");
        return;
    }
    
    int pilihan1, pilihan2;
    printf ("Urutkan berdasarkan?\n1. ID\n2. Nama");
    while (1) {
        printf("\n>>> Pilihan: ");
        scanf("%d", &pilihan1);
        if (pilihan1 == 1 || pilihan1 == 2) break;
        else printf("Pilihan harus 1 atau 2!\n");
    }

    printf ("\nUrutan sort?\n1. ASC (A-Z)\n2. DESC (Z-A)");
    while (1) {
        printf("\n>>> Pilihan: ");
        scanf("%d", &pilihan2);
        if (pilihan2 == 1 || pilihan2 == 2) break;
        else printf("Pilihan harus 1 atau 2!\n");
    }
    printf("\nMenampilkan semua pengguna dengan %s terurut %s...\n",
           (pilihan1 == 1 ? "ID" : "nama"),
           (pilihan1 == 1 ? "ascending" : "descending"));

    int idx[MAX_CAPACITY];
    int len = L.length;
    for (int i = 0; i < len; i++) idx[i] = i;

    sort_user (L, idx, len, pilihan1 == 1, pilihan2 == 1);
    printf("\n+-----------------------------------------------+\n");
    printf("|                  DAFTAR USER                  |\n"); 
    printf("+-----------------------------------------------+\n");
    print_user (L, idx, len, 0);
}

void lihat_pasien (ListUser L){
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_MANAGER){
        printf ("nERROR: Hanya manajer yang bisa melihat pasien.\n");
        return;
    }
    
    int pilihan1, pilihan2;
    printf ("Urutkan berdasarkan?\n1. ID\n2. Nama");
    while (1) {
        printf("\n>>> Pilihan: ");
        scanf("%d", &pilihan1);
        if (pilihan1 == 1 || pilihan1 == 2) break;
        else printf("Pilihan harus 1 atau 2!\n");
    }

    printf ("\nUrutan sort?\n1. ASC (A-Z)\n2. DESC (Z-A)");
    while (1) {
        printf("\n>>> Pilihan: ");
        scanf("%d", &pilihan2);
        if (pilihan2 == 1 || pilihan2 == 2) break;
        else printf("Pilihan harus 1 atau 2!\n");
    }

    printf("\nMenampilkan pasien dengan %s terurut %s...\n",
           (pilihan1 == 1 ? "ID" : "nama"),
           (pilihan1 == 1 ? "ascending" : "descending"));

    int idx[MAX_CAPACITY];
    int len = L.length;
    for (int i = 0; i < len; i++) idx[i] = i;

    sort_user (L, idx, len, pilihan1 == 1, pilihan2 == 1);
    printf("\n+-----------------------------------------------+\n");
    printf("|                  DAFTAR PASIEN                |\n"); 
    printf("+-----------------------------------------------+\n");
    print_user (L, idx, len, 1);
    
}

void lihat_dokter (ListUser L){
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_MANAGER){
        printf ("nERROR: Hanya manajer yang bisa melihat dokter.\n");
        return;
    }
    
    int pilihan1, pilihan2;
    printf ("Urutkan berdasarkan?\n1. ID\n2. Nama");
    while (1) {
        printf("\n>>> Pilihan: ");
        scanf("%d", &pilihan1);
        if (pilihan1 == 1 || pilihan1 == 2) break;
        else printf("Pilihan harus 1 atau 2!\n");
    }

    printf ("\nUrutan sort?\n1. ASC (A-Z)\n2. DESC (Z-A)");
    while (1) {
        printf("\n>>> Pilihan: ");
        scanf("%d", &pilihan2);
        if (pilihan2 == 1 || pilihan2 == 2) break;
        else printf("Pilihan harus 1 atau 2!\n");
    }

    printf("\nMenampilkan dokter dengan %s terurut %s...\n",
           (pilihan1 == 1 ? "ID" : "nama"),
           (pilihan1 == 1 ? "ascending" : "descending"));
    
    int idx[MAX_CAPACITY];
    int len = L.length;
    for (int i = 0; i < len; i++) idx[i] = i;

    sort_user (L, idx, len, pilihan1 == 1, pilihan2 == 1);
    printf("\n+-----------------------------------------------+\n");
    printf("|                  DAFTAR DOKTER                |\n"); 
    printf("+-----------------------------------------------+\n");
    print_user (L, idx, len, 2);
}