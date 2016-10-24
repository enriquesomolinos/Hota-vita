/*
 * Heart of The Alien: Renderer
 * Copyright (c) 2004 Gil Megidish
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include <string.h>
#include <SDL2/SDL.h>
#include "debug.h"
#include "render.h"
#include "game2bin.h"

#include "scale2x.h"
#include "scale3x.h"

#include <debugnet.h>
static int fullscreen = 0;
static int scroll_reg = 0;

extern int fullscreen_flag;
extern int filtered_flag;
extern int scale;
extern int palette_changed;
extern SDL_Color palette[256];
#if SDL_VERSION_ATLEAST(2, 0, 0)
	extern SDL_Window *_window;
	SDL_Renderer *_renderer;
	SDL_Texture *_texture;
	SDL_GameController *_controller;
#endif
	SDL_Surface *screen;
SDL_PixelFormat *_fmt;


int palette_changed = 0;
static int current_palette = 0;
 SDL_Color palette[256];

int get_current_palette()
{
	return current_palette;
}

/* set scroll register */
void set_scroll(int scroll)
{
	scroll_reg = scroll;
}

int get_scroll_register()
{
	return scroll_reg;
}

void render1x(char *src)
{
	
	
	int y, p;
	for (y=0; y<192; y++)
		{
			//SDL_RenderDrawPoint(_renderer, y, (int)(src + 304*y));
			memcpy((char *)screen->pixels + y*screen->pitch, src + 304*y, 304);
		}
	//SDL_RenderPresent(_renderer);
	/*if (scroll_reg == 0)
	{
		// no scroll 
		for (y=0; y<192; y++)
		{
			memcpy((char *)screen->pixels + y*screen->pitch, src + 304*y, 304);
		}
	}
	else if (scroll_reg < 0)
	{
		// scroll from bottom 
		p = 1 - scroll_reg;
		for (y=p; y<192; y++)
		{
			memcpy((char *)screen->pixels + (y-p)*screen->pitch, src + 304*y, 304);
		}

		for (y=192; y<192+p; y++)
		{
			memcpy((char *)screen->pixels + (y-p)*screen->pitch, src + 304*(y-192), 304);
		}
	}
	else 
	{
		// scroll from top 
		p = scroll_reg;
		for (y=0; y<p; y++)
		{
			memcpy((char *)screen->pixels + y*screen->pitch, src + 304*(191-p+y), 304);
		}

		for (y=p; y<192; y++)
		{
			memcpy((char *)screen->pixels + y*screen->pitch, src + 304*(y-p), 304);
		}
	}*/
}

/* advmame2x scaler */
void render2x_scaled(char *src)
{
	scale2x(screen, src, 304, 304, 192);
}

/* advmame3x scaler */
void render3x_scaled(char *src)
{
	scale3x(screen, src, 304, 304, 192);
}
/* simple x2 scaler */


void rendervita2x(char *src)
{
	//screen = SDL_GetWindowSurface(_window);
	int x, y;
	unsigned char wide[304*6];
	
        
	for (y=0; y<192; y++)
	{
		unsigned char *srcp, *widep;

		srcp = src + 304*y;
		widep = wide;
		for (x=0; x<304; x++)
		{
			*widep++ = *srcp;
			*widep++ = *srcp;
			*widep++ = *srcp;
			*widep++ = *srcp;
			*widep++ = *srcp;
			
			*widep++ = *srcp++;
		}

		memcpy((char *)screen->pixels + y*2*screen->pitch, wide, 304*6);
		memcpy((char *)screen->pixels + (y*2+1)*screen->pitch, wide, 304*6);
	}
}



void renderVita(char *src)
{
	//screen = SDL_GetWindowSurface(_window);
	int x, y;
	unsigned char wide[304*6];
	
        
	for (y=0; y<192; y++)
	{
		unsigned char *srcp, *widep;

		srcp = src + 304*y;
		widep = wide;
		for (x=0; x<304; x++)
		{
			*widep++ = *srcp;
			*widep++ = *srcp;
			*widep++ = *srcp;
			*widep++ = *srcp;
			*widep++ = *srcp;
			
			*widep++ = *srcp++;
		}

		memcpy((char *)screen->pixels + y*2*screen->pitch, wide, 304*6);
		memcpy((char *)screen->pixels + (y*2+1)*screen->pitch, wide, 304*6);
	}
}


/* simple x2 scaler */
void render2x(char *src)
{
	
	int x, y;
	unsigned char wide[304*2];
	
        
	for (y=0; y<192; y++)
	{
		unsigned char *srcp, *widep;

		srcp = src + 304*y;
		widep = wide;
		for (x=0; x<304; x++)
		{
			*widep++ = *srcp;
			*widep++ = *srcp++;
		}

		memcpy((char *)screen->pixels + y*2*screen->pitch, wide, 304*2);
		memcpy((char *)screen->pixels + (y*2+1)*screen->pitch, wide, 304*2);
	}
}

/* simple x3 scaler */
void render3x(char *src)
{
	
	int x, y;
	unsigned char wide[304*3];
        
	for (y=0; y<192; y++)
	{
		unsigned char *srcp, *widep;

		srcp = src + 304*y;
		widep = wide;
		for (x=0; x<304; x++)
		{
			*widep++ = *srcp;
			*widep++ = *srcp;
			*widep++ = *srcp++;
		}

		memcpy((char *)screen->pixels + y*3*screen->pitch, wide, 304*3);
		memcpy((char *)screen->pixels + (y*3+1)*screen->pitch, wide, 304*3);
		memcpy((char *)screen->pixels + (y*3+2)*screen->pitch, wide, 304*3);
	}
}

