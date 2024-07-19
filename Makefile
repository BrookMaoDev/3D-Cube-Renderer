# Compiler flags
CXXFLAGS := -Idependencies\include\SDL2

# Linker flags
LDFLAGS := -Ldependencies\lib -mwindows

# Libraries
LDLIBS := -lmingw32 -lSDL2main -lSDL2

# Source files
SRCS := Driver.cpp

# Default target
all: 3DRenderingEngine

# Link the object files to create the executable
3DRenderingEngine: $(SRCS)
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# Clean up build files
clean:
	rm -f 3DRenderingEngine

# Phony targets
.PHONY: all clean
