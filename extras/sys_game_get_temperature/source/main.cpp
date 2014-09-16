#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <lv2_syscall.h>

//"UI"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <io/pad.h>

void patch_proc_checks()
{
	//unicorns (4.46)
	//lv2_lv1_poke(0x7203A8, 0x3860000138210080ULL);
	//disable product mode check (4.46)
	//lv2_lv1_poke(0x720670, 0x2F3E000060000000ULL);
	//lv2_lv1_poke(0x720680, 0x7FA3EB7860000000ULL);
	//disable auth check (4.46)
	lv2_lv1_poke(0x16fb64, 0x2f80000048000050ULL);
}

int main()
{
	int res = 0;
	uint32_t cell_temp = 0,rsx_temp = 0;
		
	patch_proc_checks();
	
	padInfo2 joypadInfo;
	padData joypadData;
	ioPadInit(1);
	
	SDL_Init( SDL_INIT_VIDEO );
	SDL_Surface * screen = SDL_SetVideoMode(1280, 720, 32, SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	
	SDL_Color colorGreen = { 0, 255, 0 };
	
	char cputemp[256],rsxtemp[256];
	
	memset(cputemp, 0, sizeof(char)*256);
	memset(rsxtemp, 0, sizeof(char)*256);
	
	TTF_Init();
	TTF_Font * font = TTF_OpenFont("/dev_flash/data/font/SCE-PS3-RD-L-LATIN2.TTF", 24);
	TTF_Font * tFont = TTF_OpenFont("/dev_flash/data/font/SCE-PS3-RD-L-LATIN2.TTF", 36);
	
	SDL_Surface * helptxtSurface = TTF_RenderText_Solid(font, "Press START to quit.", colorGreen);
	SDL_Surface * cputxtSurface = NULL;
	SDL_Surface * rsxtxtSurface = NULL;
	
	SDL_Rect helptxtRect = { 100, 100, 500, 25 };
	SDL_Rect cputRect = { 200, 300, 1080, 420 };
	SDL_Rect rsxtRect = { 200, 400, 1080, 320 };
	
	SDL_BlitSurface(helptxtSurface, NULL, screen, &helptxtRect);
	
	bool loop = true;
	while(loop)
	{
		SDL_FillRect(screen, &cputRect, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_FillRect(screen, &rsxtRect, SDL_MapRGB(screen->format, 0, 0, 0));
		
		res = sys_game_get_temperature(0, &cell_temp);
		if(!res)
			sprintf(cputemp, "Cell Temp: %d °C", (cell_temp>>24));
		else
			sprintf(cputemp, "Cell Temp: error 0x%x", res);
			
		cputxtSurface = TTF_RenderText_Solid(tFont, cputemp, colorGreen);
		SDL_BlitSurface(cputxtSurface, NULL, screen, &cputRect);
		
		res = sys_game_get_temperature(1, &rsx_temp);
		if(!res)
			sprintf(rsxtemp, "RSX Temp: %d °C", (rsx_temp>>24));
		else
			sprintf(rsxtemp, "RSX Temp: error 0x%x", res);
			
		rsxtxtSurface = TTF_RenderText_Solid(tFont, rsxtemp, colorGreen);
		SDL_BlitSurface(rsxtxtSurface, NULL, screen, &rsxtRect);
		
		ioPadGetInfo2(&joypadInfo);
		if(joypadInfo.port_status[0])
		{
			ioPadGetData(0, &joypadData);
			if( joypadData.BTN_START )
			{
				loop = false;
			}
		}
		
		SDL_Flip(screen);
		
	}
	
	
	TTF_Quit();
	SDL_FreeSurface(helptxtSurface);
	SDL_FreeSurface(cputxtSurface);
	SDL_FreeSurface(rsxtxtSurface);
	SDL_FreeSurface(screen);
	SDL_Quit();
	
	return 0;
}

