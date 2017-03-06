#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//echange des valeurs en memoires
void swap( int * const x, int * const y )
{
   int temp = *x;
   *x = *y;
   *y = temp;
}
 
 // sort array int
void selectionSort( int * const array, const int size )
{
   int smallest; // index du plus petit element
   for ( int i = 0; i < size - 1; i++ )
   {
      smallest = i; // premier element restant
      // loop pour trouver le plus petit element restant
      for ( int index = i + 1; index < size; index++ )
         if ( array[ index ] < array[ smallest ] )
            smallest = index;
      swap( &array[ i ], &array[ smallest ] );
   } 
} 

int main()
{
    int N; //nb de Oods
    cin >> N; cin.ignore();
    cerr << "N " << N << endl; 
    int C; //prix du cadeau
    cin >> C; cin.ignore();
    cerr << "C " << C << endl;
    int * PersBudget = new int[N]; //stock le budget de chaque ood
    int total = 0; //total budget
    for (int i = 0; i < N; i++) {
        int B;
        cin >> B; cin.ignore();
        cerr << "B " << B << endl;
        PersBudget[i] = B;
        total += B;
    }
    cerr << "total " << total << endl;
    selectionSort(PersBudget, N); //on trie les budget dans l'ordre croissant
    if(total < C) //si total budget plus petit que prix du cadeau
        cout << "IMPOSSIBLE" << endl;
    else{
        int Oods = N; 
        int Cost = C;
        while(Oods > 0){ //tant qu'il y a des Oods
            int avg = Cost / Oods; //calcul du prix moyen par Ood
            bool avgPos = true; //si le Ood a moins que le prix moyen on affiche  
            //sinon le ood mettra que le prix moyen
            int remain = Cost % Oods; //reste entre le prix du cadeau et le nb de Oods
            cerr << "avg " << avg << endl;
            cerr << "Cost " << Cost << endl;
            cerr << "Oods " << Oods << endl;
            cerr << "restant " << remain << endl;
            for(int i = N - Oods; i < N; i++){
                if(PersBudget[i] <= avg){
                    cout << PersBudget[i] << endl;
                    Cost -= PersBudget[i];
                    Oods--;
                    avgPos = false;
                }else{
                    if(avgPos){
                        //boucle entre le Oods qui a moins que le prix moyen
                        cerr << "i " << i << endl;
                        cerr << "N - remain " << N - remain << endl;
                        for(int j = i; j < N - remain; j++){
                            cout << avg << endl;
                        }
                        for(int j = N - remain; j < N; j++){
                            cout << avg+1 << endl;
                        }
                        Oods = 0;
                        break;
                    }else{ //un nouveau prix moyen doit etre calcul
                        break;
                    }
                }
            }
        }
    }
}
