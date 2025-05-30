#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdlib.h>

void displayMainMenu();
//void displayTitleOnly(); hanya untuk title
void displayMenuPasien();
void displayMenuDokter();
void displayMenuManajer();
void displayHelp();
void displayStatusUser(const char* username, const char* role);

#endif
