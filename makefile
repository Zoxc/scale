CPP=g++
LFLAGS=`sdl-config --cflags --libs` -lSDL_ttf -lSDL_image
CFLAGS=-Wall
TARGET=GUIDemo
 
SOURCES=*.cpp
 
$(TARGET): $(SOURCES)
        $(CPP) $(CFLAGS) $(LFLAGS) -o $@ $(SOURCES)
 
run: $(TARGET)
        ./$(TARGET)
 
clean:
        rm -f *.o $(TARGET)