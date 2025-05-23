#include <stdio.h>
#include "../header/map.h"

/**
 * @brief Membuat dan menginisialisasi Map baru.
 *
 * @param capacity Kapasitas maksimum Map. Asumsikan bahwa nilai capacity selalu
 * > 0.
 * @return Pointer ke objek Map yang baru dibuat, atau NULL jika alokasi gagal
 * atau kapasitas tidak valid.
 */
Map *create_map(int capacity) {
    Map *new_map = (Map *) malloc(sizeof(Map));
    if (new_map == NULL) {
        return NULL;
    }

    new_map->entries = (MapEntry *) malloc(sizeof(MapEntry) * capacity);
    if (new_map->entries == NULL) {
        free(new_map);
        return NULL;
    }

    new_map->capacity = capacity;
    new_map->size = 0;
    return new_map;
}
/**
 * @brief Menyisipkan pasangan key-value baru ke dalam Map, atau memperbarui
 * value jika key sudah ada.
 *
 * @param map Pointer ke objek Map.
 * @param key Kunci yang akan disisipkan atau diperbarui.
 * @param value Nilai yang akan diasosiasikan dengan kunci.
 * @return true jika berhasil (penyisipan atau pembaruan), false jika Map penuh
 * atau input tidak valid.
 * Keterangan: string yang dijadikan value harus dialokasikan ulang agar
 * kepemilikan string tersebut berpindah ke map.
 */
boolean map_insert(Map *map, int key, const char *value) {
    if (map == NULL || value == NULL || map->size >= map->capacity) {
        return false;
    }

    for (int i = 0; i < map->size; i++) {
        if (map->entries[i].key == key) {
            free(map->entries[i].value);                
            map->entries[i].value = strdup(value);
            return true;
        }
    }
    map->entries[map->size].key = key;
    map->entries[map->size].value = strdup(value);
    map->size++;
    return true;
}
/**
 * @brief Mengambil value yang terikat dengan key tertentu.
 *
 * @param map Pointer ke objek Map.
 * @param key Kunci yang nilainya akan diambil.
 * @return nilai jika kunci ditemukan, atau NULL jika kunci
 * tidak ditemukan atau input tidak valid.
 */
char *map_get(const Map *map, int key) {
    for (int i = 0; i < map->size; i++) {
        if (map->entries[i].key == key) {
            return map->entries[i].value;
        }
    }
    return NULL;
}

/**
 * @brief Menghapus pasangan key-value dari Map berdasarkan key.
 *
 * @param map Pointer ke objek Map.
 * @param key Kunci elemen yang akan dihapus.
 * @return true jika berhasil dihapus, false jika kunci tidak ditemukan atau
 * input tidak valid.
 */
boolean map_delete(Map *map, int key) {
    if (map == NULL) {
        return false;
    }

    for (int i = 0; i < map->size; i++) {
        if (map->entries[i].key == key) {
            free(map->entries[i].value);

            for (int j = i; j < map->size; j++) {
                map->entries[j] = map->entries[j+1];
            }
            map->size--;
            return true;
        }
    }

    return false;
}

/**
 * @brief Mendapatkan jumlah elemen (pasangan key-value) dalam Map.
 *
 * @param map Pointer ke objek Map.
 * @return Jumlah elemen dalam Map .
 */
int map_size(const Map *map) {
    return map->size;
}

/**
 * @brief Memeriksa apakah kunci tertentu ada di dalam Map.
 *
 * @param map Pointer ke objek Map.
 * @param key Kunci yang akan diperiksa keberadaannya.
 * @return true jika kunci ada, false jika kunci tidak ada.
 */
boolean map_contains_key(const Map *map, int key) {
    for (int i = 0; i < map->size; i++) {
        if (map->entries[i].key == key) {
            return true;
        }
    }
    return false;
}