class point{
	public:
	vect c;
	bool act;
	bool fix;
	bool vis;
	point(){
		act = 0;
		fix = 0;
		vis = 1;
	}
};

class line{
	public:
	int p[2];
	bool act;
	bool fix;
	bool vis;
	line(){
		p[0]=-1;p[1]=-1;
		act = 0;
		fix = 0;
		vis = 1;
	}
};

class mesh{
	public:
	int p[3];//point link
	vect n[3];//normals
	float tx[3],ty[3];//texture
	int cn;//current normal
	bool act;
	bool fix;
	bool vis;
	mesh(){
		p[0]=-1;p[1]=-1;p[2]=-1;
		cn = -1;
		act = 0;
		fix = 0;
		vis = 1;
	}
};

/*class bezier_surface{
	public:
	int p[4];
	point s[12];
	mesh(){
		p[0]=-1;p[1]=-1;p[2]=-1;p[3]=-1;
	}
};*/

point * p;
int np = 0;

line * l;
int nl = 0;

mesh * m;
int nm = 0;

void addpoint(vect ac){
	point * tmp;
	if(np){tmp = new point[np];}
	for(int i=0;i<np;i++){
		tmp[i] = p[i];
	}
	int tnp = np;
	np = 0;
	if(np){delete[] p;}
	p = new point[tnp+1];
	for(int i=0;i<tnp;i++){
		p[i] = tmp[i];
	}
	p[tnp].c = ac;
	np = tnp+1;
	tnp = 0;
	if(np-1){delete[] tmp;}
}

void addline(int n0, int n1){
	line * tmp;
	if(nl){tmp = new line[nl];}
	for(int i=0;i<nl;i++){
		tmp[i] = l[i];
	}
	int tnl = nl;
	nl = 0;
	if(nl){delete[] l;}
	l = new line[tnl+1];
	for(int i=0;i<tnl;i++){
		l[i] = tmp[i];
	}
	l[tnl].p[0] = n0;
	l[tnl].p[1] = n1;
	nl = tnl+1;
	tnl = 0;
	if(nl-1){delete[] tmp;}
}

void addmesh(int n0, int n1, int n2){
	mesh * tmp;
	if(nm){tmp = new mesh[nm];}
	for(int i=0;i<nm;i++){
		tmp[i] = m[i];
	}
	int tnm = nm;
	nm = 0;
	if(nm){delete[] m;}
	m = new mesh[tnm+1];
	for(int i=0;i<tnm;i++){
		m[i] = tmp[i];
	}
	m[tnm].p[0] = n0;
	m[tnm].p[1] = n1;
	m[tnm].p[2] = n2;
	nm = tnm+1;
	tnm = 0;
	if(nm-1){delete[] tmp;}
	//m[nm-1].c = 0.33333f*(p[n0].c+p[n1].c+p[n2].c);
	vect tn = norm((p[n1].c-p[n0].c)^(p[n2].c-p[n0].c));
	m[nm-1].n[0] = tn;
	m[nm-1].n[1] = tn;
	m[nm-1].n[2] = tn;
}

void delpoint(int n){
	if(n<0||n>=np){return;}
	point * tmp;
	if(np-1){tmp = new point[np-1];}
	for(int i=0;i<n;i++){
		tmp[i] = p[i];
	}
	for(int i=n+1;i<np;i++){
		tmp[i-1] = p[i];
	}
	int tnp = np-1;
	np = 0;
	delete[] p;
	if(tnp){p = new point[tnp];}
	for(int i=0;i<tnp;i++){
		p[i] = tmp[i];
	}
	np = tnp;
	tnp = 0;
	if(np){delete[] tmp;}
}

void delline(int n){
	if(n<0||n>=nl){return;}
	line * tmp;
	if(nl-1){tmp = new line[nl-1];}
	for(int i=0;i<n;i++){
		tmp[i] = l[i];
	}
	for(int i=n+1;i<nl;i++){
		tmp[i-1] = l[i];
	}
	int tnl = nl-1;
	nl = 0;
	delete[] l;
	if(tnl){l = new line[tnl];}
	for(int i=0;i<tnl;i++){
		l[i] = tmp[i];
	}
	nl = tnl;
	tnl = 0;
	if(nl){delete[] tmp;}
}

void delmesh(int n){
	if(n<0||n>=nm){return;}
	mesh * tmp;
	if(nm-1){tmp = new mesh[nm-1];}
	for(int i=0;i<n;i++){
		tmp[i] = m[i];
	}
	for(int i=n+1;i<nm;i++){
		tmp[i-1] = m[i];
	}
	int tnm = nm-1;
	nm = 0;
	delete[] m;
	if(tnm){m = new mesh[tnm];}
	for(int i=0;i<tnm;i++){
		m[i] = tmp[i];
	}
	nm = tnm;
	tnm = 0;
	if(nm){delete[] tmp;}
}

