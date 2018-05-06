#include <iostream>
#include <fstream>
#include <string>

#define BE "ki.txt" 		//feltörendő fájl neve

using namespace std;

bool clean(string s2)
{
    return (string::npos!=s2.find("ha")&&string::npos!=s2.find("az")&&string::npos!=s2.find("hogy"))&&string::npos!=s2.find("nem");
}

string exor(string kulcs, string titkos)
{
    for (int i=0;i<titkos.length();++i)
       {
            titkos[i]^=kulcs[i%kulcs.length()];
        }
        return titkos;
}

int main(void)
{

    string kulcs="00000";	//ide annyi 0 kell ahány karakterű a kód
    string titkos="";
    char c;					
    ifstream be(BE,ios::binary);
    while(be.get(c))
    {
        titkos+=c;
    }
    be.close();
    int start = 'A';
    int end = 'Z';
    #pragma omp parallel for
    for (int ii = start; ii <= end; ++ii)
        {
        for (int ji = start; ji <= end; ++ji)
            for (int ki = start; ki <= end; ++ki)
                for (int li = start; li <= end; ++li)
                   for (int mi = start; mi <= end; ++mi)
                        //for (int ni = start; ni <= end; ++ni)
                            //for (int oi = start; oi <= end; ++oi)
                                //for (int pi = start; pi <= end; ++pi)
                                    {
                                        string kulcs="00000";		//ide annyi 0 kell ahány karakterű a kód
                                        kulcs[0] = ii;
                                        kulcs[1] = ji;
                                        kulcs[2] = ki;
                                        kulcs[3] = li;
                                        kulcs[4] = mi;
                                        //kulcs[5] = ni;
                                        //kulcs[6] = oi;
                                        //kulcs[7] = pi;
                                        string buffer;
                                        buffer=exor(kulcs,titkos);
                                        if (clean(buffer))
                                        {
                                            cout<<endl<<kulcs<<endl;
                                            cout<<buffer<<endl;
                                        }
                                    }
        }
  return 0;
}
