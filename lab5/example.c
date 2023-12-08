int a;
int getint(int u){
	u=u+1;
    return u+1;
}
int main(){
	a = getint(a);
    getint(a+1);
	if( a>0 ){
		return a+2;
	}
	else{
		return 0;
	}
}
