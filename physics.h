class point{
	public:
	float m;
	vect c,s,a;
	point(){
		m = 1.0f;
	}
	void step(){
		c += s*sec;
		s += a*sec;
		a.nul();
	}
};

class vertex{
	public:
	vect c,s,f;
	vect cf,tf;
	void force(vect af){
		f += af;
	}
	void clean(){
		f.nul();
	}
	void cfreeze(){
		cf = tf;
	}
	void tfreeze(){
		tf = c;
	}
};

class line{
	public:
	int p[2];
};

class mesh{
	public:
	int p[3];
	vect n[3];
	float tx[3],ty[3];
};

class ori{
	public:
	vect f,t,r;//front/top/right directions
	vect s,a;//speed and axis of rotation/acceleration of rotation and axis of acceleration
	vect j;//moments of inertions/next on front/top/side directions
	ori(){
		j.set(1.0f,1.0f,1.0f);
	}
	void step(){
		//getting axis and angle from superposition of them
		vect ax = s*sec;
		float an = sqrt(ax*ax);
		ax = ax/an;
		
		f = rotate(f,an,ax);
		t = rotate(t,an,ax);
		r = f^t;
		
		s += a*sec;
		
		a.nul();
	}
	void force(vect aforce, vect aarm){//force and arm
		vect lfm = aarm^aforce; //force moment
		moment(lfm);
	}
	void moment(vect lfm){
		if(lfm*lfm==0.0f){return;}//to avoid division by zero
		a += lfm/inertia(lfm);//force moment / computed inertia moment
	}
	float inertia(vect spinax){
		if(spinax*spinax==0.0f){return 0.0f;}//to avoid division by zero
		vect lax(spinax*r,spinax*f,spinax*t);//moment in local coordinates
		return (lax.x*j.x*lax.x + lax.y*j.y*lax.y + lax.z*j.z*lax.z)/(lax*lax);//force moment / computed inertia moment
	}
};
		

class ressor{
	public:
	vect dir,nor;//direction, normal of force
	float dev;//deviation
	vertex * fv;//fix vertex
	vertex * cv;//control vertex
	float bal,mln,har,qhar,amr;//balance length, maximal length, hardness, amortization coefficient
	ressor(){
		fv = NULL;
		cv = NULL;
	}
	vect force(){
		if(dev<mln&&dev>=-mln){
			return (har*(dev-bal)-qhar*(dev-bal)*(dev-bal) - amr*(fv->s*dir))*dir;
		}
		return NUL;
	}
	void interact(){
		if(fv!=NULL&&cv!=NULL){
			fv->force(force());
		}
	}
	void build(){
		cv->c = fv->c + dev*dir;
		dev = mln; nor.nul();
	}
};

class wheel{
	public:
	vertex c;//point of a wheel
	vect nor,top;//normal to wheel plane, top of wheel
	float p,s,a,in;//angular position, speed, acceleration, inertia moment
	float wf,lf,kf;//wheel dry/liquid friction/ koeff of friction of a rubber
	bool st;//stop wheel rotating
	float rad,hvd,thc;//radius/horizontal deviation/thickness(not tetrahydrocanabinol)
	void force(float af){
		a += af/in;
	}
	void step(){
		//a -= s*lf;
		//s += a*sec;
		if(st){s = 0.0f;};
		p += s*sec;
		//a = 0.0f;
	}
	void cfreeze(){
		c.cfreeze();
	}
	void tfreeze(){
		c.tfreeze();
	}
};

class solid{
	public:
	point c;//center of a mass
	ori o;//orientation
	vertex * v, * bv;//vertexes of solid body/builded coords of vertexes/next I need to add polygons here
	line * l; mesh * m;
	unsigned int nv,nl,nm;//in v orientation x - left, y - front, z - top sides
	vertex cf;
	solid(){
		nv = 0;
	}
	void build(){
		for(unsigned int i=0;i<nv;i++){
			bv[i].c = v[i].c.x*o.r + v[i].c.y*o.f + v[i].c.z*o.t + c.c;
			bv[i].s = c.s + (o.s^(bv[i].c-c.c));
		}
	}
	void coll(vect r, vect n){
		vect vel = c.s + (o.s^r);
		float ine = o.inertia(n^r);
		vect zn = (n/c.m + (r^(n^r))/ine);
		float imp = ((vel-(vel*n)*n)*zn)/(zn*zn);
		c.s += (imp*n)/c.m; o.s += (r^(imp*n))/ine;
	}
	void frict(vect r, vect n, vect s, vect m){
		vect st = s - (s*n)*n;
		vect vel = c.s + (o.s^r) - st;
		vect fd = -norm(vel-(vel*n)*n);
		float ine = o.inertia(fd^r);
		if(ine==0.0f){return;}
		vect zn = (fd/c.m + (r^(fd^r))/ine);
		float imp = (((vel*fd)*fd)*zn)/(zn*zn);
		if(-imp>m*n*sec){c.a += m*n*fd/c.m; o.force(m*n*fd,r);}
		else{c.s -= (imp*fd)/c.m; o.s -= (r^(imp*fd))/ine;}
	}
	void step(){
		for(unsigned int i=0;i<nv;i++){
			c.a += bv[i].f/c.m;
			o.force(bv[i].f,bv[i].c-c.c);//force and arm
		}
		for(unsigned int i=0;i<nv;i++){
			bv[i].clean();
		}
		c.step();
		o.step();
		build();
		cf.c = c.c;
	}
	void tfreeze(){
		cf.tfreeze();
		for(unsigned int i=0;i<nv;i++){
			bv[i].tfreeze();
		}
	}
	void cfreeze(){
		cf.cfreeze();
		for(unsigned int i=0;i<nv;i++){
			bv[i].cfreeze();
		}
	}
};
