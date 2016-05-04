class point{
	public:
	float m;
	vect c,s,a;
	vect ff;
	point(){
		m = 1.0f;
	}
	void force(vect af){
		a += af/m;
	}
	void frict(vect aff){
		ff += aff;
	}
	vect frict(){
		if(ff*ff==0.0f){return ff;}//to avoid division by zero
		float afv = sqrt(ff*ff);
		vect an = ff/afv;
		vect ls = s - (s*an)*an;
		float lsv;
		vect lsd;
		if(ls*ls!=0.0f){//analogically
			lsv = sqrt(ls*ls);
			lsd = ls/lsv;
		}
		if(lsv*m>=afv*sec){
			a -= lsd*afv/m;
			return lsd*afv;
		}
		vect lf = a*m - ((a*m)*an)*an;
		float lfv = sqrt((lf+ls*m/sec)*(lf+ls*m/sec));
		vect lfd;
		if(lfv!=0.0f){
			lfd = (lf+ls*m/sec)/lfv;//analogically
		}
		if(lfv>=afv){
			a -= lfd*afv/m;
			return lfd*afv;
		}
		a -= ls/sec + lf/m;
		return ls*m/sec + lf;
	}
	
	void step(){
		frict();
		ff.nul();
		
		s += a*sec;
		c += s*sec;
		a.nul();
	}
};

class vertex{
	public:
	vect c,s,f;
	float ff;
	void force(vect af){
		f += af;
	}
	void frict(float aff){
		ff += aff;
	}
	vect frict(){
		return -ff*s;
	}
	void clean(){
		f.nul();
		ff = 0.0f;
	}
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
		s += a*sec;
		//getting axis and angle from superposition of them
		vect ax = s*sec;
		float an = sqrt(ax*ax);
		ax = ax/an;
		
		f = rotate(f,an,ax);
		t = rotate(t,an,ax);
		r = f^t;
		
		a.nul();
	}
	void force(vect aforce, vect aarm){//force and arm
		vect lfm = aarm^aforce; //force moment
		moment(lfm);
	}
	void moment(vect lfm){
		if(lfm*lfm==0.0f){return;}//to avoid division by zero
		vect lax(lfm*r,lfm*f,lfm*t);//moment in local coordinates
		a += lfm*(lax*lax/(lax.x*j.x*lax.x + lax.y*j.y*lax.y + lax.z*j.z*lax.z));//force moment / computed inertia moment
	}
};

float 	ressor_directed_hardness = 1.0f,
		ressor_directed_amortization = 1.0f,
		ressor_deviated_hardness = 16.0f,
		ressor_deviated_amortization = 0.98f,
		ressor_oversize_linear_hardness = 8.0f,
		ressor_oversize_quadratic_hardness = 16.0f,
		ressor_oversize_amortization = 0.96f;
		

class ressor{
	public:
	vect dir;//direction
	vertex * fv;//fix vertex
	point * cv;//control vertex
	float bal,mln,har,amr;//balance length, maximal length, hardness, amortization coefficient
	ressor(){
		fv = NULL;
		cv = NULL;
	}
	void interact(){
		if(fv!=NULL&&cv!=NULL){
			vect dist = cv->c-fv->c;
			vect luft = dist-(dist*dir)*dir;
			float dev = dist*dir;
			vect spd = cv->s-fv->s;
			vect drs = spd*dir*dir;
			vect dvs = spd - drs;
			vect frc = ressor_directed_hardness*har*(dev-bal)*dir
			+ har*ressor_deviated_hardness*luft;
			if(dev<0.0f){
				frc += ressor_oversize_linear_hardness*har*(dev-0.0f)*dir
				- ressor_oversize_quadratic_hardness*har*(0.0f-dev)*(0.0f-dev)*dir;
			}
			if(dev>mln){
				frc += ressor_oversize_linear_hardness*har*(dev-mln)*dir
				+ ressor_oversize_quadratic_hardness*har*(dev-mln)*(dev-mln)*dir;
			}
			fv->force(frc);
			cv->force(-frc);
		}
	}
	void amortize(){
		if(fv!=NULL&&cv!=NULL){
			vect dist = cv->c-fv->c;
			vect luft = dist-(dist*dir)*dir;
			float dev = dist*dir;
			vect spd = cv->s-fv->s;
			vect drs = spd*dir*dir;
			vect dvs = spd - drs;
			float fir = cv->m/sec;
			vect frc = ressor_directed_amortization*amr*drs*fir
			+ ressor_deviated_amortization*dvs*fir;
			if(dev<0.0f){
				frc += ressor_oversize_amortization*drs;
			}
			if(dev>mln){
				frc += ressor_oversize_amortization*drs;
			}
			fv->force(frc);
			cv->force(-frc);
		}
	}
};

