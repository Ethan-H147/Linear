#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct matrixInfo{
        int row,col;
        double* value;

};

vector<vector<double>> makeMatrix(matrixInfo m){
    const int a=m.row,b=m.col;
    vector<vector<double>> matrix(a,vector<double>(b, 0));
    return matrix;
}

matrixInfo makeMatrixInfo(int rows, int cols){
    matrixInfo m;
    m.row=rows;
    m.col=cols;
    return m;
}

int main() {
    matrixInfo m = makeMatrixInfo(3,4);
    vector<vector<double>> matrix = makeMatrix(m);
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[i].size();j++){
            cout << matrix[i][j];
        }
    }
}
