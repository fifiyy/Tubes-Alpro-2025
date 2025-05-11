#ifndef LUPA_PASSWORD_H
#define LUPA_PASSWORD_H

#include "../ADT/header/list_user.h"

void lupa_password_system(ListUser *users); 
void generate_kode_unik(const char* username, char* kode_unik);

#endif
