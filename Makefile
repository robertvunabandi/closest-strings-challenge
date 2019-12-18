TARGETS := \
		cs

CC := clang
# The -std flag defaults to "gnu11" if not set. However, here 
# I'm just making it explicit. I grabbed this from 6.172 
# project3 in which it used to be "gnu89". Anyway, see the link
# below for more details.
# https://clang.llvm.org/docs/UsersManual.html
CFLAGS := -std=gnu11 -g -Wall
LDFLAGS := 

# put headers here
HEADERS := cs.h util.h closest_strings.h distances.h

# If you add a new file called "filename.c", add
# "filename.o \" to this list.
OBJS := cs.o util.o closest_strings.o distances.o

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

cs: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# compile objects

# pattern rule for building objects
%.o: %.c .cflags
	$(CC) $(CFLAGS) -c $*.c -o $@

clean:
	$(RM) $(TARGETS) $(OBJS) *.pyc