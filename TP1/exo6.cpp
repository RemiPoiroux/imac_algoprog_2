/* REMARQUE
Le sujet demandait pour certaines fonctions de réfléchir en index (de 0 à n-1)
et pour d'autres en Nieme valeur (de 1 à n)
J'ai donc suivi ces instructions et ai du modifier le main.
////
Par exemple,
Le sujet demandait :
recupere(int n) : Retourne le nième entier de la structure
J'ai donc fait des fonctions qui prennait en argument l'index +1
Et dans le main, il était écrit :
"5e valeur de la liste "<<recupere(&liste, 4)
"5e valeur du tableau "<<recupere(&tableau, 4)
Soit des fonctions qui recherchaient la 5e valeur du tableau
en recherchant l'index 4.
J'ai donc modifié les appels de fonction dans le main
Pour que ca colle avec mes fonctions (changer 4 en 5)
////
Même chose pour les fonction stocke
sujet:
stocke(int n, int valeur) : Redéfini la nième valeur de la structure avec valeur
////
Mais pas pour cherche :
cherche(int valeur) : Retourne l’index de valeur dans la structure ou -1 s’il n’existe pas
*/


#include <iostream>

using namespace std;

struct Noeud{
    int donnee;
    Noeud* suivant;
};

struct Liste{
    Noeud* premier;
    // your code
};

struct DynaTableau{
    int* donnees;
    // your code
    int capacite;
    int taille;
};

//Fonctions pour Liste

void initialise(Liste* liste)
{
    liste->premier=nullptr;
}

bool est_vide(const Liste* liste)
{
    if (liste->premier){
        return false;
    }
    else{
        return true;
    }
}

void ajoute(Liste* liste, int valeur)
{
    if (liste->premier==nullptr){
        Noeud* nouveauNoeud=new Noeud;
        nouveauNoeud->donnee=valeur;
        nouveauNoeud->suivant=nullptr;
        liste->premier=nouveauNoeud;
    }
    else{
        Noeud* dernierNoeud=liste->premier;

        while(dernierNoeud->suivant!=nullptr)
        {
            dernierNoeud=dernierNoeud->suivant;
        }

        Noeud* nouveauNoeud=new Noeud;
        nouveauNoeud->donnee=valeur;
        nouveauNoeud->suivant=nullptr;
        dernierNoeud->suivant=nouveauNoeud;
    }
}

void affiche(const Liste* liste)
{
    Noeud* lireNoeud=liste->premier;

    while (lireNoeud->suivant!=nullptr)
    {
        std::cout<<lireNoeud->donnee<<std::endl;
        lireNoeud=lireNoeud->suivant;
    }
}

int recupere(const Liste* liste, int n)
{
    Noeud* NiemeNoeud=liste->premier;

    for (int i=1; i<n; i++)
    {
        if(NiemeNoeud->suivant!=nullptr)
        {
            NiemeNoeud=NiemeNoeud->suivant;
        }
        else{
           std::cout<<"Il n'y a moins de "<<n<<"valeurs dans la liste."<<std::endl;
           return -1;
        }
    }
    return NiemeNoeud->donnee;
}

int cherche(const Liste* liste, int valeur)
{
    int count=0;

    Noeud* lireNoeud=liste->premier;

    while (lireNoeud!=nullptr)
    {
        if (lireNoeud->donnee==valeur)
        {
               return count;
        }

        lireNoeud=lireNoeud->suivant;
        count++;
    }
    return -1;
}

void stocke(Liste* liste, int n, int valeur)
{
    if (liste->premier==nullptr){
         std::cout<<"La liste est vide."<<std::endl;
    }

    else {
        if (n==1)
        {
            liste->premier->donnee=valeur;
        }

        else{

            Noeud* NiemeNoeud=liste->premier;

            for (int i=1; i<n; i++)
            {
                if(NiemeNoeud->suivant!=nullptr)
                {
                    NiemeNoeud=NiemeNoeud->suivant;
                }
                else{
                   std::cout<<"Il n'y a moins de "<<n<<"valeurs dans la liste."<<std::endl;
                }
            }

            NiemeNoeud->donnee=valeur;
        }
    }
}

//Fonctions pour DynaTableau

void ajoute(DynaTableau* tableau, int valeur)
{
    if (tableau->taille<tableau->capacite-1){
        tableau->capacite++;
        int* newTab= new int[tableau->capacite];
        for (int i=0; i<tableau->taille; i++){
            newTab[i]=tableau->donnees[i];
        }
        delete tableau->donnees;
        tableau->donnees=newTab;
    }

    tableau->donnees[tableau->taille]=valeur;
    tableau->taille++;
}


