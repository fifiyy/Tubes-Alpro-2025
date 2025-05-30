#include "../header/list_user.h"

void MakeEmpty(ListUser *L) {
    L->length = 0;
}

int NbElmt(ListUser L) {
    return L.length;
}

int MaxNbEl(ListUser L) {
    return MAX_CAPACITY;
}

IdxType GetFirstIdx(ListUser L) {
    return 0;
}

IdxType GetLastIdx(ListUser L) {
    return L.length - 1;
}

User GetElmt(ListUser L, IdxType i) {
    return L.data[i];
}

void SetTab(ListUser Lin, ListUser *Lout) {
    Lout->length = Lin.length;
    for (int i = 0; i < Lin.length; i++) {
        Lout->data[i] = Lin.data[i];
    }
}

void SetEl(ListUser *L, IdxType i, User v) {
    L->data[i] = v;
    if (L->length < i + 1) {
        L->length = i + 1;
    }
}

void SetLength(ListUser *L, IdxType N) {
    L->length = N;
}

boolean IsIdxValid(ListUser L, IdxType i) {
    return i >= GetFirstIdx(L) && i < MAX_CAPACITY;
}

boolean IsIdxEff(ListUser L, IdxType i) {
    return i >= GetFirstIdx(L) && i <= GetLastIdx(L);
}

boolean IsEmpty(ListUser L) {
    return L.length == 0;
}

boolean IsFull(ListUser L) {
    return L.length == MAX_CAPACITY;
}
