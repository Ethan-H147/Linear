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



/*vector<vector<double>> inverseMatrix(vector<vector<double>> matrix){

}*/

void solveMatrix(vector<vector<double>> matrix,vector<double> rhs){
    int n = 3;
    cout << "Augmented Matrix:" <<endl;
    printAugmentedMatrix(matrix, rhs);
    double tempfactor = matrix[1][0]/matrix[0][0];
    vector<double> xcancelled1(n);
    for (int i=0; i<n; i++){
        xcancelled1[i] = matrix[1][i] - tempfactor * matrix[0][i];
    }
    double rhs1 = rhs[1] - tempfactor * rhs[0];
    tempfactor = matrix[2][0] / matrix[0][0];
    vector<double> xcancelled2(n);
    for (int j=0; j<n; j++){
        xcancelled2[j] = matrix[2][j] - tempfactor * matrix[0][j];
    }
    double rhs2 = rhs[2] - tempfactor * rhs[0];
    vector<vector<double>> matrixXcancelled = {matrix[0], xcancelled1, xcancelled2};
    vector<double> rhsAfterFirst = { rhs[0], rhs1, rhs2 };
    cout << "After eliminating x:" << endl;
    printAugmentedMatrix(matrixXcancelled, rhsAfterFirst);
    tempfactor = xcancelled2[1] / xcancelled1[1];
    vector<double> ycancelled2(n);
    for (int j = 0; j < n; j++){
        ycancelled2[j] = xcancelled2[j]-tempfactor*xcancelled1[j];
    }
    double rhs2final = rhs2 - tempfactor * rhs1;
    vector<vector<double>> matrixAfterSecond = { matrix[0], xcancelled1, ycancelled2 };
    vector<double> rhsAfterSecond = { rhs[0], rhs1, rhs2final };
    cout << "After eliminating y:" << endl;
    printAugmentedMatrix(matrixAfterSecond, rhsAfterSecond);
    double x,y,z;
    z = rhs2final/ycancelled2[2];
    y = (rhs1-xcancelled1[2] * z)/xcancelled1[1];
    x = (rhs[0]-matrix[0][1] * y-matrix[0][2] * z)/matrix[0][0];
    cout << "Solution:" << endl;
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
}

int main() {
    matrixInfo m = makeMatrixInfo(3,3);
    vector<vector<double>> matrix = /*makeMatrix(m)*/{{8,3,5}, 
    {1,6,8},
    {5,2,3}};
    vector<double> rhs = {8,11,-3};
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[i].size();j++){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    solveMatrix(matrix,rhs);
    printAugmentedMatrix(matrix,rhs);
}
