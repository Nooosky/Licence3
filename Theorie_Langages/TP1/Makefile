CC := gcc -std=c11 -O2
CFLAGS := -Wall

DIRECSRC := ./src
DIRECBIN := ./bin
DIRECOBJ := ./obj

EXENAME := app
OBJ := $(DIRECSRC)/fa.o $(DIRECSRC)/testfa.o


all: $(EXENAME) install

$(EXENAME): $(OBJ)
	@echo "** Building"
	$(CC) -o $(DIRECSRC)/$@ $^

$(DIRECSRC)/%.o: $(DIRECSRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

install:
	@echo "** Installing..."
	cp $(DIRECSRC)/$(EXENAME) $(DIRECBIN)
	cp $(DIRECSRC)/$(OBJ) $(DIRECOBJ)
	chmod u+x $(DIRECBIN)/$(EXENAME)

clean:
	@echo "** Removing object files and executable..."
	rm -f $(OBJ)
	rm -f $(EXENAME)

execute:
	@echo "** start .."
	./$(DIRECBIN)/$(EXENAME)
