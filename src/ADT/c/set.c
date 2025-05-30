#include <stdio.h>
#include "../header/set.h"

void set_create_empty (Set *S) {
    S->Count = 0; // Inisialisasi jumlah elemen Set menjadi 0
    for (int i = 0; i < MaxEl; i++) {
        S->Elements[i][0] = '\0'; // Inisialisasi setiap elemen sebagai string kosong
    }
}

boolean set_is_empty (Set S) {
    return S.Count == 0;}

boolean set_is_full (Set S) {
    return S.Count == MaxEl;
}

void set_insert (Set *S, const char *Elmt) {
    if (set_is_full(*S)) return; // Tidak bisa menambahkan jika penuh
    if (set_is_member(*S, Elmt)) return; // Tidak menambahkan elemen duplikat

    strcpy(S->Elements[S->Count], Elmt); // Salin elemen ke dalam Set
    S->Count++;
}

void set_delete (Set *S, const char *Elmt) {
    if (set_is_empty(*S)) return; // Tidak bisa menghapus jika kosong

    int idx = -1;
    for (int i = 0; i < S->Count; i++) {
        if (strcmp(S->Elements[i], Elmt) == 0) { // Bandingkan string
            idx = i;
            break;
        }
    }

    if (idx == -1) return; // Elemen tidak ditemukan

    for (int i = idx; i < S->Count - 1; i++) {
        strcpy(S->Elements[i], S->Elements[i + 1]); // Geser elemen
    }
    S->Count--;
}

boolean set_is_member (Set S, const char *Elmt) {
    for (int i = 0; i < S.Count; i++) {
        if (strcmp(S.Elements[i], Elmt) == 0) { // Bandingkan string
            return true;
        }
    }
    return false;
}