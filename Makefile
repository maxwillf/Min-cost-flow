# Default Conventions
Target = min-cost-flow 	# Name of the project
INCLUDES = include
HEADERS = $(wildcard $(INCLUDES)/*)
CXX = g++
CXXFLAGS = -std=c++11 -g -ggdb -I $(INCLUDES)
DOCS = html latex
RM = -rm

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Some locations
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


all: project #docs

project: $(OBJECTS) $(HEADERS) | $(BINDIR)
	$(CXX) $(OBJECTS) $(CXXFLAGS) -o $(BINDIR)/$(Target)
	@echo "link created: "
	@ln -sfv $(BINDIR)/$(Target) $(Target)

docs: 
	@doxygen Doxyfile
	
$(OBJECTS):	$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# PHONY targets
.PHONY: clean clean_txt clean_docs clean_proj

clean: clean_proj #clean_txt clean_docs

clean_proj:
	$(RM) -r $(OBJDIR)
	$(RM) -r $(BINDIR)
	$(RM) $(Target)	

clean_txt: $(TEXT)
	$(RM) -f $(TEXT)	

clean_docs: $(DOCS)
	$(RM) -rf $(DOCS)
