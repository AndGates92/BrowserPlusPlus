# Makefile for machine learning C implementation

DATE_FORMAT = %a %d %b %Y
TIME_FORMAT = %H:%M:%S

# Makefile variables
VERBOSE =
VERBOSE_ECHO = @

MKDIR = mkdir -p

# Project name
PROJ_NAME ?= browser

# Executable filename
EXE_NAME ?= $(PROJ_NAME)

# Dependency directory
DEP_DIR ?= dep

# Dependency filename
DEPFILENAME ?= Makefile.deps

# Dependency file
DEPFILE=$(DEP_DIR)/$(DEPFILENAME)

# Log directory
LOG_DIR ?= log

# Log filename
LOGFILENAME ?= $(EXE_NAME).log

# Log file
LOGFILE=$(LOG_DIR)/$(LOGFILENAME)

VERBOSITY ?= 1

# Program Language
PROG_LANG ?= C++

# File extensions
ifeq ($(PROG_LANG), C++)
  SRC_EXT = cpp
  # - g++ for C++ files
  CC = g++
else ifeq ($(PROG_LANG), C)
  SRC_EXT = c
  # - gcc for C files
  CC = gcc
endif

OBJ_EXT = o
HEADER_EXT = h

# Compile-time flags
# Upgrade all warnings to errors
# PIC (Position Independent Code) is required by Qt
# C++14 standard
# -rdyanmic: ELF linked adds all symbols to the dynamic symbol table
CFLAGS = -g -Wall -fPIC -Werror -Wextra -Wpedantic -std=c++14 -rdynamic
CEXTRAFLAGS ?=
BEHFLAGS ?=
DEPENDFLAG = -MM

# Defines
LOG_DEFINES = LOGFILE="$(LOGFILE)" VERBOSITY=$(VERBOSITY)
DEFINE_LIST = $(LOG_DEFINES)
DFLAGS := $(foreach DEF, ${DEFINE_LIST}, -D${DEF})

# Libraries
MATHLIBS= m
GLUTLIBS = GLU GL glut
QTLIBS = Qt5Widgets Qt5Gui Qt5Core
X11LIBS = X11
LIB_LIST = $(MATHLIBS) \
           $(GLUTLIBS) \
           $(QTLIBS)   \
           $(X11LIBS)
LIBS := $(foreach LIB, ${LIB_LIST}, -l${LIB})

# Directory containing source and header files
TOP_DIR = top
TEST_DIR = test
LIB_DIR = .

# Directory containing source files
SRC_DIR = src

# Directory containing include files
INCLUDE_DIR = include

# Directory containing object files
OBJ_DIR = obj

# Directory containing binary files
BIN_DIR ?= bin

# Doxygen variables
DOXYGEN = doxygen
DOX_DIR = doxygen
DOX_CFG_FILENAME = ${PROJ_NAME}.config

DOX_CFG_FILE = $(DOX_DIR)/$(DOX_CFG_FILENAME)

DOX_DOC_DIR = doc

# Valgrind variables
VALGRIND=valgrind

MEMCHECKOPTS = --leak-check=full --error-limit=no --show-leak-kinds=all --track-origins=yes
VALGRINDTOOLOPTS =
VALGRINDLOGFILENAME ?= valgrind.log
VALGRINDLOGFILE = $(LOG_DIR)/$(VALGRINDLOGFILENAME)
VALGRINDLOGOPTS = -v --log-file=$(VALGRINDLOGFILE) --time-stamp=yes
VALGRINDEXEARGS ?=

DIR_LIST = $(LIB_DIR) \
           $(TOP_DIR) \
           $(TEST_DIR)

INCLUDE_PATH := $(foreach DIR, ${DIR_LIST}, $(DIR)/$(INCLUDE_DIR))
INCLUDE_HEADERS := $(foreach INCHEADER, ${INCLUDE_PATH}, -I${INCHEADER})

ifneq ($(wildcard /usr/include/x86_64-linux-gnu/qt5),)
  INCLUDE_QT_LIBS = /usr/include/x86_64-linux-gnu/qt5
