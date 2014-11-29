CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := bin
TARGET1 := bin/ast2xml
TARGET2 := bin/shaman
TARGET := $(TARGET1) $(TARGET2)
SCRIPT := bin/shamanAll.sh
 
SRCEXT := cpp
SOURCES1 := $(SRCDIR)/pugixml.cpp $(SRCDIR)/shmtreenode.cpp  $(SRCDIR)/shmparser.cpp $(SRCDIR)/ast2xml.cpp
SOURCES2 := $(SRCDIR)/pugixml.cpp $(SRCDIR)/shmtreenode.cpp  $(SRCDIR)/shmindex.cpp $(SRCDIR)/shaman.cpp

OBJECTS1 := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES1:.$(SRCEXT)=.o))
OBJECTS2 := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES2:.$(SRCEXT)=.o))

CFLAGS := -g -Wno-c++11-extensions # -Wall
LIB := -lstdc++
INC := -I include

all: clean $(TARGET)

$(TARGET1): $(OBJECTS1)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET1) $(LIB)

$(TARGET2): $(OBJECTS2)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET2) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean: clean-build

clean-build:
	@echo " Cleaning build..."; 
	@echo " $(RM) $(TARGET) $(OBJECTS1) $(OBJECTS2)"; $(RM) $(TARGET) $(OBJECTS1) $(OBJECTS2)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

run:
	@chmod +x $(SCRIPT);
	$(SCRIPT)


.PHONY: clean