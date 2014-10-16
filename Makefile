CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := bin
TARGET := bin/ast2xml
SCRIPT := bin/all2xml.sh
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
LIB := -lstdc++
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean: clean-build clean-ast clean-xml

clean-build:
	@echo " Cleaning build..."; 
	@echo " $(RM) $(TARGET)"; $(RM) $(TARGET)

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
	@echo " $(RM) -r $(XMLS)"; $(RM) -r $(XMLS)

$(INPDIR)/%.$(XMLEXT): $(INPDIR)/%.$(ASTEXT)
	@echo "$(TARGET) $< >$@ ";  $(TARGET) $< >$@


.PHONY: clean