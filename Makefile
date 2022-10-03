# This is the Makefile to use for Homework Assignment #5
# To use, at the prompt, type:
#
#       make Calc               # This will make executable calc
# or
#       make Driver             # This will make executable driver
# or
#       make clean              # This will safely remove old stuff

DIR=$(HOME)/../public/hw7

all:	Driver1 Calc1 Driver2 Calc2

Calc1:	Calc.o Decin.o Tree.o Main.o Namein.o List.o Stack.o
	g++ -Wall -pedantic -o Calc1 -g Calc.o Decin.o \
		Tree.o List.o Main.o Namein.o Stack.o

Calc.o:	Base.h Calc.c Calc.h Decin.h Tree.h List.h Stack.h SymTab.h
	g++ -Wall -pedantic -g -c Calc.c

Calc2:	Calculator.class Main.class

Calculator.class:	Base.java Calculator.java MyLib.java Stack.java \
		SymTab.java
	javac -g Calculator.java
	echo 'java Main $$*' > Calc2
	chmod ug+rx Calc2

Driver1:	Driver.o Tree.o
	g++ -Wall -pedantic -o Driver1 -g Driver.o Tree.o

Driver.o:	Base.h Driver.c Tree.h
	g++ -Wall -pedantic -g -c Driver.c

Driver2:	Driver.class

Driver.class:	Base.java Driver.java MyLib.java SymTab.java Tree.java
	javac -g Driver.java
	echo 'java Driver $$*' > Driver2
	chmod ug+rx Driver2

Decin.o:	Decin.c Decin.h
	g++ -Wall -pedantic -g -c Decin.c

Tree.o:	Base.h Tree.c Tree.h SymTab.h
	g++ -Wall -pedantic -g -c Tree.c

List.o:	Base.h List.c List.h
	g++ -Wall -pedantic -g -c List.c

Main.class:	Calculator.java Main.java
	javac -g Main.java

Main.o:	Base.h Main.c Calc.h Tree.h List.h Stack.h SymTab.h
	g++ -Wall -pedantic -g -c Main.c

Namein.o:	Namein.h Namein.c
	g++ -Wall -pedantic -g -c Namein.c

Stack.o:	Base.h List.h Stack.c Stack.h
	g++ -Wall -pedantic -g -c Stack.c

SymTab.class:	Base.java SymTab.java Tree.java
	javac -g SymTab.java

valgrind_Driver: Driver1
	valgrind \
	--leak-check=full \
	--read-var-info=yes \
	--show-reachable=yes \
	./Driver1 $(DEBUG)

valgrind_Calc: Calc1
	valgrind --leak-check=full --read-var-info=yes \
	    --show-reachable=yes ./Calc1 $(DEBUG)

clean:
	rm -f *.o *.class Driver1 Driver2 Calc1 Calc2 core

new:
	make clean
	make

backup:	Makefile *.[ch] *.java
	cp Makefile *.[ch] *.java $(HOME)/hw7/backup

directories:
	mkdir $(HOME)/hw7
	mkdir $(HOME)/hw7/backup

install:
	cp $(DIR)/Makefile \
	$(DIR)/*.h \
	$(DIR)/Main.c \
	$(DIR)/Decin.c \
	$(DIR)/Stack.c \
	$(DIR)/Calc.c \
	$(DIR)/Namein.c \
	$(DIR)/Tree.c.empty \
	$(DIR)/List.c \
	$(DIR)/Driver.c.empty \
	$(DIR)/MyLib.java \
	$(DIR)/Base.java \
	$(DIR)/List.java \
	$(DIR)/Stack.java \
	$(DIR)/SymTab.java \
	$(DIR)/Driver.java.empty \
	$(DIR)/Tree.java.empty \
	$(DIR)/Main.java \
	$(DIR)/Calculator.java \
	$(HOME)/hw7

public:
	make new
	
	# remove .o files to prepare for java executable creation
	rm -f *.o

	# produce java executables
	#gcj -c *.java
	#gcj -o Driver2 --main=Driver Base.o Driver.o List.o MyLib.o \
	#	Stack.o SymTab.o Tree.o
	#gcj -o Calc2 --main=Main Base.o Calculator.o Tree.o List.o \
	#	Main.o MyLib.o Stack.o SymTab.o
	
	# done with .o files
	rm -f *.o

	# lock public directory
	chmod 700 $(DIR)

	# copy all files to directory
	cp -p Makefile Calc1 Driver1 *.h *.c *empty* *.java alphabet $(DIR)

	# copy html files into public_html/hw7/
	cp -p *html $(HOME)/public_html/hw7/
	 
	# strip executables of debugging information
	strip $(DIR)/Calc1 $(DIR)/Driver1 

	# remove solution files from public directory
	rm $(DIR)/Driver.c $(DIR)/Tree.c $(DIR)/Tree.java $(DIR)/Driver.java

	# give all permissions to other users, take away some permissions later
	chmod go-rwx $(DIR)/*

	# set correct permissions on executables
	chmod go+x $(DIR)/Calc1 $(DIR)/Driver1

	# set correct permissions on source files
	chmod go+r $(DIR)/*.h $(DIR)/Stack.c $(DIR)/Main.c \
		$(DIR)/Makefile \
		$(DIR)/Tree.c.empty \
		$(DIR)/Driver.c.empty \
		$(DIR)/alphabet \
		$(DIR)/Namein.c \
		$(DIR)/Tree.java.empty \
		$(DIR)/Driver.java.empty \
		$(DIR)/List.java \
		$(DIR)/Stack.java \
		$(DIR)/Base.java \
		$(DIR)/SymTab.java \
		$(DIR)/Main.java \
		$(DIR)/Calculator.java \
		$(DIR)/MyLib.java
	chmod go+r $(DIR)/Calc.c
	chmod go+r $(DIR)/Decin.c
	chmod go+r $(DIR)/List.c

        # move html files to public_html directory
	rm -r $(HOME)/public_html/hw7/
	mkdir $(HOME)/public_html/hw7
	cp *html $(HOME)/public_html/hw7
	chmod 644 $(HOME)/public_html/hw7/*html
	chmod 755 $(HOME)/public_html/hw7/

        # Unlock public directory
	chmod 755 $(DIR)

        # copy solution to Tracker's account
	#scp -p Makefile *.c *.h *.java cs12xzz@ieng6-201.ucsd.edu:~/hw7
	#rm -f *.o *.class core
