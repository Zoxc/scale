CPP=g++
LFLAGS+=`sdl-config --libs` -lSDL_ttf -lSDL_image
CFLAGS+=-Wall `sdl-config --cflags` -I./Framework
TARGET=./bin/scale
 
OBJS=Framework/Application.o Framework/Element.o Image.o Button.o Graphics.o Label.o Solid.o Category.o CategoryBackground.o Main.o

 
$(TARGET): $(OBJS) Main.o $(wildcard *.hpp)
	$(CPP) $(CFLAGS) $(LFLAGS) -o $@ $(OBJS)

Main.o: Main.cpp $(wildcard *.hpp) 
	$(CPP) $(CFLAGS) -c $<

%.o: %.cpp %.hpp
	$(CPP) $(CFLAGS) -c $<  -o $@

.PHONY: clean 
clean:
	rm -f $(OBJS) $(TARGET)
