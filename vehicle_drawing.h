void vehicle::draw(){
	met.put();
	glBindTexture(GL_TEXTURE_2D,texture[5]);
	//CAR BODY
	glBegin(GL_TRIANGLES);
		for(int i=0;i<p.nm;i++){
			glNormalv(p.m[i].n[0].y*p.o.f + p.m[i].n[0].x*p.o.r + p.m[i].n[0].z*p.o.t);
			glTexCoord2f(p.m[i].tx[0],p.m[i].ty[0]);
			glVertexv(p.bv[p.m[i].p[0]].cf);
			glNormalv(p.m[i].n[1].y*p.o.f + p.m[i].n[1].x*p.o.r + p.m[i].n[1].z*p.o.t);
			glTexCoord2f(p.m[i].tx[1],p.m[i].ty[1]);
			glVertexv(p.bv[p.m[i].p[1]].cf);
			glNormalv(p.m[i].n[2].y*p.o.f + p.m[i].n[2].x*p.o.r + p.m[i].n[2].z*p.o.t);
			glTexCoord2f(p.m[i].tx[2],p.m[i].ty[2]);
			glVertexv(p.bv[p.m[i].p[2]].cf);
		}		
	glEnd();
	bum.put();
	//RESSORES
	/*glBegin(GL_LINES);
	for(unsigned int i=0;i<nr;i++){
		glVertexv(p.bv[1].c);glVertexv(tr[0].c.cf);
		glVertexv(p.bv[2].c);glVertexv(tr[1].c.cf);
		glVertexv(p.bv[5].c);glVertexv(tr[2].c.cf);
		glVertexv(p.bv[6].c);glVertexv(tr[3].c.cf);
		
		//glVertexv(tr[0].c.c);glVertexv(tr[0].c.c+tr[0].nor*tr[0].s);
		//glVertexv(tr[1].c.c);glVertexv(tr[1].c.c+tr[1].nor*tr[1].s);
		//glVertexv(tr[2].c.c);glVertexv(tr[2].c.c+tr[2].nor*tr[2].s);
		//glVertexv(tr[3].c.c);glVertexv(tr[3].c.c+tr[3].nor*tr[3].s);
	}
	glEnd();*/
	//WHEELS
	float sa = M_PI/6;
	float ssa = sin(sa), csa = cos(sa);
	unsigned int nvr = 24;
	vect * lvr = new vect[2*nvr+2];
	vect * lnr = new vect[nvr];
	vect * ltr = new vect[nvr];
	for(unsigned int j=0;j<nr;j++){
		lvr[0] = tr[j].c.cf + tr[j].nor*(tr[j].hvd+tr[j].thc);
		lvr[1] = tr[j].c.cf + tr[j].nor*(tr[j].hvd-tr[j].thc);
		vect oy = tr[j].top;
		vect ox = tr[j].nor^oy;
		for(unsigned int i=0;i<nvr;i++){
			ltr[i].x = cos(2.0f*M_PI*(float)i/nvr); ltr[i].y = sin(2.0f*M_PI*(float)i/nvr);
			lnr[i] = oy*sin(tr[j].p+2.0f*M_PI*(float)i/nvr)+ox*cos(tr[j].p+2.0f*M_PI*(float)i/nvr);
			lvr[2+i*2] = lvr[0]+lnr[i]*tr[j].rad;
			lvr[2+i*2+1] = lvr[1]+lnr[i]*tr[j].rad;
		}
		
		glBindTexture(GL_TEXTURE_2D,texture[3]);
		glBegin(GL_TRIANGLES);
		for(unsigned int i=0;i<nvr-1;i++){
			glNormalv(tr[j].nor*csa + lnr[i+1]*ssa);
			glTexCoord2f((1-ltr[i+1].x)/2,(1-ltr[i+1].y)/2);
			glVertexv(lvr[2+(i+1)*2]);
			glNormalv(tr[j].nor*csa + lnr[i]*ssa);
			glTexCoord2f((1-ltr[i].x)/2,(1-ltr[i].y)/2);
			glVertexv(lvr[2+i*2]);
			glNormalv(tr[j].nor);
			glTexCoord2f(0.5f,0.5f);
			glVertexv(lvr[0]);
		}
		glNormalv(tr[j].nor*csa + lnr[0]*ssa);
		glTexCoord2f((1-ltr[0].x)/2,(1-ltr[0].y)/2);
		glVertexv(lvr[2]);
		glNormalv(tr[j].nor*csa + lnr[nvr-1]*ssa);
		glTexCoord2f((1-ltr[nvr-1].x)/2,(1-ltr[nvr-1].y)/2);
		glVertexv(lvr[2+(nvr-1)*2]);
		glNormalv(tr[j].nor);
		glTexCoord2f(0.5f,0.5f);
		glVertexv(lvr[0]);
		
		glTexCoord2f(0.5f,0.12f);
		
		for(unsigned int i=0;i<nvr-1;i++){
			glNormalv(-tr[j].nor*csa + lnr[i]*ssa);
			glVertexv(lvr[2+i*2+1]);
			glNormalv(-tr[j].nor*csa + lnr[i+1]*ssa);
			glVertexv(lvr[2+(i+1)*2+1]);
			glNormalv(-tr[j].nor);
			glVertexv(lvr[1]);
		}
		glNormalv(-tr[j].nor*csa + lnr[nvr-1]*ssa);
		glVertexv(lvr[2+(nvr-1)*2+1]);
		glNormalv(-tr[j].nor*csa + lnr[0]*ssa);
		glVertexv(lvr[3]);
		glNormalv(-tr[j].nor);
		glVertexv(lvr[1]);
		glEnd();
		
		float tirg = 6.0f;//only integers
		glBindTexture(GL_TEXTURE_2D,texture[4]);
		glBegin(GL_QUADS);
		for(unsigned int i=0;i<nvr-1;i++){
			glNormalv(lnr[i]);//*csa - tr[j].nor*ssa);
			glTexCoord2f(1,tirg*i/nvr);
			glVertexv(lvr[2+i*2+1]);
			glNormalv(lnr[i]);//*csa + tr[j].nor*ssa);
			glTexCoord2f(0,tirg*i/nvr);
			glVertexv(lvr[2+i*2]);
			glNormalv(lnr[i+1]);//*csa + tr[j].nor*ssa);
			glTexCoord2f(0,tirg*(i+1)/nvr);
			glVertexv(lvr[2+(i+1)*2]);
			glNormalv(lnr[i+1]);//*csa - tr[j].nor*ssa);
			glTexCoord2f(1,tirg*(i+1)/nvr);
			glVertexv(lvr[2+(i+1)*2+1]);
		}
		glNormalv(lnr[(nvr-1)]);//*csa - tr[j].nor*ssa);
		glTexCoord2f(1,tirg*(nvr-1)/nvr);
		glVertexv(lvr[2+(nvr-1)*2+1]);
		glNormalv(lnr[(nvr-1)]);//*csa + tr[j].nor*ssa);
		glTexCoord2f(0,tirg*(nvr-1)/nvr);
		glVertexv(lvr[2+(nvr-1)*2]);
		glNormalv(lnr[0]);//*csa + tr[j].nor*ssa);
		glTexCoord2f(0,tirg);
		glVertexv(lvr[2]);
		glNormalv(lnr[0]);//*csa - tr[j].nor*ssa);
		glTexCoord2f(1,tirg);
		glVertexv(lvr[2+1]);
		glEnd();
	}
	nvr = 0;
	delete[] lvr;
	delete[] lnr;
	delete[] ltr;
}
