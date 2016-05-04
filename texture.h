GLuint * texture;
unsigned int ntextures = 0;

void loadtextures(){
	char *texaddr[6] = {"textures/grass.bmp","textures/sand.bmp","textures/snow.bmp","textures/wheel.bmp","textures/tire.bmp","models/l200.bmp"};
	ntextures = 6;
	texture = new GLuint[ntextures];
	SDL_Surface * tex;
 	glGenTextures(ntextures,texture);
 	for(unsigned int i=0;i<ntextures;i++){
	 	tex = SDL_LoadBMP(texaddr[i]);
	 	if(tex==NULL){continue;}
  		tex = SDL_ConvertSurface(tex,&gl.sdlformatnoalpha,SDL_HWSURFACE);
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
