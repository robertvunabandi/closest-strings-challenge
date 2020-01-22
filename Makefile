# Copyright (c) 2020 Robert M. Vunabandi
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

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
HEADERS := \
		alphabet.h \
		closest_strings.h \
		colors.h \
		cs.h \
		distances.h \
		tests.h \
		util.h
TEST_HEADERS := $(shell ls | grep "_tests.h" 2> /dev/null)
HEADERS += $(TEST_HEADERS)

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
%.o: %.c .cflags $(HEADERS)
	$(CC) $(CFLAGS) -c $*.c -o $@

clean:
	$(RM) $(TARGETS) $(OBJS) $(TEST_OBJS) 
	$(RM) py/__pycache__/*.pyc
	$(RM) -d py/__pycache__

BENCHMARK_VERBOSE := 
ifeq ($(VERBOSE), 1)
	BENCHMARK_VERBOSE += -v
endif

benchmark-simple:
	make clean
	make
	./benchmark.py -mt 60 -r 15 -s SIMPLE -nw 3 $(BENCHMARK_VERBOSE)

benchmark-vary:
	make clean
	make
	./benchmark.py -mt 60 -r 15 -s VARY -nw 3 $(BENCHMARK_VERBOSE)

benchmark-random:
	make clean
	make
	./benchmark.py -mt 60 -r 15 -s RANDOM -nw 3 $(BENCHMARK_VERBOSE)
