#include <iostream>
#include <string>
#include "ejercicio2-utils/HashID.cpp"

using namespace std;

//Divide un string en substrings, a partir de un separador.
void split(string & linea, char sep, string* palabras){
   string temp = "";
   int cont = 0;

   for(int i=0; i < linea.size(); i++){
        if(linea[i] != sep){
            temp += linea[i];
        } else{
           palabras[cont] = string(temp);
           temp = "";
           cont++;
        }
    }
       
    palabras[cont] = temp;
    return;
}

int main() {
    //Leer generos.
    string cantGeneros_str;
    getline(cin, cantGeneros_str);
    int cantGeneros = stoi(cantGeneros_str);

    string* generos = new string[cantGeneros];
    for (int i = 0; i < cantGeneros; i++) {
        getline(cin, generos[i]);
    }
    
    //Leer ID's.
    string cantPelis_str;
    getline(cin, cantPelis_str);
    int cantPelis = stoi(cantPelis_str);

    HashID* peliculas = new HashID(cantPelis, cantGeneros);

    string linea;
    for (int i = 0; i < cantPelis; i++) {
        getline(cin, linea);
        string* palabras = new string[2];
        split(linea, ' ', palabras);
        peliculas->addFilm(stoi(palabras[0]), palabras[1]);
        delete[] palabras;
    }

    //Leer puntajes.
    string cantPuntaje_str;
    getline(cin, cantPuntaje_str);
    int cantPuntaje = stoi(cantPuntaje_str);

    string linea2;
    for (int i = 0; i < cantPuntaje; i++) {
        getline(cin, linea2);
        string* palabras = new string[2];
        split(linea2, ' ', palabras);
        peliculas->addRating(stoi(palabras[0]), stoi(palabras[1]));
        delete[] palabras;
    }

    //Mostrar resultados.
    for (int i = 0; i < cantGeneros; i++) {
        cout << peliculas->getData(generos[i]) << endl;
    }

    delete[] generos;
    delete peliculas;
    return 0;
}