NAME    := getaway
BUILD   := build
EXEC    := $(BUILD)/$(NAME)
BIN_DIR := /usr/local/bin

all: build

build: $(NAME).c
	mkdir -p $(BUILD)
	gcc -Wall -Wextra -o $(EXEC) $<

test: build
	./$(EXEC)
	@echo ""
	./$(EXEC) -r
	@echo ""
	./$(EXEC) -r "January 1, 2014"
	@echo ""
	./$(EXEC) "December 25, 2014" 2
	@echo ""
	./$(EXEC) -r "December 25, 2014" 2
	@echo ""

memcheck:
	gcc -o $(EXEC) $(NAME).c -g -O0
	valgrind ./$(EXEC)

install: build
	install -m 0755 $(EXEC) $(BIN_DIR)

uninstall:
	rm -f $(BIN_DIR)/$(NAME)

clean:
	rm -rf $(BUILD)
