
ODIR=obj
CDIR=classes

CC = g++

CC_FLAGS = -std=c++17 -Wextra  -Wall -fstack-protector-all -g -O2 -lm -fno-exceptions

LIB_PATH = -Iclasses/ -I./	

SRC=$(wildcard *.cpp)
LOCAL_LIB=$(wildcard *.hpp)

OBJ= $(patsubst %,%, $(SRC:.cpp=.o))

DEPS= $(patsubst %,$(ODIR)/%,$(OBJ))


CLASS_SRC=$(wildcard classes/*.cpp)
CLASS_LIB=$(wildcard classes/*.hpp)

# $(FILES_OUT_1:.xls=.xlsx)
COBJ= $(patsubst classes/%,%, $(CLASS_SRC:.cpp=.o))

CDEPS= $(patsubst %,$(ODIR)/%,$(COBJ))

beaq:  class  main
# 	echo linking
	$(CC) $(CC_FLAGS)  $(CDEPS) $(DEPS)  -o beaq

# classes
$(CDEPS): $(CLASS_SRC)  $(CLASS_LIB)
	echo BULDING : $@ $(patsubst  $(ODIR)/%,classes/%,$(@:.o=.cpp))
	$(CC)  $(CC_FLAGS)  $(LIB_PATH) -c -o $@  $(patsubst  $(ODIR)/%,classes/%,$(@:.o=.cpp))

# $(CDEPS):

# $(ODIR)/%.o: $(CDIR)/%.cpp ./%.cpp
# 	echo BULDING : $@ $<
# 	$(CC) $(CC_FLAGS) $(LIB_PATH) -c -o $@ $<

$(DEPS): $(SRC) $(LOCAL_LIB) 
	echo BULDING : $@ 
	$(CC)  $(CC_FLAGS)  $(LIB_PATH) -c -o $@ $<



$(ODIR) :
	mkdir $(ODIR)

all: beaq

dummy:
	echo $(CDEPS)
	echo $(DEPS)

main: $(ODIR)  $(DEPS)
# 	echo main 

class : $(ODIR) $(CDEPS)
# 	echo class 


clean :
	test -f beaq && rm -v beaq            || true
	[ ! -z $(ODIR) ] && rm -vr obj/       || true

rebuild : clean classes main beaq
	bear make  clean classes main beaq 

.PHONY: all clean classes main rebuild