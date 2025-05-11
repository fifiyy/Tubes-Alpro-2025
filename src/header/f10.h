#ifndef F10_H
#define F10_H

#include "../ADT/header/list_user.h"
#include "../ADT/header/set.h"
#include "../header/register.h"
#include "../header/init_data.h"
#include "../header/ruangan.h"

void tambah_dokter (ListUser *users, Set *usernames);
void assign_dokter (ListUser *users, ListRuangan *ruangan);

#endif
