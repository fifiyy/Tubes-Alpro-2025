#include "../header/diagnosis.h"
#include <stdio.h>

static char *identifikasiPenyakit (Pasien *pasien) {
    for (int i = 0; i < sizeof(ketPenyakit); i++) {
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
                return p.nama;
            }
    }
    return NULL;
}
/*
void updateAntrian (Dokter *dokter) {
    for (int i = 0; i < MAX_PASIEN_RUANGAN; i++) {
        if (dokter->pasienDiRuangan[i] == NULL) {
            User *pasien_baru = dequeue(&dokter->antrian);
            if (pasien_baru != NULL) {
                if (pasien_baru->role == ROLE_PASIEN) {
                    dokter->pasienDiRuangan[i] = pasien_baru;
                    printf("Pasien");
                }
            }
        }
    }
}
*/
void diagnosisPasien (User *user_dokter) {
    if (user_dokter == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.");
        return;
    }
    
    if (user_dokter->role != ROLE_DOKTER) {
        printf("Hanya dokter yang bisa diagnosis!\n");
        return;
    }

    Dokter *dokter = user_dokter->dokter_data;

    int slot_aktif = -1;
    for (int i = 0; i < MAX_PASIEN_RUANGAN; i++) {
        if (dokter->pasienDiRuangan[i] != NULL) {
            slot_aktif = i;
            break;
        }
    }

    if (slot_aktif == -1) {
        printf("[dr. %s] Kamu lagi nggak ada pasien. Asik, free time!\n", user_dokter->username);
        return;
    }

    //  PROSES DIAGNOSIS
    User *user_pasien = dokter->pasienDiRuangan[slot_aktif];
    Pasien *pasien = user_pasien->pasien_data;

    if (pasien->status == butuhDiberiObat) {
        printf("[dr. %s] Pasien %s udah didiagnosa, tinggal dikasih obat aja\n", user_dokter->username, user_pasien->username);
        return;
    } // Validasi sudah diagnosa atau belum

    char *penyakit = identifikasiPenyakit(pasien);
    if (penyakit != NULL) {
        pasien->status = butuhDiberiObat;
        printf("[dr. %s] Pasien %s terdiagnosa mengidap penyakit: %s\n", user_dokter->username, user_pasien->username, penyakit);
        printf("Jangan lupa untuk diobatin ya, dr. %s!\n", user_dokter->username);
        printf("Untuk mengobati pasien %s, ketik NGOBATIN!\n");
    } else {
        pasien->status = butuhPulang;
        printf("[dr. %s] Pasien %s sehat banget! Dijamin kuat salto keliling kota!\n");
        dokter->pasienDiRuangan[slot_aktif] = NULL;
        dequeue(&dokter->antrian);
    }
}