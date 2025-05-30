#include <stdio.h>
#include "../header/Diagnosis.h"
#include "../header/dokter.h"
#include "../ADT/header/ruangan.h"
#include "../header/pasien.h"

extern ListRuangan ruangan;

static char *identifikasiPenyakit (Pasien *pasien) {
    static char nama_penyakit[MAX_PENYAKIT];
    for (int i = 0; i < JUMLAH_PENYAKIT; i++) {
        Penyakit p = ketPenyakit[i];
        if (pasien->suhu >= p.suhu_min && pasien->suhu <= p.suhu_max &&
            pasien->tekananDarah[0] >= p.bp_sis_min && pasien->tekananDarah[0] <= p.bp_sis_max &&
            pasien->tekananDarah[1] >= p.bp_dias_min && pasien->tekananDarah[1] <= p.bp_dias_max &&
            pasien->detakJantung >= p.bpm_min && pasien->detakJantung <= p.bpm_max &&
            pasien->saturasiOksigen >= p.sats_min && pasien->saturasiOksigen <= p.sats_max &&
            pasien->kadarGulaDarah >= p.bg_min && pasien->kadarGulaDarah <= p.bg_max &&
            pasien->beratBadan >= p.bb_min && pasien->beratBadan <= p.bb_max &&
            pasien->tinggiBadan >= p.tb_min && pasien->tinggiBadan <= p.tb_max &&
            pasien->kadarKolesterol >= p.fat_min && pasien->kadarKolesterol <= p.fat_max &&
            pasien->trombosit >= p.trom_min && pasien->trombosit <= p.trom_max) 
            {
                strcpy(pasien->penyakit, p.nama);
                strncpy(nama_penyakit, p.nama, MAX_PENYAKIT-1);
                nama_penyakit[MAX_PENYAKIT-1] = '\0';
                return nama_penyakit;
            }
    }
    return NULL;
} 

void diagnosisPasien (User *user_dokter) {
    if (user_dokter == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    if (user_dokter->role != ROLE_DOKTER) {
        printf("Hanya dokter yang bisa diagnosis!\n");
        return;
    }
    Dokter *dokter = user_dokter->dokter_data;
    int idx_ruang = dokter->ruangan - 1;
    if (idx_ruang < 0 || idx_ruang >= ruangan.jumlah) {
        printf("[dr. %s] Anda belum memiliki ruangan.\n", user_dokter->username);
        return;
    }
    Ruangan *r = &ruangan.ruang[idx_ruang];
    address current = r->Antrian.First;
    if (current == NULL) {
        printf("[dr. %s] Kamu lagi nggak ada pasien. Asik, free time!\n", user_dokter->username);
        return;
    }
    User *user_pasien = current->pasien;
    Pasien *pasien = user_pasien->pasien_data;
    if (pasien->status == statusDiberiObat) {
        printf("[dr. %s] Pasien %s udah didiagnosa, tinggal dikasih obat aja\n", user_dokter->username, user_pasien->username);
        return;
    }
    char *penyakit = identifikasiPenyakit(pasien);
    if (penyakit != NULL) {
        pasien->status = statusDiberiObat;
        printf("[dr. %s] Pasien %s terdiagnosa mengidap penyakit: %s\n", user_dokter->username, user_pasien->username, penyakit);
        printf("Jangan lupa untuk diobatin ya, dr. %s!\n", user_dokter->username);
        printf("Untuk mengobati pasien %s, ketik NGOBATIN!\n", user_pasien->username);
    } else {
        pasien->status = statusPulang;
        printf("[dr. %s] Pasien %s sehat banget! Dijamin kuat salto keliling kota!\n", user_dokter->username, user_pasien->username);
        // Keluarkan pasien dari queue (dequeue)
        queue_dequeue(&r->Antrian);
    }
}