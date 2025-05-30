#ifndef CHECKUP_H
#define CHECKUP_H

#include "User.h"
#include "../../ADT/header/Ruangan.h"
#include "../../ADT/header/List_User.h"

/**
 * @brief Validates that a float value is positive
 * @param nilai The value to validate
 * @param namaVar Name of the variable for error messages
 * @return true if valid, false otherwise
 */
boolean validasi_float (float nilai, const char* namaVar);

/**
 * @brief Validates that an integer value is positive
 * @param nilai The value to validate
 * @param namaVar Name of the variable for error messages
 * @return true if valid, false otherwise
 */
boolean validasi_integer (int nilai, const char* namaVar);

/**
 * @brief Displays available doctors and their queue status
 * @param users Array of all users
 * @param banyakUser Total number of users
 * @param ruangan Pointer to room list structure
 */
void display_dokter (User *users, int banyakUser, ListRuangan *ruangan);

/**
 * @brief Handles patient check-up registration process
 * @param currUser The patient user registering
 * @param users Array of all users
 * @param banyakUser Total number of users
 * @param ruangan Pointer to room list structure
 */
void daftar_check_up(User *currUser, User *users, int banyakUser, ListRuangan *ruangan);

#endif // CHECKUP_H