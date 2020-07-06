bool model_loading = 0;

class model{
	public:
	vertex * p; int np;
	line * l; int nl;
	mesh * m; int nm;
}mdl;

void loadmodel(){
	model_loading = 1;
	
    int ib;//integer buffer
	float fb;//float buffer
	//opening file
	std::fstream scene("models/l200.hmdl",std::ios::binary|std::ios::in|std::ios::out);
	
	//reading version
	scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
	if(ib != 204){return;}
	
	//reading numbers of
	//points
	scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
	mdl.np = ib;
	mdl.p = new vertex[mdl.np];
	//lines
	scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
	mdl.nl = ib;
	mdl.l = new line[mdl.nl];
	//meshes
	scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
	mdl.nm = ib;
	mdl.m = new mesh[mdl.nm];
	
	//printing points
	for(int i=0;i<mdl.np;i++){
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.p[i].c.x = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.p[i].c.y = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.p[i].c.z = fb;
	}
	
	//printing lines
	for(int i=0;i<mdl.nl;i++){
		scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
		mdl.l[i].p[0] = ib;
		scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
		mdl.l[i].p[1] = ib;
	}
	
	//printing meshes
	for(int i=0;i<mdl.nm;i++){
		scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
		mdl.m[i].p[0] = ib;
		scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
		mdl.m[i].p[1] = ib;
		scene.read(reinterpret_cast<char*>(&ib),sizeof(int));
		mdl.m[i].p[2] = ib;
		//normals
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].n[0].x = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].n[0].y = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].n[0].z = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].n[1].x = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].n[1].y = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].n[1].z = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].n[2].x = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].n[2].y = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].n[2].z = fb;
		//textures
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].tx[0] = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].ty[0] = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].tx[1] = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].ty[1] = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].tx[2] = fb;
		scene.read(reinterpret_cast<char*>(&fb),sizeof(float));
		mdl.m[i].ty[2] = fb;
	}
	
	//closing file
	scene.close();
	model_loading = 0;
}