#include <debugnet.h>

/* render a virtual screen */
void render(unsigned char *src)
{
	
	//SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255 );
	// Clear the window and make it all red
//	SDL_RenderClear( _renderer );
	
	SDL_SetRenderDrawColor(_renderer,0, 0,255,255 );
	//SDL_RenderClear( _renderer );
	
	//TODO arreglar paletas
	if (palette_changed)
	{
		palette_changed = 0;
		//TODO arreglar 
		//SDL_SetColors(screen, palette, 0, 256);
		
		//SDL_Palette *sdlpalette = (SDL_Palette *)malloc(sizeof(SDL_Color)*256);
		//SDL_SetSurfacePalette(screen, sdlpalette);
		int i;
		/*for ( i=0; i<256; i++)
		{
			debugNetPrintf(DEBUG,"palette  %d %d %d\n",palette[i].r,palette[i].g,palette[i].b);
		}*/
		screen = SDL_GetWindowSurface(_window);
			SDL_SetPaletteColors(screen->format->palette, palette, 0, 256);
			SDL_SetSurfacePalette(screen, palette);
			debugNetPrintf(DEBUG,"palette  %s \n",SDL_GetError());
		
		
		//SDL_SetPalette(_window, SDL_LOGPAL, colors, 0, 256);
		//screen = SDL_GetWindowSurface(_window);
		
		
		
	/*	SDL_Texture *texture2 = SDL_CreateTextureFromSurface(_renderer, screen);
	SDL_RenderCopy(_renderer, texture2, NULL, NULL);*/
		//SDL_SetSurfacePalette(screen, sdlpalette);
		
	}
	
	
	scale=2;
	/*switch(scale)
	{
		case 1:
		
		render1x(src);
		break;

		case 2:
		if (filtered_flag == 0)
		{
			render2x(src);
		}
		else
		{
			render2x_scaled(src);
		}
		break;

		case 3:
		if (filtered_flag == 0)
		{
			render3x(src);
		}
		else
		{
			render3x_scaled(src);
		}
		break;
	}*/
	rendervita2x(src);

	scroll_reg = 0;
	//SDL_Texture *_texture = SDL_CreateTextureFromSurface(_renderer, screen);
	//static const uint32_t kPixelFormat = SDL_PIXELFORMAT_RGB565;
	//_texture = SDL_CreateTexture(_renderer, kPixelFormat, SDL_TEXTUREACCESS_STREAMING, 304, 192);
	SDL_UpdateTexture(_texture, 0, screen->pixels, screen->pitch);
	//SDL_UpdateWindowSurface(_window);

	SDL_RenderCopy(_renderer, _texture, 0, 0);
	SDL_RenderPresent(_renderer);
	//SDL_UnlockSurface(screen);
}

/* module initializer */
int render_init()
{
	return 0;
}

/* convert a Sega CD RGB444 to RGB888 */
void set_palette_rgb12(unsigned char *rgb12)
{
	int i;

	for (i=0; i<256; i++)
	{
		int c, r, g, b;

		c = (rgb12[i*2] << 8) | rgb12[i*2+1];
		r = (c & 0xf) << 4;
		g = ((c >> 4) & 0xf) << 4;
		b = ((c >> 8) & 0xf) << 4;
		
		palette[i].r = r;
		palette[i].g = g;
		palette[i].b = b;
		
		
	}

	palette_changed = 1;
}

void set_palette(int which)
{
	unsigned char rgb12[256*2];

	copy_from_game2bin(rgb12, 0x5cb8 + (which * 16 * 2), sizeof(rgb12));
	current_palette = which;
	set_palette_rgb12(rgb12);

	palette[255].r = 255;
	palette[255].g = 0;
	palette[255].b = 255;
}



int render_create_surface()
{
scale=3;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	#if SDL_VERSION_ATLEAST(2, 0, 0)
			debugNetPrintf(DEBUG,"_window");
			_window = SDL_CreateWindow("Heart of The Alien Redux PsVita", 
			//SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 304*scale, 192*scale, 0);
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 304*scale, 192*2, 0);
			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);
			 SDL_RenderSetLogicalSize(_renderer,304*scale, 192*2);
			//SDL_RenderSetLogicalSize(_renderer,  960*scale, 544*scale);
			//SDL_RenderSetLogicalSize(_renderer,  304*scale, 192*scale);
			screen = SDL_GetWindowSurface(_window);
			//_renderer = SDL_CreateSoftwareRenderer(screen);
			 
			// SDL_SetPaletteColors(screen->format->palette, palette, 0, 256);
debugNetPrintf(DEBUG,"screen");
			static const uint32_t kPixelFormat =  SDL_PIXELFORMAT_RGB565;
			_texture = SDL_CreateTexture(_renderer, kPixelFormat, SDL_TEXTUREACCESS_STREAMING, 304*scale, 192*2);
			//_fmt = SDL_AllocFormat(kPixelFormat);		
	#else
		screen = SDL_SetVideoMode(304*scale, 192*scale, 8, SDL_SWSURFACE);
		if (screen == NULL) 
		{
			return -1;
		}	
		SDL_WM_SetCaption("Heart of The Alien Redux", 0);
	#endif

	

	/*if (fullscreen_flag)
	{
		toggle_fullscreen();
	}*/

	return 0;
}
