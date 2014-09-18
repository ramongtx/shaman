CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := bin
TARGET := bin/ast2xml
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
LIB := -lstdc++
INC := -I include

run: $(TARGET) ast
	@echo "\n---- ---- ----\n"
	$(TARGET)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean: clean-ast
	@echo " Cleaning build..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket


INPDIR := input
INPEXT := c
INPUTS := $(shell find $(INPDIR) -type f -name *.$(INPEXT))
ASTS := $(patsubst $(INPDIR)/%,$(INPDIR)/%,$(INPUTS:.$(INPEXT)=.ast))
CLANG := clang
CLANGFLAGS = -cc1 -ast-dump

ast: $(ASTS)

clean-ast:
	@echo " $(RM) -r $(ASTS)"; $(RM) -r $(ASTS)
	
$(INPDIR)/%.ast: $(INPDIR)/%.$(INPEXT)
	@echo " $(CLANG) $(CLANGFLAGS) $< | sed -n '/$(notdir $<)/,$$p' >$@ ";  $(CLANG) $(CLANGFLAGS) $< | sed -n '/$(notdir $<)/,$$p' >$@ 


.PHONY: clean