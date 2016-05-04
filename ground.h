class gvert{
	public:
	vect pos;
	vect nor;
};

class gedge{
	public:
	gvert ** ver;
	vect dir;
	bool ini;
	gedge(){
		ini = false;
	}
	void set(gvert * av0, gvert * av1){
		if(ini){
			delete[] ver;
			ini = false;
		}
		if(av0==NULL||av1==NULL){
			return;
		}
		ver = new gvert*[2];
		ver[0] = av0;
		ver[1] = av1;
		dir = norm(ver[1]->pos - ver[0]->pos);
		ini = true;
	}
	void clear(){
		ini = false;
		delete[] ver;
	}
};

class gtile{
	public:
	gvert ** ver;
	vect nor;
	Uint16 mat;
	bool ini;
	gtile(){
		ini = false;
	}
	void set(gvert * av0, gvert * av1, gvert * av2){
		if(ini){
			delete[] ver;
			ini = false;
		}
		if(av0==NULL||av1==NULL||av2==NULL){
			return;
		}
		ver = new gvert*[3];
		ver[0] = av0;
		ver[1] = av1;
		ver[2] = av2;
		nor = (ver[2]->pos-ver[1]->pos)^(ver[0]->pos-ver[1]->pos);
		ver[0]->nor += nor;
		ver[1]->nor += nor;
		ver[2]->nor += nor;
		nor = norm(nor);
		ini = true;
		return;
	}
	void draw(){
		if(!ini){return;}
		//glNormalv(nor);
		glNormalv(ver[0]->nor);
		glTexCoord2f(0.4f*ver[0]->pos.x,0.4f*ver[0]->pos.y);
		glVertexv(ver[0]->pos);
		glNormalv(ver[1]->nor);
		glTexCoord2f(0.4f*ver[1]->pos.x,0.4f*ver[1]->pos.y);
		glVertexv(ver[1]->pos);
		glNormalv(ver[2]->nor);
		glTexCoord2f(0.4f*ver[2]->pos.x,0.4f*ver[2]->pos.y);
		glVertexv(ver[2]->pos);
	}
	void clear(){
		ini = false;
		delete[] ver;
	}
};

/*class garea{
	public:
	gvert ** ver; unsigned int nver;
	gedge ** edg; unsigned int nedg;
	gtile ** til; unsigned int ntil;
	
	float lev;
	float bx,ex,by,ey;
	
	void build(){
		
	}
	
	bool under(vect ac){
		if(ac.z>lev){return false;}
		return true;
	}
	bool inside(vect ac){
		if(ac.x>=bx&&ac.x<=ex&&ac.y>=by&&ac.y<=ey){
			return true;
		}
		return false;
	}
};*/

float ground_friction = 2.0f;

class ground{
	private:
	gvert * ver; unsigned int nver;
	gedge * edg; unsigned int nedg;
	gtile * til; unsigned int ntil;
	public:
	void init(){
		unsigned int size = 16;
		nver = size*size;
		nedg = 3*(size-1)*(size-1);
		ntil = 2*(size-1)*(size-1);
		ver = new gvert[nver];
		edg = new gedge[nedg];
		til = new gtile[ntil];
		
		for(unsigned int ix=0;ix<size;ix++){
			for(unsigned int iy=0;iy<size;iy++){
				ver[ix*size+iy].pos.set(ix*4,iy*4,-256.0f/(float)(32+(ix-size/2)*(ix-size/2)+(iy-size/2)*(iy-size/2)));
			}
		}
		
		for(unsigned int ix=0;ix<size-1;ix++){
			for(unsigned int iy=0;iy<size-1;iy++){
				edg[3*(ix*(size-1)+iy)].set(&ver[ix*size+iy],&ver[ix*size+iy+1]);
				edg[3*(ix*(size-1)+iy)+1].set(&ver[ix*size+iy],&ver[(ix+1)*size+iy]);
				edg[3*(ix*(size-1)+iy)+2].set(&ver[ix*size+iy+1],&ver[(ix+1)*size+iy]);
			}
		}
		
		for(unsigned int ix=0;ix<size-1;ix++){
			for(unsigned int iy=0;iy<size-1;iy++){
				til[2*(ix*(size-1)+iy)].set(&ver[ix*size+iy+1],&ver[ix*size+iy],&ver[(ix+1)*size+iy]);
				til[2*(ix*(size-1)+iy)+1].set(&ver[(ix+1)*size+iy+1],&ver[ix*size+iy+1],&ver[(ix+1)*size+iy]);
			}
		}
		
		for(unsigned int i=0;i<nver;i++){
			ver[i].nor = norm(ver[i].nor);
		}
	}
	
	bool insidetest(gtile * til, vect p){
		if((((til->ver[1]->pos-til->ver[0]->pos)^(p-til->ver[0]->pos))*til->ver[0]->nor>=0.0f)&&
			(((til->ver[2]->pos-til->ver[1]->pos)^(p-til->ver[1]->pos))*til->ver[1]->nor>=0.0f)&&
			(((til->ver[0]->pos-til->ver[2]->pos)^(p-til->ver[2]->pos))*til->ver[2]->nor>=0.0f)){
				return true;
			}
		return false;
	}
	
	vect direct(gtile * til, vect p, vect d){//d must be normalized
		return p+d*((p-til->ver[0]->pos)*til->nor);
	}
	
	bool directinsidetest(gtile * til, vect p, vect d){
		return insidetest(til,direct(til,p,d));
	}
	
	float depthtest(gtile * til, vect p){
		return til->nor*(p-til->ver[0]->pos);
	}
	
	void roll(solid * sol, ressor * res, wheel * whe){
		for(unsigned int i=0;i<ntil;i++){
			vect p = direct(&til[i],res->fv->c+whe->hvd*whe->nor,-whe->top);
			if(insidetest(&til[i],p)){
				float d = (p-res->fv->c)*(-whe->top) - whe->rad;
				if(d<res->dev&&d>=-res->mln){
					res->dev = d;
					res->nor = til[i].nor;
					if(!whe->st){
						vect nfw;
						if(!whe->a){
							nfw = sol->c.s + (sol->o.s^(p-sol->c.c));
						}
						else{
							//nfw = whe->a*sec*(whe->top^whe->nor);//discrete transmission without differential
							//nfw = 12*whe->a*sec*(whe->top^whe->nor) + (sol->o.s^(p-sol->c.c));//discrete transmission with differential
							nfw = sol->c.s + (sol->o.s^(p-sol->c.c)) + whe->a*sec*(whe->top^whe->nor);//sliding auto-transmission
						}
						nfw -= (nfw*til[i].nor)*til[i].nor;
						nfw -= (nfw*whe->nor)*whe->nor;
						nfw = nfw*0.996f;
						sol->frict((p-sol->c.c),til[i].nor,nfw,ground_friction*res->force());
						whe->s = (nfw^(whe->top/whe->rad))*whe->nor;
					}
					else{
						sol->frict((p-sol->c.c),til[i].nor,NUL,ground_friction*res->force());
					}
				}
			}
		}
	}
	
	void draw(){
		for(unsigned int i=0;i<ntil;i++){
			til[i].draw();
		}
	}
	void remove(){
		nver = 0;
		delete[] ver;
		
		for(unsigned int i=0;i<nedg;i++){
			edg[i].clear();
		}
		nedg = 0;
		delete[] edg;
		
		for(unsigned int i=0;i<ntil;i++){
			til[i].clear();
		}
		ntil = 0;
		delete[] til;
	}
};
