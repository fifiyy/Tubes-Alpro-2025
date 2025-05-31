#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdlib.h>
#include "User.h"

void display_main_menu();
//void display_title_only(); hanya untuk title
void display_menu_pasien();
void display_menu_dokter();
void display_menu_manajer();
void display_help();
void display_status_user(const char* username, UserRole *role);
#endif