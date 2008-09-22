CPP=g++
LFLAGS=`sdl-config --libs` -lSDL_ttf -lSDL_image
CFLAGS=-Wall `sdl-config --cflags`
TARGET=./bin/scale
 
OBJS=Application.o Element.o Image.o Button.o Graphics.o Label.o Solid.o

 
$(TARGET): $(OBJS) Main.o $(wildcard *.hpp)
	$(CPP) $(CFLAGS) $(LFLAGS) -o $@ $(OBJS) Main.o

Main.o: Main.cpp $(wildcard *.hpp) 
	$(CPP) $(CFLAGS) -c $<

%.o: %.cpp %.hpp
	$(CPP) $(CFLAGS) -c $< 

.PHONY: clean 
clean:
	rm -f *.o $(TARGET)
