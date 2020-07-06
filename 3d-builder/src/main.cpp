#include<stdlib.h>
#include<SDL/SDL.h>
#include<math.h>
#include<iostream>
#include<fstream>
#include"vect.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include"glredef.h"
#include"tools.h"
#include"texture.h"
#include"viewport.h"
#include"gl.h"
bool done = false;
#include"data.h"
#include"files.h"
#include"input.h"
#include"interface.h"

int main(int argc, char * argv[]){
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0){
  			printf("%s: %s","Unable to init SDL",SDL_GetError());
  			exit(1);
 		}
 	atexit(SDL_Quit);
 	
 	SDL_ShowCursor(1);
 	
 	gl.init(800,600);
 	loadtextures();
 	vpinterface.regime = VERTEX;
 	
 	//glEnable(GL_LIGHT0);
 	//float lamb[4] = {0.8f,0.8f,0.8f,1.0f};
 	//float ldif[4] = {1.0f,1.0f,1.0f,1.0f};
 	//float lpos[4] = {0.0f,M_SQRT1_2,M_SQRT1_2,0.0f};
 	//glLightfv(GL_LIGHT0,GL_AMBIENT,lamb);
 	//glLightfv(GL_LIGHT0,GL_DIFFUSE,ldif);
 	//glLightfv(GL_LIGHT0,GL_POSITION,lpos);
 	
 	while(!done){
		inp.getevent();
		inp.getmousemotion();
		vpinterface.mousetest();
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		for(int i=0;i<4;i++){
			vp[i].active();
			
			if(vp[i].type!=PERSP){
				glBegin(GL_LINES);
				glColor3f(0,0.32f,0);
				for(int j=0;j<4;j++){
					if(vp[j].type!=vp[i].type&&vp[j].type!=PERSP){
						switch(vp[i].type){
							case TOP:
								if(vp[j].type==RIGHT){glVertex2f(vp[j].crd.x,4.0f);glVertex2f(vp[j].crd.x,-4.0f);}
								if(vp[j].type==BACK){glVertex2f(4.0f,vp[j].crd.y);glVertex2f(-4.0f,vp[j].crd.y);}
								break;
							case RIGHT:
								if(vp[j].type==TOP){glVertex2f(4.0f,vp[j].crd.z);glVertex2f(-4.0f,vp[j].crd.z);}
								if(vp[j].type==BACK){glVertex2f(vp[j].crd.y,4.0f);glVertex2f(vp[j].crd.y,-4.0f);}
								break;
							case BACK:
								if(vp[j].type==RIGHT){glVertex2f(vp[j].crd.x,4.0f);glVertex2f(vp[j].crd.x,-4.0f);}
								if(vp[j].type==TOP){glVertex2f(4.0f,vp[j].crd.z);glVertex2f(-4.0f,vp[j].crd.z);}
								break;
						}
					}
				}
				glEnd();
			}
			
			draw(vp[i].type);
		}
		
		glLoadIdentity();
		vpinterface.active();
		vpinterface.draw();
		
		glFlush();
  		SDL_GL_SwapBuffers();
  		SDL_Delay(4);
	}
	removeall();
	removetextures();
 	exit(1);
 	return 0;
}
