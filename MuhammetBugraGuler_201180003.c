// Name and Surname: Muhammet Bugra Guler --- Number: 201180003 
// Sparse Matrix Representation in C Using an array of structures.

#include <stdio.h>
#include <stdlib.h>
#define MAX_TERM 101 // I define array size.
#define K 3 // I define row and column numbers.
#define L 4
#define M 5

typedef struct { // I define struct and variables.
	int row, column, value;
} nonZeroValues;

void printMatrix(nonZeroValues compactMatrix[MAX_TERM]) { // This is print matrix function.
	int count = 1; // This is variable required to return the value in array.
	for (int i = 0; i < compactMatrix[0].row; i++) {
		for (int j = 0; j < compactMatrix[0].column; j++) { // If the related row and column are full, it writes this number. If not it writes 0.
			if (i == compactMatrix[count].row && j == compactMatrix[count].column) { 
				printf(" %d  ", compactMatrix[count].value);
				count++;
			}
			else {
				printf(" 0  ");
			}
		}
		printf("\n"); // It puts to switch to new line.
	}
	printf("\n");
}

void printArray(nonZeroValues compactMatrix[MAX_TERM]) { // This is print array function.
	printf(" Row: \t Column: \t Value: \n"); // Print row, column, and value.
	for (int i = 0; i <= compactMatrix[0].value; i++) { // Print row, column, and value numbers.
		printf(" %d \t %d \t\t %d \n", compactMatrix[i].row, compactMatrix[i].column, compactMatrix[i].value);
	}
}

void sortingMatrix(nonZeroValues compactMatrix[MAX_TERM]) { // This is sorting function.
	nonZeroValues tempArray[1]; // A temporary array is created.
	for (int i = 2; i <= compactMatrix[0].value; i++) {
		for (int j = 1; j <= compactMatrix[0].value - i + 1; j++) { // Sorts by row number. It is already sorted by the number of columns.
			if (compactMatrix[j].column > compactMatrix[j + 1].column) {
				tempArray[0] = compactMatrix[j + 1];
				compactMatrix[j + 1] = compactMatrix[j];
				compactMatrix[j] = tempArray[0];
			}
		}
	}
}

void returnTranspose(nonZeroValues compactMatrix[MAX_TERM]) { // Converts the second matrix to the transpose matrix.
	sortingMatrix(compactMatrix); // Sends it to the sorting function.
	int temporary; // This is temporary variable for replace. 
	temporary = compactMatrix[0].row; // Replaces row and column numbers.
	compactMatrix[0].row = compactMatrix[0].column;
	compactMatrix[0].column = temporary;
	for (int i = 1; i <= compactMatrix[0].value; i++) { // Replaces row and column data.
		temporary = compactMatrix[i].column;
		compactMatrix[i].column = compactMatrix[i].row;
		compactMatrix[i].row = temporary;
	}
	printf(" ----- Second Matrix Transpose ----- \n"); // Prints the transpose matrix.
	printf(" Second Matrix Transpose -> Row: %d --- Column: %d --- Value: %d \n", compactMatrix[0].row, compactMatrix[0].column, compactMatrix[0].value);
	printMatrix(compactMatrix);
}

