# The name of the games
C++MAINSRCS  = run-hash.cpp
C++MAINSRCS += run-map.cpp

C++FLAGS     = -std=c++11
C++FLAGS    += -Wno-sign-compare
C++FLAGS    += -fPIC
INCLUDE     += `pkg-config --cflags Qt5Core`
SYSLIBS     += `pkg-config --libs Qt5Core`
SYSLIBS     += -lstdc++

include ../../etc/Make.rules
