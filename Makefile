#leave blank to use normal compiler
CROSS_COMPILE =
CPP = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
STRIP = $(CROSS_COMPILE)strip
CFLAGS += -Wall `sdl-config --cflags` -I./Framework -O2
LDFLAGS += -lSDL_ttf -lSDL_image -lSDL_mixer

TARGET = ./bin/scale
BUILDDIR = ./obj

#activate debug by compiling with `DEBUG=1 make`
ifeq ($(DEBUG), 1)
CFLAGS += -ggdb
endif

#activate static binaries with `STATIC=1 make`
ifeq ($(STATIC), 1)
LDFLAGS += -static `sdl-config --static-libs`
else
LDFLAGS += `sdl-config --libs`
endif


SRCS = $(wildcard *.cpp Framework/*.cpp)
OBJS = $(patsubst %.cpp, $(BUILDDIR)/%.o, $(SRCS) )

all: depend objdir $(TARGET)

objdir:
	mkdir -p $(BUILDDIR)/Framework

$(TARGET): $(OBJS)
	$(CPP) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)
ifneq ($(DEBUG), 1)
	$(STRIP) $@
endif

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

./obj/CategoryBackground.o: /usr/include/math.h /usr/include/features.h
./obj/CategoryBackground.o: /usr/include/sys/cdefs.h
./obj/CategoryBackground.o: /usr/include/bits/wordsize.h
./obj/CategoryBackground.o: /usr/include/gnu/stubs.h
./obj/CategoryBackground.o: /usr/include/gnu/stubs-32.h
./obj/CategoryBackground.o: /usr/include/bits/huge_val.h
./obj/CategoryBackground.o: /usr/include/bits/huge_valf.h
./obj/CategoryBackground.o: /usr/include/bits/huge_vall.h
./obj/CategoryBackground.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
./obj/CategoryBackground.o: /usr/include/bits/mathdef.h
./obj/CategoryBackground.o: /usr/include/bits/mathcalls.h
./obj/CategoryBackground.o: CategoryBackground.hpp /usr/include/SDL/SDL.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_main.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_stdinc.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_config.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_config-i386.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_platform.h
./obj/CategoryBackground.o: /usr/include/sys/types.h
./obj/CategoryBackground.o: /usr/include/bits/types.h
./obj/CategoryBackground.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/CategoryBackground.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/CategoryBackground.o: /usr/include/sys/select.h
./obj/CategoryBackground.o: /usr/include/bits/select.h
./obj/CategoryBackground.o: /usr/include/bits/sigset.h
./obj/CategoryBackground.o: /usr/include/bits/time.h
./obj/CategoryBackground.o: /usr/include/sys/sysmacros.h
./obj/CategoryBackground.o: /usr/include/bits/pthreadtypes.h
./obj/CategoryBackground.o: /usr/include/stdio.h /usr/include/libio.h
./obj/CategoryBackground.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/CategoryBackground.o: /usr/include/bits/stdio_lim.h
./obj/CategoryBackground.o: /usr/include/bits/sys_errlist.h
./obj/CategoryBackground.o: /usr/include/stdlib.h
./obj/CategoryBackground.o: /usr/include/bits/waitflags.h
./obj/CategoryBackground.o: /usr/include/bits/waitstatus.h
./obj/CategoryBackground.o: /usr/include/xlocale.h /usr/include/alloca.h
./obj/CategoryBackground.o: /usr/include/string.h /usr/include/strings.h
./obj/CategoryBackground.o: /usr/include/inttypes.h /usr/include/stdint.h
./obj/CategoryBackground.o: /usr/include/bits/wchar.h /usr/include/ctype.h
./obj/CategoryBackground.o: /usr/include/iconv.h
./obj/CategoryBackground.o: /usr/include/SDL/begin_code.h
./obj/CategoryBackground.o: /usr/include/SDL/close_code.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_audio.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_error.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_endian.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_mutex.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_thread.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_rwops.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_cdrom.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_cpuinfo.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_events.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_active.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_keyboard.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_keysym.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_mouse.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_video.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_joystick.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_quit.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_loadso.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_timer.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_version.h
./obj/CategoryBackground.o: /usr/include/SDL/SDL_image.h
./obj/CategoryBackground.o: ./Framework/Element.hpp CategoryScroller.hpp
./obj/CategoryBackground.o: ./Framework/Graphics.hpp
./obj/CategoryBackground.o: /usr/include/SDL/SDL_ttf.h ./Framework/Button.hpp
./obj/Category.o: /usr/include/SDL/SDL_mixer.h /usr/include/SDL/SDL_types.h
./obj/Category.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
./obj/Category.o: /usr/include/SDL/SDL_config-i386.h
./obj/Category.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
./obj/Category.o: /usr/include/features.h /usr/include/sys/cdefs.h
./obj/Category.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./obj/Category.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
./obj/Category.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/Category.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/Category.o: /usr/include/sys/select.h /usr/include/bits/select.h
./obj/Category.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
./obj/Category.o: /usr/include/sys/sysmacros.h
./obj/Category.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
./obj/Category.o: /usr/include/libio.h /usr/include/_G_config.h
./obj/Category.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
./obj/Category.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
./obj/Category.o: /usr/include/bits/waitflags.h
./obj/Category.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
./obj/Category.o: /usr/include/alloca.h /usr/include/string.h
./obj/Category.o: /usr/include/strings.h /usr/include/inttypes.h
./obj/Category.o: /usr/include/stdint.h /usr/include/bits/wchar.h
./obj/Category.o: /usr/include/ctype.h /usr/include/iconv.h
./obj/Category.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
./obj/Category.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_error.h
./obj/Category.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_endian.h
./obj/Category.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
./obj/Category.o: /usr/include/SDL/SDL_version.h Category.hpp
./obj/Category.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
./obj/Category.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
./obj/Category.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
./obj/Category.o: /usr/include/SDL/SDL_keyboard.h
./obj/Category.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
./obj/Category.o: /usr/include/SDL/SDL_video.h
./obj/Category.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
./obj/Category.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
./obj/Category.o: /usr/include/SDL/SDL_image.h ./Framework/Element.hpp
./obj/Category.o: CategoryBackground.hpp CategoryScroller.hpp
./obj/Category.o: ./Framework/Graphics.hpp /usr/include/SDL/SDL_ttf.h
./obj/Category.o: ./Framework/Button.hpp Main.hpp ./Framework/Options.hpp
./obj/Category.o: ./Framework/Application.hpp Image.hpp Label.hpp Icon.hpp
./obj/Category.o: Solid.hpp
./obj/CategoryScroller.o: /usr/include/math.h /usr/include/features.h
./obj/CategoryScroller.o: /usr/include/sys/cdefs.h
./obj/CategoryScroller.o: /usr/include/bits/wordsize.h
./obj/CategoryScroller.o: /usr/include/gnu/stubs.h
./obj/CategoryScroller.o: /usr/include/gnu/stubs-32.h
./obj/CategoryScroller.o: /usr/include/bits/huge_val.h
./obj/CategoryScroller.o: /usr/include/bits/huge_valf.h
./obj/CategoryScroller.o: /usr/include/bits/huge_vall.h
./obj/CategoryScroller.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
./obj/CategoryScroller.o: /usr/include/bits/mathdef.h
./obj/CategoryScroller.o: /usr/include/bits/mathcalls.h CategoryScroller.hpp
./obj/CategoryScroller.o: ./Framework/Element.hpp /usr/include/SDL/SDL.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_main.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_stdinc.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_config.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_config-i386.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_platform.h
./obj/CategoryScroller.o: /usr/include/sys/types.h /usr/include/bits/types.h
./obj/CategoryScroller.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/CategoryScroller.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/CategoryScroller.o: /usr/include/sys/select.h
./obj/CategoryScroller.o: /usr/include/bits/select.h
./obj/CategoryScroller.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
./obj/CategoryScroller.o: /usr/include/sys/sysmacros.h
./obj/CategoryScroller.o: /usr/include/bits/pthreadtypes.h
./obj/CategoryScroller.o: /usr/include/stdio.h /usr/include/libio.h
./obj/CategoryScroller.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/CategoryScroller.o: /usr/include/bits/stdio_lim.h
./obj/CategoryScroller.o: /usr/include/bits/sys_errlist.h
./obj/CategoryScroller.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
./obj/CategoryScroller.o: /usr/include/bits/waitstatus.h
./obj/CategoryScroller.o: /usr/include/xlocale.h /usr/include/alloca.h
./obj/CategoryScroller.o: /usr/include/string.h /usr/include/strings.h
./obj/CategoryScroller.o: /usr/include/inttypes.h /usr/include/stdint.h
./obj/CategoryScroller.o: /usr/include/bits/wchar.h /usr/include/ctype.h
./obj/CategoryScroller.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
./obj/CategoryScroller.o: /usr/include/SDL/close_code.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_audio.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_error.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_endian.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_mutex.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_thread.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_rwops.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_cdrom.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_cpuinfo.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_events.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_active.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_keyboard.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_keysym.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_mouse.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_video.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_joystick.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_quit.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_loadso.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_timer.h
./obj/CategoryScroller.o: /usr/include/SDL/SDL_version.h
./obj/Icon.o: /usr/include/SDL/SDL_mixer.h /usr/include/SDL/SDL_types.h
./obj/Icon.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
./obj/Icon.o: /usr/include/SDL/SDL_config-i386.h
./obj/Icon.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
./obj/Icon.o: /usr/include/features.h /usr/include/sys/cdefs.h
./obj/Icon.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./obj/Icon.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
./obj/Icon.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/Icon.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/Icon.o: /usr/include/sys/select.h /usr/include/bits/select.h
./obj/Icon.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
./obj/Icon.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
./obj/Icon.o: /usr/include/stdio.h /usr/include/libio.h
./obj/Icon.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/Icon.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
./obj/Icon.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
./obj/Icon.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
./obj/Icon.o: /usr/include/alloca.h /usr/include/string.h
./obj/Icon.o: /usr/include/strings.h /usr/include/inttypes.h
./obj/Icon.o: /usr/include/stdint.h /usr/include/bits/wchar.h
./obj/Icon.o: /usr/include/ctype.h /usr/include/iconv.h
./obj/Icon.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
./obj/Icon.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_error.h
./obj/Icon.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_endian.h
./obj/Icon.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
./obj/Icon.o: /usr/include/SDL/SDL_version.h Icon.hpp /usr/include/SDL/SDL.h
./obj/Icon.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_cdrom.h
./obj/Icon.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
./obj/Icon.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
./obj/Icon.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
./obj/Icon.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
./obj/Icon.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
./obj/Icon.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_image.h
./obj/Icon.o: ./Framework/Button.hpp ./Framework/Element.hpp
./obj/Icon.o: ./Framework/Graphics.hpp /usr/include/SDL/SDL_ttf.h
./obj/Image.o: Image.hpp /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
./obj/Image.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
./obj/Image.o: /usr/include/SDL/SDL_config-i386.h
./obj/Image.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
./obj/Image.o: /usr/include/features.h /usr/include/sys/cdefs.h
./obj/Image.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./obj/Image.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
./obj/Image.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/Image.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/Image.o: /usr/include/sys/select.h /usr/include/bits/select.h
./obj/Image.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
./obj/Image.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
./obj/Image.o: /usr/include/stdio.h /usr/include/libio.h
./obj/Image.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/Image.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
./obj/Image.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
./obj/Image.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
./obj/Image.o: /usr/include/alloca.h /usr/include/string.h
./obj/Image.o: /usr/include/strings.h /usr/include/inttypes.h
./obj/Image.o: /usr/include/stdint.h /usr/include/bits/wchar.h
./obj/Image.o: /usr/include/ctype.h /usr/include/iconv.h
./obj/Image.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
./obj/Image.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
./obj/Image.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
./obj/Image.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
./obj/Image.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
./obj/Image.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
./obj/Image.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
./obj/Image.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
./obj/Image.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
./obj/Image.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
./obj/Image.o: /usr/include/SDL/SDL_version.h /usr/include/SDL/SDL_image.h
./obj/Image.o: ./Framework/Element.hpp ./Framework/Graphics.hpp
./obj/Image.o: /usr/include/SDL/SDL_ttf.h
./obj/Label.o: Label.hpp /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
./obj/Label.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
./obj/Label.o: /usr/include/SDL/SDL_config-i386.h
./obj/Label.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
./obj/Label.o: /usr/include/features.h /usr/include/sys/cdefs.h
./obj/Label.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./obj/Label.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
./obj/Label.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/Label.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/Label.o: /usr/include/sys/select.h /usr/include/bits/select.h
./obj/Label.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
./obj/Label.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
./obj/Label.o: /usr/include/stdio.h /usr/include/libio.h
./obj/Label.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/Label.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
./obj/Label.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
./obj/Label.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
./obj/Label.o: /usr/include/alloca.h /usr/include/string.h
./obj/Label.o: /usr/include/strings.h /usr/include/inttypes.h
./obj/Label.o: /usr/include/stdint.h /usr/include/bits/wchar.h
./obj/Label.o: /usr/include/ctype.h /usr/include/iconv.h
./obj/Label.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
./obj/Label.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
./obj/Label.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
./obj/Label.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
./obj/Label.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
./obj/Label.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
./obj/Label.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
./obj/Label.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
./obj/Label.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
./obj/Label.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
./obj/Label.o: /usr/include/SDL/SDL_version.h /usr/include/SDL/SDL_image.h
./obj/Label.o: /usr/include/SDL/SDL_ttf.h ./Framework/Element.hpp
./obj/Label.o: ./Framework/Graphics.hpp
./obj/Main.o: Main.hpp ./Framework/Options.hpp ./Framework/Application.hpp
./obj/Main.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
./obj/Main.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
./obj/Main.o: /usr/include/SDL/SDL_config-i386.h
./obj/Main.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
./obj/Main.o: /usr/include/features.h /usr/include/sys/cdefs.h
./obj/Main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./obj/Main.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
./obj/Main.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/Main.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/Main.o: /usr/include/sys/select.h /usr/include/bits/select.h
./obj/Main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
./obj/Main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
./obj/Main.o: /usr/include/stdio.h /usr/include/libio.h
./obj/Main.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/Main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
./obj/Main.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
./obj/Main.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
./obj/Main.o: /usr/include/alloca.h /usr/include/string.h
./obj/Main.o: /usr/include/strings.h /usr/include/inttypes.h
./obj/Main.o: /usr/include/stdint.h /usr/include/bits/wchar.h
./obj/Main.o: /usr/include/ctype.h /usr/include/iconv.h
./obj/Main.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
./obj/Main.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
./obj/Main.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
./obj/Main.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
./obj/Main.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
./obj/Main.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
./obj/Main.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
./obj/Main.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
./obj/Main.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
./obj/Main.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
./obj/Main.o: /usr/include/SDL/SDL_version.h ./Framework/Element.hpp
./obj/Main.o: Image.hpp /usr/include/SDL/SDL_image.h Label.hpp
./obj/Main.o: /usr/include/SDL/SDL_ttf.h Icon.hpp ./Framework/Button.hpp
./obj/Main.o: Solid.hpp Category.hpp CategoryBackground.hpp
./obj/Main.o: CategoryScroller.hpp
./obj/Solid.o: Solid.hpp /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
./obj/Solid.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
./obj/Solid.o: /usr/include/SDL/SDL_config-i386.h
./obj/Solid.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
./obj/Solid.o: /usr/include/features.h /usr/include/sys/cdefs.h
./obj/Solid.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./obj/Solid.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
./obj/Solid.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/Solid.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/Solid.o: /usr/include/sys/select.h /usr/include/bits/select.h
./obj/Solid.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
./obj/Solid.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
./obj/Solid.o: /usr/include/stdio.h /usr/include/libio.h
./obj/Solid.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/Solid.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
./obj/Solid.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
./obj/Solid.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
./obj/Solid.o: /usr/include/alloca.h /usr/include/string.h
./obj/Solid.o: /usr/include/strings.h /usr/include/inttypes.h
./obj/Solid.o: /usr/include/stdint.h /usr/include/bits/wchar.h
./obj/Solid.o: /usr/include/ctype.h /usr/include/iconv.h
./obj/Solid.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
./obj/Solid.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
./obj/Solid.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
./obj/Solid.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
./obj/Solid.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
./obj/Solid.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
./obj/Solid.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
./obj/Solid.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
./obj/Solid.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
./obj/Solid.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
./obj/Solid.o: /usr/include/SDL/SDL_version.h ./Framework/Element.hpp
./obj/Solid.o: ./Framework/Graphics.hpp /usr/include/SDL/SDL_ttf.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_ttf.h
./obj/Framework/Application.o: /usr/include/SDL/SDL.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_main.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_stdinc.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_config.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_config-i386.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_platform.h
./obj/Framework/Application.o: /usr/include/sys/types.h
./obj/Framework/Application.o: /usr/include/features.h
./obj/Framework/Application.o: /usr/include/sys/cdefs.h
./obj/Framework/Application.o: /usr/include/bits/wordsize.h
./obj/Framework/Application.o: /usr/include/gnu/stubs.h
./obj/Framework/Application.o: /usr/include/gnu/stubs-32.h
./obj/Framework/Application.o: /usr/include/bits/types.h
./obj/Framework/Application.o: /usr/include/bits/typesizes.h
./obj/Framework/Application.o: /usr/include/time.h /usr/include/endian.h
./obj/Framework/Application.o: /usr/include/bits/endian.h
./obj/Framework/Application.o: /usr/include/sys/select.h
./obj/Framework/Application.o: /usr/include/bits/select.h
./obj/Framework/Application.o: /usr/include/bits/sigset.h
./obj/Framework/Application.o: /usr/include/bits/time.h
./obj/Framework/Application.o: /usr/include/sys/sysmacros.h
./obj/Framework/Application.o: /usr/include/bits/pthreadtypes.h
./obj/Framework/Application.o: /usr/include/stdio.h /usr/include/libio.h
./obj/Framework/Application.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/Framework/Application.o: /usr/include/bits/stdio_lim.h
./obj/Framework/Application.o: /usr/include/bits/sys_errlist.h
./obj/Framework/Application.o: /usr/include/stdlib.h
./obj/Framework/Application.o: /usr/include/bits/waitflags.h
./obj/Framework/Application.o: /usr/include/bits/waitstatus.h
./obj/Framework/Application.o: /usr/include/xlocale.h /usr/include/alloca.h
./obj/Framework/Application.o: /usr/include/string.h /usr/include/strings.h
./obj/Framework/Application.o: /usr/include/inttypes.h /usr/include/stdint.h
./obj/Framework/Application.o: /usr/include/bits/wchar.h /usr/include/ctype.h
./obj/Framework/Application.o: /usr/include/iconv.h
./obj/Framework/Application.o: /usr/include/SDL/begin_code.h
./obj/Framework/Application.o: /usr/include/SDL/close_code.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_audio.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_error.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_endian.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_mutex.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_thread.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_rwops.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_cdrom.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_cpuinfo.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_events.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_active.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_keyboard.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_keysym.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_mouse.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_video.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_joystick.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_quit.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_loadso.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_timer.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_version.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_mixer.h
./obj/Framework/Application.o: /usr/include/SDL/SDL_types.h
./obj/Framework/Application.o: ./Framework/Application.hpp
./obj/Framework/Application.o: ./Framework/Options.hpp
./obj/Framework/Application.o: ./Framework/Element.hpp
./obj/Framework/Button.o: ./Framework/Button.hpp ./Framework/Element.hpp
./obj/Framework/Button.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_stdinc.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_config.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_config-i386.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_platform.h
./obj/Framework/Button.o: /usr/include/sys/types.h /usr/include/features.h
./obj/Framework/Button.o: /usr/include/sys/cdefs.h
./obj/Framework/Button.o: /usr/include/bits/wordsize.h
./obj/Framework/Button.o: /usr/include/gnu/stubs.h
./obj/Framework/Button.o: /usr/include/gnu/stubs-32.h
./obj/Framework/Button.o: /usr/include/bits/types.h
./obj/Framework/Button.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/Framework/Button.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/Framework/Button.o: /usr/include/sys/select.h
./obj/Framework/Button.o: /usr/include/bits/select.h
./obj/Framework/Button.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
./obj/Framework/Button.o: /usr/include/sys/sysmacros.h
./obj/Framework/Button.o: /usr/include/bits/pthreadtypes.h
./obj/Framework/Button.o: /usr/include/stdio.h /usr/include/libio.h
./obj/Framework/Button.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/Framework/Button.o: /usr/include/bits/stdio_lim.h
./obj/Framework/Button.o: /usr/include/bits/sys_errlist.h
./obj/Framework/Button.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
./obj/Framework/Button.o: /usr/include/bits/waitstatus.h
./obj/Framework/Button.o: /usr/include/xlocale.h /usr/include/alloca.h
./obj/Framework/Button.o: /usr/include/string.h /usr/include/strings.h
./obj/Framework/Button.o: /usr/include/inttypes.h /usr/include/stdint.h
./obj/Framework/Button.o: /usr/include/bits/wchar.h /usr/include/ctype.h
./obj/Framework/Button.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
./obj/Framework/Button.o: /usr/include/SDL/close_code.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_audio.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_error.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_endian.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_mutex.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_thread.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_rwops.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_cdrom.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_cpuinfo.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_events.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_active.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_keyboard.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_keysym.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_mouse.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_video.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_joystick.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_quit.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_loadso.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_timer.h
./obj/Framework/Button.o: /usr/include/SDL/SDL_version.h
./obj/Framework/Button.o: ./Framework/Graphics.hpp /usr/include/SDL/SDL_ttf.h
./obj/Framework/Element.o: ./Framework/Element.hpp /usr/include/SDL/SDL.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_main.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_stdinc.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_config.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_config-i386.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_platform.h
./obj/Framework/Element.o: /usr/include/sys/types.h /usr/include/features.h
./obj/Framework/Element.o: /usr/include/sys/cdefs.h
./obj/Framework/Element.o: /usr/include/bits/wordsize.h
./obj/Framework/Element.o: /usr/include/gnu/stubs.h
./obj/Framework/Element.o: /usr/include/gnu/stubs-32.h
./obj/Framework/Element.o: /usr/include/bits/types.h
./obj/Framework/Element.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/Framework/Element.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/Framework/Element.o: /usr/include/sys/select.h
./obj/Framework/Element.o: /usr/include/bits/select.h
./obj/Framework/Element.o: /usr/include/bits/sigset.h
./obj/Framework/Element.o: /usr/include/bits/time.h
./obj/Framework/Element.o: /usr/include/sys/sysmacros.h
./obj/Framework/Element.o: /usr/include/bits/pthreadtypes.h
./obj/Framework/Element.o: /usr/include/stdio.h /usr/include/libio.h
./obj/Framework/Element.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/Framework/Element.o: /usr/include/bits/stdio_lim.h
./obj/Framework/Element.o: /usr/include/bits/sys_errlist.h
./obj/Framework/Element.o: /usr/include/stdlib.h
./obj/Framework/Element.o: /usr/include/bits/waitflags.h
./obj/Framework/Element.o: /usr/include/bits/waitstatus.h
./obj/Framework/Element.o: /usr/include/xlocale.h /usr/include/alloca.h
./obj/Framework/Element.o: /usr/include/string.h /usr/include/strings.h
./obj/Framework/Element.o: /usr/include/inttypes.h /usr/include/stdint.h
./obj/Framework/Element.o: /usr/include/bits/wchar.h /usr/include/ctype.h
./obj/Framework/Element.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
./obj/Framework/Element.o: /usr/include/SDL/close_code.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_audio.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_error.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_endian.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_mutex.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_thread.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_rwops.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_cdrom.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_cpuinfo.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_events.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_active.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_keyboard.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_keysym.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_mouse.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_video.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_joystick.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_quit.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_loadso.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_timer.h
./obj/Framework/Element.o: /usr/include/SDL/SDL_version.h
./obj/Framework/Graphics.o: /usr/include/math.h /usr/include/features.h
./obj/Framework/Graphics.o: /usr/include/sys/cdefs.h
./obj/Framework/Graphics.o: /usr/include/bits/wordsize.h
./obj/Framework/Graphics.o: /usr/include/gnu/stubs.h
./obj/Framework/Graphics.o: /usr/include/gnu/stubs-32.h
./obj/Framework/Graphics.o: /usr/include/bits/huge_val.h
./obj/Framework/Graphics.o: /usr/include/bits/huge_valf.h
./obj/Framework/Graphics.o: /usr/include/bits/huge_vall.h
./obj/Framework/Graphics.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
./obj/Framework/Graphics.o: /usr/include/bits/mathdef.h
./obj/Framework/Graphics.o: /usr/include/bits/mathcalls.h
./obj/Framework/Graphics.o: ./Framework/Graphics.hpp /usr/include/SDL/SDL.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_main.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_stdinc.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_config.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_config-i386.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_platform.h
./obj/Framework/Graphics.o: /usr/include/sys/types.h
./obj/Framework/Graphics.o: /usr/include/bits/types.h
./obj/Framework/Graphics.o: /usr/include/bits/typesizes.h /usr/include/time.h
./obj/Framework/Graphics.o: /usr/include/endian.h /usr/include/bits/endian.h
./obj/Framework/Graphics.o: /usr/include/sys/select.h
./obj/Framework/Graphics.o: /usr/include/bits/select.h
./obj/Framework/Graphics.o: /usr/include/bits/sigset.h
./obj/Framework/Graphics.o: /usr/include/bits/time.h
./obj/Framework/Graphics.o: /usr/include/sys/sysmacros.h
./obj/Framework/Graphics.o: /usr/include/bits/pthreadtypes.h
./obj/Framework/Graphics.o: /usr/include/stdio.h /usr/include/libio.h
./obj/Framework/Graphics.o: /usr/include/_G_config.h /usr/include/wchar.h
./obj/Framework/Graphics.o: /usr/include/bits/stdio_lim.h
./obj/Framework/Graphics.o: /usr/include/bits/sys_errlist.h
./obj/Framework/Graphics.o: /usr/include/stdlib.h
./obj/Framework/Graphics.o: /usr/include/bits/waitflags.h
./obj/Framework/Graphics.o: /usr/include/bits/waitstatus.h
./obj/Framework/Graphics.o: /usr/include/xlocale.h /usr/include/alloca.h
./obj/Framework/Graphics.o: /usr/include/string.h /usr/include/strings.h
./obj/Framework/Graphics.o: /usr/include/inttypes.h /usr/include/stdint.h
./obj/Framework/Graphics.o: /usr/include/bits/wchar.h /usr/include/ctype.h
./obj/Framework/Graphics.o: /usr/include/iconv.h
./obj/Framework/Graphics.o: /usr/include/SDL/begin_code.h
./obj/Framework/Graphics.o: /usr/include/SDL/close_code.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_audio.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_error.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_endian.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_mutex.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_thread.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_rwops.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_cdrom.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_cpuinfo.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_events.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_active.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_keyboard.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_keysym.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_mouse.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_video.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_joystick.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_quit.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_loadso.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_timer.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_version.h
./obj/Framework/Graphics.o: /usr/include/SDL/SDL_ttf.h
./obj/Framework/List.o: Framework/List.hpp
