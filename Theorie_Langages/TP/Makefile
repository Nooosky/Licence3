CC := gcc -std=c11 -O2
CFLAGS := -pedantic -Wall -Wextra -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow -Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Wlogical-op -Winline

DIRECSRC := ./src
DIRECBIN := ./bin

EXENAME := app
OBJ := $(DIRECSRC)/fa.o $(DIRECSRC)/testfa.o


all: $(EXENAME) install execute

$(EXENAME): $(OBJ)
	@echo "** Building"
	$(CC) $(CFLAGS) -o $(DIRECSRC)/$@ $^

$(DIRECSRC)/%.o: $(DIRECSRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

install:
	@echo "** Installing..."
	cp $(DIRECSRC)/$(EXENAME) $(DIRECBIN)
	cp $(OBJ) $(DIRECBIN)
	chmod u+x $(DIRECBIN)/$(EXENAME)

clean:
	@echo "** Removing object files and executable..."
	rm -f $(OBJ)
	rm -f $(EXENAME)

execute:
	@echo "** start .."
	$(DIRECBIN)/$(EXENAME)
