//REDEFINING
void glVertexv(vect v){
	glVertex3f(v.x,v.y,v.z);
}

void glTexCoordv(vect v){
	glTexCoord2f(v.x,v.y);
}

void glNormalv(vect n){
	 glNormal3f(n.x,n.y,n.z);
}

void gluLookAt(vect ac, vect ad, vect au){
	gluLookAt(ac.x,ac.y,ac.z,ad.x,ad.y,ad.z,au.x,au.y,au.z);
}
