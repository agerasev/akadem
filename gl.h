class{
 public:
	int width,height;
	bool fullscreen;
	float visangle,pixel;
	float xscale,yscale;
	SDL_PixelFormat sdlformat,sdlformatnoalpha;
	void init(int w, int h, bool fs){
		width = w;
		height = h;
		fullscreen = fs;
		visangle = 60.0f;
		pixel = 2.0f*tan(visangle*M_PI/360.0f)/height;
		xscale = pixel*width; yscale = pixel*height;
		
		sdlformat = *SDL_CreateRGBSurface(SDL_HWSURFACE,0,0,0x20,0x000000ff,0x0000ff00,0x00ff0000,0xff000000)->format;
		sdlformatnoalpha = *SDL_CreateRGBSurface(SDL_HWSURFACE,0,0,24,0x000000ff,0x0000ff00,0x00ff0000,0x00000000)->format;
		
 		if(SDL_SetVideoMode(w,h,32,SDL_OPENGL|SDL_HWACCEL|SDL_ASYNCBLIT|(SDL_FULLSCREEN)*fullscreen) == NULL){
  			printf("%s\n%s","Unable to set video mode(opengl)",SDL_GetError());
  			exit(1);
 		}
		
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5); 
		
		//glEnable(GL_CULL_FACE);
		//ALPHA
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		//TEXTURE
		glEnable(GL_TEXTURE_2D);
		//LIGHTING
		glEnable(GL_LIGHTING);
		float glma[4] = {0.0f,0.0f,0.0f,1.0f};
 		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,glma);
		//BASE
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClearDepth(1.0);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(visangle,(float)w/(float)h,0.1f,1024.0f);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		//ADDING
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		//glShadeModel(GL_SMOOTH);
	}

} gl;

//REDEFINING
void glVertexv(vect v){
	glVertex3f(v.x,v.y,v.z);
}

void glTexCoordv(vect v){
	glTexCoord2f(v.x,v.y);
}

void glNormalv(vect n){
	 glNormal3f(n.x,n.y,n.z);
}

void gluLookAt(vect ac, vect ad, vect au){
	gluLookAt(ac.x,ac.y,ac.z,ad.x,ad.y,ad.z,au.x,au.y,au.z);
}
