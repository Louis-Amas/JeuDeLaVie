#include <iostream>
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <random>
#include <unistd.h>
using namespace std;
void initialiserMatrice(bool ** matrice, unsigned lignes, unsigned colones) {
    srand(time(NULL));
    for (int i = 0 ; i < lignes ; ++i ) {
        for (int j = 0 ; j < colones ; ++j) {
            
            if (rand() % 8 == 0) 
                matrice[i][j] = true;
            else
                matrice[i][j] = false;
        }
    }
}
void initialiserMatricetest(bool ** matrice, unsigned lignes, unsigned colones) {
    srand(time(NULL));
    for (int i = 0 ; i < lignes ; ++i ) {
        for (int j = 0 ; j < colones ; ++j) {
                matrice[i][j] = false;

        }
    }
    matrice[2][3] = true;
    matrice[2][4] = true;
    matrice[2][5] = true;
}

bool verifierIndice(int x, int y, unsigned lignes, unsigned colones) {
    
    if ( ( x < 0 || x >= colones) || (y < 0 || y >= lignes)) 
        return false;
    return true;
}

short compterNombreDeVoisin(bool ** matrice, int x, int y, unsigned lignes, unsigned colones) {
    short cpt = 0;

    
    for (int i = y - 1 ; i <= y + 1 ; ++i ) {
        for (int j = x - 1 ; j <= x + 1 ; ++j) {
            if (verifierIndice(j, i, lignes,colones))
                if (matrice[i][j] == true && (i != y || x != j ) )
                    ++cpt;

        }
    }
    return cpt;
}


void afficherMatrice(bool ** matrice, unsigned lignes, unsigned colones) {
    for (int i = 0 ; i < colones +2 ; ++i )
        cout << '#';
    cout << endl;
    for (int i = 0 ; i < lignes ; ++i ) {
        cout << '#';
        for (int j = 0 ; j < colones ; ++j) {
            if (matrice[i][j] == true)
                cout << '@';
            else 
                cout << ' ';
            }
        cout << '#' << endl;
    }
    for (int i = 0 ; i < colones +2 ; ++i )
        cout << '#';
    cout << endl;
}
bool ** avancer(bool ** matrice, unsigned lignes, unsigned colones) {
    bool ** matrice2;
    
    matrice2 = new bool * [lignes];
    
    for (unsigned i = 0 ; i < lignes  ; ++i)
        matrice2[i] = new bool[colones]; 
    for (int i = 0 ; i < lignes ; ++i ) {
        
        for (int j = 0 ; j < colones - 1; ++j) {
            
            short nbVoisin = compterNombreDeVoisin(matrice,j,i,lignes, colones);
            //cout << i << ' ' << j << ' ' << nbVoisin << endl;
            if (nbVoisin == 3) {
                
                matrice2[i][j] = true;
            }
            if (nbVoisin == 2) {
                matrice2[i][j] = matrice[i][j];
            }
            if (nbVoisin < 2 || nbVoisin > 3 ) {
                matrice2[i][j] = false;
            }

            
        }
    }
    return matrice2;
}
int main(int argc, char * argv[]) {
    if (argc < 3) {
        cout << "Il manque des arguments";
        return 1;
    }
    
    unsigned lignes = atoi(argv[1]);
    unsigned colones = atoi(argv[2]);
    bool ** matrice;
    
    matrice = new bool * [lignes];
    
    for (unsigned i = 0 ; i < lignes  ; ++i)
        matrice[i] = new bool[colones]; 
    initialiserMatrice(matrice, lignes, colones);
    while (true) {
        afficherMatrice(matrice, lignes, colones);
        matrice = avancer(matrice,lignes,colones);
        usleep(100000);
        system ("clear");
    }
    
}
