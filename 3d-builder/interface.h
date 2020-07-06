#define VERTEX	0x01
#define LINE	0x02
#define MESH	0x03

/*class button{
	
};*/

class{
	public:
	Uint8 regime;
	bool drag;
	void mousetest(){
		//SELECT VIEWPORT
		for(int i=0;i<4;i++){
			if(!inp.lmb&&!inp.rmb&&!inp.mmb){
				if(insidetest(vp[i].px,vp[i].py,vp[i].px+vp[i].sx,vp[i].py+vp[i].sy,inp.mx,inp.my)){curvp = i; break;}
			}
		}
		//FIXING && HIDING
		if(inp.f){
			if(regime==VERTEX){
				for(int i=0;i<np;i++){
					if(!inp.shift&&p[i].act){p[i].fix=1;p[i].act=0;}
					if(inp.shift){p[i].fix=0;}
				}
			}
			if(regime==LINE){
				for(int i=0;i<nl;i++){
					if(!inp.shift&&l[i].act){l[i].fix=1;l[i].act=0;}
					if(inp.shift){l[i].fix=0;}
				}
			}
			if(regime==MESH){
				for(int i=0;i<nm;i++){
					if(!inp.shift&&m[i].act){m[i].fix=1;m[i].act=0;}
					if(inp.shift){m[i].fix=0;}
				}
			}
			inp.f = 0;
		}
		if(inp.h){
			if(regime==VERTEX){
				for(int i=0;i<np;i++){
					if(!inp.shift&&p[i].act){p[i].vis=0;p[i].act=0;}
					if(inp.shift){p[i].vis=1;}
				}
			}
			if(regime==LINE){
				for(int i=0;i<nl;i++){
					if(!inp.shift&&l[i].act){l[i].vis=0;l[i].act=0;}
					if(inp.shift){l[i].vis=1;}
				}
			}
			if(regime==MESH){
				for(int i=0;i<nm;i++){
					if(!inp.shift&&m[i].act){m[i].vis=0;m[i].act=0;}
					if(inp.shift){m[i].vis=1;}
				}
			}
			inp.h = 0;
		}
		//SELECT VERTEXES
		if(regime==VERTEX){
			if(inp.lcu&&!inp.shift&&!drag){
				if(vp[curvp].type!=PERSP){
					if(mod(inp.cx-inp.mx)<=gl.pointsize/2&&mod(inp.cy-inp.my)<=gl.pointsize/2){
						vect d(vp[curvp].wtos(inp.mx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.my-vp[curvp].py-vp[curvp].sy/2.0f),0);
						float ps = vp[curvp].wtos(gl.pointsize+4);
						for(int i=0;i<np;i++){
							if(p[i].fix||!p[i].vis){continue;}
							vect tr = transform(p[i].c-vp[curvp].crd,vp[curvp].type);
							if(insidetest(tr.x-ps/2,tr.y-ps/2,ps,ps,d.x,d.y)){
								if(!inp.alt){p[i].act = 1;}
								else{p[i].act = 0;}
							}
							else{
								if(!inp.ctrl&&!inp.alt){p[i].act = 0;}
							}
						}
					}
					else{
						vect d1(vp[curvp].wtos(inp.mx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.my-vp[curvp].py-vp[curvp].sy/2.0f),0);
						vect d0(vp[curvp].wtos(inp.cx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.cy-vp[curvp].py-vp[curvp].sy/2.0f),0);
						for(int i=0;i<np;i++){
							if(p[i].fix||!p[i].vis){continue;}
							//printf("before_chosing\n");
							vect tr = transform(p[i].c-vp[curvp].crd,vp[curvp].type);
							//printf("after_chosing\n\n");
							if(insidetest(d0.x,d0.y,d1.x-d0.x,d1.y-d0.y,tr.x,tr.y)){
								if(!inp.alt){p[i].act = 1;}
								else{p[i].act = 0;}
							}
							else{
								if(!inp.ctrl&&!inp.alt){p[i].act = 0;}
							}
						}
					}
				}
			}
		}
		//SELECT LINES
		if(regime==LINE){
			if(inp.lcu&&!inp.shift&&!drag){
				if(vp[curvp].type!=PERSP){
					vect d1(vp[curvp].wtos(inp.mx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.my-vp[curvp].py-vp[curvp].sy/2.0f),0);
					vect d0(vp[curvp].wtos(inp.cx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.cy-vp[curvp].py-vp[curvp].sy/2.0f),0);
					for(int i=0;i<np;i++){
						if(p[i].fix||!p[i].vis){continue;}
						//printf("before_chosing\n");
						vect tr = transform(p[i].c-vp[curvp].crd,vp[curvp].type);
						//printf("after_chosing\n\n");
						if(insidetest(d0.x,d0.y,d1.x-d0.x,d1.y-d0.y,tr.x,tr.y)){
							if(!inp.alt){p[i].act = 1;}
							else{p[i].act = 0;}
						}
						else{
							if(!inp.ctrl&&!inp.alt){p[i].act = 0;}
						}
					}
					for(int i=0;i<nl;i++){
						if(l[i].fix||!l[i].vis){continue;}
						if(p[l[i].p[0]].act&&p[l[i].p[1]].act){l[i].act=1;}
						else{l[i].act=0;}
					}
				}
			}
		}
		//SELECT MESHES
		if(regime==MESH){
			if(inp.lcu&&!inp.shift&&!drag){
				if(vp[curvp].type!=PERSP){
					vect d1(vp[curvp].wtos(inp.mx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.my-vp[curvp].py-vp[curvp].sy/2.0f),0);
					vect d0(vp[curvp].wtos(inp.cx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.cy-vp[curvp].py-vp[curvp].sy/2.0f),0);
					for(int i=0;i<np;i++){
						if(p[i].fix||!p[i].vis){continue;}
						//printf("before_chosing\n");
						vect tr = transform(p[i].c-vp[curvp].crd,vp[curvp].type);
						//printf("after_chosing\n\n");
						if(insidetest(d0.x,d0.y,d1.x-d0.x,d1.y-d0.y,tr.x,tr.y)){
							if(!inp.alt){p[i].act = 1;}
							else{p[i].act = 0;}
						}
						else{
							if(!inp.ctrl&&!inp.alt){p[i].act = 0;}
						}
					}
					for(int i=0;i<nm;i++){
						if(m[i].fix||!m[i].vis){continue;}
						if(p[m[i].p[0]].act&&p[m[i].p[1]].act&&p[m[i].p[2]].act){m[i].act=1;}
						else{m[i].act=0;}
					}
				}
			}
		}
		if(inp.shift){drag=1;}
		if(!inp.shift&&!inp.lmb){drag=0;}
		if(inp.lcu){drag=0;}
		//SCROLL AND ZOOM
		if(inp.scr){
			if(!inp.rmb){
				if(inp.scr>0){vp[curvp].scal/=1.2f;inp.scr=0;}
				else{vp[curvp].scal*=1.2f;inp.scr=0;}
			}
			else{
				if(inp.scr>0){vp[curvp].crd += 0.1f*vp[curvp].dir; inp.scr=0;}
				else{vp[curvp].crd -= 0.1f*vp[curvp].dir; inp.scr=0;}
			}
		}
		//DRAGGING VERTEXES
		if(regime==VERTEX&&inp.lcd&&!inp.shift){
			if(vp[curvp].type!=PERSP){
				if(mod(inp.cx-inp.mx)<=gl.pointsize/2&&mod(inp.cy-inp.my)<=gl.pointsize/2){
					vect d(vp[curvp].wtos(inp.mx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.my-vp[curvp].py-vp[curvp].sy/2.0f),0);
					float ps = vp[curvp].wtos(gl.pointsize+4);
					int in = 0;
					for(int i=0;i<np;i++){
						vect tr = transform(p[i].c-vp[curvp].crd,vp[curvp].type);
						if(insidetest(tr.x-ps/2,tr.y-ps/2,ps,ps,d.x,d.y)){
							if(p[i].act){in++;}
						}
					}
					if(in){drag = 1;}
				}
			}
		}
		if(regime==VERTEX&&drag&&inp.lmb){
			vect d(vp[curvp].wtos(inp.dx),vp[curvp].wtos(inp.dy),0);
			d = retransform(d,vp[curvp].type);
			for(int i=0;i<np;i++){
				if(p[i].act){
					p[i].c -= d;
				}
			}
		}
		//ADDING VERTEXES
		if(regime==VERTEX){
			if(inp.mcd&&vp[curvp].type!=PERSP){
				//vect f = vp[curvp].crd;//lots of laugh! add/remove this useless string and find a problem xDDD
				vect d(vp[curvp].wtos(inp.mx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.my-vp[curvp].py-vp[curvp].sy/2.0f),0);
				//printf("before_adding\n");
				addpoint(retransform(d,vp[curvp].type)+vp[curvp].crd);
				//printf("after_adding\n\n");
			}
		}
		//ADDING LINES
		if(regime==LINE){
			if(inp.mcu&&vp[curvp].type!=PERSP){
				vect d1(vp[curvp].wtos(inp.mx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.my-vp[curvp].py-vp[curvp].sy/2.0f),0);
				vect d0(vp[curvp].wtos(inp.cx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.cy-vp[curvp].py-vp[curvp].sy/2.0f),0);
				float ps = vp[curvp].wtos(gl.pointsize+4);
				int p0=-1,p1=-1;
				for(int i=0;i<np;i++){
					if(p[i].fix||!p[i].vis){continue;}
					//printf("before_line_transform\n");
					vect tr = transform(p[i].c-vp[curvp].crd,vp[curvp].type);
					//printf("after_line_transform\n");
					if(insidetest(tr.x-ps/2,tr.y-ps/2,ps,ps,d0.x,d0.y)){
						p0 = i;
					}
					if(insidetest(tr.x-ps/2,tr.y-ps/2,ps,ps,d1.x,d1.y)){
						p1 = i;
					}
					if(p0>=0&&p1>=0){break;}
				}
				if(p1!=p0&&p0>=0&&p1>=0){
					//printf("before_line_adding\n");
					addline(p0,p1);
					//printf("after_line_adding\n\n");
				}
			}
		}
		if(regime==VERTEX&&inp.bl){
			int p0=-1,p1=-1;
			for(int i=0;i<np;i++){
				if(p0<0){if(p[i].act){p0=i;continue;}}
				if(p1<0){if(p[i].act){p1=i;break;}}
			}
			if(p1!=p0&&p0>=0&&p1>=0){
				//printf("before_line_adding\n");
				addline(p0,p1);
				//printf("after_line_adding\n\n");
			}
			inp.bl = 0;
		}
		//ADDING MESHES
		if(regime==VERTEX&&inp.bm){
			int p0=-1,p1=-1,p2=-1;
			for(int i=0;i<np;i++){
				if(p0<0){if(p[i].act){p0=i;continue;}}
				if(p1<0){if(p[i].act){p1=i;continue;}}
				if(p2<0){if(p[i].act){p2=i;break;}}
			}
			if(p0>=0&&p1>=0&&p2>=0){
				//printf("before_mesh_adding\n");
				addmesh(p0,p1,p2);
				//printf("after_mesh_adding\n\n");
			}
			inp.bm = 0;
		}
		//DELETING VERTEXES
		if(inp.del&&regime==VERTEX){
			for(int i=np-1;i>=0;i--){
				if(p[i].act){
					for(int j=0;j<nm;j++){
						if(m[j].p[0]==i||m[j].p[1]==i||m[j].p[2]==i){
							delmesh(j);
						}
					}
					for(int j=0;j<nl;j++){
						if(l[j].p[0]==i||l[j].p[1]==i){
							delline(j);
						}
					}
					movearr(i);
					delpoint(i);
				}
			}
			inp.del=0;
		}
		//DELETING LINES
		if(inp.del&&regime==LINE){
			for(int i=nl-1;i>=0;i--){
				if(l[i].act){
					delline(i);
				}
			}
			inp.del=0;
		}
		//DELETING MESHES
		if(inp.del&&regime==MESH){
			for(int i=nm-1;i>=0;i--){
				if(m[i].act){
					delmesh(i);
				}
			}
			inp.del=0;
		}
		//DRAGGING NORMALS
		if(regime==MESH&&inp.lcd&&!inp.shift){
			if(vp[curvp].type!=PERSP){
				if(mod(inp.cx-inp.mx)<=gl.pointsize/2&&mod(inp.cy-inp.my)<=gl.pointsize/2){
					vect d(vp[curvp].wtos(inp.mx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.my-vp[curvp].py-vp[curvp].sy/2.0f),0);
					float ps = vp[curvp].wtos(gl.pointsize+4);
					int in = 0;
					for(int i=0;i<nm;i++){
						if(m[i].act){
							vect tr[3];
							tr[0] = transform(p[m[i].p[0]].c+0.2f*m[i].n[0]-vp[curvp].crd,vp[curvp].type);
							tr[1] = transform(p[m[i].p[1]].c+0.2f*m[i].n[1]-vp[curvp].crd,vp[curvp].type);
							tr[2] = transform(p[m[i].p[2]].c+0.2f*m[i].n[2]-vp[curvp].crd,vp[curvp].type);
							if(insidetest(tr[0].x-ps/2,tr[0].y-ps/2,ps,ps,d.x,d.y)){ m[i].cn = 0; in++; continue;}
							if(insidetest(tr[1].x-ps/2,tr[1].y-ps/2,ps,ps,d.x,d.y)){ m[i].cn = 1; in++; continue;}
							if(insidetest(tr[2].x-ps/2,tr[2].y-ps/2,ps,ps,d.x,d.y)){ m[i].cn = 2; in++; continue;}
							m[i].cn = -1;
						}
					}
					if(in){drag = 1;}
					//printf("mesh selected!\n");
				}
			}
		}
		if(regime==MESH&&drag&&inp.lmb){
			vect d(vp[curvp].wtos(inp.mx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.my-vp[curvp].py-vp[curvp].sy/2.0f),0),
			f(0,0,1); d = retransform(d,vp[curvp].type)+vp[curvp].crd; f = retransform(f,vp[curvp].type);
			for(int i=0;i<nm;i++){
				if(m[i].act){
					if(m[i].cn>=0){
						float fx = m[i].n[m[i].cn]*f;
						m[i].n[m[i].cn] -= d*5.0f;
						m[i].n[m[i].cn] = sqrt(1.0f-fx*fx)*norm(d-p[m[i].p[m[i].cn]].c+(p[m[i].p[m[i].cn]].c*f)*f) + fx*f;
					}
				}
			}
		}
		//COMMON NORMALS
		if(regime==MESH&&inp.bl){
			for(int i=0;i<np;i++){
				if(p[i].act){
					vect comnor;
					for(int j=0;j<nm;j++){
						if(m[j].act){
							if(m[j].p[0]==i){comnor+=m[j].n[0];}
							if(m[j].p[1]==i){comnor+=m[j].n[1];}
							if(m[j].p[2]==i){comnor+=m[j].n[2];}
						}
					}
					if(comnor*comnor>0.0f){comnor = norm(comnor);}
					else{comnor.set(0,0,1);}
					for(int j=0;j<nm;j++){
						if(m[j].act){
							if(m[j].p[0]==i){m[j].n[0]=comnor;}
							if(m[j].p[1]==i){m[j].n[1]=comnor;}
							if(m[j].p[2]==i){m[j].n[2]=comnor;}
						}
					}
				}
			}
			inp.bl = 0;
		}
		//INVERTING FACE && BUILDING ORTHO NORMALS
		if(regime==MESH&&inp.bm){
			for(int i=0;i<nm;i++){
				if(m[i].act){
					int t = m[i].p[0];
					m[i].p[0]=m[i].p[1];
					m[i].p[1]=t;
					vect tn = norm((p[m[i].p[1]].c-p[m[i].p[0]].c)^(p[m[i].p[2]].c-p[m[i].p[0]].c));
					m[i].n[0] = tn;
					m[i].n[1] = tn;
					m[i].n[2] = tn;
				}
			}
			inp.bm = 0;
		}
		//BINDING TEXTURES
		if(inp.t){
			if(regime==MESH){
				for(int i=0;i<nm;i++){
					if(m[i].act){
						//if(m[i].cn<0){
						vect d;
						d = transform(p[m[i].p[0]].c,vp[curvp].type);
						m[i].tx[0] = (d.x - (vp[curvp].bgx-vp[curvp].bgs*stex[vp[curvp].bg]))/(2.0f*vp[curvp].bgs*stex[vp[curvp].bg]);
						m[i].ty[0] = 1.0f-(d.y - (vp[curvp].bgy-vp[curvp].bgs))/(2.0f*vp[curvp].bgs);
						d = transform(p[m[i].p[1]].c,vp[curvp].type);
						m[i].tx[1] = (d.x - (vp[curvp].bgx-vp[curvp].bgs*stex[vp[curvp].bg]))/(2.0f*vp[curvp].bgs*stex[vp[curvp].bg]);
						m[i].ty[1] = 1.0f-(d.y - (vp[curvp].bgy-vp[curvp].bgs))/(2.0f*vp[curvp].bgs);
						d = transform(p[m[i].p[2]].c,vp[curvp].type);
						m[i].tx[2] = (d.x - (vp[curvp].bgx-vp[curvp].bgs*stex[vp[curvp].bg]))/(2.0f*vp[curvp].bgs*stex[vp[curvp].bg]);
						m[i].ty[2] = 1.0f-(d.y - (vp[curvp].bgy-vp[curvp].bgs))/(2.0f*vp[curvp].bgs);
						//}
					}
				}
			}
			inp.t = 0;
		}
		if(inp.rmb&&!inp.mmb){
			//VIEWPORT MOVING
			if(vp[curvp].type!=PERSP){vp[curvp].move(inp.dx,inp.dy);}
			//PITCH ROTATING PERSPECTIVE VIEWPORT
			else{  
				/*vect axis = vp[3].top^vp[3].dir;
				vp[3].dir = rotate(0.64f*inp.dy*M_PI/180.0f,axis,vp[3].dir);
				vp[3].top = rotate(0.64f*inp.dy*M_PI/180.0f,axis,vp[3].top);
				vect up(0,0,1);
				vp[3].dir = rotate(0.64f*inp.dx*M_PI/180.0f,up,vp[3].dir);
				vp[3].top = rotate(0.64f*inp.dx*M_PI/180.0f,up,vp[3].top);*/
				vp[3].dir = rotate(0.64f*inp.dx*M_PI/180.0f,vp[3].top,vp[3].dir);
				vect axis = vp[3].top^vp[3].dir;
				vp[3].dir = rotate(0.64f*inp.dy*M_PI/180.0f,axis,vp[3].dir);
				vp[3].top = rotate(0.64f*inp.dy*M_PI/180.0f,axis,vp[3].top);
				vp[3].dir = vp[3].dir/sqrt(vp[3].dir*vp[3].dir);
				vp[3].top = vp[3].top/sqrt(vp[3].top*vp[3].top);
			}
		}
		if(inp.mmb&&!inp.rmb){
			if(vp[curvp].type==PERSP){vp[curvp].move(inp.dx,inp.dy);}
		}
		//YAW ROTATING PERSPECTIVE VIEWPORT
		if(inp.mmb&&inp.rmb){
			if(vp[curvp].type==PERSP){
				float ry = (float)(inp.my-vp[3].py-vp[3].sy/2)/vp[3].sy, rx = (float)(inp.mx-vp[3].px-vp[3].sx/2)/vp[3].sx;
				float dev = 0.0f;
				if(rx!=0.0f&&ry!=0.0f){dev = (inp.dx*ry - inp.dy*rx)/(rx*rx+ry*ry);}
				vp[3].top = rotate(0.16f*dev*M_PI/180.0f,vp[3].dir,vp[3].top);
			}
		}
		//COORDINATE PRINTING
		if(vp[curvp].type!=PERSP&&(inp.dx||inp.dy)){
			vect d(vp[curvp].wtos(inp.mx-vp[curvp].px-vp[curvp].sx/2.0f),vp[curvp].wtos(inp.my-vp[curvp].py-vp[curvp].sy/2.0f),0);
			vect inf = retransform(d,vp[curvp].type)+vp[curvp].crd;
			SDL_WM_SetCaption(scrd(inf),NULL);
		}
		//SWITCHING REGIMES
		if(inp.v){regime = VERTEX; SDL_WM_SetCaption("VERTEX REGIME ON",NULL); inp.v=0;dnorm=0;}
		if(inp.l){regime = LINE; SDL_WM_SetCaption("LINE REGIME ON",NULL); inp.l=0;dnorm=0;}
		if(inp.m){regime = MESH; SDL_WM_SetCaption("MESH REGIME ON",NULL); inp.m=0;dnorm=1;}
	}
	void active(){
		glViewport(0,0,gl.width,gl.height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,gl.width,0,gl.height);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	}
	void draw(){
		if(inp.lmb&&!drag){
			glLineWidth(1.0f);
			glColor3f(0,0,0.64f);
			glBegin(GL_LINE_LOOP);
			glVertex2f(inp.cx,inp.cy);
			glVertex2f(inp.cx,inp.my);
			glVertex2f(inp.mx,inp.my);
			glVertex2f(inp.mx,inp.cy);
			glEnd();
		}
		if(inp.mmb&&regime==LINE&&vp[curvp].type!=PERSP){
			glLineWidth(1.0f);
			glColor3f(0.64f,0.64f,0.64f);
			glBegin(GL_LINES);
			glVertex2f(inp.cx,inp.cy);
			glVertex2f(inp.mx,inp.my);
			glEnd();
		}
		glLineWidth(2.0f);
		glPointSize(2.0f);
		for(int i=0;i<4;i++){
			if(i==curvp){glColor3f(1.0f,1.0f,0.0f);}
			else{glColor3f(0.64f,0.64f,0.64f);}
			glBegin(GL_LINE_LOOP);
			glVertex2f(vp[i].px+1,vp[i].py+1);
			glVertex2f(vp[i].px+vp[i].sx-1,vp[i].py+1);
			glVertex2f(vp[i].px+vp[i].sx-1,vp[i].py+vp[i].sy-1);
			glVertex2f(vp[i].px+1,vp[i].py+vp[i].sy-1);
			glEnd();
			glBegin(GL_POINTS);
			glVertex2f(vp[i].px+1,vp[i].py+1);
			glVertex2f(vp[i].px+vp[i].sx-1,vp[i].py+1);
			glVertex2f(vp[i].px+vp[i].sx-1,vp[i].py+vp[i].sy-1);
			glVertex2f(vp[i].px+1,vp[i].py+vp[i].sy-1);
			glEnd();
		}
		glLineWidth(gl.linewidth);
		glPointSize(gl.pointsize);
	}
}vpinterface;
