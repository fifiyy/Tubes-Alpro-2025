#include <stdio.h>
#include "../header/Set.h"

void set_create_empty (Set *S) {
    S->count = 0;
}

boolean set_is_empty (Set S) {
    return S.count == 0; // Mengembalikan true jika count adalah 0
}

boolean set_is_full (Set S) {
    return S.count == MaxEl;
}

void set_insert (Set *S, const char *Elmt) {
    if (set_is_full(*S)) return; // Tidak bisa menambahkan jika penuh
    if (set_is_member(*S, Elmt)) return; // Tidak menambahkan elemen duplikat

    strcpy(S->elements[S->count], Elmt); // Salin elemen ke dalam Set
    S->count++;
}

void set_delete (Set *S, const char *Elmt) {
    if (set_is_empty(*S)) return; // Tidak bisa menghapus jika kosong

    int idx = -1;
    for (int i = 0; i < S->count; i++) {
        if (strcmp(S->elements[i], Elmt) == 0) { // Bandingkan string
            idx = i;
            break;
        }
    }

    if (idx == -1) return; // Elemen tidak ditemukan

    for (int i = idx; i < S->count - 1; i++) {
        strcpy(S->elements[i], S->elements[i + 1]); // Geser elemen
    }
    S->count--;
}

boolean set_is_unique (const Set *S, const char *usernames) {
    for (int i = 0; i < S->count; i++) {
        const char *a = S->elements[i];
        const char *b = usernames;
       
        while (*a && *b) {
            char a_char = *a;
            char b_char = *b;
           
            // Case-insensitive comparison
            if (a_char >= 'A' && a_char <= 'Z') a_char += 32;
            if (b_char >= 'A' && b_char <= 'Z') b_char += 32;
           
            if (a_char != b_char) break;
           
            a++;
            b++;
        }
       
        if (*a == '\0' && *b == '\0') {
            return false;
        }
    }
    return true;
}

boolean set_is_member (Set S, const char *Elmt) {
    if (set_is_empty(S)) return false; // Jika Set kosong, tidak ada anggota

    for (int i = 0; i < S.count; i++) {
        if (set_is_unique(&S, Elmt)) return false; // Jika elemen unik, tidak ada anggota

        // Cek apakah Elmt ada dalam Set
        if (strcmp(S.elements[i], Elmt) == 0) { // Bandingkan string
            return true;
        }
    }
    return false;
}