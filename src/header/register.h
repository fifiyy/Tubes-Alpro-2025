#ifndef REGISTER_H
#define REGISTER_H

#include <stdlib.h>
#include <stdio.h>
#include "../ADT/header/List_User.h"
#include "../ADT/header/Set.h"
#include "../ADT/header/Stack.h"

boolean is_username_unique(const Set *usernames, const char* username);
void register_pasien(ListUser *users, Set *usernames);

#endif
