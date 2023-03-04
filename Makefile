CFLAGS = -Wall -Wextra -Werror
CPPFLAGS =  -I src -MP -MMD
TESTFLAGS = -I thirdparty

APP_SOURCES = $(shell find src/nim -name '*.c')
APP_OBJECTS = $(APP_SOURCES:src/nim/%.c=obj/src/nim/%.o)

LIB_SOURCES = $(shell find src/libnim -name '*.c')
LIB_OBJECTS = $(LIB_SOURCES:src/libnim/%.c=obj/src/libnim/%.o)
LIB_PATH = obj/src/libnim/libnim.a
TEST_SOURCES = $(shell find test -name '*.c')
TEST_OBJECTS = $(TEST_SOURCES:test/%.c=obj/test/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

-include $(DEPS)

.PHONY: all
all: bin/nim_game

bin/nim_game: $(APP_OBJECTS) $(LIB_PATH)
	gcc $(CFLAGS) $(CPPFLAGS) $^ -o $@ -lncurses

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

obj/src/nim/%.o: src/nim/%.c
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

obj/src/libnim/%.o: src/libnim/%.c
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: test
test: bin/test

bin/test: $(TEST_OBJECTS) $(LIB_PATH)
	gcc $(CFLAGS) $(TESTFLAGS) $(CPPFLAGS) $^ -o $@ -lncurses

obj/%.o: %.c
	gcc -c $(CFLAGS) $(TESTFLAGS) $(CPPFLAGS) $< -o $@ -Wno-pragmas

.PHONY: clean
clean:
	rm -rf $(APP_OBJECTS) $(LIB_PATH) $(LIB_OBJECTS) bin/nim_game bin/test $(DEPS)