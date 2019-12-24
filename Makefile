.DEFAULT_GOAL := cs

TARGETS := \
		cs \
		tests

CC := clang
# The -std flag defaults to "gnu11" if not set. However, here 
# I'm just making it explicit. I grabbed this from 6.172 
# project3 in which it used to be "gnu89". Anyway, see the link
# below for more details.
# https://clang.llvm.org/docs/UsersManual.html
CFLAGS := -std=gnu11 -g -Wall
LDFLAGS := 

# put headers here
HEADERS := cs.h util.h closest_strings.h distances.h tests.h colors.h alphabet.h

# If you add a new file called "filename.c", add
# "filename.o \" to this list.
CS_OBJ := cs.o
OBJS := util.o closest_strings.o distances.o
TEST_OBJS := tests.o

ifeq ($(DEBUG),1)
	CFLAGS += -DDEBUG -O0
else
	CFLAGS += -DNDEBUG -O3
endif

# You shouldn't need to touch this.  This keeps track of whether or
# not you've changed CFLAGS.
OLD_CFLAGS := $(shell cat .cflags 2> /dev/null)
ifneq ($(CFLAGS),$(OLD_CFLAGS))
.cflags::
	@echo "$(CFLAGS)" > $@
endif

all: $(TARGETS)

cs: $(CS_OBJ) $(OBJS)
	$(CC) $(LDFLAGS) $(CS_OBJ) $(OBJS) -o $@

tests: $(OBJS) $(TEST_OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(TEST_OBJS) -o $@

# compile objects

# pattern rule for building objects
%.o: %.c .cflags
	$(CC) $(CFLAGS) -c $*.c -o $@

clean:
	$(RM) $(TARGETS) $(OBJS) $(TEST_OBJS) *.pyc
