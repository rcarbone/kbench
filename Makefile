# List of subdirectories
SUBDIRS  = src

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
	@find . -name '*~' | xargs rm -f
	@for dir in ${SUBDIRS} ; do \
           if [ -d $$dir ] ; then \
             (cd $$dir && make -s --no-print-directory $@) ; \
           fi \
         done

distrib:
	@(make -s distclean && cd .. && tar chvfz kbench.tar.gz kbench && mv kbench.tar.gz kbench/)

# Run tests
DRIVER   = src/run-it/run-it
PROGRAMS = $(shell ls -1 src/*/run-*)
TYPES    = i s
DATASETS = 1 2
run:
	@for d in ${DATASETS}; do \
           for t in ${TYPES}; do \
             for p in ${PROGRAMS} ; do \
               if [ -x $$p -a "$$p" != "${DRIVER}" ] ; then \
                 echo "Running test $$p (-$$t) (-$$d). Please wait ..." ; \
                 ${DRIVER} $$p -$$t -$$d ; \
               fi \
             done \
           done \
         done

runs:
	@for p in ${PROGRAMS} ; do \
           if [ -x $$p -a "$$p" != "${DRIVER}" ] ; then \
             echo "Running test $$p (-s) (-1). Please wait ..." ; \
             ${DRIVER} $$p -s -1 ; \
           fi \
         done
