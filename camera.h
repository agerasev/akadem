class camera{
	public:
	vect * pos;
	vect * dir;
	vect * top;
	float dis;
	bool ini;
	bool abs;
	camera(){
		ini=0;
		abs=0;
	}
	void create(){
		pos = new vect;
		dir = new vect;
		top = new vect;
		pos->set(0,0,5);
		dir->set(0,1,0);
		top->set(0,0,1);
		dis = 0.0f;
		ini = 1;
		abs = 1;
	}
	void attract(vect * ap){
		pos = ap;
		dir = new vect;
		top = new vect;
		dir->set(0,1,0);
		top->set(0,0,1);
		dis = 6.0f;
		ini = 1;
		abs = 0;
	}
	void put(){
		if(dis){gluLookAt(*pos-*dir*dis,*pos,*top);}
		else{gluLookAt(*pos,*pos+*dir,*top);}
	}
};
