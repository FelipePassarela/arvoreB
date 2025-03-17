TARGET = arvoreB
CC = gcc
CFLAGS = -std=c11 -Iinclude -Wall -Wextra -g

SRCDIR = src
BUILDDIR = build
BINDIR = bin

SOURCES = $(SRCDIR)/main.c $(SRCDIR)/BTree.c $(SRCDIR)/BTreeNode.c
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

all: directories $(BINDIR)/$(TARGET)

directories:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BINDIR)

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: all
	./$(BINDIR)/$(TARGET) $(INPUT_FILE) $(OUTPUT_FILE)

clean:
	rm -f $(BUILDDIR)/*.o $(BINDIR)/$(TARGET)

.PHONY: all clean directories run