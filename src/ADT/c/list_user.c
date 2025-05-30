#include "../header/List_User.h"
#include "../../header/User.h"

void make_empty (ListUser *L) {
    L->length = 0;
}

int nb_elmt(ListUser L) {
    return L.length;
}

int max_nb_el (ListUser L) {
    return MAX_CAPACITY;
}

IdxType get_first_idx (ListUser L) {
    return 0;
}

IdxType get_last_idx (ListUser L) {
    return L.length - 1;
}

User get_elmt (ListUser L, IdxType i) {
    return L.data[i];
}

void set_tab (ListUser Lin, ListUser *Lout) {
    Lout->length = Lin.length;
    for (int i = 0; i < Lin.length; i++) {
        Lout->data[i] = Lin.data[i];
    }
}

void set_el (ListUser *L, IdxType i, User v) {
    L->data[i] = v;
    if (L->length < i + 1) {
        L->length = i + 1;
    }
}

void set_length (ListUser *L, IdxType N) {
    L->length = N;
}

boolean is_idx_valid (ListUser L, IdxType i) {
    return i >= GetFirstIdx(L) && i < MAX_CAPACITY;
}

boolean is_idx_eff (ListUser L, IdxType i) {
    return i >= GetFirstIdx(L) && i <= GetLastIdx(L);
}

boolean is_empty (ListUser L) {
    return L.length == 0;
}

boolean is_full (ListUser L) {
    return L.length == MAX_CAPACITY;
}

