#include <stdio.h>
#include "../header/Diagnosis.h"
#include "../header/Dokter.h"
#include "../ADT/header/Ruangan.h"
#include "../header/Pasien.h"

extern ListRuangan ruangan;

static char *identifikasi_penyakit (Pasien *pasien) {
    static char namaPenyakit[MAX_PENYAKIT];
    for (int i = 0; i < jumlahPenyakit; i++) {
        Penyakit p = ketPenyakit[i];
        if (pasien->suhu >= p.suhuMin && pasien->suhu <= p.suhuMax &&
            pasien->tekananDarah[0] >= p.bpSisMin && pasien->tekananDarah[0] <= p.bpSisMax &&
            pasien->tekananDarah[1] >= p.bpDiasMin && pasien->tekananDarah[1] <= p.bpDiasMax &&
            pasien->detakJantung >= p.bpmMin && pasien->detakJantung <= p.bpmMax &&
            pasien->saturasiOksigen >= p.satsMin && pasien->saturasiOksigen <= p.satsMax &&
            pasien->kadarGulaDarah >= p.bgMin && pasien->kadarGulaDarah <= p.bgMax &&
            pasien->beratBadan >= p.bbMin && pasien->beratBadan <= p.bbMax &&
            pasien->tinggiBadan >= p.tbMin && pasien->tinggiBadan <= p.tbMax &&
            pasien->kadarKolesterol >= p.fatMin && pasien->kadarKolesterol <= p.fatMax &&
            pasien->trombosit >= p.tromMin && pasien->trombosit <= p.tromMax) 
            {
                strcpy(pasien->penyakit, p.nama);
                strncpy(namaPenyakit, p.nama, MAX_PENYAKIT-1);
                namaPenyakit[MAX_PENYAKIT-1] = '\0';
                return namaPenyakit;
            }
    }
    return NULL;
} 

void diagnosis_pasien (User *userDokter) {
    if (userDokter == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    if (userDokter->role != ROLE_DOKTER) {
        printf("Hanya dokter yang bisa diagnosis!\n");
        return;
    }
    Dokter *dokter = userDokter->dataDokter;
    int idxRuang = dokter->ruangan - 1;
    if (idxRuang < 0 || idxRuang >= ruangan.jumlah) {
        printf("[dr. %s] Anda belum memiliki ruangan.\n", userDokter->username);
        return;
    }
    Ruangan *r = &ruangan.ruang[idxRuang];
    address current = r->Antrian.first;
    if (current == NULL) {
        printf("[dr. %s] Kamu lagi nggak ada pasien. Asik, free time!\n", userDokter->username);
        return;
    }
    User *user_pasien = current->pasien;
    Pasien *pasien = user_pasien->dataPasien;
    if (pasien->status == butuhDiberiObat) {
        printf("[dr. %s] Pasien %s udah didiagnosa, tinggal dikasih obat aja\n", userDokter->username, user_pasien->username);
        return;
    }
    char *penyakit = identifikasi_penyakit(pasien);
    if (penyakit != NULL) {
        pasien->status = butuhDiberiObat;
        printf("[dr. %s] Pasien %s terdiagnosa mengidap penyakit: %s\n", userDokter->username, user_pasien->username, penyakit);
        printf("Jangan lupa untuk diobatin ya, dr. %s!\n", userDokter->username);
        printf("Untuk mengobati pasien %s, ketik NGOBATIN!\n", user_pasien->username);
    } else {
        pasien->status = butuhPulang;
        printf("[dr. %s] Pasien %s sehat banget! Dijamin kuat salto keliling kota!\n", userDokter->username, user_pasien->username);
        // Keluarkan pasien dari queue (dequeue)
        queue_dequeue(&r->Antrian);
    }
}