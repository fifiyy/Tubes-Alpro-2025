#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdlib.h>
#include "User.h"

void display_main_menu();
void display_status_user(const char* username, UserRole *role);
#endif