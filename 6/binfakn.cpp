#include <iostream>
#include <cmath>
#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <iterator>

class LZWBinFa {
public:
    // ctor
    LZWBinFa() : fa(&gyoker)
    {
    }
    // dtor
    ~LZWBinFa()
    {
        szabadit(gyoker.egyesGyermek());
        szabadit(gyoker.nullasGyermek());
    }
    void operator<<(char b)
    {

        if (b == '0') {

            if (!fa->nullasGyermek()) {

                Csomopont* uj = new Csomopont('0');

                fa->ujNullasGyermek(uj);

                fa = &gyoker;
            }
            else {

                fa = fa->nullasGyermek();
            }
        }

        else {
            if (!fa->egyesGyermek()) {
                Csomopont* uj = new Csomopont('1');
                fa->ujEgyesGyermek(uj);
                fa = &gyoker;
            }
            else {
                fa = fa->egyesGyermek();
            }
        }
    }

    void kiir(void)
    {

        melyseg = 0;

        kiir(&gyoker, std::cout);
    }
    int getMelyseg(void);
    double getAtlag(void);
    double getSzoras(void);
    friend std::ostream& operator<<(std::ostream& os, LZWBinFa& bf)
    {
        bf.kiir(os);
        return os;
    }

    void kiir(std::ostream& os)
    {
        melyseg = 0;
        kiir(&gyoker, os);
    }



    class Csomopont {
    public:
        Csomopont(char b = '/')
            : betu(b)
            , balNulla(0)
            , jobbEgy(0){};
        ~Csomopont(){};

        Csomopont* nullasGyermek() const
        {
            return balNulla;
        }

        Csomopont* egyesGyermek() const
        {
            return jobbEgy;
        }

        void ujNullasGyermek(Csomopont* gy)
        {
            balNulla = gy;
        }

        void ujEgyesGyermek(Csomopont* gy)
        {
            jobbEgy = gy;
        }

        char getBetu() const
        {
            return betu;
        }
        Csomopont(const Csomopont&)
        {
        	
        }
    private:
        char betu;

        Csomopont* balNulla;
        Csomopont* jobbEgy;

        
        Csomopont& operator=(const Csomopont&);
    };
private:
    Csomopont* fa;

    int melyseg, atlagosszeg, atlagdb;
    double szorasosszeg;

    
    

    void kiir(Csomopont* elem, std::ostream& os)
    {

        if (elem != NULL) {
            ++melyseg;
            for (int i = 0; i < melyseg; ++i)
                os << "---";
            os << elem->getBetu() << "(" << melyseg - 1 << ")" << std::endl;
            kiir(elem->egyesGyermek(), os);

            
            kiir(elem->nullasGyermek(), os);

            --melyseg;
        }
    }
    void szabadit(Csomopont* elem)
    {
        if (elem != NULL) {
            szabadit(elem->egyesGyermek());
            szabadit(elem->nullasGyermek());

            delete elem;
        }
    }
     

protected:
    Csomopont gyoker;
    int maxMelyseg;
    double atlag, szoras;

    void rmelyseg(Csomopont* elem);
    void ratlag(Csomopont* elem);
    void rszoras(Csomopont* elem);
};

int LZWBinFa::getMelyseg(void)
{
    melyseg = maxMelyseg = 0;
    rmelyseg(&gyoker);
    return maxMelyseg - 1;
}

double
LZWBinFa::getAtlag(void)
{
    melyseg = atlagosszeg = atlagdb = 0;
    ratlag(&gyoker);
    atlag = ((double)atlagosszeg) / atlagdb;
    return atlag;
}

double
LZWBinFa::getSzoras(void)
{
    atlag = getAtlag();
    szorasosszeg = 0.0;
    melyseg = atlagdb = 0;

    rszoras(&gyoker);

    if (atlagdb - 1 > 0)
        szoras = std::sqrt(szorasosszeg / (atlagdb - 1));
    else
        szoras = std::sqrt(szorasosszeg);

    return szoras;
}

void LZWBinFa::rmelyseg(Csomopont* elem)
{
    if (elem != NULL) {
        ++melyseg;
        if (melyseg > maxMelyseg)
            maxMelyseg = melyseg;
        rmelyseg(elem->egyesGyermek());

        rmelyseg(elem->nullasGyermek());
        --melyseg;
    }
}

void LZWBinFa::ratlag(Csomopont* elem)
{
    if (elem != NULL) {
        ++melyseg;
        ratlag(elem->egyesGyermek());
        ratlag(elem->nullasGyermek());
        --melyseg;
        if (elem->egyesGyermek() == NULL && elem->nullasGyermek() == NULL) {
            ++atlagdb;
            atlagosszeg += melyseg;
        }
    }
}

void LZWBinFa::rszoras(Csomopont* elem)
{
    if (elem != NULL) {
        ++melyseg;
        rszoras(elem->egyesGyermek());
        rszoras(elem->nullasGyermek());
        --melyseg;
        if (elem->egyesGyermek() == NULL && elem->nullasGyermek() == NULL) {
            ++atlagdb;
            szorasosszeg += ((melyseg - atlag) * (melyseg - atlag));
        }
    }
}

void usage(void)
{
    std::cout << "Usage: lzwtree in_file -o out_file" << std::endl;
}


int main(int argc, char* argv[])
{
    if (argc != 4) {;

        usage();

        return -1;
    }

    char* inFile = *++argv;

    if (*((*++argv) + 1) != 'o') {
        usage();
        return -2;
    }

    std::fstream beFile(inFile, std::ios_base::in);

    if (!beFile) {
        std::cout << inFile << " nem letezik..." << std::endl;
        usage();
        return -3;
    }

    std::fstream kiFile(*++argv, std::ios_base::out);

    unsigned char b;
    LZWBinFa binFa;

    while (beFile.read((char*)&b, sizeof(unsigned char)))
        if (b == 0x0a)
            break;

    bool kommentben = false;

    int counter = 0;

    while (beFile.read((char*)&b, sizeof(unsigned char)) && counter != sizeof(unsigned char)*2*1024) {

        if (b == 0x3e) {
            kommentben = true;
            continue;
        }

        if (b == 0x0a) {
            kommentben = false;
            continue;
        }

        if (kommentben)
            continue;

        if (b == 0x4e)
            continue;

        for (int i = 0; i < 8; ++i) {

            if (b & 0x80)

                binFa << '1';
            else

               binFa << '0';
            b <<= 1;
        }
  
        counter++;
    }

    std::cout << binFa;

    std::cout << "depth = " << binFa.getMelyseg() << std::endl;
    std::cout << "mean = " << binFa.getAtlag() << std::endl;
   std::cout << "var = " << binFa.getSzoras() << std::endl;
    kiFile.close();
    beFile.close();

    return 0;
}
