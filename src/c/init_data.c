#include "../header/init_data.h"
#include "../header/list_user.h"
#include "../header/set.h"

void init_data(ListUser *users, Set *usernames) {
    MakeEmpty(users); // Inisialisasi list
    set_create_empty(usernames); // Inisialisasi set

    // Tambahkan pengguna awal ke ListUser dan Set
    SetEl(users, 0, (User){"nimonsslatte", "nimonatutgajah23", ROLE_MANAGER});
    set_insert(usernames, "nimonsslatte");
    SetEl(users, 1, (User){"Neroifa", "Neroifa123", ROLE_DOKTER});
    set_insert(usernames, "Neroifa");
    SetEl(users, 2, (User){"GRO", "NeroifaCantik", ROLE_PASIEN});
    set_insert(usernames, "GRO");
    SetEl(users, 3, (User){"nimonsganteng", "KelompokAmatGacor", ROLE_PASIEN});
    set_insert(usernames, "nimonsganteng");
    SetLength(users, 4);
}