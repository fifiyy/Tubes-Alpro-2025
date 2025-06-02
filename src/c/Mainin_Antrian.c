#include "../header/Mainin_Antrian.h"

void skip_antrian(User *user, ListRuangan *ruangan, int banyakUser) {
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (user->role != ROLE_PASIEN) {
        printf("\nERROR: Hanya pasien yang bisa melewati antrian!\n");
        return;
    }

    Pasien *pasien = user->dataPasien;
    if (pasien->posisiAntrian < 0) {
        printf("\nERROR: Kamu belum terdaftar dalam antrian check-up.\n");
        return;
    }

    // Cek apakah pasien ada di antrian
    int idxRuang = pasien->idRuangan - 1;
    if (idxRuang < 0 || idxRuang >= ruangan->jumlah) {
        printf("\nERROR: Ruangan tidak ditemukan!\n");
        return;
    }

    AntrianDokter *antrian = &ruangan->ruang[idxRuang].Antrian;
    int maxDalamRuangan = ruangan->ruang[idxRuang].kapasitas; // misal field kapasitas
    address prev = NULL;
    address curr = antrian->first;
    int pos = 1;
    address prevSkip = NULL; // pointer ke node sebelum posisi skip (N)
    address firstAntrian = NULL; // node ke-(N+1)

    // Cari posisi pasien, dan node ke-(N+1)
    while (curr != NULL) {
        if (pos == maxDalamRuangan) {
            prevSkip = curr;
            firstAntrian = curr->next;
        }
        if (curr->pasien->dataPasien == pasien) {
            break;
        }
        prev = curr;
        curr = curr->next;
        pos++;
    }

    if (curr == NULL) {
        printf("\nERROR: Kamu tidak berada di antrian.\n");
        return;
    }

    if (pos <= maxDalamRuangan) {
        printf(">> Kamu sedang berada di dalam ruangan, tidak bisa skip antrian.\n");
        return;
    }

    if (curr == firstAntrian) {
        printf(">> Kamu sudah berada di posisi pertama antrian.\n");
        return;
    }

    // Hapus node dari posisi lama
    if (prev != NULL) {
        prev->next = curr->next;
        if (curr == antrian->last) {
            antrian->last = prev;
        }
    }

    // Masukkan ke posisi pertama antrian (setelah pasien di ruangan)
    if (prevSkip != NULL) {
        curr->next = prevSkip->next;
        prevSkip->next = curr;
        if (curr->next == NULL) {
            antrian->last = curr;
        }
    }

    printf(">> Kamu berhasil pindah ke posisi pertama antrian!\n");
}
