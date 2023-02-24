#include <iostream>
#include <fstream>
#include <time.h>
#define file "gara.txt"
using namespace std;

struct anagrafica
{
    string cognome, matricola;
    int distanza[30];
};

void registra(int &num, anagrafica partecipanti[])
{
    string scl;
    ofstream fout(file);

    for (int c = 0; c < num; c++)
    {
        int appoge;

        cout<<endl<<"il codice matricola verra' generato automaticamente"<<endl;
        cout<<"Cognome: ";
        cin>>partecipanti[c].cognome;

        partecipanti[c].matricola = partecipanti[c].cognome[0];
        appoge = partecipanti[c].cognome.length() / 2;
        partecipanti[c].matricola = partecipanti[c].matricola + partecipanti[c].cognome[appoge];
        appoge = partecipanti[c].cognome.length()-1;
        partecipanti[c].matricola = partecipanti[c].matricola + partecipanti[c].cognome[appoge];

        appoge = rand()%900+100;
        partecipanti[c].matricola = partecipanti[c].matricola + to_string(appoge);

        fout << partecipanti[c].matricola << ", " << partecipanti[c].cognome << endl;
    }

    fout.close();
}

void stampa (anagrafica partecipanti[])
{
    ifstream fin(file);

    string appoge;
    while(!fin.eof())
    {
        getline(fin,appoge);
        cout<<appoge<<endl;
    }

    fin.close();
}

int main()
{
    srand(time(NULL));
    string sc;
    int num;

    cout<<"***BENVENUTO ALLA GARA DI KITE-SNOWBOARDING!!***"<<endl;

    do{
        cout<<"Registra qualche atleta per dare il via alla competizione, sei d'accordo? (s/n)"<<endl;
        cin>>sc;
    }while(sc != "s" && sc != "n");

    if (sc == "s")
    {
        cout<<"Quanti atleti vuoi inserire? ";
        cin>>num;
    }
    else
    {
        cout<<endl<<"e' stato un piacere, purtroppo non ci sono abbastanza atleti per dare il via alla competizione"<<endl;
        return 0;
    }

    anagrafica partecipanti[num];
    registra(num, partecipanti);
    system("cls");
    cout<<"Perfetto, i partecipanti sono pronti e sono elencati qui sotto:"<<endl<<endl;
    stampa(partecipanti);
    cout<<"Essi sono indicati con i loro codice matricola e i loro cognomi"<<endl<<endl;

    return 0;
}