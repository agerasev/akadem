//base elements of vector geometry
#ifndef _vect3d
#define _vect3d

class vect {
	public:
	float x;
	float y;
	float z;
	//constructors
	vect(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	vect(float ax, float ay, float az){
		x = ax;
		y = ay;
		z = az;
	}
	vect(const vect& a){
		x = a.x;
		y = a.y;
		z = a.z;
	}
	//operations
	friend vect operator+(vect a, vect b){
		vect r;
		r.x = a.x + b.x;
		r.y = a.y + b.y;
		r.z = a.z + b.z;
		return r;
	}
	friend vect operator-(vect a, vect b){
		vect r;
		r.x = a.x - b.x;
		r.y = a.y - b.y;
		r.z = a.z - b.z;
		return r;
	}
	friend vect operator-(vect a){
		vect r;
		r.x = -a.x;
		r.y = -a.y;
		r.z = -a.z;
		return r;
	}
	
	friend void operator+=(vect &a, vect b){
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
	}
	friend void operator-=(vect &a, vect b){
		a.x -= b.x;
		a.y -= b.y;
		a.z -= b.z;
	}
	
	friend float operator*(vect a, vect b){
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}
	
	friend vect operator*(vect a, float b){
		vect r;
		r.x = a.x*b;
		r.y = a.y*b;
		r.z = a.z*b;
		return r;
	}
	
	friend vect operator*(float b, vect a){
		vect r;
		r.x = a.x*b;
		r.y = a.y*b;
		r.z = a.z*b;
		return r;
	}
	
	friend vect operator^(vect a, vect b){
		vect r;
		r.x = a.y*b.z-b.y*a.z;
		r.y = a.z*b.x-b.z*a.x;
		r.z = a.x*b.y-b.x*a.y;
		return r;
	}
	
	friend vect operator/(vect a, float b){
		vect r;
		r.x = a.x/b;
		r.y = a.y/b;
		r.z = a.z/b;
		return r;
	}
	
	void set(float ax, float ay, float az){
		x = ax;
		y = ay;
		z = az;
	}
	void add(float ax, float ay, float az){
		x += ax;
		y += ay;
		z += az;
	}
	void add(vect p){
		x += p.x;
		y += p.y;
		z += p.z;
	}
	void nul(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

float length(vect a){
	return sqrt(a*a);
}

vect norm(vect a){
	return a/sqrt(a*a);
}

//r - angle of rotating, a - rotating axis, v - vector we need to rotate
vect rotate(float r, vect a, vect v){
	vect ret;
	if(r==0.0){return v;}
	float sa = sin(r), ca = cos(r);
	float oa = 1.0f - ca;
	ret.x = v.x*(ca+oa*a.x*a.x) + v.y*(oa*a.x*a.y-sa*a.z) + v.z*(oa*a.x*a.z+sa*a.y);
	ret.y = v.x*(oa*a.y*a.x+sa*a.z) + v.y*(ca+oa*a.y*a.y) + v.z*(oa*a.y*a.z-sa*a.x);
	ret.z = v.x*(oa*a.z*a.x-sa*a.y) + v.y*(oa*a.z*a.y+sa*a.x) + v.z*(ca+oa*a.z*a.z);
	return ret;
}

float angle(vect a1, vect a2, vect * axis){
	vect vm = a1^a2;
	float sm = a1*a2;
	float vml = sqrt(vm*vm);
	if(vml==0.0){return 0;}
	*axis = vm/vml;
	if(sm>0.0){return atan(vml/sm);}
	if(sm==0.0){return M_PI/2.0;}
	if(sm<0.0){return M_PI-atan(-vml/sm);}
}

#endif
//(c)heroin
