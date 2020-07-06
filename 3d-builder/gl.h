class{
 public:
	int width,height;
	int pointsize,linewidth;
	void init(int w, int h){
		width = w; height = h;
		pointsize = 4; linewidth = 1;
 		if(SDL_SetVideoMode(w,h,32,SDL_OPENGL|SDL_HWACCEL|SDL_ASYNCBLIT|SDL_RESIZABLE) == NULL){
  			printf("%s\n%s","Unable to set video mode(opengl)",SDL_GetError());
  			exit(1);
 		}
		
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,6);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
		
		//ALPHA
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_BLEND);
		//glColor4f(1.0f,1.0f,1.0f,1.0f);
		//BASE
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClearDepth(1.0);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		//FACE TEST
		//glEnable(GL_CULL_FACE);
		glLoadIdentity();
		
		vp[0].settype(RIGHT);
		vp[0].position(0,h/2,w/2,h/2);
		
		vp[1].settype(BACK);
		vp[1].position(w/2,h/2,w/2,h/2);
		
		vp[2].settype(TOP);
		vp[2].position(0,0,w/2,h/2);
		
		vp[3].settype(PERSP);
		vp[3].position(w/2,0,w/2,h/2);
		
		glPointSize(pointsize);
		glLineWidth(linewidth);
	}

} gl;
