#include <stdio.h>
#include <string.h>
#include "Pulangdok.h"

// extern AntrianDokter antrianDokter;
extern User *currUser;

void make_default_pasien(Pasien *pasien) {
    pasien->id = -1;
    pasien->suhu = 0.0;
    pasien->beratBadan = 0.0;
    pasien->tinggiBadan = 0;
    pasien->tekananDarah[0] = 0; // sistol
    pasien->tekananDarah[1] = 0; // diastol
    pasien->detakJantung = 0;
    pasien->saturasiOksigen = 0.0;
    pasien->kadarGulaDarah = 0;
    pasien->kadarKolesterol = 0;
    pasien->trombosit = 0;
    pasien->jumlahObat = 0;
    pasien->jumlahObatResep = 0;
    pasien->status = butuhDiagnosa;
    pasien->idRuangan = -1; // belum ada ruangan
    pasien->posisiAntrian = -1; // belum terdaftar di antrian
}

void pulangdok(User *user_pasien, ListRuangan *listRuangan) {
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    else if (currUser->role != ROLE_PASIEN) {
        printf("\nERROR: Hanya pasien yang bisa konsultasi pada dokter lagi!\n");
        return;
    }
    printf("\n+-----------------------------------------------+\n");
    printf("|                    PULANG                     |\n");
    printf("+-----------------------------------------------+\n");
    
    Pasien *pasien = user_pasien->dataPasien;
    int idRuangan = pasien->idRuangan; 
    
    // Cari ruangan yang sesuai idRuangan
    Ruangan *ruanganDokter = NULL;
    for (int i = 0; i < listRuangan->jumlah; i++) {
        if (listRuangan->ruang[i].nomor == idRuangan) {
            ruanganDokter = &listRuangan->ruang[i];
            break;
        }
    }

    if (ruanganDokter == NULL) {
        printf("\nERROR: Ruangan pasien tidak ditemukan!\n");
        return;
    }

    AntrianDokter *antrianDokterRuangan = &(ruanganDokter->Antrian);

    // cek paling depan
    if (antrianDokterRuangan->first == NULL || antrianDokterRuangan->first->pasien != user_pasien) {
        printf(">> Maaf, kamu bukan pasien paling depan di antrian. Tunggu giliranmu ya.\n");
        return;
    } else {
        Pasien *pasien = user_pasien->dataPasien;
        Obat *daftarObat = pasien->daftarObat;
        int jumlahObat = pasien->jumlahObat;
        Stack *perutPasien = &(pasien->perutPasien);

        if (pasien->status == butuhDiagnosa) {
            printf("[@%s] Loh... kamu belum didiagnosa dokter sama sekali, jangan buru-buru pulang!\n", user_pasien->username);
            printf("HELP: Untuk daftar gunakan DAFTAR_CHECKUP dan untuk cek antrianmu gunakan LIHAT_ANTRIAN!\n");
            return;
        }
        else if (pasien->status == butuhMinumObat && pasien->jumlahObat > 0) {
            printf("Kamu belum menghabiskan seluruh obat yang diberikan. Yuk minum obatmu dulu!\n");
         return;
        }
        else if (pasien->status == butuhPenawar) {
            printf(">> Dokter sedang memeriksa...\n");
            printf("\nMaaf, kamu kayaknya masih belum bisa pulang, masih sakit ya?\n");
            printf("Urutan obat yang diharapkan: \n");
            printf("        ");
            for (int i = 0; i < pasien->jumlahObatResep; i++) {
                printf("%s", pasien->daftarObatResep[i].nama);
                if (i < pasien->jumlahObatResep - 1) {
                    printf(" -> ");
                }
            }
            printf("\n");

            printf("Urutan obat yang kamu minum: \n");
            printf("        ");
            for (int i = 0; i <= perutPasien->idxTop; i++) {
                printf("%s", perutPasien->buffer[i].nama);
                if (i < perutPasien->idxTop) {
                    printf(" -> ");
                }
            }
            printf("\n");

            printf("Kunjungi dokter untuk meminta penawar yang sesuai yaa!\n");
            return;
        }
        else {
            printf(">> Dokter sedang periksa kamu...\n");
            printf("[@%s] Yayy Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu\n", user_pasien->username);
    
            // reset data pasien seperti pas register

            make_default_pasien(pasien);
    
            int keluar = queue_dequeue(antrianDokterRuangan);
            currUser = NULL;
            return;
        }
    }
}
