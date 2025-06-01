#include <stdio.h>
#include <string.h>
#include "Minum_Obat.h"

void minum_obat(User *user_pasien) {
    if (currUser == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    else if (currUser->role != ROLE_PASIEN) {
        printf("Eits...pasien doang yang bisa minum obat!\n");
        return;
    }

    printf("\n+-----------------------------------------------+\n");
    printf("|                   MINUM OBAT                  |\n");
    printf("+-----------------------------------------------+\n");
    
    Pasien *pasien = user_pasien->dataPasien;
    Stack *perutPasien = &(pasien->perutPasien);

    if (pasien->status == butuhMinumObat || pasien->status == butuhPenawar) {
        printf("Yuk minum obatmu dulu..\n");
        printf("Kamu punya %d obat yang harus diminum.\n", pasien->jumlahObat);
    }
    else {
        printf("Kamu lagi ga perlu minum obat kok.\n");
        return;
    }

    while (pasien->jumlahObat > 0) {
        if (pasien->status == butuhPenawar) {
            char konfirmasi;
            int valid = 0;
            while (!valid) {
                printf("Kamu lagi keracunan gara-gara urutan minumnya salah.. Mau minum penawarnya dulu gak? (y/n): ");
                scanf(" %c", &konfirmasi);
                if (konfirmasi == 'n' || konfirmasi == 'N') {
                    valid = 1; // lanjut ke proses minum obat
                }
                else if (konfirmasi == 'y' || konfirmasi == 'Y') {
                    printf("Oke, minum penawarnya dulu ya!.\n");
                    return;
                }
                else {
                    printf("Input tidak valid. Silakan coba lagi.\n");
                }
            }
        }
        // cek validitas pasien dan jumlahObat sudah dicek di atas
    
        // print daftar obat
        printf("\n============ DAFTAR OBAT ============\n");
        printf("Urutan minum obat sesuai resep dokter:\n");
        for (int i = 0; i < pasien->jumlahObatResep; i++) {
                printf("%s", pasien->daftarObatResep[i].nama);
                if (i < pasien->jumlahObatResep - 1) {
                    printf(" -> ");
                }
            }
            printf("\n\n");
        
        printf("Obat yang harus diminum:\n");
        for (int i = 0; i < pasien->jumlahObat; i++) {
            printf("%d. %s\n", i + 1, pasien->daftarObat[i].nama);
        }
        printf("\n");

        printf("Obat yang sudah diminum:\n");
        if (stack_is_empty(*perutPasien)) {
            printf("Belum ada obat yang diminum.\n");
        } else {
            for (int i = 0; i <= perutPasien->idxTop; i++) {
                printf("%s", perutPasien->buffer[i].nama);
                if (i < perutPasien->idxTop) {
                    printf(" -> ");
                }
            }
            printf("\n");
        }

        printf("\nPilih obat untuk diminum: ");
        int pilihanObat;
        scanf("%d", &pilihanObat);
    
        if (pilihanObat < 1 || pilihanObat > pasien->jumlahObat) {
            printf("\nObatnya gak diresepkan buat kamu!\n");
            continue;
        }
    
        int idxObat = pilihanObat - 1;
    
        // if (stack_is_full(*perutPasien)) {
        //     printf("Perut penuh! Kamu gak bisa minum obat lagi.\n");
        //     return;
        // } gaperlu soalnya logika kodenya aja kalo obatnya belum habis diminum

        // masukkan obat ke perutPasien (stack)
        stack_push(perutPasien, pasien->daftarObat[idxObat]);
        printf("GLEKGLEKGLEK.. %s berhasil diminum!\n", pasien->daftarObat[idxObat].nama);

        // hapus obat dari daftar obat (geser array dari idx)
        for (int i = idxObat; i < pasien->jumlahObat - 1; i++) {
            pasien->daftarObat[i] = pasien->daftarObat[i + 1];
        }
        pasien->jumlahObat--;

        // obat yang diminum tidak sesuai dengan resep dokter
        for (int i = 0; i <= perutPasien->idxTop; i++) {
            if (strcmp(perutPasien->buffer[i].nama, pasien->daftarObatResep[i].nama) != 0) {
                pasien->status = butuhPenawar;
                printf("Kamu merasa makin gak enak badan...kayaknya kamu salah minum urutan obat deh..\n");
                printf("Dok! Butuh obat penawar!!");
            return;
            }
        }

        if (pasien->jumlahObat == 0) {
            if (pasien->status == butuhPenawar) {
                printf("Kamu sudah minum semua obat, tapi masih butuh penawar.\n");
                pasien->status = butuhPenawar;
                return;
            }
            else {
                pasien->status = butuhPulang;
                printf("Kamu sudah minum semua obat yang diberikan dokter. Silakan pulang ya!\n");
            }
            break;
        }
    }
}