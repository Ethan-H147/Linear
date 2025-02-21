#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct matrixInfo{
        int row,col;
        vector<double> rhs;

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

int determinant(vector<vector<double>> matrix){
    if(matrix.size()==2&&matrix[0].size()==2){
        return matrix[0][0]*matrix[1][1]-matrix[1][0]*matrix[0][1];
    }
    else{
        int det=0;
        for(int i=0;i<matrix.size();i++){
             vector<vector<double>> submatrix;
        for(int j=1;j< matrix.size(); j++) {
            vector<double> row;
            for(int k=0; k< matrix.size();k++) {
                if(k==i) continue;
                row.push_back(matrix[j][k]);
            }
            submatrix.push_back(row);
        }
        double sign;
        if (i%2==0){
            sign=1.0;
        } 
        else{
            sign=-1.0;
        }
        det += sign * matrix[0][i] * determinant(submatrix);
    }
    return det;
    }
}

void printAugmentedMatrix(vector<vector<double>> matrix, vector<double> rhs) {
    int size = matrix.size();
    for (int i=0; i<size; i++) {
        for (int j=0; j<matrix[i].size(); j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << "| " << rhs[i] << endl;
    }
    cout << endl;
}



vector<vector<double>> inverseMatrix(vector<vector<double>> matrix){

}

void solveMatrix(vector<vector<double>> matrix){
    double tempfactor = matrix[0][0]/matrix[1][0];
    vector<double> temp = {matrix[1][0]*tempfactor,matrix[1][1]*tempfactor,matrix[1][2]*tempfactor};
    
    vector<double> xcancelled1 = {matrix[0][0]-temp[0],matrix[0][1]-temp[1],matrix[0][2]-temp[2]};
    for(int j=0;j<3;j++){
        cout << xcancelled1[j] << " ";
    }
    cout << endl;
    tempfactor = matrix[0][0]/matrix[2][0];
    temp = {matrix[2][0]*tempfactor,matrix[2][1]*tempfactor,matrix[2][2]*tempfactor};
    cout << endl;
    vector<double> xcancelled2 = {matrix[0][0]-temp[0],matrix[0][1]-temp[1],matrix[0][2]-temp[2]};
    for(int j=0;j<3;j++){
        cout << xcancelled2[j] << " ";
    }
    tempfactor=xcancelled1[1]/xcancelled2[1];
    

    double x,y,z;

    cout << "Solution:" << endl;
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
}

int main() {
    matrixInfo m = makeMatrixInfo(3,3);
    vector<vector<double>> matrix = /*makeMatrix(m)*/{{3.0,4.0,5.0}, 
    {2.0,3.0,4.0},
    {1,2,3}};
    vector<double> rhs = {8,11,-3};
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[i].size();j++){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    solveMatrix(matrix);
    printAugmentedMatrix(matrix,rhs);
}
