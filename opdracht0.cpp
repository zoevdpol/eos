#include <iostream>
#define max_len_naam 8

int main(){
char a[max_len_naam];

std::cout << "voer naam in" << std::endl;
std::cin.getline(a, max_len_naam);
for(int i = 0; i < max_len_naam; i++){
    if(a[i] == 'e'){
        a[i] = '3';
    }
    if(a[i] == 'l'){
        a[i]='1';
    }
    if(a[i] == 'o'){
        a[i]='0';
    }
    if(a[i] == 't'){
        a[i] = '7';
    }

}

std::cout << a;
}