JAVAC := javac
JAVADOC := javadoc
JAVA := java

BIN := ./bin
SRC := ./src
DOC := ./doc
LIBS := ./libs
TESTS := ./src/tests
REPORT := ./reports

JUNIT := $(LIBS)/junit-4.12.jar:$(LIBS)/hamcrest-core-1.3.jar
MOCKITO := $(LIBS)/mockito-core-2.10.0.jar:$(LIBS)/byte-buddy-1.7.5.jar:$(LIBS)/byte-buddy-agent-1.7.5.jar:$(LIBS)/objenesis-2.6.jar
JACOCO_AGENT :=  $(LIBS)/jacocoagent.jar
JACOCO_CLI :=  $(LIBS)/jacococli.jar

RUN_ARGS := tests.testAccount tests.testATM tests.MyCardTest


all: appli javadoc tests runtests coverage report

appli:
	 $(JAVAC) -d $(BIN) $(SRC)/appli/fr/ufc/l3info/oprog/*.java

javadoc:
	$(JAVADOC) -d $(DOC) $(SRC)/appli/fr/ufc/l3info/oprog/*.java

tests:
	$(JAVAC) -cp $(BIN):$(JUNIT):$(MOCKITO) -d $(BIN) $(SRC)/tests/*.java

runtests:
	$(JAVA) -cp $(BIN):$(JUNIT):$(MOCKITO) org.junit.runner.JUnitCore $(RUN_ARGS)

coverage:
	$(JAVA) -javaagent:$(JACOCO_AGENT)=destfile=$(REPORT)/jacoco.exec -cp $(BIN):$(JUNIT):$(MOCKITO) org.junit.runner.JUnitCore $(RUN_ARGS)

report:
	$(JAVA) -jar $(JACOCO_CLI) report $(REPORT)/jacoco.exec --sourcefiles $(SRC)/appli/ --classfiles $(BIN) --html $(REPORT)/html
