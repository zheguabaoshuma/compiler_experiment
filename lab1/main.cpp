#include <iostream>
#define x 10

int main() {
    #ifndef debug
    std::cout<<"in debugging";
    #endif
    int i,n,f;
    std::cin>>n;
    i=2;
    f=1;
    while(i<=n){
        f=f+i;
        i=i+1;
    }
    std::cout<<f<<std::endl;
    std::cout<<x;//macro definition
}
