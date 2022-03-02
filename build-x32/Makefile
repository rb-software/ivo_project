# Output target
TARGET_X32 = ivo_x32.exe

# Compiler
CXX=i686-w64-mingw32-g++

# Libraries
LIBS =	-L"../3pp/lib/lib-mingw"\
		-L"../3pp/lib/Release/Win32"\
		-lglfw3dll\
		-lopengl32\
		-lglu32\
		-lglew32\
		-lglew32s\

# Flags
CFLAGS = -g -Wall

# Others
OBJECTS =	$(patsubst ../%.cpp, ../%.o, $(wildcard ../src/*.cpp))
HEADERS	=	$(wildcard ../*.h)

CXXINCS	=	-I"../include"\
			-I"../3pp/include"\
			-I"../3pp/include/tinygltf-master"\

CXXFLAGS =	$(CXXINCS)\
			-D OPERATING_SYSTEM=2\
			-std=c++17

$(TARGET_X32): clean $(OBJECTS)
	@echo $^
	$(CXX)  --static  $(OBJECTS) $(LIBS)  -o $@ 
	@echo "-----------------------------"

########################################################
# Cleaning
clean_target:
	rm -f $(TARGET_X32)
clean: clean_target
	rm -f ../src/*.o
