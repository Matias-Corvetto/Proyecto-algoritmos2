#include <iostream>
using namespace std;

struct Game{
    string name;
    int weight;
    int value;
    Game(string name, int weight,int value):name(name),weight(weight),value(value){}
};

int dpMethod(Game** games, int gamesAmount, int storage){
    int** matDP = new int*[gamesAmount+1];
    for(int i = 0; i <= gamesAmount; i++){
        matDP[i] = new int[storage+1];
    }

    for (int i = 0; i <= gamesAmount; i++) {
        matDP[i][0] = 0;
    }        
    
    for (int i = 0; i <= storage; i++) {
        matDP[0][i] = 0;   
    }        

    for (int i = 1; i <= gamesAmount; i++) {
        for (int j = 1; j <= storage; j++) {
            if (games[i-1]->weight > j) {
                matDP[i][j] = matDP[i-1][j];
            } else {
                matDP[i][j] = max(matDP[i-1][j], games[i-1]->value + matDP[i-1][j-games[i-1]->weight]);
            }            
        }            
    }        

    int result = matDP[gamesAmount][storage];

    for (int i = 0; i <= gamesAmount; i++)
        delete []matDP[i];
    
    delete[]matDP;

    return result;
}

int main(){        
    int storage;    
    cin >> storage;

    int currentYear;
    cin >> currentYear;

    int n;    
    cin >> n;

    Game** games = new Game*[n];

    for(int i = 0; i < n; i++){
        string name;
        cin >> name;

        int weight;
        cin >> weight;

        int value;
        cin >> value;

        int year;
        cin >> year;

        int realValue = value - (5 * (currentYear - year));
        games[i] = new Game(name, weight, realValue);
    }

    int result = dpMethod(games,n,storage);

    for (int i = 0; i < n; i++)
        delete games[i];
    
    delete []games;

    cout << result << endl;

    return 0;
}