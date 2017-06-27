ROOT=/Users/saiheiyeung/git/producer_consumer
TARGET=procon
SRCDIR=../src
OBJS=main.o
#CC = g++
CC = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++
INCLUDE_FLAGS=-I$(SRCDIR) -I$(ROOT)/install/bde/include -I$(ROOT)/install/bde/include/bsl -I$(ROOT)/install/bde/include/bdl
#CPPFLAGS=-g -std=gnu++11 $(INCLUDE_FLAGS) $(shell PKG_CONFIG_PATH=/Users/saiheiyeung/git/producer_consumer/install/bde/lib/pkgconfig:$(PKG_CONFIG_PATH) pkg-config --cflags bdl bsl)
CPPFLAGS=-g -std=gnu++11 
#LDFLAGS=$(shell PKG_CONFIG_PATH=/Users/saiheiyeung/git/producer_consumer/install/bde/lib/pkgconfig:$(PKG_CONFIG_PATH) pkg-config --libs bdl bsl)
LIBS=$(ROOT)/install/bde/lib/libbsl.a $(ROOT)/install/bde/lib/libbdl.a
LDFLAGS=-g -lpthread


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

%.o: $(SRCDIR)/%.cpp $(wildcard $(SRCDIR)/%.h)
	$(CC) -c -o $@ $< $(CPPFLAGS) $(INCLUDE_FLAGS)

.PHONY: clean

cleano:
	rm *.o

clean: cleano
	rm $(TARGET)




