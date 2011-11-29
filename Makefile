CC=g++
CFLAGS=-Wall

SOURCES = main.cpp CSVParser.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
DEPS = make.dep
TARGET = CSVSearch

RM=rm -f

$(TARGET): $(OBJECTS)
	$(CC) -pg -rdynamic -Wl,-rpath,. -L. -lfuzzy -o $@ $(OBJECTS) -ldl -Wl,--unresolved-symbols=ignore-in-shared-libs

%.o: %.cpp
	$(CC) $(CFLAGS) -c -pg $< 


$(DEPS): $(SOURCES)
	$(CC) -MM $(SOURCES) > $(DEPS)

-include $(DEPS)

clean:
	$(RM) $(OBJECTS) $(TARGET) $(DEPS)

