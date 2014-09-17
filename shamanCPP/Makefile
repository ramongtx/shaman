CFLAGS = -g -Wall
CC = g++
TARGET = shaman
BINFOLDER = bin/
SRCFOLDER = src/
TGTSOURCE = $(SRCFOLDER)$(TARGET).cpp

run: all
	$(BINFOLDER)$(TARGET)

all: $(TARGET)

$(TARGET): $(TGTSOURCE)
	$(CC) $(CFLAGS) -o $(BINFOLDER)$(TARGET) $(TGTSOURCE)

clean:
	$(RM) -r $(BINFOLDER)*
