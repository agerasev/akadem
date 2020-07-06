GLuint * texture;
unsigned int ntextures = 0;
float * stex;

void loadtextures(){
	char *texaddr[1] = {"textures/in.bmp"};
	//{"textures/base/1.bmp","textures/base/3.bmp","textures/base/5.bmp","textures/base/7.bmp"};
	ntextures = 1;
	texture = new GLuint[ntextures];
	stex = new float[ntextures];
	SDL_Surface * tex;
 	glGenTextures(ntextures,texture);
 	for(unsigned int i=0;i<ntextures;i++){
	 	tex = SDL_LoadBMP(texaddr[i]);
	 	if(tex==NULL){continue;}
  		tex = SDL_ConvertSurface(tex,SDL_CreateRGBSurface(SDL_HWSURFACE,0,0,24,0x000000ff,0x0000ff00,0x00ff0000,0x00000000)->format,SDL_HWSURFACE);
		stex[i] = (float)tex->w/tex->h;
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D,3,tex->w,tex->h,GL_RGB,GL_UNSIGNED_BYTE,tex->pixels);
	}
}

void removetextures(){
	glDeleteTextures(ntextures,texture);
	ntextures = 0;
}
