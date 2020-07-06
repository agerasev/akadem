class light{
	public:
	float amb[4];
	float dif[4];
	float pos[4];
	GLuint id;
	void enable(){
		glEnable(id);
	}
	void disable(){
		glDisable(id);
	}
	void setid(GLuint aid){
		id = aid;
	}
	void setposition(vect ap, float far){
		pos[0] = ap.x;
		pos[1] = ap.y;
		pos[2] = ap.z;
		pos[3] = far;
	}
	void setposition(float ax, float ay, float az, float far){
		pos[0] = ax;
		pos[1] = ay;
		pos[2] = az;
		pos[3] = far;
	}
	void setambient(float ar, float ag, float ab){
		amb[0] = ar;
		amb[1] = ag;
		amb[2] = ab;
		amb[3] = 1.0f;
	}
	void setdiffuse(float ar, float ag, float ab){
		dif[0] = ar;
		dif[1] = ag;
		dif[2] = ab;
		dif[3] = 1.0f;
	}
	void put(){
		glLightfv(id,GL_AMBIENT,amb);
		glLightfv(id,GL_DIFFUSE,dif);
		glLightfv(id,GL_POSITION,pos);
	}
};
