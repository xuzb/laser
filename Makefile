CXX := g++
RTTIFLAG := -fno-rtti
LLVM_BIN_DIR := $(HOME)/llvm-build/Debug+Asserts/bin
CXXFLAGS := $(shell $(LLVM_BIN_DIR)/llvm-config --cxxflags) $(RTTIFLAG)
LLVMLDFLAGS := $(shell $(LLVM_BIN_DIR)/llvm-config --libs) $(shell $(LLVM_BIN_DIR)/llvm-config --ldflags)

SOURCES = Laser.cpp FunctionSimulator.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = laser

all: $(EXE)
$(EXE): $(OBJECTS) $(SOURCES)
	$(CXX) -o $(EXE) $(OBJECTS) -L../ModuleLoader/src/ -lModuleLoader $(LLVMLDFLAGS)
%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

clean:
	rm -f *.o *.so laser
