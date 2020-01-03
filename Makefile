SHELL = /bin/sh

GCC_STRICT_FLAGS = -pedantic -ansi -W -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2
OTHER_SOURCE = -I./t
OTHER_INCLUDE =
CPPFLAGS = -g -I. $(OTHER_INCLUDE)
CFLAGS = $(GCC_STRICT_FLAGS) 
LDFLAGS =
LDFLAGS_EFENCE = -L/usr/lib -lefence $(LDFLAGS)
#VALGRIND_FLAGS = --verbose --leak-check=full --undef-value-errors=yes --track-origins=yes
VALGRIND_FLAGS = --leak-check=full --undef-value-errors=yes

INDENT_FLAGS = -TFILE -Tsize_t -Tuint8_t

.PHONY: check vcheck indent stamp clean

##TESTS = t/test01 t/test02 t/test03 t/test04 t/test
TESTS = t/test

strutils.o: strutils.c strutils.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ strutils.c

check: strutils.o
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c strutils.o $(LDFLAGS) ) \
	  && ( t/a.out ); \
	done 

vcheck: strutils.o
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c strutils.o $(LDFLAGS) ) \
	  && ( valgrind $(VALGRIND_FLAGS) t/a.out ); \
	done 

echeck: strutils.o
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c strutils.o $(LDFLAGS_EFENCE) ) \
	  && ( LD_PRELOAD=libefence.so ./t/a.out ); \
	done 

indent: stamp
	@indent $(INDENT_FLAGS) strutils.c
	@indent $(INDENT_FLAGS) strutils.h
	@for i in $(TESTS); \
	do \
	  indent $(INDENT_FLAGS) $$i.c; \
	done

stamp:
	@stamper.bash strutils.c
	@stamper.bash strutils.h

clean:
	@/bin/rm -f strutils.o *.o *~ *.BAK *.bak core.* a.out
	@/bin/rm -f t/*.o t/*~ t/*.BAK t/*.bak t/core.* t/a.out

