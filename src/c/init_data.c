#include "../header/init_data.h"
#include "../header/list_user.h"
#include "../header/set.h"

void init_data(ListUser *users, Set *usernames) {
    MakeEmpty(users); // Inisialisasi list
    CreateEmpty(usernames); // Inisialisasi set

    // Tambahkan pengguna awal ke ListUser dan Set
    SetEl(users, 0, (User){"nimonsslatte", "nimonatutgajah23", ROLE_MANAGER});
    Insert(usernames, "nimonsslatte");
    SetEl(users, 1, (User){"Neroifa", "Neroifa123", ROLE_DOKTER});
    Insert(usernames, "Neroifa");
    SetEl(users, 2, (User){"GRO", "NeroifaCantik", ROLE_PASIEN});
    Insert(usernames, "GRO");
    SetEl(users, 3, (User){"nimonsganteng", "KelompokAmatGacor", ROLE_PASIEN});
    Insert(usernames, "nimonsganteng");
    SetLength(users, 4);
}