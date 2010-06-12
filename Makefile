#leave blank to use normal compiler
CROSS_COMPILE =
CPP = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
STRIP = $(CROSS_COMPILE)strip
CFLAGS += -pipe -DX11 -DNO_FRAME_LIMIT -DFRAME_EVENT -DSHADER_BENCH -DNO_GL_ALPHA  -Wall `freetype-config --cflags` -I./Framework -O3 -mfloat-abi=softfp -mfpu=neon -mcpu=cortex-a8 -mtune=cortex-a8
LDFLAGS += -lpng `freetype-config --libs` -lEGL -lGLESv2 -lX11

TARGET = ./bin/scale
BUILDDIR = ./obj

#activate debug by compiling with `DEBUG=1 make`
ifeq ($(DEBUG), 1)
CFLAGS += -g
endif

SRCS = Font.cpp Framework/Application.cpp Framework/Button.cpp Framework/Element.cpp Framework/OpenGL/OpenGL.Program.cpp Framework/OpenGL/OpenGL.Shader.cpp Framework/OpenGL/OpenGL.Buffer.cpp Framework/OpenGL/OpenGL.Texture.cpp Graphics.cpp Icon.cpp Image.cpp Label.cpp List.cpp ListSearch.cpp Main2.cpp Resources.cpp Scroller.cpp Solid.cpp Switcher.cpp VerticalBar.cpp

OBJS = $(patsubst %.cpp, $(BUILDDIR)/%.o, $(SRCS) )

all: objdir $(TARGET)

objdir:
	mkdir -p $(BUILDDIR)/Framework
	mkdir -p $(BUILDDIR)/Framework/OpenGL

$(TARGET): $(OBJS)
	$(CPP) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

$(BUILDDIR)/%.o: %.cpp %.hpp
	$(CPP) $(CFLAGS) -c $<  -o $@

.PHONY: clean 
clean:
	rm -f $(OBJS) $(TARGET)

depend:
	makedepend -p$(BUILDDIR)/ -- $(CFLAGS) -- $(SRCS) 2>/dev/null

# End of Makefile. Lines below are auto-generated with the depend rule
#
# DO NOT DELETE
