#define SDL_WHEEL_UP 	4
#define SDL_WHEEL_DOWN 	5

class input{
	private:
	
	SDL_Event event;
	Uint8 * key;
	
	int mx,my;
	float sens;
	
 	public:
	input(){
		sens = 0.002f;
	}
	
	void getevent(){
  		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){done = 1;}
			if(event.type == SDL_KEYDOWN){
				if(event.key.keysym.sym == SDLK_ESCAPE){done = 1;}
				if(event.key.keysym.sym == SDLK_F4){if(key[SDLK_LALT]){done = 1;}}
				if(event.key.keysym.sym == SDLK_LSHIFT){pause = !pause;}
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				if(event.button.button == SDL_WHEEL_UP){}
				if(event.button.button == SDL_WHEEL_DOWN){}
			}
		}
		
		//PRESS
		key = SDL_GetKeyState(NULL);
		//person
		//if(key[SDLK_w]){}//*(cam.pos)+=*(cam.dir)*0.04f;}
		//if(key[SDLK_a]){}//*(cam.pos)-=norm(*(cam.dir)^UP)*0.04f;}
		//if(key[SDLK_s]){}//*(cam.pos)-=*(cam.dir)*0.04f;}
		//if(key[SDLK_d]){}//*(cam.pos)+=norm(*(cam.dir)^UP)*0.04f;}
		//if(key[SDLK_SPACE]){}//*(cam.pos)+=UP*0.04f;}
		//if(key[SDLK_c]){}//*(cam.pos)-=UP*0.04f;}
		//vehicle
		float accdir = 0.0f, turnax = 0.0f;
		bool stopflag = 0;
		if(key[SDLK_w]){accdir += 32.0f;}
		if(key[SDLK_s]){accdir -= 32.0f;}
		if(key[SDLK_d]){turnax -= 0.6f;}
		if(key[SDLK_a]){turnax += 0.6f;}
		if(key[SDLK_SPACE]){stopflag = 1;}
		//if(key[SDLK_PAGEUP]){turnax.y -= 0.1f;}
		//if(key[SDLK_PAGEDOWN]){turnax.y += 0.1f;}
		mworld.cveh->stop(stopflag);
		mworld.cveh->accel(accdir);
		mworld.cveh->turn(turnax);
		return;
	}
	
	void getmousemotion(){
		int dx,dy;
		SDL_GetMouseState(&dx,&dy);
		dx-=gl.width/2; dy-=gl.height/2;
		if(dx!=0.0f){
			*(cam.dir) = rotate(*(cam.dir),-dx*sens,UP);
		}
		if(dy!=0.0f){
			vect si = norm(*(cam.dir)^UP);
			vect td = rotate(*(cam.dir),-dy*sens,si);
			if(si*(td^UP)>0.0f){*(cam.dir) = td;}
		}
		
		SDL_WarpMouse(gl.width/2,gl.height/2);
	}
};
