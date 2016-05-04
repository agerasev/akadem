class matrix{
	public:
	float ** e;
	unsigned int x,y;
	matrix(){
		x = 0;
		y = 0;
	}
	void create(unsigned int ay, unsigned int az){
		e = new float*[ay];
		for(int i=0;i<ay;i++){
			e[i] = new float[ax];
		}
	}
	void remove(){
		x = 0; y = 0;
		for(int i=0;i<y;i++){
			delete[] e[i];
		}
		delete e;
	}
};
