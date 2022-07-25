common:
	@g++ main.C luamgr.C ../common/logout.C -o ../../bin/luavm -I../include/libevent -L../../bin -levent -lwsock32 -llua
	@del *.o
	@cd ../common/ && del *.o
#	@make -f makefile all

Exe=../../bin/luavm

Src_C=main.C \
	../common/logout.C

MY_FLAGS =  

include ../common/makefile.incl