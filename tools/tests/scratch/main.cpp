#include <iostream>
#include <string>
//#include "wpp.h"

using namespace std;

int main() {
    for (int i = 6; i <=16; i++){
        for (int j = 17; j <=31; j++){
            cout << "http://www.submarinoviagens.com.br/travel/resultado-passagens.aspx?searchtype=Air&Origem=BHZ&Destino=BER&Origem=BER&Destino=BHZ&Proximity=&ProximityId=0&Data=" ;
            cout << i;
            cout << "-07-2017&RoundTrip=1&Data=" ;
            cout << j ;
            cout << "-07-2017&SomenteDireto=false&ExecutiveFlight=false&NumADT=1&NumCHD=0&NumINF=0&Hora=&Hora=&Multi=false&DataConsulta=Wed%20Jun%2021%202017%2020:33:01%20GMT-0300%20(-03)&Nav=Safari%2010" ;
            cout << endl;
        }
    }
    return 0;
}