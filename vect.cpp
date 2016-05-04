vect::vect(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
vect::vect(float ax, float ay, float az){
	x = ax;
	y = ay;
	z = az;
}
vect::vect(const vect& a){
	x = a.x;
	y = a.y;
	z = a.z;
}
//operations
friend vect vect::operator+(vect a, vect b){
	vect r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	return r;
}
friend vect vect::operator-(vect a, vect b){
	vect r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return r;
}
friend vect vect::operator-(vect a){
	vect r;
	r.x = -a.x;
	r.y = -a.y;
	r.z = -a.z;
	return r;
}

friend void vect::operator+=(vect &a, vect b){
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
}
friend void vect::operator-=(vect &a, vect b){
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
}

friend float vect::operator*(vect a, vect b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

friend vect vect::operator*(vect a, float b){
	vect r;
	r.x = a.x*b;
	r.y = a.y*b;
	r.z = a.z*b;
	return r;
}

friend vect vect::operator*(float b, vect a){
	vect r;
	r.x = a.x*b;
	r.y = a.y*b;
	r.z = a.z*b;
	return r;
}

friend vect vect::operator^(vect a, vect b){
	vect r;
	r.x = a.y*b.z-b.y*a.z;
	r.y = a.z*b.x-b.z*a.x;
	r.z = a.x*b.y-b.x*a.y;
	return r;
}

friend vect vect::operator/(vect a, float b){
	vect r;
	r.x = a.x/b;
	r.y = a.y/b;
	r.z = a.z/b;
	return r;
}

void vect::set(float ax, float ay, float az){
	x = ax;
	y = ay;
	z = az;
}
void vect::add(float ax, float ay, float az){
	x += ax;
	y += ay;
	z += az;
}
void vect::add(vect p){
	x += p.x;
	y += p.y;
	z += p.z;
}
void vect::nul(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

//(c)heroin
