#include <iostream>
#include <fstream>
#include <string>
#include <list>



using namespace std;

namespace grp
{

class graphs {

private:

    fstream Archive;
    string ArchiveName;
    int V, E;
    bool is_ordened;
    string line;

public:

    graphs(string);

    int** Adjac();

    int** Incid();

    void GetInformations(list<int> * vector); 

    list<int>* MatToList(int** matriz);

    bool is_Regular(list<int> * vector);

    int degreeMat(int ** matriz, int k);

    int degreelist(list<int>* vector, int k);

    void Open();

    void Close();


};



    graphs::graphs(string NewArchive){
    
        Archive.open(NewArchive, ios::in | ios::out | ios::app);
        ArchiveName = NewArchive;

        if(Archive.is_open())
            cout << "Opened Archive!" << endl;

        char OrienteLatter;

        Archive >> V;
        Archive >> E;
        Archive >> OrienteLatter;

        //getline(Archive, line);

            if(OrienteLatter != 'G')
             is_ordened = true;
            else
             is_ordened = false;

    }



    int ** graphs::Adjac(){

        int ** matriz;

        matriz = (int **) malloc(V * sizeof(int *));

        for(int i = 0; i < V; i++){
        
            matriz[i] = (int * ) malloc (V * sizeof(int));
        
        }


        for(int i = 0; i < V; i++){
            
            for(int j = 0; j < V; j++){

                matriz[i][j] = 0;
            
            }
        } 

        int cont = 0;
        int line[3];

        while(!Archive.eof()){

            if(cont >= 3){
                
                matriz[line[0] - 1][line[1] - 1] = line[2];
                cout << "matriz" << "[" << line[0] << "]" << "[" << line[1] << "]" << " = " << line[2] << endl;
                cont = 0;

            }

            else{
                Archive >> line[cont];
                cont++;
            }

        
        }

        

    return matriz;

    }


    void graphs::Open(){
        Archive.open(ArchiveName, ios::in | ios::out | ios::app);
    }


    void graphs::Close(){
        Archive.close();
    }


    int** graphs::Incid(){

    int ** matriz;

        matriz = (int **) malloc(E * sizeof(int *));

        for(int i = 0; i < E; i++){
        
            matriz[i] = (int * ) malloc (V * sizeof(int));
        
        }




        for(int i = 0; i < V; i++){
            
            for(int j = 0; j < E; j++){

                matriz[i][j] = 0;
            
            }
        } 

        int cont = 0;
        int line[3];
        int vertice = 0;

        while(!Archive.eof()){

            if(cont >= 3){

                matriz[line[0]- 1][vertice] = 1;//line[2];
                matriz[vertice][line[1]- 1] = 1;//line[2];
            

                cont = 0;
                vertice++;
            }

            else{
                Archive >> line[cont];
                cont++;
            }

        }

    return matriz;
    }


    list<int>* graphs::MatToList(int** matriz){

        list<int> *vector;

        vector = new list<int>[V];

        for(int i = 0; i < V; i++){

            for(int j = 0; j < V; j++){
                
                if(is_ordened == false)
                {
                   if(matriz[i][j] != 0)
                    {
                     vector[i].push_back(j + 1);
                     vector[j].push_back(i + 1); 
                    }
                }
                else{

                    if(matriz[i][j] != 0){
                     
                        vector[i].push_back(j + 1);
                        
                    }
                }

            }
        }
            
    return vector;
    }


    void graphs::GetInformations(list<int> * vector){

        if(is_ordened == true){
        
            cout << "Oriented!" << endl;

            int maior = 0, menor = 10000, iM, Im;

            for(int i = 0; i < V; i++){
                

                if(vector[i].size() > maior){
                    maior = vector[i].size();
                    iM = i + 1;
                }

                if(vector[i].size() < menor){
                    menor = vector[i].size();
                    Im = i+ 1;
                }

            }
            cout << "Maior grau: " << iM << " " << "Menor grau: " << Im << endl; 
        }
        else if(is_ordened == false){

            cout << "No Oriented!" << endl;

            for(int i = 0; i < V; i++){
                cout << vector[i].size() << endl;
            }

        }

    }



    bool graphs::is_Regular(list<int> *vector){

        int temp = vector[0].size();

        for(int i = 1; i < V; i++){

            if(vector[i].size() == temp)
                continue;

            else
            {
                return false;
            }
            

        }
    return true;

    }


    int graphs::degreeMat(int ** matriz, int k){

        int cont = 0;

        for(int i = 0; i < V; i++){
        
            if(matriz[i][k - 1] != 0)
                cont++;
        }
        for(int i = 0; i < V; i++){
        
            if(matriz[k - 1][i] != 0)
                cont++;
        }

    return cont;

    }

    int graphs::degreelist(list<int> *vector, int k){
        return vector[k - 1].size();
    }

} //end namespace




    void graphGenerate(int k){

        cout << "welcome to graph generator! You can select a option that you wish..." << endl;

        cout << "Please, choose a option: " << endl;

        cout << "1. Cycle Graph" << endl << "2. Connected Graph" << endl << "3. Complete Graph" << endl << "4. Split Graph" << endl;

        int option;
        
        do{
        
            cin >> option;
        
        }while(option < 1 || option > 4);

        fstream NewArchive;

        NewArchive.open("saida.txt", ios::app | ios::out);

        if(option == 1 || option == 2){
            
            int matriz[k][k];

            for(int i = 0; i < k; i++)
                for(int j = 0; j < k; j++)
                    matriz[i][j] = 0;


            for(int i = 0; i < k; i++){

                if(i == k - 1)
                    matriz[i][i - i] = 1;
                
                else
                    matriz[i][i + 1] = 1;

            }

            for(int i = 0; i < k; i++)

                for(int j = 0; j < k; j++){
            
                    if(matriz[i][j] == 1){
                        NewArchive << i + 1 << " " << j + 1 << endl;
                    }
            
                }
                
            


        }

        else if(option == 3){

        int matriz[k][k];

            for(int i = 0; i < k; i++)
                for(int j = 0; j < k; j++)
                    if(i != j)
                        matriz[i][j] = 1;
                    else
                        matriz[i][j] = 0;

            for(int i = 0; i < k; i++)

                for(int j = 0; j < k; j++){
            
                    if(matriz[i][j] == 1){
                        NewArchive << i + 1 << " " << j + 1 << endl;
                    }
            
                }
        }

        else if(option == 4){

        }

    }
