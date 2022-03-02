# Output target
TARGET_LINUX = ivo_linux

# Compiler
CXX=g++

# Libraries
LIBS =	-lglfw\
		-lGL\
		-lGLU\
		-lGLEW\
		-lm\

# Flags
CFLAGS = -g -Wall

# Others
OBJECTS = $(patsubst ../%.cpp, ../%.o, $(wildcard ../src/*.cpp))
HEADERS = $(wildcard ../*.h)

CXXINCS	=	-I"../include"\
			-I"../3pp/include"\
			-I"../3pp/include/tinygltf-master"\

CXXFLAGS =	$(CXXINCS)\
			-D OPERATING_SYSTEM=1\
			-std=c++17

$(TARGET_LINUX): clean $(OBJECTS)
	$(CXX) $(OBJECTS) -Wall $(LIBS) -o $@
	@echo "-----------------------------"

########################################################
# Cleaning
clean_target:
	rm -f $(TARGET_LINUX)
clean: clean_target
	rm -f ../src/*.o
