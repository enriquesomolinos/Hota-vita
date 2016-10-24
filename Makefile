TITLE_ID= SOMO00003
TARGET = HOA
PSVITAIP=192.168.0.199

INCDIR = -I/local/vitasdk/$(PREFIX)/include/vita2d  -I/local/vitasdk/$(PREFIX)/include/SDL2 -I/local/vitasdk/$(PREFIX)/include/SDL2_mixer 


PREFIX   = arm-vita-eabi
CC       = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
SDL_CFLAGS = `sdl-config --cflags`
SDL_LIBS = `sdl-config --libs`
CFLAGS   =  $(INCDIR)   -Wl,-q -Wall -O3  -Wno-unused-variable -Wno-unused-function  -Wno-unused-but-set-variable -Wno-pointer-sign -DPSVITA

SRCS =\
	common.c vm.c sprites.c decode.c animation.c rooms.c \
	render.c main.c music.c debug.c lzss.c cd_iso.c sound.c \
	screen.c scale2x.c scale3x.c game2bin.c
	
OBJS = $(SRCS:.c=.o)

LIBS2=$(SDL_LIBS) -lSDLmain -lsmpeg -lSDL_mixer


LIBS +=   -ldebugnet  -lSceNetCtl_stub -lSceNet_stub -lSceSysmodule_stub  -lSDL2 -lSDL2_mixer -lvita2d  \
	     -lSceKernel_stub -lSceGxm_stub -lSceDisplay_stub -lSceCtrl_stub -lSceAudio_stub \
		 -lSceSysmodule_stub -lScePgf_stub -lSceCommonDialog_stub \
		 -lScePower_stub -lfreetype -lpng -ljpeg -lz -lm -lc 





all: $(TARGET).vpk

%.vpk: eboot.bin
	vita-mksfoex  -s TITLE_ID=$(TITLE_ID) "$(TARGET)" param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin \
		--add pkg/sce_sys/icon0.png=sce_sys/icon0.png \
		--add pkg/sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png \
		--add pkg/sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png \
		--add pkg/sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml \
	$(TARGET).vpk
	
eboot.bin: $(TARGET).velf
	vita-make-fself -s $< $@
	
%.velf: %.elf	
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS)  $^ $(LIBS) -o $@



	
vpksend: $(TARGET).vpk
	curl -T $(TARGET).vpk ftp://$(PSVITAIP):1337/ux0:/
	@echo "Sent."
send: eboot.bin
	curl -T eboot.bin ftp://$(PSVITAIP):1337/ux0:/app/$(TITLE_ID)/
	@echo "Sent."
clean:    
	@rm -rf *.velf *.elf *.vpk eboot.bin param.sfo *.o
