bool insidetest(float px, float py, float sx, float sy, float ax, float ay){
	if(sx>0&&sy>0){
		if(ax<px+sx&&ax>px&&ay<py+sy&&ay>py){return 1;}
		return 0;
	}
	if(sx<0&&sy>0){
		if(ax>px+sx&&ax<px&&ay<py+sy&&ay>py){return 1;}
		return 0;
	}
	if(sx>0&&sy<0){
		if(ax<px+sx&&ax>px&&ay>py+sy&&ay<py){return 1;}
		return 0;
	}
	if(sx<0&&sy<0){
		if(ax>px+sx&&ax<px&&ay>py+sy&&ay<py){return 1;}
		return 0;
	}
	return 0;
}

float mod(float a){
	if(a>=0.0f){return a;}
	return -a;
}

char * ftos(float arg){
	int sap = 4;
	char * str;
	int lln = 0;
	bool ltz = 0;//lower than zero
	if(arg<0){arg=-arg; lln += 1; ltz = 1;}
	int num = (int)arg;
	if(!num){lln += 1; goto post;}
	if(!(num/10)){lln += 1; goto post;}
	if(!(num/100)){lln += 2; goto post;}
	if(!(num/1000)){lln += 3; goto post;}
	if(!(num/10000)){lln += 4; goto post;}
	post:
	str = new char[lln+sap+2];
	str[lln+sap+1] = 0;
	if(ltz){str[0]='-';}
	
	for(int i=0;i<lln-ltz;i++){
		int ten = 1;
		for(int j=0;j<i;j++){
			ten*=10;
		}
		if(((num/ten)%10)==0){str[lln-i-1]='0';}
		if(((num/ten)%10)==1){str[lln-i-1]='1';}
		if(((num/ten)%10)==2){str[lln-i-1]='2';}
		if(((num/ten)%10)==3){str[lln-i-1]='3';}
		if(((num/ten)%10)==4){str[lln-i-1]='4';}
		if(((num/ten)%10)==5){str[lln-i-1]='5';}
		if(((num/ten)%10)==6){str[lln-i-1]='6';}
		if(((num/ten)%10)==7){str[lln-i-1]='7';}
		if(((num/ten)%10)==8){str[lln-i-1]='8';}
		if(((num/ten)%10)==9){str[lln-i-1]='9';}
	}
	
	num = (int)(((arg)-(float)num)*10000);
	str[lln] = '.';
	
	for(int i=0;i<sap;i++){
		int ten = 1;
		for(int j=0;j<i;j++){
			ten*=10;
		}
		if(((num/ten)%10)==0){str[lln+sap-i]='0';}
		if(((num/ten)%10)==1){str[lln+sap-i]='1';}
		if(((num/ten)%10)==2){str[lln+sap-i]='2';}
		if(((num/ten)%10)==3){str[lln+sap-i]='3';}
		if(((num/ten)%10)==4){str[lln+sap-i]='4';}
		if(((num/ten)%10)==5){str[lln+sap-i]='5';}
		if(((num/ten)%10)==6){str[lln+sap-i]='6';}
		if(((num/ten)%10)==7){str[lln+sap-i]='7';}
		if(((num/ten)%10)==8){str[lln+sap-i]='8';}
		if(((num/ten)%10)==9){str[lln+sap-i]='9';}
	}
	
	return str;
}

char * scrd(vect a){
	char * str;
	char *cx, *cy, *cz;
	cx = ftos(a.x); cy = ftos(a.y); cz = ftos(a.z);
	int ln = 14;
	for(int i=0;;i++){
		if(cx[i]!=0){ln++;}
		else{break;}
	}
	for(int i=0;;i++){
		if(cy[i]!=0){ln++;}
		else{break;}
	}
	for(int i=0;;i++){
		if(cz[i]!=0){ln++;}
		else{break;}
	}
	str = new char[ln+1];
	str[ln] = 0;
	int cp = 0;
	str[cp++]='x'; str[cp++]=':'; str[cp++]=' ';
	for(int i=0;;i++){
		if(cx[i]!=0){str[cp] = cx[i]; cp++;}
		else{break;}
	}
	str[cp++]=';'; str[cp++]=' '; str[cp++]='y'; str[cp++]=':'; str[cp++]=' ';
	for(int i=0;;i++){
		if(cy[i]!=0){str[cp] = cy[i]; cp++;}
		else{break;}
	}
	str[cp++]=';'; str[cp++]=' '; str[cp++]='z'; str[cp++]=':'; str[cp++]=' ';
	for(int i=0;;i++){
		if(cz[i]!=0){str[cp] = cz[i]; cp++;}
		else{break;}
	}
	str[cp++]=';';
	return str;
}
