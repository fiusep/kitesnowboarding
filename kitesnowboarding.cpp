/*!
\author Giuseppe Taronno
\version 1.0
\brief Questo software simula un evento dove si svolge una gara di KiteSnowboarding.
\file main.cpp
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#define file "gara.txt"
using namespace std;

/*!
\struct anagrafica
\brief Nella struct sono contenuti i dati dei partecipanti.
*/
struct anagrafica
{
    string cognome, matricola;
    int distanza = 0, x[30], y[30], tempo;
};

/*!
\fn registra
\brief Questa funzione chiede l'inserimento del cognome del partecipante e genera casualmente il suo codice matricola.
\param num
\brief Contiene il numero di partecipanti.
\param partecipanti
\brief Variabile della struct con informazioni relative ai partecipanti in generale.
*/
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

/*!
\fn stampa
\brief Stampa il contenuto del file.
\param partecipanti
*/
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

/*!
\fn coordinate
\brief Genera casualmente le coordinate per ogni concorrente e le scrive nel file.
\param num
\param partecipanti
*/
void coordinate (int num, anagrafica partecipanti[])
{
    for (int c = 0; c < num; c++)
    {
        partecipanti[c].tempo = rand()%21+10;
        for (int j = 0; j < partecipanti[c].tempo; j++)
        {
            partecipanti[c].x[j] = rand()%101;
            partecipanti[c].y[j] = rand()%101;
        }
    }

    ofstream fout (file);

    for (int c = 0; c < num; c++)
    {
        fout << partecipanti[c].matricola << ", " << partecipanti[c].cognome << endl << "COORDINATE DELLA MEZZ'ORA: ";
        for (int j = 0; j < partecipanti[c].tempo; j++)
        {
            fout << partecipanti[c].x[j] << ";" << partecipanti[c].y[j] << "  ";
        }
        fout << endl << endl;
    }

    fout.close();
}

/*!
\fn distanza
\brief Acquisisce le coordinate x e y e, tramite la formula euclidea della distanza, calcola il percorso di ogni partecipante.
\param num
\param partecipanti
*/
void distanza (int num, anagrafica partecipanti[])
{
    for(int c = 0; c < num; c++)
    {
        for(int j = 0; j < partecipanti[c].tempo; j++)
        {
            partecipanti[c].distanza = abs(partecipanti[c].distanza + sqrt(pow((partecipanti[c].x[j] - partecipanti[c].x[j+1]), 2) + pow((partecipanti[c].y[j] - partecipanti[c].y[j+1]), 2)));
        }
    }
}

/*!
\fn primi
\brief Funzione che contiene l'algoritmo per smistare i primi tre classificati.
\param num
\param partecipanti
\param podio
\brief Variabile della struct dove sono ordinati i primi tre classificati.
*/
void primi (int num, anagrafica partecipanti[], anagrafica podio[])
{
    for(int c = 0; c < num; c++)
    {
        for(int j = c+1; j < num; j++)
        {
            if(partecipanti[j].distanza > partecipanti[c].distanza)
            {
                anagrafica temp = partecipanti[c];
                partecipanti[c] = partecipanti[j];
                partecipanti[j] = temp;
            }
        }
    }

    for(int c = 0; c < 3; c++)
    {
        podio[c] = partecipanti[c];
    }
}

/*!
\fn main
\brief Parte centrale del programma dove vengono descritti i vari avvenimenti e vengono richiamate le funzioni per il corretto funzionamento del programma.
*/
int main()
{
    srand(time(NULL));
    string sc;
    int num;

    cout<<"***BENVENUTO ALLA GARA DI KITE-SNOWBOARDING!!***"<<endl;

    do{
        cout<<"Registra qualche atleta per dare il via alla competizione (min 3, max 20), sei d'accordo? (s/n)"<<endl;
        cin>>sc;
    }while(sc != "s" && sc != "n");

    if (sc == "s")
    {
        do{
            cout<<"Quanti atleti vuoi inserire? ";
            cin>>num;
        }while(num < 3 || num > 20);
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
    cout<<"Essi sono indicati con i loro codice matricola e i loro cognomi"<<endl;
    cout<<"Ognuno di loro ha diritto ad un massimo di 30 minuti, con possibilita' di ritirarsi anche prima." << endl << endl;

    cout<<endl<<"Constatate le regole ed i partecipanti, possiamo dare il via alla competizione e visionare i risultati"<<endl;
    cout<<"sei pronto? (s/n) ";
    do{
        cin>>sc;
        if (sc == "n")
            cout<<"ora? ";
    }while(sc != "s");

    coordinate(num, partecipanti);
    system("cls");
    stampa(partecipanti);

    cout << "Un po' disordinato, non trovi?" <<endl;
    cout << "Mettiamo un po' d'ordine calcolando le distanze percorse da ogni partecipante\nDimmi quando sei pronto (s/n) ";
        do{
        cin>>sc;
        if (sc == "n")
            cout<<"ora? ";
    }while(sc != "s");

    distanza(num, partecipanti);

    system("cls");
    cout << "perfetto, le distanze sono state calcolate, ecco elencati tutti i partecipanti con la loro distanza:"<< endl << endl;

    ofstream fout (file);
    for (int c = 0; c < num; c++)
        fout << partecipanti[c].matricola << ", " << partecipanti[c].cognome << " DISTANZA PERCORSA: " << partecipanti[c].distanza << " m" << endl << endl;
    fout.close();

    stampa(partecipanti);

    anagrafica podio[3];

    cout << "perfetto, ora che abbiamo i risultati e' il momento di svelare il podio! sei pronto? (s/n) ";
    do{
        cin>>sc;
        if (sc == "n")
            cout<<"ora? ";
    }while(sc != "s");

    primi(num, partecipanti, podio);

    system("cls");
    cout << "Grazie per aver seguito questo fantastico evento avviatosi ormai alla conclusione. Di seguito e' riportato il podio dei nostri atleti." << endl << endl;

    for (int c = 0; c < 3; c++)
        cout << c+1 << "> " << podio[c].matricola << " - " << podio[c].cognome << " - " << podio[c].distanza << " m" << endl;

    cout << endl << endl << "Dunque il nostro vincitore e' " << podio[0].cognome << " con " << podio[0].distanza << " metri percorsi, ottimo lavoro.\nSperiamo di trovarvi ad assistere anche alla prossima edizione. ARRIVEDERCI!!!" << endl;

    return 0;
}