void initialise(DynaTableau* tableau, int capacite)
{
    tableau->donnees=new int[capacite];
    tableau->capacite=capacite;
    tableau->taille=0;
}

bool est_vide(const DynaTableau* tableau)
{
    if(tableau->taille==0){
        return true;
    }
    else{
        return false;
    }
}

void affiche(const DynaTableau* tableau)
{
    for (int i=0; i<tableau->taille; i++){
        std::cout<<tableau->donnees[i]<<std::endl;
    }
}

int recupere(const DynaTableau* tableau, int n)
{
    if (n>tableau->taille){
        std::cout<<"Il n'y a que "<<tableau->taille<<" valeurs dans le tableau."<<std::endl;
        return 0;
    }
    else {
        return tableau->donnees[n-1];
    }
}

int cherche(const DynaTableau* tableau, int valeur)
{
    for (int i=0; i<tableau->taille; i++){
        if (tableau->donnees[i]==valeur){
            return i;
        }
    }
    return -1;
}

void stocke(DynaTableau* tableau, int n, int valeur)
{
    if (n>tableau->taille){
        std::cout<<"Il n'y a que "<<tableau->taille<<" valeurs dans le tableau."<<std::endl;
    }
    else{
        tableau->donnees[n-1]=valeur;
    }
}

//fonctions pour file

void pousse_file(Liste* liste, int valeur)
{
    Noeud* premierNoeud=new Noeud;
    premierNoeud->donnee=valeur;
    premierNoeud->suivant=liste->premier;
    liste->premier=premierNoeud;

}

int retire_file(Liste* liste)
{
    int premiereVal=liste->premier->donnee;
    liste->premier=liste->premier->suivant;
    return premiereVal;
}

//fonctions pour pile

void pousse_pile(Liste* liste, int valeur)
{
    Noeud* newSommet=new Noeud;
    newSommet->donnee=valeur;
    newSommet->suivant=nullptr;

    if (liste->premier==nullptr){
        liste->premier=newSommet;
    }

    else{
        Noeud* dernierNoeud;
        dernierNoeud=liste->premier;
        while (dernierNoeud->suivant!=nullptr)
        {
            dernierNoeud=dernierNoeud->suivant;
        }
        dernierNoeud->suivant=newSommet;
    }
}

int retire_pile(Liste* liste)
{
    Noeud* dernierNoeud;
    Noeud* avantDernierNoeud;
    dernierNoeud=liste->premier;

    while (dernierNoeud->suivant!=nullptr)
    {
        avantDernierNoeud=dernierNoeud;
        dernierNoeud=dernierNoeud->suivant;
    }

    avantDernierNoeud->suivant=nullptr;

    if (dernierNoeud==liste->premier){
        liste->premier=nullptr;
    }

    return dernierNoeud->donnee;
}


int main()
{
    Liste liste;
    initialise(&liste);
    DynaTableau tableau;
    initialise(&tableau, 5);

    if (!est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (!est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    for (int i=1; i<=7; i++) {
        ajoute(&liste, i*7);
        ajoute(&tableau, i*5);
    }

    if (est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    std::cout << "Elements initiaux:" << std::endl;
    affiche(&liste);
    std::cout<<std::endl;
    affiche(&tableau);
    std::cout << std::endl;

    std::cout << "5e valeur de la liste " << recupere(&liste, 5) << std::endl;
    std::cout << "5e valeur du tableau " << recupere(&tableau, 5) << std::endl;

    std::cout << "21 se trouve dans la liste à l'index " << cherche(&liste, 21) << std::endl;
    std::cout << "15 se trouve dans le tableau à l'index " << cherche(&tableau, 15) << std::endl;

    stocke(&liste, 4, 7);
    stocke(&tableau, 4, 7);

    std::cout << "Elements après stockage de 7 à la 4e valeur :" << std::endl;
    affiche(&liste);
    std::cout<<std::endl;
    affiche(&tableau);
    std::cout << std::endl;

    Liste pile; // DynaTableau pile;
    Liste file; // DynaTableau file;

    initialise(&pile);
    initialise(&file);

    for (int i=1; i<=7; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    int compteur = 10;
    while(!est_vide(&file) && compteur > 0)
    {
        std::cout << retire_file(&file) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    std::cout<<std::endl;

    compteur = 10;
    while(!est_vide(&pile) && compteur > 0)
    {
        std::cout << retire_pile(&pile) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    return 0;
}
