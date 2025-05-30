#ifndef REGISTER_H
#define REGISTER_H

#include <stdlib.h>
#include <stdio.h>
#include "../ADT/header/list_user.h"
#include "../ADT/header/set.h"

boolean is_username_unique(const Set *usernames, const char* username);
void register_pasien(ListUser *users, Set *usernames);

#endif
