#leave blank to use normal compiler
CROSS_COMPILE =
CPP = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
STRIP = $(CROSS_COMPILE)strip
CFLAGS += -DNO_FRAME_LIMIT -DFRAME_EVENT -DSHADER_BENCH -DNO_GL_ALPHA  -Wall `freetype-config --cflags` -I./Framework -O3 -mfloat-abi=softfp -mfpu=neon -mcpu=cortex-a8 -mtune=cortex-a8
LDFLAGS += -lpng `freetype-config --libs` -lEGL -lGLESv2

TARGET = ./bin/scale
BUILDDIR = ./obj

#activate debug by compiling with `DEBUG=1 make`
ifeq ($(DEBUG), 1)
CFLAGS += -g
endif

SRCS = Font.cpp Font.hpp Framework\Application.cpp Framework/Application.hpp Framework/Button.cpp Framework/Button.hpp Framework/Element.cpp Framework/Element.hpp Framework/OpenGL\OpenGL.Program.cpp Framework/OpenGL/OpenGL.Program.hpp Framework/OpenGL/OpenGL.Shader.cpp Framework/OpenGL/OpenGL.Shader.hpp Framework/OpenGL/OpenGL.Texture.cpp Framework/OpenGL/OpenGL.Texture.hpp Framework/Options.hpp Graphics.cpp Graphics.hpp Icon.cpp Icon.hpp Image.cpp Image.hpp Label.cpp Label.hpp List.cpp List.hpp ListSearch.cpp ListSearch.hpp Main2.cpp Main2.hpp Resources.cpp Resources.hpp Scroller.cpp Scroller.hpp Solid.cpp Solid.hpp Switcher.cpp Switcher.hpp VerticalBar.cpp VerticalBar.hpp

OBJS = $(patsubst %.cpp, $(BUILDDIR)/%.o, $(SRCS) )

all: depend objdir $(TARGET)

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
