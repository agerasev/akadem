#define TOP		0x00
#define BOTTOM	0x01
#define LEFT	0x02
#define RIGHT	0x03
#define FRONT	0x04
#define BACK	0x05
#define PERSP	0x06

vect transform(vect a, Uint8 t){
	vect r;
	switch(t){
		case PERSP: return a;
		case TOP: r.x = a.x; r.y = a.y; return r;
		case RIGHT: r.x = a.y; r.y = a.z; return r;
		case BACK: r.x = a.x; r.y = a.z; return r;
		default: return r;
	}
}

vect retransform(vect a, Uint8 t){
	vect r;
	switch(t){
		case TOP: r.x = a.x; r.y = a.y; r.z = a.z; return r;
		case RIGHT: r.y = a.x; r.z = a.y; r.x = a.z; return r;
		case BACK: r.x = a.x; r.z = a.y; r.y = -a.z; return r;
		default: return r;
	}
}	

class viewport{
	public:
	bool redraw;
	int px,py,sx,sy;
	Uint8 type;
	vect crd,dir,top;
	float scal;
	int bg;
	float bgs,bgx,bgy;
	viewport(){
		type = 0x00;
		crd.set(0,0,0);
		scal = 1.0f;
		sx = 0; sy = 0;
		px = 0; py = 0;
		redraw = 1;
		
		bg = -1;
		bgs = 1.0f;
		bgx = 0.0f;
		bgy = 0.0f;
	}
	void position(int apx, int apy, int asx, int asy){
		px = apx; py = apy; sx = asx; sy = asy;
	}
	void settype(Uint8 atp){
		type = atp;
		switch(type){
			case PERSP: dir.set(0,M_SQRT1_2,-M_SQRT1_2); top.set(0,M_SQRT1_2,M_SQRT1_2); scal = 2.0f; break;
			case TOP: dir.set(0,0,-1); top.set(0,1,0); break;
			case RIGHT: dir.set(-1,0,0); top.set(0,0,1); break;
			case BACK: dir.set(0,1,0); top.set(0,0,1); break;
		}
	}
	void active(){
		if(!redraw){/*return;*/}
		else{redraw = 0;}
		glViewport(px,py,sx,sy);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if(type == PERSP){
			gluPerspective(60.0f,(float)sx/(float)sy,0.1f,128.0f);
			glEnable(GL_DEPTH_TEST);
		}
		else{
			vect d = transform(crd,type);
			gluOrtho2D(d.x-scal*sx/sy,d.x+scal*sx/sy,d.y-scal,d.y+scal);
			glDisable(GL_DEPTH_TEST);
		}
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		int grid = 2;
		if(type == PERSP){
			//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			gluLookAt(crd-dir*scal,crd,top);
			glBegin(GL_LINES);
			glColor3f(0.24f,0.24f,0.24f);
			for(int ix=-grid;ix<=grid;ix++){
				glVertex3f(ix,grid,0);
				glVertex3f(ix,-grid,0);
			}
			for(int iy=-grid;iy<=grid;iy++){
				glVertex3f(grid,iy,0);
				glVertex3f(-grid,iy,0);
			}
			glColor3f(0.32f,0.32f,0.32f);
			glVertex3f(0,2*grid,0);
			glVertex3f(0,-2*grid,0);
			glVertex3f(2*grid,0,0);
			glVertex3f(-2*grid,0,0);
			glEnd();
		}
		else{
			//glClear(GL_COLOR_BUFFER_BIT);
			if(bg>=0){
				glColor3f(1,1,1);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,texture[bg]);
				glBegin(GL_QUADS);
				glTexCoord2f(0,0);
				glVertex2f(bgx-bgs*stex[bg],bgy+bgs);
				glTexCoord2f(0,1);
				glVertex2f(bgx-bgs*stex[bg],bgy-bgs);
				glTexCoord2f(1,1);
				glVertex2f(bgx+bgs*stex[bg],bgy-bgs);
				glTexCoord2f(1,0);
				glVertex2f(bgx+bgs*stex[bg],bgy+bgs);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
			glBegin(GL_LINES);
			glColor3f(0.24f,0.24f,0.24f);
			for(int ix=-grid;ix<=grid;ix++){
				glVertex2f(ix,grid);
				glVertex2f(ix,-grid);
			}
			for(int iy=-grid;iy<=grid;iy++){
				glVertex2f(grid,iy);
				glVertex2f(-grid,iy);
			}
			glColor3f(0.32f,0.32f,0.32f);
			glVertex2f(0,2*grid);
			glVertex2f(0,-2*grid);
			glVertex2f(2*grid,0);
			glVertex2f(-2*grid,0);
			glEnd();
		}
	}
	void move(float ax, float ay){
		redraw = 1;
		vect d(wtos(ax),wtos(ay),0);
		if(type != PERSP){
			crd += retransform(d,type);
		}
		else{
			crd += d.x*(dir^top) + d.y*top;
		}	
	}
	//w - window, s - scene
	float wtos(float arg){
		return 2*arg*scal/sy;
	}
	float stow(float arg){
		return arg*sy/scal/2;
	}
};

viewport vp[4];
int curvp = 0;
