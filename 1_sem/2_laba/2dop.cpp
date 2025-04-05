#include <iostream>

int main(){
        std::cout<<"Дополнительное задание"<<std::endl;
        int M, N;
        std::cout<<"Введите размеры матрицы А через пробел: ";
        std::cin>> M >> N;
        srand(time(0));

        std::cout<< std::endl;
        std::cout<<"Матрица А:" << std::endl;
        int **matr = new int*[M];
        for(int i=0; i<M; i++){
            matr[i] = new int [N];
            for(int j=0; j<N; j++){
                matr[i][j] = rand()%100;
                std::cout << matr[i][j] << " ";
            }
            std::cout<<std::endl;
        }  
        
        std::cout<< std::endl;
        std::cout<<"Матрица А^T:" << std::endl;
        int **matrTr = new int*[N];
        for(int i=0; i<N; i++){
            matrTr[i] = new int [M];
            for(int j=0; j<M; j++){
                matrTr[i][j] = matr[j][i];
                std::cout << matrTr[i][j] << " ";
            }
            std::cout<<std::endl;
        } 


        for(int i=0; i<M; i++){
            delete [] matr[i];
        }
        for(int i=0; i<N; i++){
            delete [] matrTr[i];
        }
        delete [] matr;
        delete [] matrTr;
        return 0;
    }