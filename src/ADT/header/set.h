#ifndef SET_H
#define SET_H

#include <string.h> // Untuk operasi string
#include "boolean.h"

#define Nil 0
#define MaxEl 100
#define USERNAME_LEN 50 // Panjang maksimum username

typedef struct {
    char elements[MaxEl][USERNAME_LEN]; // Array untuk menyimpan username
    int count; // Jumlah elemen dalam Set
} Set;

extern Set usernames; // Deklarasi variabel global untuk menyimpan daftar username
extern Set doctorUsernames;

/* Definisi Set S kosong : S.Count = Nil */
/* S.Count = jumlah elemen Set */
/* S.Elements = tempat penyimpanan elemen Set */

/* ********* Prototype ********* */

/* *** Konstruktor/Kreator *** */
void set_create_empty(Set *S);
/* I.S. Sembarang */
/* F.S. Membuat sebuah Set S kosong berkapasitas MaxEl */
/* Ciri Set kosong : count bernilai Nil */

/* ********* Predikat Untuk test keadaan KOLEKSI ********* */
boolean set_is_empty(Set S);
/* Mengirim true jika Set S kosong */
/* Ciri Set kosong : count bernilai Nil */

boolean set_is_full(Set S);
/* Mengirim true jika Set S penuh */
/* Ciri Set penuh : count bernilai MaxEl */

/* ********** Operator Dasar Set ********* */
void set_insert(Set *S, const char *Elmt);
/* Menambahkan Elmt sebagai elemen Set S. */
/* I.S. S mungkin kosong, S tidak penuh
        S mungkin sudah beranggotakan Elmt */
/* F.S. Elmt menjadi anggota dari S. Jika Elmt sudah merupakan anggota, operasi tidak dilakukan */

void set_delete(Set *S, const char *Elmt);
/* Menghapus Elmt dari Set S. */
/* I.S. S tidak kosong
        Elmt mungkin anggota / bukan anggota dari S */
/* F.S. Elmt bukan anggota dari S */

boolean set_is_member(Set S, const char *Elmt);
/* Mengembalikan true jika Elmt adalah anggota dari S */

#endif