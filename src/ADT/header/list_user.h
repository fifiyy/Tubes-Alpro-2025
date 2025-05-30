
#ifndef ListofUser_H
#define ListofUser_H

#include "boolean.h"
#include <stdio.h>
#include <string.h>
#include "../header/user.h"

#define MAX_CAPACITY 100
#define IDX_UNDEF -999 /* Tidak terdefinisi */

typedef int IdxType;

typedef struct {
    User data[MAX_CAPACITY];  // Gunakan forward declaration
    IdxType length;
} ListUser;

typedef struct {
    User data[MAX_CAPACITY];  // Gunakan forward declaration
    IdxType length;
} ListDokter;

// Deklarasi extern untuk ListUser, ListObat, dan ListPenyakit

/* Indeks yang digunakan [0..MAX_CAPACITY-1]
 * Jika L adalah ListUser, cara deklarasi dan akses:
 *
 * Deklarasi:  ListUser L;
 *
 * Maka cara akses:
 * L.Neff untuk mengetahui banyaknya elemen
 * L.daftar untuk mengakses seluruh nilai elemen tabel
 * L.daftar[i] untuk mengakses elemen ke-i
 *
 * Definisi:
 * Tabel kosong: L.Neff = 0
 * Definisi elemen pertama : L.daftar[i] dengan i=1
 * Definisi elemen terakhir yang terdefinisi: L.daftar[i] dengan i=L.Neff

/* ********** KONSTRUKTOR ARRAY ********** */
/* Konstruktor : create tabel kosong */
void make_empty (ListUser *L);
/* I.S. sembarang */
/* F.S. Terbentuk list L kosong dengan kapasitas MAX_CAPACITY */
// (*L).Neff = 0;

/* ********** SELEKTOR ********** */
/* *** Banyaknya elemen *** */
int nb_elmt (ListUser L);
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list kosong */
// return L.Neff;

/* *** Daya tampung container *** */
int max_nb_el(ListUser L);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh list */
// return MAX_CAPACITY;

/* *** Selektor INDEKS *** */
IdxType get_first_idx(ListUser L);
/* Prekondisi : List L tidak kosong */
/* Mengirimkan indeks elemen pertama */
// return 0;

IdxType get_last_idx(ListUser L);
/* Prekondisi : List L tidak kosong */
/* Mengirimkan indeks elemen terakhir */
// return L.Neff-1;

/* *** Menghasilkan sebuah elemen *** */
User get_elmt(ListUser L, IdxType i);
/* Prekondisi : List tidak kosong, i antara FirstIdx(L)..LastIdx(L) */
/* Mengirimkan elemen list yang ke-i */
// return L.daftar[i];

/* *** Selektor SET : Mengubah nilai list dan elemen list *** */
/* Untuk type private/limited private pada bahasa tertentu */
void set_tab(ListUser Lin, ListUser *Lout);
/* I.S. Lin terdefinisi, sembarang */
/* F.S. Lout berisi salinan Lin */
/* Assignment Lout = Lin */
// (*Lout).Neff = Lin.Neff;
// for(int i = 0; i < Lin.Neff; i++){
//     (*Lout).daftar[i] = Lin.daftar[i];
// }

void set_el(ListUser *L, IdxType i, User v);
/* I.S. L terdefinisi, sembarang */
/* F.S. Elemen L yang ke-i bernilai v */
/* Mengeset nilai elemen list yang ke-i sehingga bernilai v */
// (*L).daftar[i] = v;
// if ((*L).Neff < i+1){
//     (*L).Neff = i+1;
// }

void set_length(ListUser *L, IdxType N);
/* I.S. L terdefinisi, sembarang */
/* F.S. Nilai indeks efektif L bernilai N */
/* Mengeset nilai indeks elemen efektif sehingga bernilai N */
// (*L).Neff = N;

/* ********** Test Indeks yang valid ********** */
boolean is_idx_valid(ListUser L, IdxType i);
/* Prekondisi : i sembarang */
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran list */
/* yaitu antara indeks yang terdefinisi utk container */
// return i >= GetFirstIdx(L) && i < MAX_CAPACITY;

boolean is_idx_eff(ListUser L, IdxType i);
/* Prekondisi : i sembarang*/
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara GetFirstIdx(L)..GetLastIdx(L) */
// return i >= GetFirstIdx(L) && i <= GetLastIdx(L);

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean is_empty(ListUser L);
/* Mengirimkan true jika list L kosong, mengirimkan false jika tidak */
// return L.Neff == 0;

/* *** Test tabel penuh *** */
boolean is_full(ListUser L);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
// return L.Neff == MAX_CAPACITY;

#endif