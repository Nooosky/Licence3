JAVAC := javac
JAVADOC := javadoc
JAVA := java

BIN := ./bin
SRC := ./src
DOC := ./doc
LIBS := ./libs
TESTS := ./src/tests

JUNIT := $(LIBS)/junit-4.12.jar:$(LIBS)/hamcrest-core-1.3.jar
RUN_ARGS := testAccount testATM testCard


all: appli javadoc tests runtests

appli:
	 $(JAVAC) -d $(BIN) $(SRC)/*.java 

javadoc:
	$(JAVADOC) -d $(DOC) $(SRC)/*.java 

tests: 
	$(JAVAC) -cp $(BIN):$(JUNIT) -d $(BIN) $(SRC)/tests/*.java
	
runtests:
	$(JAVA) -cp $(BIN):$(JUNIT):$(TESTS) org.junit.runner.JUnitCore $(RUN_ARGS) 

coverage:

report: