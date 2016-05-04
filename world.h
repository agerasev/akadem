#include"ground.h"
#include"building.h"
#include"plant.h"
#include"vehicle.h"
#include"animal.h"
#include"human.h"
#include"thing.h"

#include"collision.h"

class world{
	private:
	
	ground 		* gro; 		unsigned int 	ngro;
	building 	* bui; 		unsigned int 	nbui;
	plant 		* pla;  	unsigned int 	npla;
	vehicle 	* veh;  	unsigned int 	nveh;
	animal 		* ani;  	unsigned int 	nani;
	human 		* hum;  	unsigned int 	nhum;
	thing 		* thi;  	unsigned int 	nthi;
	
	public:
		
	human * chum;
	vehicle * cveh;
	
	world(){
		ngro = 0;
		nbui = 0;
		npla = 0;
		nveh = 0;
		nani = 0;
		nhum = 0;
		nthi = 0;
	}
	
	void init(){
		ngro = 1;
		gro = new ground[ngro];
		for(unsigned int i=0;i<ngro;i++){
			gro[i].init();
		}
		nveh = 1;
		veh = new vehicle[nveh];
		for(unsigned int i=0;i<nveh;i++){
	 		vect vehpos(12+16*i,12,0);
			veh[i].create(vehpos);
		}
		cveh = &veh[0];
	}
	
	void interact(){
		for(unsigned int i=0;i<ngro;i++){
			for(unsigned int j=0;j<nveh;j++){
				veh[j].collide(&gro[i]);
			}
		}
	}
	
	void grav(){
		for(unsigned int j=0;j<nveh;j++){
			veh[j].grav();
		}
	}
	
	void frict(){
		for(unsigned int i=0;i<ngro;i++){
			for(unsigned int j=0;j<nveh;j++){
				//veh[j].frict(&gro[i]);
			}
		}
	}
	
	void step(){
		for(unsigned int i=0;i<nveh;i++){
			veh[i].step();
		}
	}
	
	void draw(){
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glBegin(GL_TRIANGLES);
		for(unsigned int i=0;i<ngro;i++){
			gro[i].draw();
		}
		glEnd();
		for(unsigned int i=0;i<nveh;i++){
			veh[i].draw();
		}
	}
	
	void remove(){
		//removing grounds
		for(unsigned int i=0;i<ngro;i++){
			gro[i].remove();
		}
		ngro = 0;
		delete[] gro;
		//removing vehicles
		for(unsigned int i=0;i<nveh;i++){
			veh[i].remove();
		}
		nveh = 0;
		delete[] veh;
	}
	
	void cfreeze(){
		for(unsigned int i=0;i<nveh;i++){
			veh[i].cfreeze();
		}
	}
	void tfreeze(){
		for(unsigned int i=0;i<nveh;i++){
			veh[i].tfreeze();
		}
	}
};
