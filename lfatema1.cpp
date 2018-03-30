#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
int CxF, CxSigma, q0;
class automat_finit
{
    int CxQ, CxTranzitii, q0, SC;
    char *Sigma;

    struct delta
    {
        int a1, a2;
        char c;
    }*G;

public:
    int *F;
    int tranzitie(int x, char c)
    {
        for(int i = 0; i < CxTranzitii; i++)
            if((G[i].a1 == x) && (G[i].c == c))
                return G[i].a2;
        return -1;
    }

    automat_finit()
    {
        ifstream f("automatfinit.in");
        SC = 0;
        f >> CxQ;
        //f >> CxF;
        F = new int[CxF];
        for(int i = 0; i < CxF; i++)
            f >> F[i];
        //f >> CxSigma;
        Sigma = new char[CxSigma];
        for(int i = 0; i < CxSigma; i++)
            f >> Sigma[i];
        f >> CxTranzitii;
        G = new delta[CxTranzitii];
        for(int i = 0; i < CxTranzitii; i++)
            f >> G[i].a1 >> G[i].c >> G[i].a2;
        q0 = G[0].a1;
        f.close();
    }

    bool citire(char *cuvant)
    {
        int l = strlen(cuvant);
        for(int i = 0; i < l; i++)
        {
            SC = tranzitie(SC, cuvant[i]);
            if(SC == -1) return false;
        }
        for(int i = 0; i < CxF; i++)
            if(SC == F[i]) return true;
        return false;
    }
};

int main()
{
    cout<<"Introduceti cardinalul starilor finale si cardinalul alfabetului"<<endl;
    cin>>CxF>>CxSigma;
    automat_finit A;
    char w[100];
    cin>>w;
    for(int i = 0; i < CxF; i++)
        if(q0 == A.F[i] && w[0] == '*')
        {
            cout<<"Cuvant acceptat!!!";
            return 0;
        }
    if(A.citire(w) == true) cout<<"Cuvant acceptat"<<endl;
    else cout<<"Cuvant respins"<<endl;
}
