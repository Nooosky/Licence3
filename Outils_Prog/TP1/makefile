JAVAC := javac
JAVADOC := javadoc
JAVA := java

BIN := ./bin
SRC := ./src
DOC := ./doc
LIBS := ./libs
TESTS := ./src/tests
REPORT := ./reports
JACOCO_AGENT := jacocoagent.jar
JACOCO_CLI := jacococli.jar

JUNIT := $(LIBS)/junit-4.12.jar:$(LIBS)/hamcrest-core-1.3.jar
RUN_ARGS := testAccount testATM testCard


all: appli javadoc tests runtests coverage report

appli:
	 $(JAVAC) -d $(BIN) $(SRC)/*.java 

javadoc:
	$(JAVADOC) -d $(DOC) $(SRC)/*.java 

tests: 
	$(JAVAC) -cp $(BIN):$(JUNIT) -d $(BIN) $(SRC)/tests/*.java
	
runtests:
	$(JAVA) -cp $(BIN):$(JUNIT):$(TESTS) org.junit.runner.JUnitCore $(RUN_ARGS) 

coverage:
	$(JAVA) -javaagent:$(JACOCO_AGENT)=destfile=$(REPORT)/jacoco.exec -cp $(BIN):$(JUNIT):$(MOCKITO) org.junit.runner.JUnitCore $(RUN_ARGS) 

report:
	$(JAVA) -jar $(JACOCO_CLI) report $(REPORT)/jacoco.exec --sourcefiles $(SRC)/appli/ --classfiles $(BIN) --html $(REPORT)/html 