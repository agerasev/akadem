class material{
	public:
	float dif[4];
	float amb[4];
	float spec[4];
	float shin;
	void setamb(float ar, float ag, float ab){
		amb[0] = ar;
		amb[1] = ag;
		amb[2] = ab;
		amb[3] = 1.0f;
	}
	void setdif(float ar, float ag, float ab){
		dif[0] = ar;
		dif[1] = ag;
		dif[2] = ab;
		dif[3] = 1.0f;
	}
	void setspec(float ar, float ag, float ab){
		spec[0] = ar;
		spec[1] = ag;
		spec[2] = ab;
		amb[3] = 1.0f;
	}
	void setshin(float a){
		shin = a;
	}
	void put(){
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dif);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
		glMaterialf(GL_FRONT,GL_SHININESS,shin);
	}
};
