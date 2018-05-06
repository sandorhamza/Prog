#include <iostream>
#include <fstream>

#define BE"be.txt"
#define KI"ki.txt"


using namespace std;

int main()
{
    string kulcs="08234932";
    int db=0;
    char c;
    ifstream be(BE,ios::binary);
    ofstream ki(KI);
    while(be.get(c))
    {
        for(int i=7;i>=0;i--)
        {
            cout<<((c>>i)&1);
        }cout<<endl;
        c^=kulcs[db%kulcs.length()];
        cout<<endl;
        for(int i=7;i>=0;i--)
        {
            cout<<((kulcs[0]>>i)&1);
        }
        cout<<endl;
        for(int i=7;i>=0;i--)
        {
            cout<<((c>>i)&1);
        }
        cout<<endl<<"============"<<endl;
        ki<<c;
        db++;
    }
    ki.close();
    be.close();
    return 0;

}
