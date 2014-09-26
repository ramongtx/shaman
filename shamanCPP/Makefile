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

run: xml

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean-all: clean clean-ast clean-xml

clean:
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
ASTEXT := ast
XMLEXT := xml
INPUTS := $(shell find $(INPDIR) -type f -name *.$(INPEXT))
ASTS := $(patsubst $(INPDIR)/%,$(INPDIR)/%,$(INPUTS:.$(INPEXT)=.$(ASTEXT)))
XMLS := $(patsubst $(INPDIR)/%,$(INPDIR)/%,$(INPUTS:.$(INPEXT)=.$(XMLEXT)))
CLANG := clang
CLANGFLAGS = -cc1 -ast-dump

ast: $(ASTS)

clean-ast:
	@echo " Cleaning ASTS..."; 
	@echo " $(RM) -r $(ASTS)"; $(RM) -r $(ASTS)
	
$(INPDIR)/%.$(ASTEXT): $(INPDIR)/%.$(INPEXT)
	@echo " $(CLANG) $(CLANGFLAGS) $< | sed -n '/$(notdir $<)/,$$p' >$@ ";  $(CLANG) $(CLANGFLAGS) $< | sed -n '/$(notdir $<)/,$$p' >$@ 

xml: $(TARGET) $(XMLS)

clean-xml:
	@echo " Cleaning XMLS..."; 
	@echo " $(RM) -r $(XMLS)"; $(RM) -r $(XMLS)

$(INPDIR)/%.$(XMLEXT): $(INPDIR)/%.$(ASTEXT)
	@echo "$(TARGET) $< $@ ";  $(TARGET) $< $@


.PHONY: clean