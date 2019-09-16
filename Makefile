# Object files to create for the executable
OBJS = obj/matrix.o obj/main.o

# Warnings to be raised by the C compiler
WARNS = -Wall

# Names of tools to use when building
CXX = g++ -g
EXE = matrix

# Compiler flags. Compile ANSI build only if CHARSET=ANSI.
ifeq (${CHARSET}, ANSI)
  CXXFLAGS = -O2 ${WARNS} -Iinclude
else
  CXXFLAGS = -O2 -D _UNICODE ${WARNS} -Iinclude
endif


ifeq ($(OS),Windows_NT)
	DEL_BIN = if exist bin\* del /q bin\* 
	DEL_OBJ = if exist obj\* del /q obj\*
else
   	DEL_BIN = rm -f bin/*;
	DEL_OBJ = rm -f obj/*;
endif

# Linker flags
LDFLAGS = -W

.PHONY: all clean

# Build executable by default
all: executable

# strip symbols for release
release: LDFLAGS += -s
release: executable

executable: bin/${EXE}

# Delete all build output
clean:
	${DEL_BIN}
	${DEL_OBJ}

# Create build output directories if they don't exist
bin obj:
	@if not exist "$@" mkdir "$@"

# Compile object files for executable
obj/%.o: src/%.cpp | obj
	${CXX} ${CXXFLAGS} -c "$<" -o "$@"

# Build the exectuable
bin/${EXE}: ${OBJS} | bin
	${CXX} -o "$@" ${OBJS} ${LDFLAGS}

# C header dependencies
obj/matrix.o: 	include/matrix.h
obj/main.o:  	include/main.h