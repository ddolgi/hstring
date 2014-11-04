CC = g++
CFLAGS = -g -Wall -fPIC #-pthread
#CFLAGS = -O2 -Wall -fPIC -pthread
LDFLAGS = -fPIC -pthread 
DEFINES = -D_REENTRANT

INC_PATH = $(GTEST_DIR)/include
OBJ_DIR = .

GTEST_LIB = -lgtest_main -L$(GTEST_DIR)/lib
LDLIBS    = $(GTEST_LIB) 

TARGET_LIB	= libhstring.a
TARGET_APP	= 
TEST_APP	= hstring_test

%.o: %.c
	$(CC) -c $(CFLAGS) $(DEFINES) $(INC_PATH:%=-I%) $< -o $(OBJ_DIR)/$@
%.o: %.cc
	$(CC) -c $(CFLAGS) $(DEFINES) $(INC_PATH:%=-I%) $< -o $(OBJ_DIR)/$@
%.o: %.cpp
	$(CC) -c $(CFLAGS) $(DEFINES) $(INC_PATH:%=-I%) $< -o $(OBJ_DIR)/$@

all:	$(TARGET_APP) $(TARGET_LIB) $(TEST_APP)

libhstring.a: hstring.o astring.o
	ar rcv $@ $(addprefix $(OBJ_DIR)/,$(notdir $(filter %.o,$^))) $(filter-out %.o,$^)
	ranlib $@

hstring_test: hstring_test.o -lhstring
	$(CC) -o $@ $(addprefix $(OBJ_DIR)/,$(notdir $(filter %.o,$^))) $(filter-out %.o,$^) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(TARGET_LIB) $(TARGET_APP) $(TEST_APP) $(OBJ_DIR)/*.o

tag:
	ctags -B --C++-kinds=+l -R .

dep:
	$(CC) -MM $(CFLAGS) $(DEFINES) *.c *.cc *.cpp > .depend

-include .depend
