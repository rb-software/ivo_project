# Output target
TARGET_X64 = ivo_x64.exe

# Compiler
CXX=x86_64-w64-mingw32-g++

# Libraries
LIBS =	-L"../3pp/lib/lib-mingw-w64"\
		-L"../3pp/lib/Release/x64"\
		-lglfw3dll\
		-lopengl32\
		-lglu32\
		-lglew32\
		-lglew32s\

# Flags
CFLAGS = -g -Wall

# Others
OBJECTS =	$(patsubst ../%.cpp, ../%.o, $(wildcard ../src/*.cpp))
HEADERS =	$(wildcard ../*.h)

CXXINCS	=	-I"../include"\
			-I"../3pp/include"\
			-I"../3pp/include/tinygltf-master"\

CXXFLAGS =	$(CXXINCS)\
			-D OPERATING_SYSTEM=3\
			-std=c++17

$(TARGET_X64): clean $(OBJECTS)

	$(CXX) --static $(OBJECTS) -Wall $(LIBS) -o $@
	@echo "-----------------------------"

########################################################
# Cleaning
clean_target:
	rm -f $(TARGET_X64)
clean: clean_target
	rm -f ../src/*.o
