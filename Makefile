# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I"src/header" -I"src/ADT/header"

# Source files
SRCDIR = src/c
ADTDIR = src/ADT/c
SRC = $(wildcard $(SRCDIR)/*.c) $(wildcard $(ADTDIR)/*.c) 

# Output executable
OUTDIR = bin
OUT = $(OUTDIR)/program.exe

# Default target
all: $(OUT)

# Rule to build the executable
$(OUT): $(SRC)
	@mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) $^ -o $@

# Clean target to remove compiled files
clean:
	rm -rf $(OUTDIR)