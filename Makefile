#leave blank to use normal compiler
CROSS_COMPILE =
CPP = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
STRIP = $(CROSS_COMPILE)strip
LFLAGS += `sdl-config --libs` -lSDL_ttf -lSDL_image
CFLAGS += -Wall `sdl-config --cflags` -I./Framework -O2

TARGET = ./bin/scale
BUILDDIR = ./obj

#activate debug by compiling with `DEBUG=1 make`
ifeq ($(DEBUG), 1)
CFLAGS += -ggdb
endif

SRCS = $(wildcard *.cpp Framework/*.cpp)
OBJS = $(patsubst %.cpp, $(BUILDDIR)/%.o, $(SRCS) )

all: depend objdir $(TARGET)

objdir:
	mkdir -p obj/Framework

$(TARGET): $(OBJS)
	$(CPP) $(CFLAGS) $(LFLAGS) -o $@ $(OBJS)
ifneq ($(DEBUG), 1)
	$(STRIP) $@
endif

$(BUILDDIR)/%.o: %.cpp %.hpp
	$(CPP) $(CFLAGS) -c $<  -o $@

.PHONY: clean 
clean:
	rm -f $(OBJS) $(TARGET)

depend:
	makedepend -- $(CFLAGS) -- $(SRCS) 2>/dev/null

# End of Makefile. Lines below are auto-generated with the depend rule
#
# DO NOT DELETE

Button.o: Button.hpp /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Button.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Button.o: /usr/include/SDL/SDL_config-i386.h /usr/include/SDL/SDL_platform.h
Button.o: /usr/include/sys/types.h /usr/include/features.h
Button.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Button.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
Button.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
Button.o: /usr/include/time.h /usr/include/endian.h
Button.o: /usr/include/bits/endian.h /usr/include/sys/select.h
Button.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
Button.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
Button.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
Button.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
Button.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Button.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
Button.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
Button.o: /usr/include/alloca.h /usr/include/string.h /usr/include/strings.h
Button.o: /usr/include/inttypes.h /usr/include/stdint.h
Button.o: /usr/include/bits/wchar.h /usr/include/ctype.h /usr/include/iconv.h
Button.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Button.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Button.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Button.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Button.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Button.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Button.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Button.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Button.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Button.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Button.o: /usr/include/SDL/SDL_version.h /usr/include/SDL/SDL_image.h
Button.o: ./Framework/Element.hpp ./Framework/Graphics.hpp
Button.o: /usr/include/SDL/SDL_ttf.h
CategoryBackground.o: CategoryBackground.hpp /usr/include/SDL/SDL.h
CategoryBackground.o: /usr/include/SDL/SDL_main.h
CategoryBackground.o: /usr/include/SDL/SDL_stdinc.h
CategoryBackground.o: /usr/include/SDL/SDL_config.h
CategoryBackground.o: /usr/include/SDL/SDL_config-i386.h
CategoryBackground.o: /usr/include/SDL/SDL_platform.h
CategoryBackground.o: /usr/include/sys/types.h /usr/include/features.h
CategoryBackground.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
CategoryBackground.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
CategoryBackground.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
CategoryBackground.o: /usr/include/time.h /usr/include/endian.h
CategoryBackground.o: /usr/include/bits/endian.h /usr/include/sys/select.h
CategoryBackground.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
CategoryBackground.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
CategoryBackground.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
CategoryBackground.o: /usr/include/libio.h /usr/include/_G_config.h
CategoryBackground.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
CategoryBackground.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
CategoryBackground.o: /usr/include/bits/waitflags.h
CategoryBackground.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
CategoryBackground.o: /usr/include/alloca.h /usr/include/string.h
CategoryBackground.o: /usr/include/strings.h /usr/include/inttypes.h
CategoryBackground.o: /usr/include/stdint.h /usr/include/bits/wchar.h
CategoryBackground.o: /usr/include/ctype.h /usr/include/iconv.h
CategoryBackground.o: /usr/include/SDL/begin_code.h
CategoryBackground.o: /usr/include/SDL/close_code.h
CategoryBackground.o: /usr/include/SDL/SDL_audio.h
CategoryBackground.o: /usr/include/SDL/SDL_error.h
CategoryBackground.o: /usr/include/SDL/SDL_endian.h
CategoryBackground.o: /usr/include/SDL/SDL_mutex.h
CategoryBackground.o: /usr/include/SDL/SDL_thread.h
CategoryBackground.o: /usr/include/SDL/SDL_rwops.h
CategoryBackground.o: /usr/include/SDL/SDL_cdrom.h
CategoryBackground.o: /usr/include/SDL/SDL_cpuinfo.h
CategoryBackground.o: /usr/include/SDL/SDL_events.h
CategoryBackground.o: /usr/include/SDL/SDL_active.h
CategoryBackground.o: /usr/include/SDL/SDL_keyboard.h
CategoryBackground.o: /usr/include/SDL/SDL_keysym.h
CategoryBackground.o: /usr/include/SDL/SDL_mouse.h
CategoryBackground.o: /usr/include/SDL/SDL_video.h
CategoryBackground.o: /usr/include/SDL/SDL_joystick.h
CategoryBackground.o: /usr/include/SDL/SDL_quit.h
CategoryBackground.o: /usr/include/SDL/SDL_loadso.h
CategoryBackground.o: /usr/include/SDL/SDL_timer.h
CategoryBackground.o: /usr/include/SDL/SDL_version.h
CategoryBackground.o: /usr/include/SDL/SDL_image.h /usr/include/math.h
CategoryBackground.o: /usr/include/bits/huge_val.h
CategoryBackground.o: /usr/include/bits/huge_valf.h
CategoryBackground.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
CategoryBackground.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
CategoryBackground.o: /usr/include/bits/mathcalls.h ./Framework/Element.hpp
CategoryBackground.o: ./Framework/Graphics.hpp /usr/include/SDL/SDL_ttf.h
CategoryBackground.o: Button.hpp
Category.o: Category.hpp /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Category.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Category.o: /usr/include/SDL/SDL_config-i386.h
Category.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
Category.o: /usr/include/features.h /usr/include/sys/cdefs.h
Category.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Category.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
Category.o: /usr/include/bits/typesizes.h /usr/include/time.h
Category.o: /usr/include/endian.h /usr/include/bits/endian.h
Category.o: /usr/include/sys/select.h /usr/include/bits/select.h
Category.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Category.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Category.o: /usr/include/stdio.h /usr/include/libio.h
Category.o: /usr/include/_G_config.h /usr/include/wchar.h
Category.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Category.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
Category.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
Category.o: /usr/include/alloca.h /usr/include/string.h
Category.o: /usr/include/strings.h /usr/include/inttypes.h
Category.o: /usr/include/stdint.h /usr/include/bits/wchar.h
Category.o: /usr/include/ctype.h /usr/include/iconv.h
Category.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Category.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Category.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Category.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Category.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Category.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Category.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Category.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Category.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Category.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Category.o: /usr/include/SDL/SDL_version.h /usr/include/SDL/SDL_image.h
Category.o: ./Framework/Element.hpp CategoryBackground.hpp
Category.o: /usr/include/math.h /usr/include/bits/huge_val.h
Category.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
Category.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
Category.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
Category.o: ./Framework/Graphics.hpp /usr/include/SDL/SDL_ttf.h Button.hpp
Category.o: Main.hpp ./Framework/Application.hpp Image.hpp Label.hpp
Category.o: Solid.hpp
Image.o: Image.hpp /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Image.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Image.o: /usr/include/SDL/SDL_config-i386.h /usr/include/SDL/SDL_platform.h
Image.o: /usr/include/sys/types.h /usr/include/features.h
Image.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Image.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
Image.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
Image.o: /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h
Image.o: /usr/include/sys/select.h /usr/include/bits/select.h
Image.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Image.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Image.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Image.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Image.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Image.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
Image.o: /usr/include/xlocale.h /usr/include/alloca.h /usr/include/string.h
Image.o: /usr/include/strings.h /usr/include/inttypes.h /usr/include/stdint.h
Image.o: /usr/include/bits/wchar.h /usr/include/ctype.h /usr/include/iconv.h
Image.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Image.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Image.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Image.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Image.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Image.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Image.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Image.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Image.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Image.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Image.o: /usr/include/SDL/SDL_version.h /usr/include/SDL/SDL_image.h
Image.o: ./Framework/Element.hpp ./Framework/Graphics.hpp
Image.o: /usr/include/SDL/SDL_ttf.h
Label.o: Label.hpp /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Label.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Label.o: /usr/include/SDL/SDL_config-i386.h /usr/include/SDL/SDL_platform.h
Label.o: /usr/include/sys/types.h /usr/include/features.h
Label.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Label.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
Label.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
Label.o: /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h
Label.o: /usr/include/sys/select.h /usr/include/bits/select.h
Label.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Label.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Label.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Label.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Label.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Label.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
Label.o: /usr/include/xlocale.h /usr/include/alloca.h /usr/include/string.h
Label.o: /usr/include/strings.h /usr/include/inttypes.h /usr/include/stdint.h
Label.o: /usr/include/bits/wchar.h /usr/include/ctype.h /usr/include/iconv.h
Label.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Label.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Label.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Label.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Label.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Label.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Label.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Label.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Label.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Label.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Label.o: /usr/include/SDL/SDL_version.h /usr/include/SDL/SDL_image.h
Label.o: /usr/include/SDL/SDL_ttf.h ./Framework/Element.hpp
Label.o: ./Framework/Graphics.hpp
Main.o: Main.hpp ./Framework/Application.hpp /usr/include/SDL/SDL.h
Main.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
Main.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_config-i386.h
Main.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
Main.o: /usr/include/features.h /usr/include/sys/cdefs.h
Main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Main.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
Main.o: /usr/include/bits/typesizes.h /usr/include/time.h
Main.o: /usr/include/endian.h /usr/include/bits/endian.h
Main.o: /usr/include/sys/select.h /usr/include/bits/select.h
Main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Main.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Main.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Main.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Main.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
Main.o: /usr/include/xlocale.h /usr/include/alloca.h /usr/include/string.h
Main.o: /usr/include/strings.h /usr/include/inttypes.h /usr/include/stdint.h
Main.o: /usr/include/bits/wchar.h /usr/include/ctype.h /usr/include/iconv.h
Main.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Main.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Main.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Main.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Main.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Main.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Main.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Main.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Main.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Main.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Main.o: /usr/include/SDL/SDL_version.h ./Framework/Element.hpp Image.hpp
Main.o: /usr/include/SDL/SDL_image.h Label.hpp /usr/include/SDL/SDL_ttf.h
Main.o: Button.hpp Solid.hpp Category.hpp CategoryBackground.hpp
Main.o: /usr/include/math.h /usr/include/bits/huge_val.h
Main.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
Main.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
Main.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
Solid.o: Solid.hpp /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Solid.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Solid.o: /usr/include/SDL/SDL_config-i386.h /usr/include/SDL/SDL_platform.h
Solid.o: /usr/include/sys/types.h /usr/include/features.h
Solid.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Solid.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
Solid.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
Solid.o: /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h
Solid.o: /usr/include/sys/select.h /usr/include/bits/select.h
Solid.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Solid.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Solid.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Solid.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Solid.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Solid.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
Solid.o: /usr/include/xlocale.h /usr/include/alloca.h /usr/include/string.h
Solid.o: /usr/include/strings.h /usr/include/inttypes.h /usr/include/stdint.h
Solid.o: /usr/include/bits/wchar.h /usr/include/ctype.h /usr/include/iconv.h
Solid.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Solid.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Solid.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Solid.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Solid.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Solid.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Solid.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Solid.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Solid.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Solid.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Solid.o: /usr/include/SDL/SDL_version.h ./Framework/Element.hpp
Solid.o: ./Framework/Graphics.hpp /usr/include/SDL/SDL_ttf.h
Framework/Application.o: /usr/include/SDL/SDL_ttf.h /usr/include/SDL/SDL.h
Framework/Application.o: /usr/include/SDL/SDL_main.h
Framework/Application.o: /usr/include/SDL/SDL_stdinc.h
Framework/Application.o: /usr/include/SDL/SDL_config.h
Framework/Application.o: /usr/include/SDL/SDL_config-i386.h
Framework/Application.o: /usr/include/SDL/SDL_platform.h
Framework/Application.o: /usr/include/sys/types.h /usr/include/features.h
Framework/Application.o: /usr/include/sys/cdefs.h
Framework/Application.o: /usr/include/bits/wordsize.h
Framework/Application.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
Framework/Application.o: /usr/include/bits/types.h
Framework/Application.o: /usr/include/bits/typesizes.h /usr/include/time.h
Framework/Application.o: /usr/include/endian.h /usr/include/bits/endian.h
Framework/Application.o: /usr/include/sys/select.h /usr/include/bits/select.h
Framework/Application.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Framework/Application.o: /usr/include/sys/sysmacros.h
Framework/Application.o: /usr/include/bits/pthreadtypes.h
Framework/Application.o: /usr/include/stdio.h /usr/include/libio.h
Framework/Application.o: /usr/include/_G_config.h /usr/include/wchar.h
Framework/Application.o: /usr/include/bits/stdio_lim.h
Framework/Application.o: /usr/include/bits/sys_errlist.h
Framework/Application.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
Framework/Application.o: /usr/include/bits/waitstatus.h
Framework/Application.o: /usr/include/xlocale.h /usr/include/alloca.h
Framework/Application.o: /usr/include/string.h /usr/include/strings.h
Framework/Application.o: /usr/include/inttypes.h /usr/include/stdint.h
Framework/Application.o: /usr/include/bits/wchar.h /usr/include/ctype.h
Framework/Application.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
Framework/Application.o: /usr/include/SDL/close_code.h
Framework/Application.o: /usr/include/SDL/SDL_audio.h
Framework/Application.o: /usr/include/SDL/SDL_error.h
Framework/Application.o: /usr/include/SDL/SDL_endian.h
Framework/Application.o: /usr/include/SDL/SDL_mutex.h
Framework/Application.o: /usr/include/SDL/SDL_thread.h
Framework/Application.o: /usr/include/SDL/SDL_rwops.h
Framework/Application.o: /usr/include/SDL/SDL_cdrom.h
Framework/Application.o: /usr/include/SDL/SDL_cpuinfo.h
Framework/Application.o: /usr/include/SDL/SDL_events.h
Framework/Application.o: /usr/include/SDL/SDL_active.h
Framework/Application.o: /usr/include/SDL/SDL_keyboard.h
Framework/Application.o: /usr/include/SDL/SDL_keysym.h
Framework/Application.o: /usr/include/SDL/SDL_mouse.h
Framework/Application.o: /usr/include/SDL/SDL_video.h
Framework/Application.o: /usr/include/SDL/SDL_joystick.h
Framework/Application.o: /usr/include/SDL/SDL_quit.h
Framework/Application.o: /usr/include/SDL/SDL_loadso.h
Framework/Application.o: /usr/include/SDL/SDL_timer.h
Framework/Application.o: /usr/include/SDL/SDL_version.h
Framework/Application.o: ./Framework/Application.hpp ./Framework/Element.hpp
Framework/Element.o: ./Framework/Element.hpp /usr/include/SDL/SDL.h
Framework/Element.o: /usr/include/SDL/SDL_main.h
Framework/Element.o: /usr/include/SDL/SDL_stdinc.h
Framework/Element.o: /usr/include/SDL/SDL_config.h
Framework/Element.o: /usr/include/SDL/SDL_config-i386.h
Framework/Element.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
Framework/Element.o: /usr/include/features.h /usr/include/sys/cdefs.h
Framework/Element.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Framework/Element.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
Framework/Element.o: /usr/include/bits/typesizes.h /usr/include/time.h
Framework/Element.o: /usr/include/endian.h /usr/include/bits/endian.h
Framework/Element.o: /usr/include/sys/select.h /usr/include/bits/select.h
Framework/Element.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Framework/Element.o: /usr/include/sys/sysmacros.h
Framework/Element.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
Framework/Element.o: /usr/include/libio.h /usr/include/_G_config.h
Framework/Element.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Framework/Element.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Framework/Element.o: /usr/include/bits/waitflags.h
Framework/Element.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
Framework/Element.o: /usr/include/alloca.h /usr/include/string.h
Framework/Element.o: /usr/include/strings.h /usr/include/inttypes.h
Framework/Element.o: /usr/include/stdint.h /usr/include/bits/wchar.h
Framework/Element.o: /usr/include/ctype.h /usr/include/iconv.h
Framework/Element.o: /usr/include/SDL/begin_code.h
Framework/Element.o: /usr/include/SDL/close_code.h
Framework/Element.o: /usr/include/SDL/SDL_audio.h
Framework/Element.o: /usr/include/SDL/SDL_error.h
Framework/Element.o: /usr/include/SDL/SDL_endian.h
Framework/Element.o: /usr/include/SDL/SDL_mutex.h
Framework/Element.o: /usr/include/SDL/SDL_thread.h
Framework/Element.o: /usr/include/SDL/SDL_rwops.h
Framework/Element.o: /usr/include/SDL/SDL_cdrom.h
Framework/Element.o: /usr/include/SDL/SDL_cpuinfo.h
Framework/Element.o: /usr/include/SDL/SDL_events.h
Framework/Element.o: /usr/include/SDL/SDL_active.h
Framework/Element.o: /usr/include/SDL/SDL_keyboard.h
Framework/Element.o: /usr/include/SDL/SDL_keysym.h
Framework/Element.o: /usr/include/SDL/SDL_mouse.h
Framework/Element.o: /usr/include/SDL/SDL_video.h
Framework/Element.o: /usr/include/SDL/SDL_joystick.h
Framework/Element.o: /usr/include/SDL/SDL_quit.h
Framework/Element.o: /usr/include/SDL/SDL_loadso.h
Framework/Element.o: /usr/include/SDL/SDL_timer.h
Framework/Element.o: /usr/include/SDL/SDL_version.h
Framework/Graphics.o: /usr/include/math.h /usr/include/features.h
Framework/Graphics.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Framework/Graphics.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
Framework/Graphics.o: /usr/include/bits/huge_val.h
Framework/Graphics.o: /usr/include/bits/huge_valf.h
Framework/Graphics.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
Framework/Graphics.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
Framework/Graphics.o: /usr/include/bits/mathcalls.h ./Framework/Graphics.hpp
Framework/Graphics.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Framework/Graphics.o: /usr/include/SDL/SDL_stdinc.h
Framework/Graphics.o: /usr/include/SDL/SDL_config.h
Framework/Graphics.o: /usr/include/SDL/SDL_config-i386.h
Framework/Graphics.o: /usr/include/SDL/SDL_platform.h
Framework/Graphics.o: /usr/include/sys/types.h /usr/include/bits/types.h
Framework/Graphics.o: /usr/include/bits/typesizes.h /usr/include/time.h
Framework/Graphics.o: /usr/include/endian.h /usr/include/bits/endian.h
Framework/Graphics.o: /usr/include/sys/select.h /usr/include/bits/select.h
Framework/Graphics.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Framework/Graphics.o: /usr/include/sys/sysmacros.h
Framework/Graphics.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
Framework/Graphics.o: /usr/include/libio.h /usr/include/_G_config.h
Framework/Graphics.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Framework/Graphics.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Framework/Graphics.o: /usr/include/bits/waitflags.h
Framework/Graphics.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
Framework/Graphics.o: /usr/include/alloca.h /usr/include/string.h
Framework/Graphics.o: /usr/include/strings.h /usr/include/inttypes.h
Framework/Graphics.o: /usr/include/stdint.h /usr/include/bits/wchar.h
Framework/Graphics.o: /usr/include/ctype.h /usr/include/iconv.h
Framework/Graphics.o: /usr/include/SDL/begin_code.h
Framework/Graphics.o: /usr/include/SDL/close_code.h
Framework/Graphics.o: /usr/include/SDL/SDL_audio.h
Framework/Graphics.o: /usr/include/SDL/SDL_error.h
Framework/Graphics.o: /usr/include/SDL/SDL_endian.h
Framework/Graphics.o: /usr/include/SDL/SDL_mutex.h
Framework/Graphics.o: /usr/include/SDL/SDL_thread.h
Framework/Graphics.o: /usr/include/SDL/SDL_rwops.h
Framework/Graphics.o: /usr/include/SDL/SDL_cdrom.h
Framework/Graphics.o: /usr/include/SDL/SDL_cpuinfo.h
Framework/Graphics.o: /usr/include/SDL/SDL_events.h
Framework/Graphics.o: /usr/include/SDL/SDL_active.h
Framework/Graphics.o: /usr/include/SDL/SDL_keyboard.h
Framework/Graphics.o: /usr/include/SDL/SDL_keysym.h
Framework/Graphics.o: /usr/include/SDL/SDL_mouse.h
Framework/Graphics.o: /usr/include/SDL/SDL_video.h
Framework/Graphics.o: /usr/include/SDL/SDL_joystick.h
Framework/Graphics.o: /usr/include/SDL/SDL_quit.h
Framework/Graphics.o: /usr/include/SDL/SDL_loadso.h
Framework/Graphics.o: /usr/include/SDL/SDL_timer.h
Framework/Graphics.o: /usr/include/SDL/SDL_version.h
Framework/Graphics.o: /usr/include/SDL/SDL_ttf.h
