#include<stdlib.h>
#include<fstream>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>

Uint32 msec = 12;
float sec = (float)msec/1000.0f;

#include<math.h>

#include"vect.h"

#include"physics.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include"gl.h"
#include"text.h"

text mtxt;
bool done = false;

#include"texture.h"
#include"model.h"
#include"material.h"
material met,bum;
#include"light.h"
light sun;
#include"camera.h"
#include"world.h"
camera cam;
world mworld;

bool pause = 0;
#include"proc.h"
#include"input.h"
input minp;

int main(int argc, char * argv[]){
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0){
  			printf("Unable to init SDL: %s\n", SDL_GetError());
  			exit(1);
 		}
 	atexit(SDL_Quit);
 	
 	if(TTF_Init() < 0) {
  		printf("Unable to init TTF: %s\n", TTF_GetError());
  		exit(1);
	}
 	
 	SDL_ShowCursor(0);
 	
 	gl.init(1600,900,0);
 	
 	mtxt.setfont("fonts/segoeui.ttf",24);
 	mtxt.setcolor(0xff,0xff,0x00);
 	
 	initfps();
 	
 	loadtextures();
 	loadmodel();
 	
 	met.setdif(0.8,0.8,0.8);
	met.setamb(0.2,0.2,0.2);
	met.setspec(0.4,0.4,0.4);
	met.setshin(12);
	bum.setdif(1,1,1);
	bum.setamb(1,1,1);
	bum.setspec(0,0,0);
	bum.setshin(0);
 	
 	sun.setid(GL_LIGHT0);
 	sun.enable();
 	sun.setposition(1/sqrt(3),1/sqrt(3),1/sqrt(3),0.0f);
 	sun.setambient(2.0f,2.0f,2.0f);
 	sun.setdiffuse(1.0f,1.0f,1.0f);
 	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,true);
 	
 	//cam.create();
 	mworld.init();
 	cam.attract(mworld.cveh->cfp);
 	
 	SDL_TimerID proc = SDL_AddTimer(msec,procCallback,procParam);
 	SDL_TimerID second = SDL_AddTimer(1000,secCallback,secParam);
 	
 	while(!done){
		minp.getevent();
		minp.getmousemotion();
		glEnable(GL_LIGHTING);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		mworld.cfreeze();
		cam.put();
		//sun.setposition(*(cam.pos),1.0f);
		sun.put();
		
		mworld.draw();
		
		glDisable(GL_LIGHTING);
		glClear(GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		drawfps();
		glFlush();
  		SDL_GL_SwapBuffers();
	}
	SDL_RemoveTimer(second);
 	SDL_RemoveTimer(proc);
 	SDL_Delay(msec);
 	mworld.remove();
 	removetextures();
 	exit(1);
 	return 0;
}