void matrixMultiply(nonZeroValues compactMatrix_1[MAX_TERM], nonZeroValues compactMatrix_2[MAX_TERM]) { // This is multiply function.
    returnTranspose(compactMatrix_2); // Sends it to the transpose function.
    nonZeroValues resultMatrix[MAX_TERM]; // define result matrix.
    resultMatrix[0].row = K; // Row and column number of the result matrix.
    resultMatrix[0].column = M;
    int i = 1, j = 1, temp_i, temp_j, count = 0, temporary, tempMatrixRow_1, tempMatrixRow_2; // Define temporary variables and a count variable.
    // I did the multiplication with the help of this site: *** https://www.educba.com/sparse-matrix-multiplication/ ***
    while (i < compactMatrix_1[0].value || j < compactMatrix_2[0].value) {
    	tempMatrixRow_1 = compactMatrix_1[i].row; // These are temporary variables.
    	tempMatrixRow_2 = compactMatrix_2[j].row;
    	temp_i = i;
    	temp_j = j;
    	temporary = 0;
    	while (compactMatrix_1[temp_i].row == tempMatrixRow_1) {
    		temp_j = j;
    		while (compactMatrix_2[temp_j].row == tempMatrixRow_2) {
    			if (compactMatrix_1[temp_i].column == compactMatrix_2[temp_j].column) { // Assigning value to "temporary" variable.
    				temporary += compactMatrix_1[temp_i].value * compactMatrix_2[temp_j].value;
				}
				temp_j++;
			}
			temp_i++;
		}
		if (temporary != 0) {
			count++;
			resultMatrix[count].row = compactMatrix_1[i].row; // Transfers the non-0 data, and row, column numbers in the compact matrix to the result matrix.
			resultMatrix[count].column = compactMatrix_2[j].row;
			resultMatrix[count].value = temporary;
		}
		while (j < compactMatrix_2[0].value && tempMatrixRow_2 == compactMatrix_2[j].row) { // Increments "j" if the relevant condition is met.
			j++;
		}
		if (tempMatrixRow_2 == compactMatrix_2[j].row) {
			while (i < compactMatrix_1[0].value && tempMatrixRow_1 == compactMatrix_1[i].row) { // Increments "i" if the relevant condition is met, and "j" value is set to 1.
				i++;
				j = 1;
			}
			if (tempMatrixRow_1 == compactMatrix_1[i].row) { // If the relevant condition is met, the break command runs and exits the loop.
				break;
			}
		}
	} // If the number of "j" and "i" exceeds the "value" number, the loop terminates.
	resultMatrix[0].value = count; // Value number of the result matrix.
	printf(" ----- Matrix Multiply ----- \n"); // Prints the result matrix.
	printf(" Matrix Multiply -> Row: %d --- Column: %d --- Value: %d \n", resultMatrix[0].row, resultMatrix[0].column, resultMatrix[0].value);
	printMatrix(resultMatrix);
	printf(" ----- Multiplication Result Matrix 1D Array. ----- \n"); // Print the multiplication result matrix as a 1D array.
	printArray(resultMatrix);
}

// I got help from homework slide with return compact matrix.
void returnCompactMatrix_1(nonZeroValues compactMatrix[MAX_TERM], int sparseMatrix[K][L]) { // This function transfers the non-0 data in the first matrix to the array.
	int count = 0; // This is variable required to return the value in array.
	compactMatrix[0].row = K; // Row and column number of the first matrix.
	compactMatrix[0].column = L;
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < L; j++) {
			if (sparseMatrix[i][j] != 0) { // Transfers the non-0 data and row, column numbers in the first matrix to the array.
				count++;
				compactMatrix[count].row = i;
				compactMatrix[count].column = j;
				compactMatrix[count].value = sparseMatrix[i][j];
			}
		}
	}
	compactMatrix[0].value = count; // Value number of the first matrix.
}

void returnCompactMatrix_2(nonZeroValues compactMatrix[MAX_TERM], int sparseMatrix[L][M]) { // This function transfers the non-0 data in the second matrix to the array.
	int count = 0; // This is variable required to return the value in array.
	compactMatrix[0].row = L; // Row and column number of the second matrix.
	compactMatrix[0].column = M;
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < M; j++) {
			if (sparseMatrix[i][j] != 0) { // Transfers the non-0 data and row, column numbers in the second matrix to the array.
				count++;
				compactMatrix[count].row = i;
				compactMatrix[count].column = j;
				compactMatrix[count].value = sparseMatrix[i][j];
			}
		}
	}
	compactMatrix[0].value = count; // Value number of the second matrix.
}

void main() { // This is main function.
	int sparseMatrix_1[K][L] = { { 0, 10, 0, 5 }, { 0, 2, 4, 0 }, { 0, 0, 3, 0 } }; // I defined first and second sparse matrix.
	int sparseMatrix_2[L][M] = { { 1, 0, 0, 2, 0 }, { 0, 0, 3, 0, 5 }, { 0, 8, 0, 0, 8 }, { 5, 0, 10, 0, 0 } }; // I got help from homework slide with sparse matrix data.
	nonZeroValues compactMatrix_1[MAX_TERM], compactMatrix_2[MAX_TERM]; // Define compact matrix.
	returnCompactMatrix_1(compactMatrix_1, sparseMatrix_1); // Call the return compact matrix functions.
	returnCompactMatrix_2(compactMatrix_2, sparseMatrix_2);
	printf(" ----- First Matrix ----- \n");  // Prints the first matrix.
	printf(" First Matrix -> Row: %d --- Column: %d --- Value: %d \n", compactMatrix_1[0].row, compactMatrix_1[0].column, compactMatrix_1[0].value);
	printMatrix(compactMatrix_1);
	printf(" ----- Second Matrix ----- \n");  // Prints the second matrix.
	printf(" Second Matrix -> Row: %d --- Column: %d --- Value: %d \n", compactMatrix_2[0].row, compactMatrix_2[0].column, compactMatrix_2[0].value);
	printMatrix(compactMatrix_2);
	matrixMultiply(compactMatrix_1, compactMatrix_2); // Call the multiply functions.
}
