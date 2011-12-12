CC=g++
CFLAGS=-Wall -iquote "./" -iquote "./libfuzzy/headers"

SOURCES = main.cpp CSVParser.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
DEPS = make.dep
TARGET = CSVSearch

RM=rm -f

all: LB $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -rdynamic -Wl,-rpath,. -L. -lfuzzy -o $@ $(OBJECTS) -ldl -Wl,--unresolved-symbols=ignore-in-shared-libs

%.o: %.cpp
	$(CC) $(CFLAGS) -c -pg $< 


$(DEPS): $(SOURCES)
	$(CC) -MM -iquote "./" -iquote "./libfuzzy/headers" $(SOURCES) > $(DEPS)

LB:
	$(MAKE) --directory=libfuzzy

-include $(DEPS)

clean:
	$(RM) $(OBJECTS) $(TARGET) $(DEPS)

cleanall:
	$(RM) $(OBJECTS) $(TARGET) $(DEPS)
	$(MAKE) cleanall --directory=libfuzzy