#include <stdio.h>
#include "../header/F10.h"
#include "../header/Dokter.h"

void tambah_dokter (ListUser *users, Set *usernames){
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_MANAGER){
        printf("\nERROR: Akses ditolak. Anda bukan Manager.\n");
        return;
    }

    printf("\n+-----------------------------------------------+\n");
    printf("|                 TAMBAH DOKTER                 |\n");
    printf("+-----------------------------------------------+\n");

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    
    printf("\nUsername: ");
    if (scanf("%49s", username) != 1) {
        printf("\nERROR: Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (!is_alpha_string(username)) {
        printf("\nERROR: Username hanya boleh berisi huruf!\n");
        return;
    }
    
    if (!is_username_unique(usernames, username)) {
        printf("\nERROR: Sudah ada user bernama %s!\n", username);
        return;
    }
    
    printf("Password: ");
    if (scanf("%49s", password) != 1) {
        printf("\nERROR: Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (list_is_full(*users)) {
        printf("\nERROR: Kapasitas user penuh!\n");
        return;
    }
    
    User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    newUser.role = ROLE_DOKTER;

    newUser.dataDokter = (Dokter*) malloc(sizeof(Dokter));
    if (newUser.dataDokter == NULL) {
        printf("\nERROR: Gagal mengalokasikan memori untuk dokter baru.\n");
        return;
    }

    newUser.idUser = list_nb_elmt(*users); // ID unik berdasarkan jumlah user
    newUser.dataDokter->id = list_nb_elmt(*users); // ID unik berdasarkan jumlah user
    strcpy(newUser.dataDokter->username, username);
    newUser.dataDokter->nomorRuangan = '\0'; // belum ditugaskan

    list_set_el(users, list_nb_elmt(*users), newUser);
    // list_set_length(users, list_nb_elmt(*users) + 1);
    set_insert(usernames, username); // Tambahkan username ke dalam Set
    
    printf(">> Dokter %s berhasil ditambahkan!\n", username);
}

void assign_dokter (ListUser *users, ListRuangan *ruangan){
     if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_MANAGER){
        printf ("\nERROR: Akses ditolak. Anda bukan Manager.\n");
        return;
    }

    char username[USERNAME_LEN];
    int nomorRuangan;

    printf("\n+-----------------------------------------------+\n");
    printf("|                 ASSIGN DOKTER                 |\n");
    printf("+-----------------------------------------------+\n");

    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        printf("\nERROR: Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (!is_alpha_string(username)) {
        printf("\nERROR: Username hanya boleh berisi huruf!\n");
        return;
    }

    boolean isDokterFound = false;
    User *newDokter = NULL;
    for (int i = list_get_first_idx(*users); i <= list_get_last_idx(*users); i++) {
        User *user = &users->data[i];
        if (strcmp(user->username, username) == 0 && user->role == ROLE_DOKTER) {
            newDokter = user;
            isDokterFound = true;
            break;
        }
    }

    if (!isDokterFound) {
        printf("\nERROR: Dokter dengan username %s tidak ditemukan!\n", username);
        return;
    }

    printf("Ruangan: ");
    if (scanf("%d", &nomorRuangan) != 1) {
        printf("\nERROR: Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }

    int isRuangFound = false;
    int idxRuang = -1;
    for (int i = 0; i < ruangan->jumlah; i++) {
        if (ruangan->ruang[i].nomor == nomorRuangan) {
            isRuangFound = true;
            idxRuang = i;
            break;
        }
    }

    if (!isRuangFound) {
        printf("\nERROR: Tidak ada ruangan nomor %d!\n", nomorRuangan);
        return;
    }

    // Cek kondisi assign dokter ke ruangan
    int dokterSudahPunyaRuangan = (newDokter->dataDokter->nomorRuangan > 0);
    int ruanganSudahAdaDokter = (ruangan->ruang[idxRuang].dokter != NULL);

    if (!dokterSudahPunyaRuangan && !ruanganSudahAdaDokter) {
        // 1. Dokter belum punya ruangan, ruangan kosong
        ruangan->ruang[idxRuang].dokter = newDokter->dataDokter;
        newDokter->dataDokter->nomorRuangan = nomorRuangan;
        printf(">> Dokter %s berhasil diassign ke ruangan %d!\n", username, nomorRuangan);
    } else if (dokterSudahPunyaRuangan && !ruanganSudahAdaDokter) {
        // 2. Dokter sudah punya ruangan, ruangan kosong (pindah beserta antrian)
        int ruanganLama = newDokter->dataDokter->nomorRuangan;
        // Pindahkan antrian pasien dari ruangan lama ke ruangan baru
        AntrianDokter *antrianLama = &ruangan->ruang[ruanganLama - 1].Antrian;
        AntrianDokter *antrianBaru = &ruangan->ruang[idxRuang].Antrian;
        // Pindahkan semua node antrian
        if (!queue_is_empty(antrianLama)) {
            if (queue_is_empty(antrianBaru)) {
                antrianBaru->first = antrianLama->first;
                antrianBaru->last = antrianLama->last;
                antrianBaru->jumlah = antrianLama->jumlah;
            } else {
                antrianBaru->last->next = antrianLama->first;
                antrianBaru->last = antrianLama->last;
                antrianBaru->jumlah += antrianLama->jumlah;
            }
            // Update idRuangan setiap pasien di antrian
            address curr = antrianBaru->first;
            while (curr != NULL) {
                if (curr->pasien->dataPasien != NULL) {
                    curr->pasien->dataPasien->idRuangan = nomorRuangan;
                }
                curr = curr->next;
            }
            // Kosongkan antrian lama
            antrianLama->first = antrianLama->last = NULL;
            antrianLama->jumlah = 0;
        }
        ruangan->ruang[idxRuang].dokter = newDokter->dataDokter;
        newDokter->dataDokter->nomorRuangan = nomorRuangan;
        ruangan->ruang[ruanganLama-1].dokter = NULL;
        printf("Dokter %s dipindahkan dari ruangan %d ke ruangan %d!\n", username, ruanganLama, nomorRuangan);
    } else if (!dokterSudahPunyaRuangan && ruanganSudahAdaDokter) {
        // 3. Ruangan sudah ada dokternya, dokter belum punya ruangan
        printf("Silakan cari ruangan lain untuk dokter %s. Ruangan %d sudah ditempati dokter %s!\n", username, nomorRuangan, ruangan->ruang[idxRuang].dokter->username);
    } else if (dokterSudahPunyaRuangan && ruanganSudahAdaDokter) {
        // 4. Ruangan sudah ada dokternya, dokter sudah punya ruangan
        printf("Dokter %s sudah menempati ruangan %d! Ruangan %d juga sudah ditempati dokter %s!\n", username, newDokter->dataDokter->nomorRuangan, nomorRuangan, ruangan->ruang[idxRuang].dokter->username);
    }
    return;
}