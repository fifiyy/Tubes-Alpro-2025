#include "../header/set.h"

void CreateEmpty(Set *S) {
    S->Count = Nil;
}

boolean Set_IsEmpty(Set S) {
    return S.Count == Nil;
}

boolean Set_IsFull(Set S) {
    return S.Count == MaxEl;
}

void Insert(Set *S, const char *Elmt) {
    if (Set_IsFull(*S)) return; // Tidak bisa menambahkan jika penuh
    if (IsMember(*S, Elmt)) return; // Tidak menambahkan elemen duplikat

    strcpy(S->Elements[S->Count], Elmt); // Salin elemen ke dalam Set
    S->Count++;
}

void Delete(Set *S, const char *Elmt) {
    if (Set_IsEmpty(*S)) return; // Tidak bisa menghapus jika kosong

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

boolean IsMember(Set S, const char *Elmt) {
    for (int i = 0; i < S.Count; i++) {
        if (strcmp(S.Elements[i], Elmt) == 0) { // Bandingkan string
            return true;
        }
    }
    return false;
}