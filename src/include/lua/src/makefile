SHELL = cmd.exe

Exe = ../../../../lib/lua.dll

SRC_CORE = \
	lapi.c lauxlib.c lcode.c lctype.c ldebug.c ldo.c ldump.c \
	lfunc.c lgc.c llex.c lmem.c lobject.c lopcodes.c lparser.c \
	lstate.c lstring.c ltable.c ltm.c lundump.c lvm.c lzio.c \
	lbaselib.c lbitlib.c lcorolib.c ldblib.c liolib.c lmathlib.c \
	loslib.c lstrlib.c ltablib.c lutf8lib.c loadlib.c linit.c

Src_c = $(SRC_CORE)

OBJS = $(Src_c:.c=.o)

common: $(OBJS)
	@echo "compiling Lua ...."
	@gcc -DLUA_BUILD_AS_DLL $(OBJS) -o $(Exe)
	@echo "compiling succ ..."
	@del *.o

clean:
	@del *.o