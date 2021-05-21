#include <bits/stdc++.h>
#include <mpi.h>

using namespace std;

char s[100];

void read_file_fopen(){
    FILE *fp;
    fp = fopen("input.txt", "r");
    while(true){
        fgets(s, 100, fp);
        if(feof(fp)){
            break;
        }
        cout << s;
    }
}

// void solve(){
//     int rank;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     printf("%d\n", rank);
// }

// void MPI_test(){
//     int rank;
//     MPI_Init(NULL, NULL);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     int iter = 2;
//     for(int i = 0; i < iter; i++){
//         solve();
//         if(rank == 0){

//         }
//     }
//     MPI_Finalize();
// }

// void MPI_communication(){
//     int rank;
//     MPI_Init(NULL, NULL);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     char buffer[100];
//     if(rank == 0){
//         MPI_Send(, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
//     }
//     MPI_Finalize();
// }

int main(int argc, char* argv[]){
    ifstream newfile("input.txt");
    string line;
    getline(newfile, line);
    cout << line.size() << endl;
    return 0;
    char char_array[100];
    char_array[0] = 'a';
    char_array[1] = 'b';
    string s = "";
    strcpy(char_array, s.c_str());
    printf("%ld\n", sizeof(char_array)/sizeof(char));
    for(int i = 0; i < s.size(); i++){
        cout << char_array[i];
    }
    cout << endl;
    string temp;
    temp += char_array;
    cout << temp.size() << endl;
    return 0;
}