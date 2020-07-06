#define SDL_WHEEL_UP 	4
#define SDL_WHEEL_DOWN 	5

class input{
	public:
	
	SDL_Event event;
	Uint8 * key;
	
	int cx,cy;//click
	int dx,dy;//deviation
	int lx,ly;//last
	int mx,my;//current mouse
	int scr;//scroll
	bool rmb,lmb,mmb;//mouse buttons down
	bool rcd,lcd,mcd;//mouse click down
	bool rcu,lcu,mcu;//mouse click up
	
	bool alt,ctrl,shift,space,del;//keyboard buttons down
	bool v,l,m,n,t,d,f,h;
	bool bl,bm;
	bool tlbp,cf;
 	
	input(){
		scr = 0;
		mx = 0; my = 0;
		rmb = 0; lmb = 0; mmb = 0;
		rcd = 0; lcd = 0; mcd = 0;
		rcu = 0; lcu = 0; mcu = 0;
		alt = 0; ctrl = 0; shift = 0; space = 0;
		v=0;l=0;m=0;t=0;
		bl=0;bm=0;del=0;
		tlbp=0;cf=0;
	}
	
	void getevent(){
		rcd = 0; lcd = 0; mcd = 0;
		rcu = 0; lcu = 0; mcu = 0;
		bl = 0; bm = 0;
  		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){done = 1;}
			if(event.type == SDL_KEYDOWN){
				if(event.key.keysym.sym == SDLK_ESCAPE){done = 1;}
				if(event.key.keysym.sym == SDLK_F4){if(key[SDLK_LALT]){done = 1;}}
				
				if(event.key.keysym.sym == SDLK_v){if(key[SDLK_LALT]){v = 1;}}
				if(event.key.keysym.sym == SDLK_q){if(key[SDLK_LALT]){l = 1;}if(key[SDLK_LCTRL]){bl = 1;}}
				if(event.key.keysym.sym == SDLK_w){if(key[SDLK_LALT]){m = 1;}if(key[SDLK_LCTRL]){bm = 1;}}
				if(event.key.keysym.sym == SDLK_t){if(key[SDLK_LCTRL]){t = 1;}}
				if(event.key.keysym.sym == SDLK_f){if(key[SDLK_LCTRL]){f = 1;}}
				if(event.key.keysym.sym == SDLK_h){if(key[SDLK_LCTRL]){h = 1;}}
				if(event.key.keysym.sym == SDLK_c){if(key[SDLK_LALT]){if(cf){glDisable(GL_CULL_FACE);cf=0;}else{glEnable(GL_CULL_FACE);cf=1;}}}
				if(event.key.keysym.sym == SDLK_DELETE){del = 1;}
				
				if(event.key.keysym.sym == SDLK_s){if(key[SDLK_LCTRL]){savescene();}}
				if(event.key.keysym.sym == SDLK_o){if(key[SDLK_LCTRL]){openscene();}}
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				if(event.button.button == SDL_BUTTON_LEFT){
					if(key[SDLK_t]){tlbp=1;}
					else{lmb=1;lcd=1;cx=mx;cy=my;}
				}
				if(event.button.button == SDL_BUTTON_RIGHT){
					if(key[SDLK_t]){vp[curvp].bg++;if(vp[curvp].bg>=ntextures){vp[curvp].bg=0;}}
					else{rmb=1;rcd=1;cx=mx;cy=my;}
				}
				if(event.button.button == SDL_BUTTON_MIDDLE){mmb=1;mcd=1;cx=mx;cy=my;}
				if(event.button.button == SDL_WHEEL_UP){if(key[SDLK_t]){vp[curvp].bgs*=1.06f;}else{scr+=1;}}
				if(event.button.button == SDL_WHEEL_DOWN){if(key[SDLK_t]){vp[curvp].bgs/=1.06f;}else{scr-=1;}}
			}
			if(event.type == SDL_MOUSEBUTTONUP){
				if(event.button.button == SDL_BUTTON_LEFT){tlbp=0;lmb=0;lcu=1;}
				if(event.button.button == SDL_BUTTON_RIGHT){rmb=0;rcu=1;}
				if(event.button.button == SDL_BUTTON_MIDDLE){mmb=0;mcu=1;}
			}
			if(event.type == SDL_VIDEORESIZE){
				removetextures();
				gl.init(event.resize.w,event.resize.h);
				loadtextures();
			}
		}
		
		if(tlbp&&key[SDLK_t]){vp[curvp].bgx+=vp[curvp].wtos(-dx);vp[curvp].bgy+=vp[curvp].wtos(-dy);}
		
		//PRESS
		alt = 0; ctrl = 0; shift = 0; space = 0;
		key = SDL_GetKeyState(NULL);
		if(key[SDLK_LALT]){alt = 1;}
		if(key[SDLK_SPACE]){space = 1;}
		if(key[SDLK_LCTRL]){ctrl = 1;}
		if(key[SDLK_LSHIFT]){shift = 1;}
		return;
	}
	
	void getmousemotion(){
		lx = mx; ly = my;
		SDL_GetMouseState(&mx,&my);
		my = gl.height-my;
		dx = lx-mx; dy = ly-my;
	}
	
} inp;
