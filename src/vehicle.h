class vehicle{
	private:
	solid p;
	ressor * r; unsigned int nr;
	wheel * tr;
	float wacc,wrot; bool stopwheel; //acceleration/rotation/stopping
	public:
	vect * cfp;//freezed coordinates
	void create(vect ap){
		cfp = &(p.cf.cf);
		//size of a vehicle = 2x4x1
		//density of a vehicle = 100 kg/m^3
		p.c.m = 1800.0f;
		p.c.c = ap;
		p.o.f.set(0,1,0);
		p.o.t.set(0,0,1);
		p.o.r.set(1,0,0);
		p.o.j.set(800.0f,200.0f,3200.0f);
		/*p.nv = 8;
		p.v = new vertex[p.nv];
		p.bv = new vertex[p.nv];
		p.v[0].c.set(1.0f,1.8f,1.0f);
		p.v[1].c.set(1.0f,1.8f,0.0f);
		p.v[2].c.set(-1.0f,1.8f,0.0f);
		p.v[3].c.set(-1.0f,1.8f,1.0f);
		p.v[4].c.set(-1.0f,-2.2f,1.0f);
		p.v[5].c.set(-1.0f,-2.2f,0.0f);
		p.v[6].c.set(1.0f,-2.2f,0.0f);
		p.v[7].c.set(1.0f,-2.2f,1.0f);*/
		p.nv = mdl.np;
		p.nl = mdl.nl;
		p.nm = mdl.nm;
		p.v = new vertex[p.nv];
		p.bv = new vertex[p.nv];
		p.l = new line[p.nl];
		p.m = new mesh[p.nm];
		for(int i=0;i<p.nv;i++){
			p.v[i].c = mdl.p[i].c - mdl.p[p.nv-1].c;
		}
		for(int i=0;i<p.nl;i++){
			p.l[i].p[0] = mdl.l[i].p[0];
			p.l[i].p[1] = mdl.l[i].p[1];
		}
		for(int i=0;i<p.nm;i++){
			p.m[i].p[0] = mdl.m[i].p[0];
			p.m[i].p[1] = mdl.m[i].p[1];
			p.m[i].p[2] = mdl.m[i].p[2];
			p.m[i].n[0] = mdl.m[i].n[0];
			p.m[i].n[1] = mdl.m[i].n[1];
			p.m[i].n[2] = mdl.m[i].n[2];
			p.m[i].tx[0] = mdl.m[i].tx[0];
			p.m[i].tx[1] = mdl.m[i].tx[1];
			p.m[i].tx[2] = mdl.m[i].tx[2];
			p.m[i].ty[0] = mdl.m[i].ty[0];
			p.m[i].ty[1] = mdl.m[i].ty[1];
			p.m[i].ty[2] = mdl.m[i].ty[2];
		}
		p.build();
		//printf("here?");
		nr = 4;
		r = new ressor[nr];
		tr = new wheel[nr];
		for(int i=0;i<nr;i++){
			r[i].dir = -p.o.t;
			r[i].bal = 0.82f;
			r[i].mln = 0.82f;
			r[i].har = 24000.0f;
			r[i].qhar = 8000.0f;
			r[i].amr = 2400.0f;
			r[i].dev = 0.8f;
			tr[i].p = 0.0f;
			tr[i].s = 0.0f;
			tr[i].a = 0.0f;
			tr[i].in = 20.0f;
			tr[i].wf = 2.0f;
			tr[i].lf = 0.02f;
			tr[i].kf = 1.2f;
			tr[i].top = p.o.t;
			tr[i].rad = 0.44f;
			tr[i].hvd = 0.06f;
			tr[i].thc = 0.16f;
		}
		r[0].fv = &p.bv[p.nv-4];
		r[1].fv = &p.bv[p.nv-3];
		r[2].fv = &p.bv[p.nv-2];
		r[3].fv = &p.bv[p.nv-5];
		r[0].cv = &(tr[0].c);
		r[1].cv = &(tr[1].c);
		r[2].cv = &(tr[2].c);
		r[3].cv = &(tr[3].c);
		tr[0].nor = p.o.r; tr[1].nor = -p.o.r;
		tr[2].nor = -p.o.r; tr[3].nor = p.o.r;
	}
	void collide(ground * ag){
		for(unsigned int i=0;i<p.nv;i++){
			
		}
		for(unsigned int i=0;i<nr;i++){
			ag->roll(&p,&r[i],&tr[i]);
			r[i].interact();
		}
	}
	
	void grav(){
		p.c.a += GRAV;
	}
	
	void accel(float ad){
		if((p.c.s*p.o.f)*ad >= -64.0f){wacc = ad;}
		else{stopwheel = true;}
	}
	void turn(float ar){
		wrot = ar;
	}
	void stop(bool stopflag){
		stopwheel = stopflag;
	}
	
	void draw();
	void step(){
		p.step();
		//tracks
		tr[0].st = stopwheel; tr[1].st = stopwheel;
		tr[2].st = stopwheel; tr[3].st = stopwheel;
		tr[0].a = wacc; tr[1].a = -wacc;
		tr[2].a = -wacc; tr[3].a = wacc;
		for(unsigned int i=0;i<nr;i++){
			tr[i].step();
			r[i].dir = -p.o.t;
			//divided wheels
			tr[i].top = p.o.t;
			r[i].build();
		}
		//divided wheels
		tr[0].nor = p.o.r; tr[1].nor = -p.o.r;
		tr[2].nor = -p.o.r; tr[3].nor = p.o.r;
		//bridge wheels(suv)
		/*vect lno;
		lno = norm(tr[0].c.c-tr[1].c.c);
		tr[0].nor = lno; tr[1].nor = -lno;
		lno = norm(tr[3].c.c-tr[2].c.c);
		tr[2].nor = -lno; tr[3].nor = lno;
		tr[0].top = tr[0].nor^p.o.f; tr[1].top = -tr[1].nor^p.o.f;
		tr[2].top = -tr[2].nor^p.o.f; tr[3].top = tr[3].nor^p.o.f;*/
		//end of bridge
		tr[0].nor = rotate(tr[0].nor,wrot,tr[0].top);
		tr[1].nor = rotate(tr[1].nor,wrot,tr[1].top);
	}
	void remove(){
		p.nv = 0;
		delete[] p.v;
		nr = 0;
		delete[] r;
		delete[] tr;
	}
	void cfreeze(){
		p.cfreeze();
		for(unsigned int i=0;i<nr;i++){
			tr[i].cfreeze();
		}
	}
	void tfreeze(){
		p.tfreeze();
		for(unsigned int i=0;i<nr;i++){
			tr[i].tfreeze();
		}
	}
};

#include"vehicle_drawing.h"
