#include<math.h>

bool isPrime(int a){
    if(a<=1)    return false;
    for(int i = 2;i<=sqrt(a);i++){
        if(!(a%i))  return false;
    }
    return true;
}
