# List of subdirectories
SUBDIRS  = run-it
SUBDIRS += amtl
SUBDIRS += apr
SUBDIRS += c-algoritms
SUBDIRS += ccan
SUBDIRS += CDS
SUBDIRS += cfu
SUBDIRS += c-hashtable
SUBDIRS += eastl
SUBDIRS += emilib
SUBDIRS += gcc-libiberty
SUBDIRS += generic-c-hashmap
SUBDIRS += ghthash
SUBDIRS += google-c
SUBDIRS += hashit
SUBDIRS += hhash
SUBDIRS += htable
# SUBDIRS += judyarray
# SUBDIRS += judy-template
SUBDIRS += khash
SUBDIRS += libevent
SUBDIRS += ltable
SUBDIRS += lua-table
SUBDIRS += mct
SUBDIRS += oddou-hashmap
SUBDIRS += python
SUBDIRS += rdestl
SUBDIRS += redis
SUBDIRS += rigtorp-hashmap
SUBDIRS += ruby-st
SUBDIRS += sglib
SUBDIRS += st
SUBDIRS += stb
SUBDIRS += tommyds
SUBDIRS += ulib
SUBDIRS += uthash

SUBDIRS += sys-apr
SUBDIRS += sys-boost
SUBDIRS += sys-gcc-stl
SUBDIRS += sys-glib
SUBDIRS += sys-judy
SUBDIRS += sys-LuaHashMap
SUBDIRS += sys-perl
SUBDIRS += sys-python
SUBDIRS += sys-Qt
# SUBDIRS += sys-ruby   # need to call rb_protect()
SUBDIRS += sys-sparsehash
SUBDIRS += sys-tcl

# Fake targets
.PHONY: all clean distclean ${SUBDIRS}

# The main target is responsible to recursively scan subdirectories and build all the programs
all:
	@for dir in ${SUBDIRS} ; do \
           if [ -d $$dir ] ; then \
             echo "Making $$dir ..." ; \
             (cd $$dir && make -s --no-print-directory) ; \
           else \
             echo "Warning: missing sub-directory $$dir" ; \
           fi \
         done

# Cleanup rules
clean distclean:
	@rm -f *~
	@for dir in ${SUBDIRS} ; do \
           if [ -d $$dir ] ; then \
             (cd $$dir && make -s --no-print-directory $@) ; \
           fi \
         done

tar:
	@(make -s distclean && cd .. && tar cvfz kbench.tar.gz kbench && mv kbench.tar.gz kbench/)

copy:
	@(make -s distclean && cd .. && tar chvfz kbench.tar.gz kbench && mv kbench.tar.gz kbench/)

# Run tests
DRIVER   = run-it/run-it
PROGRAMS = $(shell ls -1 */run-*)
TYPES    = i s
run:
	@for t in ${TYPES}; do \
           for p in ${PROGRAMS} ; do \
             if [ -x $$p ] ; then \
               echo "Running test $$p (-$$t). Please wait ..." ; \
               ${DRIVER} $$p -$$t ; \
             fi \
           done \
         done
