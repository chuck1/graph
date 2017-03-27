root_dir     = /home/crymal/git/hvac/graph/tests/test_graph_0
src_dir      = /home/crymal/git/hvac/graph/tests/test_graph_0/src
inc_dir      = /home/crymal/git/hvac/graph/tests/test_graph_0/include
build_dir    = /home/crymal/git/hvac/graph/tests/test_graph_0/build
inc          = -I/home/crymal/git/hvac/graph/include -I/home/crymal/git/hvac/graph/build/static/process/include -I$(inc_dir)
define_str   = 
binary       = /home/crymal/git/esolv/build/test_graph_0
binary_prof  = /home/crymal/git/esolv/build/test_graph_0_prof
lib_long_str = /home/crymal/git/hvac/graph/build/static/libgraph.a
lib_link_str = -lgraph
lib_dir_str  = -L/home/crymal/git/hvac/graph/build/static
compiler_dir = /media/backedup/git/pbs/pbs/..

depends_dir = $(build_dir)/depends
objects_dir = $(build_dir)/objects
process_dir = $(build_dir)/process

include $(compiler_dir)/makefiles/color.mk


#src    = $(shell find $(src_dir) -name '*.cpp')
#src_in = $(shell find $(src_dir) -name '*.cpp.in')

#inc_in = $(shell find $(inc_dir) -name '*.hpp.in')

#inc_processed = $(patsubst $(src_dir)/%.cpp.in, $(build_dir)/processed/include/%.hpp, $(inc_in))

#src_processed = $(patsubst $(src_dir)/%.cpp.in, $(build_dir)/processed/src/%.cpp,     $(src_in))
#obj_processed = $(patsubst $(src_dir)/%.cpp.in, $(build_dir)/objects/%.cpp.o, $(src_in))
#obj           = $(patsubst $(src_dir)/%.cpp,    $(build_dir)/objects/%.cpp.o, $(src))


CC = g++-4.9
CFLAGS = -g -std=c++0x -Wno-format-security -rdynamic -pthread 

CARGS = $(define_str) $(CFLAGS) $(inc)

.PHONY: all

all: $(binary) $(binary_prof)
	@bash -c "echo -e \"$(COLOR_BLUE)$(build_dir)$(COLOR_RESET)\""


MAKEDEPEND = $(CC) -c $(CARGS) -MM $< -MF $(build_dir)/depends/$*.cpp.d -MT $(build_dir)/objects/$*.cpp.o

include $(compiler_dir)/makefiles/cpp_library.mk


$(binary): $(obj) $(lib_long_str)
	@bash -c "echo -e \"$(COLOR_BLUE)build $@$(COLOR_RESET)\""
	@$(CC) $(CARGS) $(obj) -o $@ $(lib_dir_str) $(lib_link_str) $(lib_link_str) -lpthread

$(binary_prof): $(obj) $(lib_long_str)
	@bash -c "echo -e \"$(COLOR_BLUE)build $@$(COLOR_RESET)\""
	@$(CC) $(CARGS) -pg $(obj) -o $@ $(lib_dir_str) $(lib_link_str) $(lib_link_str) -lpthread


include $(compiler_dir)/makefiles/clean.mk
include $(compiler_dir)/makefiles/help.mk
include $(compiler_dir)/makefiles/depend.mk
include $(compiler_dir)/makefiles/doc.mk

