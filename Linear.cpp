//Ethan Hu
//Linear Algebra System
//Feb 20 2025
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*define the basic information of a system of equation*/
struct matrixInfo{
        int row,col;
        vector<double> rhs;
};
/*make matrix based on that information*/
vector<vector<double>> makeMatrix(matrixInfo m){
    const int a=m.row,b=m.col;
    vector<vector<double>> matrix(a,vector<double>(b, 0));
    return matrix;
}
/*constructor of the struct*/
matrixInfo makeMatrixInfo(int rows, int cols){
    matrixInfo m;
    m.row=rows;
    m.col=cols;
    return m;
}
/*find the determinant of a matrix recursively*/
int determinant(vector<vector<double>> matrix){
    if(matrix.size()==2&&matrix[0].size()==2){//base case
        return matrix[0][0]*matrix[1][1]-matrix[1][0]*matrix[0][1];//ad-bc
    }
    else{//for matrices larger than 2x2
        int det=0;//since there are many components, it's easier to create an int first and then later add them to this number
        for(int i=0;i<matrix.size();i++){
             vector<vector<double>> submatrix;//get rid of the first row and the current column 
        for(int j=1;j< matrix.size(); j++) {
            vector<double> row;//add a row
            for(int k=0; k< matrix.size();k++) {
                if(k==i) continue;//skip the current column
                row.push_back(matrix[j][k]);
            }
            submatrix.push_back(row);
        }
        double sign;//since it's harder to add rows on the left to the right, the same effect can be achieved by reversing the sign
        if (i%2==0){
            sign=1;
        } 
        else{
            sign=-1;//negative when it's on an even column
        }
        det += sign * matrix[0][i] * determinant(submatrix);
    }
    return det;
    }
}
/*prints the matrix and the right hand side separated by |*/
void printAugmentedMatrix(vector<vector<double>> matrix, vector<double> rhs) {
    int size = matrix.size();
    for (int i = 0; i < size; i++) {
        double* pRow = &matrix[i][0];// get a pointer to the row's first element
        int rowSize = matrix[i].size();
        for (int j = 0; j < rowSize; j++) {//nested loop to combine the lhs with the rhs
            cout << *(pRow + j) << "  ";
        }
        cout << "| " << rhs[i] << endl;
    }
    cout << endl;
}



/*vector<vector<double>> inverseMatrix(vector<vector<double>> matrix){

}*/
//the most complicated part, solving the system of equations
void solveMatrix(vector<vector<double>> matrix,vector<double> rhs){
    int n = 3;//currently I only made 3x3, but this logic should be expandable, I just don't have time to expand yet
    cout << "Augmented Matrix:" <<endl;//shows the original matrix
    printAugmentedMatrix(matrix, rhs);
    double tempfactor = matrix[1][0]/matrix[0][0];//ratio between the first number of the 1st and 2nd row
    vector<double> xcancelled1(n);//a row to replace the 2nd
    for (int i=0; i<n; i++){//elimination
        xcancelled1[i] = matrix[1][i] - tempfactor * matrix[0][i];
    }
    double rhs1 = rhs[1] - tempfactor * rhs[0];//same for rhs 
    tempfactor = matrix[2][0] / matrix[0][0];//do the same thing for the 3rd row
    vector<double> xcancelled2(n);
    for (int j=0; j<n; j++){
        xcancelled2[j] = matrix[2][j] - tempfactor * matrix[0][j];
    }
    double rhs2 = rhs[2] - tempfactor * rhs[0];
    vector<vector<double>> matrixXcancelled = {matrix[0], xcancelled1, xcancelled2};
    vector<double> rhsAfterFirst = { rhs[0], rhs1, rhs2 };//rhs after the first elimination, which get rid of x
    cout << "After eliminating x:" << endl;
    printAugmentedMatrix(matrixXcancelled, rhsAfterFirst);//printing to show the process
    tempfactor = xcancelled2[1] / xcancelled1[1];//the index is now 1, because we're eliminating y
    vector<double> ycancelled2(n);//the same logic 
    for (int j = 0; j < n; j++){
        ycancelled2[j] = xcancelled2[j]-tempfactor*xcancelled1[j];
    }
    double rhs2final = rhs2 - tempfactor * rhs1;
    vector<vector<double>> matrixAfterSecond = { matrix[0], xcancelled1, ycancelled2 };
    vector<double> rhsAfterSecond = { rhs[0], rhs1, rhs2final };
    cout << "After eliminating y:" << endl;
    printAugmentedMatrix(matrixAfterSecond, rhsAfterSecond);
    double x,y,z;
    z = rhs2final/ycancelled2[2];//back substitution to find the values
    y = (rhs1-xcancelled1[2] * z)/xcancelled1[1];//plugging z back
    x = (rhs[0]-matrix[0][1] * y-matrix[0][2] * z)/matrix[0][0];//same but with both y and z
    cout << "Solution:" << endl;
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
}

int main() {
    matrixInfo m = makeMatrixInfo(3,3);
    vector<vector<double>> matrix = /*makeMatrix(m)*/{{8,3,5}, 
    {1,6,8},
    {5,2,3}};//testing
    vector<double> rhs = {8,11,-3};
    solveMatrix(matrix,rhs);//testing
}
