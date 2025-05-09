CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/main.c src/auth/login.c src/auth/register.c src/auth/logout.c src/auth/lupa_password.c src/help.c src/user_utils.c
OBJ = $(subst /,\,$(SRC:.c=.o))
TARGET = bin/program.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	@if not exist bin mkdir bin
	$(CC) $(CFLAGS) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@del /Q $(OBJ) 2>NUL
	@if exist bin rmdir /S /Q bin

.PHONY: all clean
