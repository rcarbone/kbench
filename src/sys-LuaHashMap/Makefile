# The name of the games
SRCS     = LuaHashMap.c
LIB      = lib-kbench-luahashmap.a
MAINSRCS = run-luahashmap.c

INCLUDE += `pkg-config --cflags lua-5.3`
SYSLIBS += `pkg-config --libs lua-5.3`

include ../../etc/Make.rules
