# Possible output target
TARGET_LINUX = ivo_linux
TARGET_X32 = ivo_x32.exe
TARGET_X64 = ivo_x64.exe

all:
	$(MAKE) -C ./build-linux
	$(MAKE) -C ./build-x32
	$(MAKE) -C ./build-x64
	$(MAKE) clean

	cp -f ./3pp/lib/lib-mingw/glfw3.dll /mnt/c/test/x32
	cp -f ./build-x32/$(TARGET_X32) /mnt/c/test/x32

	cp -f ./3pp/lib/lib-mingw-w64/glfw3.dll /mnt/c/test/x64
	cp -f ./build-x64/$(TARGET_X64) /mnt/c/test/x64

	cp -f ./build-linux/$(TARGET_LINUX) /mnt/c/test/linux

linux_build:
ifeq ($(MAKECMDGOALS),linux_build)
		@echo "-----------------------------"
		@echo "Linux build sub-system ..."
		$(MAKE) -C ./linux
		$(MAKE) clean
else
	@echo "Error - linux sub-build system ..."
endif

x32_build:
ifeq ($(MAKECMDGOALS),x32_build)
	@echo "-----------------------------"
	@echo "x32 build sub-system ..."
	$(MAKE) -C ./x32
	$(MAKE) clean
else
	@echo "Error - x32 build sub-system ..."
	exit
endif

x64_build:
ifeq ($(MAKECMDGOALS),x64_build)
	@echo "-----------------------------"
	@echo "x64 sub-build system ..."
	$(MAKE) -C ./x64
	$(MAKE) clean
else
	@echo "Error - x64 sub-build system ..."
endif
########################################################
# Cleaning
clean:
	rm -f ./src/*.o
clean_all:
	$(MAKE) clean -C ./build-linux
	$(MAKE) clean -C ./build-x32 
	$(MAKE) clean -C ./build-x64
