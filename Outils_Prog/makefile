EXENAME := app

CC := g++ -std=c++14 #-O2
CFLAGS := -Wall

SRC := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJ := $(SRC:.cpp=.o)

all: $(EXENAME) install

$(EXENAME): $(OBJ)
	@echo "** Building the game"
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo "** Removing object files and executable..."
	rm -f $(OBJ)
	rm -f $(EXENAME)

execute:
	@echo "** start the game.."
	./$(EXENAME)
