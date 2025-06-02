#include "../header/List_User.h"
#include "../../header/User.h"

void list_make_empty(ListUser *L) {
    L->length = 0;
}

int list_nb_elmt(ListUser L) {
    return L.length;
}

int list_max_nb_el(ListUser L) {
    return MAX_CAPACITY;
}

IdxType list_get_first_idx(ListUser L) {
    return 0;
}

IdxType list_get_last_idx(ListUser L) {
    return L.length - 1;
}

User list_get_elmt(ListUser L, IdxType i) {
    return L.data[i];
}

void list_set_tab(ListUser Lin, ListUser *Lout) {
    Lout->length = Lin.length;
    for (int i = 0; i < Lin.length; i++) {
        Lout->data[i] = Lin.data[i];
    }
}

void list_set_el(ListUser *L, IdxType i, User v) {
    L->data[i] = v;
    if (L->length < i + 1) {
        L->length = i + 1;
    }
}

void list_set_length(ListUser *L, IdxType N) {
    L->length = N;
}

boolean list_is_idx_valid(ListUser L, IdxType i) {
    return i >= list_get_first_idx(L) && i < MAX_CAPACITY;
}

boolean list_is_idx_eff(ListUser L, IdxType i) {
    return i >= list_get_first_idx(L) && i <= list_get_last_idx(L);
}

boolean list_is_empty(ListUser L) {
    return L.length == 0;
}

boolean list_is_full(ListUser L) {
    return L.length == MAX_CAPACITY;
}
