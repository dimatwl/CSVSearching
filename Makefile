CC=g++
CFLAGS=-Wall

SOURCES = main.cpp CSVParser.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
DEPS = make.dep
TARGET = CSVSearch

RM=rm -f

$(TARGET): $(OBJECTS)
	$(CC) -ldl  -Wl,-rpath,. -L. -lfuzzy -o $@ $(OBJECTS) -Wl,-undefined -Wl,dynamic_lookup

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< 


$(DEPS): $(SOURCES)
	$(CC) -MM $(SOURCES) > $(DEPS)

-include $(DEPS)

clean:
	$(RM) $(OBJECTS) $(TARGET) $(DEPS)

