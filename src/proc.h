void * procParam;
Uint32 procCallback(Uint32 interval, void * param){
	if(!pause){
		mworld.tfreeze();
		mworld.grav();
		mworld.interact();
		mworld.frict();
		mworld.step();
	}
	return msec;
}

int lastsec=0,cursec=0;
void * secParam;
GLuint fpstex[2];
float fpsw[2],fpsh;
bool fpsredraw=0;
void initfps(){
 	SDL_Surface * tex;
 	glGenTextures(2,fpstex);
 	tex = mtxt.build("fps:",&fpsw[0],&fpsh);
	glBindTexture(GL_TEXTURE_2D, fpstex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);
	tex = mtxt.build(numstr(lastsec),&fpsw[1],&fpsh);
	glBindTexture(GL_TEXTURE_2D, fpstex[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);
}
Uint32 secCallback(Uint32 interval, void * param){
	lastsec = cursec;
	cursec = 0;
	fpsredraw=1;
	return interval;
}
void drawfps(){
	if(fpsredraw){
		glDeleteTextures(1,&fpstex[1]);
		glGenTextures(1,&fpstex[1]);
		SDL_Surface * tex;
		tex = mtxt.build(numstr(lastsec),&fpsw[1],&fpsh);
		glBindTexture(GL_TEXTURE_2D, fpstex[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);
		fpsredraw = 0;
	}
	
	glColor3f(1.0f,1.0f,1.0f);
	glBindTexture(GL_TEXTURE_2D, fpstex[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-gl.xscale/2,gl.yscale/2,-1);
	glTexCoord2f(0,1);
	glVertex3f(-gl.xscale/2,gl.yscale/2-fpsh,-1);
	glTexCoord2f(1,1);
	glVertex3f(-gl.xscale/2+fpsw[0],gl.yscale/2-fpsh,-1);
	glTexCoord2f(1,0);
	glVertex3f(-gl.xscale/2+fpsw[0],gl.yscale/2,-1);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, fpstex[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-gl.xscale/2+fpsw[0],gl.yscale/2,-1);
	glTexCoord2f(0,1);
	glVertex3f(-gl.xscale/2+fpsw[0],gl.yscale/2-fpsh,-1);
	glTexCoord2f(1,1);
	glVertex3f(-gl.xscale/2+fpsw[0]+fpsw[1],gl.yscale/2-fpsh,-1);
	glTexCoord2f(1,0);
	glVertex3f(-gl.xscale/2+fpsw[0]+fpsw[1],gl.yscale/2,-1);
	glEnd();
	cursec++;
}