else
  $(error Qt libraries not found)
endif
INCLUDE_PATH_LIBS = $(INCLUDE_QT_LIBS)

ifneq ($(INCLUDE_PATH_LIBS),)
  INCLUDE_LIBS := $(foreach INCLIB, ${INCLUDE_PATH_LIBS}, -isystem${INCLIB})
endif

INCLUDES = $(INCLUDE_HEADERS) \
           $(INCLUDE_LIBS)

SRCS := $(notdir $(wildcard $(foreach DIR, ${DIR_LIST}, $(DIR)/$(SRC_DIR)/*.$(SRC_EXT))))
OBJS = $(patsubst %.$(SRC_EXT),$(OBJ_DIR)/%.$(OBJ_EXT),$(notdir $(SRCS)))

SRC_PATH = $(LIB_DIR)/$(SRC_DIR)  \
           $(TOP_DIR)/$(SRC_DIR)  \
           $(TEST_DIR)/$(SRC_DIR)

MAIN = main.$(SRC_EXT)
TOP = $(TOP_DIR)/$(SRC_DIR)/$(MAIN)
EXE = $(BIN_DIR)/$(EXE_NAME)

#-include $(DEPFILE)

$(EXE) : $(OBJS)
	$(MKDIR) $(LOG_DIR)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Compiling $(@F). Object files are: $^"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) $^ $(LIBS)

$(OBJ_DIR)/%.$(OBJ_EXT) : %.$(SRC_EXT)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Compiling $(<F) and creating object $@"
	$(CC) $(CFLAGS) $(INCLUDES)  -c $< $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) -o $@ $(LIBS)

$(DEPFILE) : $(SRCS)
	rm -rf $(DEP_DIR)
	$(CC) $(CFLAGS) $(DEPENDFLAG) $(INCLUDES) $^ > $(DEPFILE)

all : $(EXE)
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Compile $(PROJ_NAME)"

depend : $(DEPFILE)
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Create dependencies for $(PROJ_NAME)"

memleak : $(EXE)
	valgrind $(MEMCHECKOPTS) $(VALGRINDTOOLOPTS) $(VALGRINDLOGOPTS) $(EXE) $(VALGRINDEXEARGS)

debug :
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Language: $(PROG_LANG)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Compiler: $(CC)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Compiler options:"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> $(PROG_LANG) flags: $(CFLAGS)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> $(PROG_LANG) extra flags: $(CEXTRAFLAGS)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Behaviour flags: $(BEHFLAGS)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> logging defines: $(LOG_DEFINES)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Math libs: $(MATHLIBS)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> OpenGL GLUT libraries: $(GLUTLIBS)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> X11 libraries: $(X11LIBS)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Qt libraries: $(QTLIBS)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Files lists:"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Source files: $(SRCS)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Object files: $(notdir $(OBJS))"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Executable file: $(notdir $(EXE_NAME))"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Directories lists:"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Source directories: $(SRC_PATH)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Include directories: $(INCLUDE_PATH)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Include Qt library path: $(INCLUDE_QT_LIBS)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Exeutable directory: $(BIN_DIR)"
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Log directory: $(LOG_DIR)"

clean_byprod :
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Remove object files: $(OBJS)"
	rm -rf $(OBJ_DIR)
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Remove dependencies directory: $(DEP_DIR)"
	rm -rf $(DEP_DIR)
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Remove doxygen documentation directory: $(DOX_DOC_DIR)"
	rm -rf $(DOX_DOC_DIR)
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Clean by-product completed"

clean_prog :
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Remove binary directory: $(BIN_DIR)"
	rm -rf $(BIN_DIR)
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Remove log directory: $(LOG_DIR)"
	rm -rf $(LOG_DIR)
	$(VERBOSE_ECHO)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Clean program completed"

clean :
	make clean_prog
	make clean_byprod

doc :
	$(MKDIR) $(DOX_DOC_DIR)
	$(DOXYGEN) $(DOX_CFG_FILE)

.PHONY: all,clean,depend,$(EXE),debug,doc,memleak
