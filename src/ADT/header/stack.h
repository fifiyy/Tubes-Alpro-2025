#include <string.h>
#include "boolean.h"

#ifndef STACK_H
#define STACK_H

#define IDX_UNDEF -1
#define CAPACITY 100

typedef int ElType;

typedef struct
{
    ElType buffer[CAPACITY];
    int idxTop;
} Stack;

#define IDX_TOP(s) (s).idxTop
#define TOP(s) (s).buffer[(s).idxTop]

/*** Konstruktor/Kreator ***/
void create_stack(Stack *s);
/* I.S. Sembarang */
/* F.S. Membuat sebuah Stack s yang kosong berkapasitas CAPACITY */
/* jadi indeksnya antara 0..CAPACITY-1 */

/* Ciri stack kosong: idxTop bernilai IDX_UNDEF */
/********** Predikat Untuk test keadaan KOLEKSI **********/
boolean stack_is_empty(Stack s);
/* Mengirim true jika Stack kosong: lihat definisi di atas */

boolean stack_is_full(Stack s);
/* Mengirim true jika Stack penuh */

int stack_length(Stack s);
/* Mengirim ukuran Stack s saat ini */

/*********** Menambahkan sebuah elemen ke Stack **********/
void stack_push(Stack *s, ElType val);
/* Menambahkan val sebagai elemen Stack s.
I.S. s mungkin kosong, tidak penuh
F.S. val menjadi TOP yang baru, TOP bertambah 1 */

/*********** Menghapus sebuah elemen Stack **********/
void stack_pop(Stack *s, ElType *val);
/* Menghapus X dari Stack S.
I.S. S tidak mungkin kosong
F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
#endif