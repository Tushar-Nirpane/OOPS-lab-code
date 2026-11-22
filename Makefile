# Object Oriented Programming Lab — build and test driver
# Usage: make | make test | make run PROG=a1_music | make sanitize | make clean

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O2
SANFLAGS := -std=c++17 -g -fsanitize=address,undefined -fno-omit-frame-pointer

SRC := $(sort $(wildcard *.cpp))
BIN := $(patsubst %.cpp,build/%,$(SRC))

.PHONY: all test run sanitize clean

all: $(BIN)

build:
	@mkdir -p build

build/%: %.cpp | build
	$(CXX) $(CXXFLAGS) -o $@ $<

# Feed each program its scripted input and report pass/fail.
test: all
	@pass=0; fail=0; \
	for b in $(BIN); do \
	    name=$$(basename $$b); \
	    if ./$$b < tests/$$name.in > /tmp/$$name.out 2>&1; then \
	        printf '  PASS  %s\n' $$name; pass=$$((pass+1)); \
	    else \
	        printf '  FAIL  %s\n' $$name; fail=$$((fail+1)); \
	    fi; \
	done; \
	printf '\n  %d passed, %d failed\n' $$pass $$fail; \
	[ $$fail -eq 0 ]

# Run one program interactively: make run PROG=a1_music
run: all
	@test -n "$(PROG)" || { echo "usage: make run PROG=a1_music"; exit 2; }
	@./build/$(PROG)

# Rebuild and run everything under AddressSanitizer + UndefinedBehaviorSanitizer.
sanitize:
	@mkdir -p build/san
	@fail=0; \
	for f in $(SRC); do \
	    name=$$(basename $$f .cpp); \
	    $(CXX) $(SANFLAGS) -o build/san/$$name $$f || exit 1; \
	done; \
	for f in $(SRC); do \
	    name=$$(basename $$f .cpp); \
	    if ASAN_OPTIONS=detect_leaks=0 ./build/san/$$name < tests/$$name.in > /dev/null 2>/tmp/san_$$name.err; then \
	        printf '  CLEAN %s\n' $$name; \
	    else \
	        printf '  ERROR %s\n' $$name; cat /tmp/san_$$name.err; fail=1; \
	    fi; \
	done; \
	exit $$fail

clean:
	rm -rf build
