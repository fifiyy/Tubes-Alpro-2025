#include <stdio.h>
#include <string.h>
#include "Minum_Obat.h"

void minum_obat(User *user_pasien) {
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    else if (currUser->role != ROLE_PASIEN) {
        printf("\nERROR: Eits...pasien doang yang bisa minum obat!\n");
        return;
    }

    printf("\n+-----------------------------------------------+\n");
    printf("|                   MINUM OBAT                  |\n");
    printf("+-----------------------------------------------+\n");
    
    Pasien *pasien = user_pasien->dataPasien;
    Stack *perutPasien = &(pasien->perutPasien);

    if (pasien->status == butuhMinumObat || pasien->status == butuhPenawar) {
        printf(">> Yuk minum obatmu dulu..\n");
        printf("[@%s] Kamu punya %d obat yang harus diminum.\n", user_pasien->username, pasien->jumlahObat);
    }
    else {
        printf("[@%s] Kamu lagi ga perlu minum obat kok :D\n", user_pasien->username);
        return;
    }

    while (pasien->jumlahObat > 0) {
        if (pasien->status == butuhPenawar) {
            char konfirmasi;
            int valid = 0;
            while (!valid) {
                printf("[@%s] Kamu lagi keracunan gara-gara urutan minumnya salah.. Mau minum penawarnya dulu gak? (y/n): ", user_pasien->username);
                scanf(" %c", &konfirmasi);
                if (konfirmasi == 'n' || konfirmasi == 'N') {
                    valid = 1; // lanjut ke proses minum obat
                }
                else if (konfirmasi == 'y' || konfirmasi == 'Y') {
                    printf(">> Oke, minum penawarnya dulu ya!.\n");
                    return;
                }
                else {
                    printf("\nERROR: Input tidak valid. Silakan coba lagi.\n");
                }
            }
        }
        // cek validitas pasien dan jumlahObat sudah dicek di atas
    
        // print daftar obat
        printf("\n============ DAFTAR OBAT ============\n");
        if (pasien->sisaNyawa < 3) {
            printf("Hati-hati! Sisa nyawamu tinggal %d lagi\n",pasien->sisaNyawa);
        }
        else {
            printf("Sisa nyawamu: %d\n",pasien->sisaNyawa);
        }

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
            printf("\nERROR: Obatnya gak diresepkan buat kamu!\n");
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
                printf("Kamu merasa makin gak enak badan... kayaknya kamu salah minum obat deh..\n");
                printf("Dok! Butuh obat penawar!! X o X\n");
                pasien->sisaNyawa -= 1;
            return;
            }
        }

        if (pasien->jumlahObat == 0) {
            if (pasien->status == butuhPenawar) {
                printf("Kamu sudah minum semua obat, tapi masih keracunan! Untung ga game over T-T.\n");
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