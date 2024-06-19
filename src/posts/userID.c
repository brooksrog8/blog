#include <stdio.h>       
#include <Windows.h>     
  

int main() {

    GEOID UserGeoID = GetUserGeoID(0x10);
    printf("UserGeoID: %d\n", UserGeoID);
    
    return 0;
}
