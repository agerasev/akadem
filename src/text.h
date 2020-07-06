char * numstr(int num){
	char * str;
	int lln = 0;
	bool ltz = 0;
	if(num<0){num=-num; lln += 1; ltz = 1;}
	if(!num){lln += 1; goto post;}
	if(!(num/10)){lln += 1; goto post;}
	if(!(num/100)){lln += 2; goto post;}
	if(!(num/1000)){lln += 3; goto post;}
	if(!(num/10000)){lln += 4; goto post;}
	if(!(num/100000)){lln += 5; goto post;}
	if(!(num/1000000)){lln += 6; goto post;}
	post:
	str = new char[lln+1];
	str[lln] = 0;
	if(ltz){str[0]='-';}
	
	for(int i=0;i<lln;i++){
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
	
	return str;
}

class text{
	private:
	TTF_Font * font;
	SDL_Color color;
	SDL_Surface * rend;
	int size;
	public:
	void setfont(char * addr, int sz){
		size = sz;
		font = TTF_OpenFont(addr,sz);
	}
	void setcolor(Uint8 r, Uint8 g, Uint8 b){
		color.r = r;
		color.g = g;
		color.b = b;
	}
	SDL_Surface * build(char * text, float * w, float * h){
		int tw,th;
		TTF_SizeText(font,text,&tw,&th);
		*w = tw*gl.pixel; *h = th*gl.pixel;
		return SDL_ConvertSurface(TTF_RenderText_Blended(font,text,color),&gl.sdlformat,SDL_HWSURFACE);
	}
};
