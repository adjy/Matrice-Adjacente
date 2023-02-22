#include <iostream>
#include <fstream>

/*
    DESIR Adjy Sedar
    Groupe 2
    Licence 2 Info
*/

using namespace std;
struct MatriceAdjacence {
    int ordre; // nombre de sommets du graphe
    int *coeff; // tableau contenant les (ordre x ordre) coefficients de la matrice
};

void creerMatrice(MatriceAdjacence &m, int size){
    m.ordre = size; // La taille de la matrice (size x size)
    m.coeff = new int[size * size]; // Creation de ma matrice (size x size)

    for(int i = 0; i< size; i++ )
        for(int j = 0; j< size; j++)
            m.coeff[i*size + j] = 0; // Remplissage de la matrice avec des 0
}

void afficher(MatriceAdjacence mat){ // Afficher ma matrice
    for(int i = 0; i< mat.ordre; i++){
        for(int j = 0; j< mat.ordre; j++)
            cout<<mat.coeff[i*mat.ordre +j]<<" ";    
        cout<<endl;
        } 
}

bool charger(char *nomFichier, MatriceAdjacence &mat){
    ifstream fichier;//flot d’entrée

    // ouverture du fichier en mode lecture
    fichier.open(nomFichier, ios::in);

    //test d'ouverture du fichier
    if( !fichier.is_open()){
        cout << "erreur d'ouverture "<< endl;
        return false;
    }

   
    fichier >> mat.ordre ; // recupere la première valeur du fichier comme la taille de la matrice
    mat.coeff = new int[mat.ordre * mat.ordre]; // Creation de la matrice (ordre x ordre)

    for(int i=0; i<mat.ordre; i++)
        for(int j=0; j<mat.ordre; j++)
            fichier >> mat.coeff[i*mat.ordre + j]; // Remplissage de la matrice avec les donnees du fichier
        
    //fermeture du fichier
    fichier.close();
    return true;
}

bool estComplet(MatriceAdjacence mat){ // Verifie si la matrice est complete
    for(int i=0; i<mat.ordre; i++)
        for(int j=0; j<mat.ordre; j++)
            if( i != j && mat.coeff[i*mat.ordre + j] == 0) // verifie si il y a au moins un arret entre 2 noeuds
                return false;
    
    return true;
}

bool estSymetrique(MatriceAdjacence mat){ // Verifie si la matrie est symetrique 
    for(int i=0; i<mat.ordre; i++)
        for(int j=i+1; j<mat.ordre; j++)
            if(mat.coeff[i*mat.ordre + j] !=  mat.coeff[j*mat.ordre + i]) // Verifie si les donnees symetriques sont differentes
                return false;
    return true;
}

bool estIsole(MatriceAdjacence mat, int i){ // Verifie si la matrice est isolee
    for(int j=0; j<mat.ordre; j++)
        if( i != j && ( mat.coeff[i * mat.ordre + j] != 0)) // Verifie si il y a au moins un arret entre 2 noueds  
            return false;         
    return true;
}

void afficherDegresNonOriente(MatriceAdjacence mat){
    // Afficher les degrees des matrices orientees
    for(int i = 0; i < mat.ordre; i++){
        int somme = 0;
        for(int j = 0; j < mat.ordre; j++)
            somme += mat.coeff[i * mat.ordre + j]; // fait la somme 
        cout<<"Degres sommet "<<i+1<<": "<<somme<<endl;
    }
}

void afficherDegresOriente(MatriceAdjacence mat){
     for(int i = 0; i < mat.ordre; i++){
        int somme = 0;
        for(int j = 0; j < mat.ordre; j++){
                somme += mat.coeff[i * mat.ordre + j];
                somme += mat.coeff[j * mat.ordre + i];                  
        }            
        cout<<"Degres sommet "<<i+1<<": "<<somme<<endl;
    }

}
int main(int argc, char *argv[]){
    if(argc != 2){
        cout<<"Erreur ! il faut 2 parametres"<<endl;
        return 0;
    }
       
    int taille;
    cout<<"Creation d'une matrice nulle: "<<endl;
    cout<<"Entrer la taille: ";
    cin >> taille;

    MatriceAdjacence matriceNulle;
    creerMatrice(matriceNulle, taille);
    cout<<"--- La matrice nulle ---"<<endl;
    afficher(matriceNulle);cout<<endl;
    cout<<endl;

    MatriceAdjacence matrice;
    if( !charger(*(argv +1), matrice))
        return 0;

    cout<<"La matrice d'adjacence"<<endl;
    afficher(matrice); cout<<endl;

    if(estComplet(matrice))
        cout<<"La matrice est complete"<<endl;
    else
        cout<<"La matrice n'est pas complete"<<endl;
    

    if(estSymetrique(matrice))
        cout<<"La matrice est symetrique"<<endl;
    else
        cout<<"La matrice n'est pas symetrique"<<endl;
    
    
    for(int i=0; i<matrice.ordre; i++)
        if(estIsole(matrice,  i))
            cout<<"Le noeud "<<i<<"Est isole"<<endl;

    cout<<endl;
    int choix;
    cout<<"Choisissez: "<<endl;
    cout<<"1. Oriente"<<endl;
    cout<<"2. NonOriente"<<endl;
    cout<<">>";
    cin>>choix;
    
    if(choix == 1)
        afficherDegresOriente(matrice);
    else if (choix == 2)
        afficherDegresNonOriente(matrice);
    else
        cout<<"Choix incorrect"<<endl;

    return 1;
}
