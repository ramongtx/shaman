CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := bin
TARGET1 := bin/ast2xml
TARGET2 := bin/xml2index
TARGET := $(TARGET1) $(TARGET2)
SCRIPT := bin/all2xml.sh
 
SRCEXT := cpp
SOURCES1 := $(SRCDIR)/pugixml.cpp $(SRCDIR)/shmtreenode.cpp  $(SRCDIR)/shmparser.cpp $(SRCDIR)/ast2xml.cpp
SOURCES2 := $(SRCDIR)/pugixml.cpp $(SRCDIR)/shmtreenode.cpp  $(SRCDIR)/shmindex.cpp $(SRCDIR)/xml2index.cpp

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

clean: clean-build clean-ast clean-xml

clean-build:
	@echo " Cleaning build..."; 
	@echo " $(RM) $(TARGET) $(OBJECTS1) $(OBJECTS2)"; $(RM) $(TARGET) $(OBJECTS1) $(OBJECTS2)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

run: clean-xml xml
	@chmod +x $(SCRIPT);
	$(SCRIPT)

INPDIR := input
INPEXT := c
ASTEXT := $(INPEXT).ast
XMLEXT := $(INPEXT).xml
INPUTS := $(shell find $(INPDIR) -type f -name *.$(INPEXT))
ASTS := $(shell find $(INPDIR) -type f -name *.$(ASTEXT))
XMLS := $(shell find $(INPDIR) -type f -name *.$(XMLEXT))
CLANG := clang
CLANGFLAGS = -cc1 -ast-dump

ast: $(ASTS)

clean-ast:
	@echo " Cleaning ASTS..."; 
	@echo " $(RM) -r $(ASTS)"; $(RM) -r $(ASTS)
	
$(INPDIR)/%.$(ASTEXT): $(INPDIR)/%.$(INPEXT)
	@echo " $(CLANG) $(CLANGFLAGS) $< | sed -n '/$(notdir $<)/,$$p' >$@ ";  $(CLANG) $(CLANGFLAGS) $< | sed -n '/$(notdir $<)/,$$p' >$@ 

xml: $(TARGET) $(XMLS)

print-xml: xml
	$(foreach file,$(XMLS),echo "\n\n\n=== $(file) ======\n"; cat $(file);)

clean-xml:
	@echo " Cleaning XMLS..."; 
	@echo " $(RM) -r $(XMLS) *.$(XMLEXT)"; $(RM) -r $(XMLS) *.$(XMLEXT)

$(INPDIR)/%.$(XMLEXT): $(INPDIR)/%.$(ASTEXT)
	@echo "$(TARGET) $< >$@ ";  $(TARGET) $< >$@


.PHONY: clean