void movearr(int n){
	for(int i=0;i<nm;i++){
		if(m[i].p[0]>=n){m[i].p[0]--;}
		if(m[i].p[1]>=n){m[i].p[1]--;}
		if(m[i].p[2]>=n){m[i].p[2]--;}
	}
	for(int i=0;i<nl;i++){
		if(l[i].p[0]>=n){l[i].p[0]--;}
		if(l[i].p[1]>=n){l[i].p[1]--;}
	}
}

/*void centermesh(int n){
	m[n].c = 0.333333f*(p[m[n].p[0]].c + p[m[n].p[1]].c + p[m[n].p[2]].c);
}*/

bool dline = 1, dnorm = 0, dmesh = 1;

void draw(Uint8 type){
	if(type==PERSP&&dmesh){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		//glEnable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
		for(int i=0;i<nm;i++){
			if(!m[i].vis){continue;}
			float li;
			li = 0.64f*m[i].n[0].z;if(li<0.0f){li=0.0f;}li+=0.32f;
			if(m[i].act){glColor3f(li,0,0);}else{glColor3f(li,li,li);}
			glNormalv(m[i].n[0]);
			glTexCoord2f(m[i].tx[0],m[i].ty[0]);
			glVertexv(p[m[i].p[0]].c);
			li = 0.64f*m[i].n[1].z;if(li<0.0f){li=0.0f;}li+=0.32f;
			if(m[i].act){glColor3f(li,0,0);}else{glColor3f(li,li,li);}
			glNormalv(m[i].n[1]);
			glTexCoord2f(m[i].tx[1],m[i].ty[1]);
			glVertexv(p[m[i].p[1]].c);
			li = 0.64f*m[i].n[2].z;if(li<0.0f){li=0.0f;}li+=0.32f;
			if(m[i].act){glColor3f(li,0,0);}else{glColor3f(li,li,li);}
			glNormalv(m[i].n[2]);
			glTexCoord2f(m[i].tx[2],m[i].ty[2]);
			glVertexv(p[m[i].p[2]].c);
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
		//glDisable(GL_LIGHTING);
	}
	//if(dnorm){
	glBegin(GL_LINES);
	for(int i=0;i<nm;i++){
		if(m[i].act&&m[i].vis){
			if(m[i].cn==0){glColor3f(1,0,1);}else{glColor3f(0,0,1);}
			glVertexv(transform(p[m[i].p[0]].c,type));
			glVertexv(transform(p[m[i].p[0]].c+0.2f*m[i].n[0],type));
			if(m[i].cn==1){glColor3f(1,0,1);}else{glColor3f(0,0,1);}
			glVertexv(transform(p[m[i].p[1]].c,type));
			glVertexv(transform(p[m[i].p[1]].c+0.2f*m[i].n[1],type));
			if(m[i].cn==2){glColor3f(1,0,1);}else{glColor3f(0,0,1);}
			glVertexv(transform(p[m[i].p[2]].c,type));
			glVertexv(transform(p[m[i].p[2]].c+0.2f*m[i].n[2],type));
		}
	}
	glEnd();
	glBegin(GL_POINTS);
	for(int i=0;i<nm;i++){
		if(m[i].act&&m[i].vis){
			if(m[i].cn==0){glColor3f(1,0,1);}else{glColor3f(0,0,1);}
			glVertexv(transform(p[m[i].p[0]].c,type));
			glVertexv(transform(p[m[i].p[0]].c+0.2f*m[i].n[0],type));
			if(m[i].cn==1){glColor3f(1,0,1);}else{glColor3f(0,0,1);}
			glVertexv(transform(p[m[i].p[1]].c,type));
			glVertexv(transform(p[m[i].p[1]].c+0.2f*m[i].n[1],type));
			if(m[i].cn==2){glColor3f(1,0,1);}else{glColor3f(0,0,1);}
			glVertexv(transform(p[m[i].p[2]].c,type));
			glVertexv(transform(p[m[i].p[2]].c+0.2f*m[i].n[2],type));
		}
	}
	glEnd();
	//}
	if(dline){
		glBegin(GL_LINES);
		for(int i=0;i<nl;i++){
			if(!l[i].vis){continue;}
			if(l[i].act){glColor3f(1,0,0);}
			else{glColor3f(0.64f,0.64f,0);}
			glVertexv(transform(p[l[i].p[0]].c,type));
			glVertexv(transform(p[l[i].p[1]].c,type));
		}
		glEnd();
	}
	glBegin(GL_POINTS);
	for(int i=0;i<np;i++){
		if(!p[i].vis){continue;}
		if(p[i].act){glColor3f(1,0,0);}
		else{glColor3f(0.48f,0.48f,0.48f);}
		glVertexv(transform(p[i].c,type));
	}
	glEnd();
}

void removeall(){
	nl=0;
	np=0;
	nm=0;
	delete[] p;
	delete[] l;
	delete[] m;
}
