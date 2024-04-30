# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = g++
CC  = $(CXX)

# Generate dependencies in *.d files
DEPFLAGS = -MT $@ -MMD -MP -MF $*.d

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
# -g is for debugging.

CPPFLAGS  = -I../include
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast
CXXFLAGS += -std=c++17
CXXFLAGS += -g
CXXFLAGS += $(DEPFLAGS)
LDFLAGS   = -g -L../lib

#CPPFLAGS += -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

# Define variables
SOURCE_DIR := src
BUILD_DIR := bin

# Targets
PROGS = client ourserver
PROGS_SRC = $(addprefix $(SOURCE_DIR)/,$(PROGS))

all: $(PROGS_SRC)
	

# Targets rely on implicit rules for compiling and linking
# The dependency on libclientserver.a is not defined.

src/client: src/client.o src/messagehandler.o src/connection.o 
src/ourserver: src/ourserver.o src/connection.o src/diskdatabase.o src/inmemorydatabase.o src/newsgroup.o src/article.o src/server.o

SRC = $(wildcard $(SOURCE_DIR)/*.cc)

# Target rule to copy files to bin/
install:
	-cp $(PROGS_SRC) $(BUILD_DIR)/


# Phony targets
.PHONY: all clean distclean


# Standard clean
clean:
	-rm -f $(SRC:.cc=.o) $(PROGS_SRC)


distclean: clean
	-rm $(SRC:.cc=.d)
	-rm $(addprefix $(BUILD_DIR)/,$(PROGS))
#	-rm -r $(addsuffix .dSym,$(PROGS)) # for cleaning on Macs


# Include the *.d files
-include $(SRC:.cc=.d)
