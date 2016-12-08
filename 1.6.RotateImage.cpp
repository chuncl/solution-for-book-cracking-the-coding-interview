// given an image represented by N*N matrix. each pixel has 4 bytes. write a method to rotate the image by 90 degree, in place.

#include <iostream>

#define N 4

// layer by layer
void rotate90InPlace(int** a, const size_t n)
{
	if ((a == nullptr) || (*a == nullptr) || (n == 0) )
		return;

	for (size_t layer = 0; layer < n/2; layer++) {
		// first and last element for each layer
		size_t first = layer, last = n-1-layer;
		for (size_t i = first; i < last; i++) {
			//relative offset
			size_t offset = i-first;
			int tmp = a[first][i];
			a[first][i] = a[last-offset][first];
			a[last-offset][first] = a[last][last-offset];
			a[last][last-offset] = a[i][last];
			a[i][last] = tmp;
		}
	}
}

void swap(int& a, int& b) 
{
	a = a^b;
	b = a^b;
	a = a^b;
}

void printMatrix2(int a[][N])
{
	for (size_t i=0; i<N; i++) { 
		for(size_t j = 0; j<N; j++) {
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

void rotate90InPlace2(int a[][N]) 
{
	// mirror with anti-diagnal
	for (size_t i = 0; i<N; i++) {
		for(size_t j=0; j<N-1-i;j++) {
			swap(a[i][j], a[N-1-j][N-1-i]);
		}
	}

	//std::cout << "after mirror with diagnal" << std::endl;
	//printMatrix2(a);

	// switch i row with n-1-i row
	for (size_t k = 0; k<N/2; k++) {
		for(size_t m=0; m<N; m++) {
			swap(a[k][m], a[N-1-k][m]);
		}
	}

}

void printMatrix(int** a, size_t n)
{
	for (size_t i=0; i<n; i++) { 
		for(size_t j = 0; j<n; j++) {
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

int main()
{
	int matrix[N][N] = {
		{1, 2, 4, 5},
		{3, 8, 7, 6},
		{6, 4, 9, 5},
		{7, 3, 1, 2}
	};

	//int **a = new int*[N];
	//for (int i=0; i<N; i++) {
	//	//a[i] = new int[N];
	//	a[i] = matrix[i];
	//	
	//}

	//printMatrix(a, N);
	//rotate90InPlace(a, N);
	//std::cout <<"after rotate: "<< std::endl;
	//printMatrix(a, N);

	///*for (int i=0; i<N; i++) {
	//	delete[] a[i];
	//}*/
	//delete[] a;


	printMatrix2(matrix);
	rotate90InPlace2(matrix);
	std::cout <<"after rotate: "<< std::endl;
	printMatrix2(matrix);

}

//There are three ways to pass a 2D array to a function:
//
//The parameter is a 2D array
//int array[10][10];
//void passFunc(int a[][10])
//{
//    // ...
//}
//passFunc(array);
//The parameter is an array containing pointers
//int *array[10];
//for(int i = 0; i < 10; i++)
//    array[i] = new int[10];
//void passFunc(int *a[10]) //Array containing pointers
//{
//    // ...
//}
//passFunc(array);
//The parameter is a pointer to a pointer
//int **array;
//array = new int *[10];
//for(int i = 0; i <10; i++)
//    array[i] = new int[10];
//void passFunc(int **a)
//{
//    // ...
//}
//passFunc(array);

//vector<vector<int> > A(dimension, vector<int>(dimension));

//One method would be to use the array to initialize the vector
//static const int arr[] = {16,2,77,29};
//vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );
//If your compiler supports C++11, you can simply do:
//
//std::vector<int> v = {1, 2, 3, 4};


