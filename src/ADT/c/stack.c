#include <stdio.h>
#include "../header/stack.h"

/*** Konstruktor/Kreator ***/
void create_stack(Stack *s) {
    IDX_TOP(*s) = IDX_UNDEF;
}
/* I.S. Sembarang */
/* F.S. Membuat sebuah Stack s yang kosong berkapasitas CAPACITY */
/* jadi indeksnya antara 0..CAPACITY-1 */

/* Ciri stack kosong: idxTop bernilai IDX_UNDEF */
/********** Predikat Untuk test keadaan KOLEKSI **********/
boolean stack_is_empty(Stack s) {
    return IDX_TOP(s) == IDX_UNDEF;
}
/* Mengirim true jika Stack kosong: lihat definisi di atas */

boolean stack_is_full(Stack s) {
    return IDX_TOP(s) == CAPACITY - 1;
}
/* Mengirim true jika Stack penuh */

int stack_length (Stack s) {
    if (stack_is_empty(s)) {
        return 0;
    } else {
        return IDX_TOP(s) + 1;
    }
}
/* Mengirim ukuran Stack s saat ini */

/*********** Menambahkan sebuah elemen ke Stack **********/
void stack_push (Stack *s, ElType val) {
        IDX_TOP(*s)++;
        TOP(*s) = val;
}
/* Menambahkan val sebagai elemen Stack s.
I.S. s mungkin kosong, tidak penuh
F.S. val menjadi TOP yang baru, TOP bertambah 1 */

/*********** Menghapus sebuah elemen Stack **********/
void stack_pop (Stack *s, ElType *val) {
    *val = TOP(*s);
    IDX_TOP(*s)--;
}
/* Menghapus X dari Stack S.
I.S. S tidak mungkin kosong
F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