class wheel{
	public:
	point c;//point of a wheel
	vect nor,top;//normal to wheel plane, top of wheel
	float p,s,a,in;//angular position, speed, acceleration, inertia moment
	float wf,lf,kf;//wheel dry/liquid friction/ koeff of friction of a rubber
	bool st;//stop wheel rotating
	float rad,hvd,thc;
	vect ff;
	void force(vect af){
		c.force(af);
	}
	void frict(vect aff){
		ff += aff*kf;
	}
	void frict(){
		if(ff*ff==0.0f){return;}//to avoid division by zero
		float afv = sqrt(ff*ff);
		vect an = ff/afv;
		vect ss = c.s + ((s*nor)^(an*rad));
		vect ls = ss - (ss*an)*an;
		float lsv;
		vect lsd;
		if(ls*ls!=0.0f){//analogically
			lsv = sqrt(ls*ls);
			lsd = ls/lsv;
		}
		if(lsv*c.m>=afv*sec){
			c.a -= lsd*afv/c.m;
			a += nor*(((lsd*afv)^(an*rad))/in);
			return;
		}
		vect lf = c.a*c.m - ((c.a*c.m)*an)*an;
		float lfv = sqrt((lf+ls*c.m/sec)*(lf+ls*c.m/sec));
		vect lfd;
		if(lfv!=0.0f){
			lfd = (lf+ls*c.m/sec)/lfv;//analogically
		}
		if(lfv>=afv){
			c.a -= lfd*afv/c.m;
			a += nor*(((lfd*afv)^(an*rad))/in);
			return;
		}
		c.a -= ls/sec + lf/c.m;
		a += nor*(((ls*c.m/sec+lf)^(an*rad))/in);
		return;
	}
	void step(){
		float fd,fv;//force direction/ force value
		if(s/sec+a>=0.0f){fd = 1.0f; fv = s/sec+a;}
		else{fd = -1.0f; fv = -s/sec-a;}
		if(fv > wf/in){a -= fd*wf/in;}
		else{a -= a + s/sec;}
		
		frict();
		ff.nul();
		c.step();
		
		if(st){a -= a + s/sec;}
		
		s += a*sec;
		p += s*sec;
		a = 0.0f;
	}
};

class solid{
	public:
	point c;//center of a mass
	ori o;//orientation
	vertex * v, * bv;//vertexes of solid body/builded coords of vertexes/next I need to add polygons here
	unsigned int nv;//in v orientation x - left, y - front, z - top sides
	solid(){
		nv = 0;
	}
	void build(){
		for(unsigned int i=0;i<nv;i++){
			bv[i].c = v[i].c.x*o.r + v[i].c.y*o.f + v[i].c.z*o.t + c.c;
			bv[i].s = c.s + (o.s^(bv[i].c-c.c));
		}
	}
	void frict(){
		vect sfr,smr;//summary force and moment resistance
		for(unsigned int i=0;i<nv;i++){
			vect tfr = bv[i].frict();
			sfr += tfr;
			smr += (bv[i].c-c.c)^tfr;
		}
		c.force(sfr);
		o.moment(smr);
	}
	void step(){
		for(unsigned int i=0;i<nv;i++){
			c.force(bv[i].f);
			o.force(bv[i].f,bv[i].c-c.c);//force and arm
		}
		//frict();
		for(unsigned int i=0;i<nv;i++){
			bv[i].clean();
		}
		c.step();
		o.step();
		build();
	}
};
