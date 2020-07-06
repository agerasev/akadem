#define TYPE_WHEEL	0x02
#define TYPE_DOOR	0x04
#define TYPE_BUMPER	0x06

bool saving = 0, opening = 0;

void savescene(){
	saving = 1;
	SDL_WM_SetCaption("SAVING FILE...",NULL);
	
	int ib;//integer buffer
	float fb;//float buffer
	
	//creating file
	std::ofstream file_out("out.hmdl");
	file_out.close();
	
	std::fstream scene("out.hmdl",std::ios::binary|std::ios::in|std::ios::out);
	
	//writing version
	ib = 204;
	scene.write(reinterpret_cast<char*>(&ib),sizeof(int));
	
	//writing numbers of
	//points
	ib = np;
	scene.write(reinterpret_cast<char*>(&ib),sizeof(int));
	//lines
	ib = nl;
	scene.write(reinterpret_cast<char*>(&ib),sizeof(int));
	//meshes
	ib = nm;
	scene.write(reinterpret_cast<char*>(&ib),sizeof(int));
	
	//printing points
	for(int i=0;i<np;i++){
		fb = p[i].c.x;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = p[i].c.y;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = p[i].c.z;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
	}
	
	//printing lines
	for(int i=0;i<nl;i++){
		ib = l[i].p[0];
		scene.write(reinterpret_cast<char*>(&ib),sizeof(int));
		ib = l[i].p[1];
		scene.write(reinterpret_cast<char*>(&ib),sizeof(int));
	}
	
	//printing meshes
	for(int i=0;i<nm;i++){
		ib = m[i].p[0];
		scene.write(reinterpret_cast<char*>(&ib),sizeof(int));
		ib = m[i].p[1];
		scene.write(reinterpret_cast<char*>(&ib),sizeof(int));
		ib = m[i].p[2];
		scene.write(reinterpret_cast<char*>(&ib),sizeof(int));
		//normals
		fb = m[i].n[0].x;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].n[0].y;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].n[0].z;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].n[1].x;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].n[1].y;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].n[1].z;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].n[2].x;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].n[2].y;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].n[2].z;
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		//texture
		fb = m[i].tx[0];
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].ty[0];
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].tx[1];
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].ty[1];
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].tx[2];
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
		fb = m[i].ty[2];
		scene.write(reinterpret_cast<char*>(&fb),sizeof(float));
	}
	
	//closing file
	scene.close();
	saving = 0;
	SDL_WM_SetCaption("SAVED!",NULL);
}

void openscene(){
	opening = 1;
	SDL_WM_SetCaption("OPENING FILE...",NULL);
	
    int ib;//integer buffer
	float fb;//float buffer
	//opening file
	std::fstream scene("in.hmdl",std::ios::binary|std::ios::in|std::ios::out);
	removeall();
	
	//reading version
	scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
	if(ib != 204){SDL_WM_SetCaption("FAILED! UNKNOWN VERSION!",NULL);return;}
	
	//reading numbers of
	//points
	scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
	np = ib;
	p = new point[np];
	//lines
	scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
	nl = ib;
	l = new line[nl];
	//meshes
	scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
	nm = ib;
	m = new mesh[nm];
	
	//printing points
	for(int i=0;i<np;i++){
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		p[i].c.x = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		p[i].c.y = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		p[i].c.z = fb;
	}
	
	//printing lines
	for(int i=0;i<nl;i++){
		scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
		l[i].p[0] = ib;
		scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
		l[i].p[1] = ib;
	}
	
	//printing meshes
	for(int i=0;i<nm;i++){
		scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
		m[i].p[0] = ib;
		scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
		m[i].p[1] = ib;
		scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
		m[i].p[2] = ib;
		//normals
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].n[0].x = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].n[0].y = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].n[0].z = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].n[1].x = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].n[1].y = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].n[1].z = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].n[2].x = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].n[2].y = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].n[2].z = fb;
		//texture
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].tx[0] = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].ty[0] = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].tx[1] = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].ty[1] = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].tx[2] = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		m[i].ty[2] = fb;
	}
	
	//closing file
	scene.close();
	opening = 0;
	SDL_WM_SetCaption("OPENED!",NULL);
}
