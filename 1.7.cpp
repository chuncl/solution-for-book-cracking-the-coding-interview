// Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column are set to 0.

#include <iostream>
#include <vector>
#include <math.h>
#include <cassert>

void setZero(int**a, int m, int n)
{
	std::vector<bool>row(m, false);
	std::vector<bool>col(n, false);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 0) {
				row[i] = true;
				col[j] = true;
			}
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (row[i] || col[j])
				a[i][j] = 0;
		}
	}

	return;
}


void setZero2(int**a, int m, int n)
{
	// bit map/matrix
	const size_t intBits = sizeof(int) * 8;
	const size_t sz = static_cast<size_t>(ceil(static_cast<double>(m*n)/intBits));
	std::vector<int> hash(sz, 0);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 0) {
				size_t idx = (i*m + j) / intBits;
				size_t shift = (i*m + j) % intBits;
				hash[idx] |= (1 << shift);
			}
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			size_t idx = (i*m + j) / intBits;
			size_t shift = (i*m + j) % intBits;
			if (hash[idx] & (1 << shift)) {
				// set row and column to 0
				for (int c = 0; c < n; c++)
					a[i][c] = 0;
				for (int r = 0; r < m; r++)
					a[r][j] = 0;
			}			
		}
	}

	return;
}

void printMatrix(int** a, int m, int n)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			std::cout << a[i][j] << " ";
		std::cout << std::endl;
	}
}


// vector of vectors for matrix
// two bit vector for hash of rows or columns
typedef std::vector<std::vector<int> > _MATRIX;
void setZero3(_MATRIX& matrix)
{
	const size_t m = matrix.size();
	if (m == 0)
		return;

	const size_t n = matrix[0].size();
	if (n == 0)
		return;

	const size_t intBits = sizeof(int) * 8;
	const size_t sz_r = (size_t)(ceil(static_cast<double>(m) / intBits));
	const size_t sz_c = (size_t)(ceil(static_cast<double>(n) / intBits));
	std::vector<int> hash_r(sz_r, false);
	std::vector<int> hash_c(sz_c, false);

	for (size_t i = 0; i < m; i++) {
		assert(matrix[i].size() == n);
		for (size_t j = 0; j < n; j++) {
			if (matrix[i][j] == 0) {
				const size_t idx_r = i / intBits;
				const size_t shift_r = i % intBits;
				hash_r[idx_r] |= (1 << shift_r);
				const size_t idx_c = j / intBits;
				const size_t shift_c = j % intBits;
				hash_c[idx_c] |= (1 << shift_c);
			}
		}
	}

	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			const size_t idx_r = i / intBits;
			const size_t shift_r = i % intBits;
			bool rzero = ((hash_r[idx_r] & (1 << shift_r)) != 0);
			const size_t idx_c = j / intBits;
			const size_t shift_c = j % intBits;
			bool czero = ((hash_c[idx_c] & (1 << shift_c)) != 0);

			if (rzero || czero) {
				matrix[i][j] = 0;
			}
		}
	}
}

void printMatrix2(const _MATRIX& a)
{
	const size_t m = a.size();
	const size_t n = a[0].size();
	for (size_t i = 0; i < m ; i++) {
		for (size_t j = 0; j < n; j++)
			std::cout << a[i][j] << " ";
		std::cout << std::endl;
	}
}

#define M 4
#define N 3
int main()
{
	
	/*int matrix[M][N] = {
	{ 1, 1, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 },
	{ 0, 1, 1 }
	};*/
	
	//int** matrix = new int*[M];
	//for (size_t i = 0; i < M; i++) {
	//	matrix[i] = new int[N];
	//}

	//for (size_t i = 0; i < M; i++)
	//	for (size_t j = 0; j < N; j++)
	//		matrix[i][j] = 1;

	//matrix[1][1] = 0;
	//matrix[3][0] = 0;	
	//
	//printMatrix(matrix, M, N);

	///*setZero(matrix, M, N);
	//std::cout << "after setting to zeror" << std::endl;
	//printMatrix(matrix, M, N);*/

	//setZero2(matrix, M, N);
	//std::cout << "after setting to zeror" << std::endl;
	//printMatrix(matrix, M, N);
	//
	//for (size_t i = 0; i < M; i++)
	//	delete[] matrix[i];
	//delete[] matrix;

	std::vector<int> r(N, 1);
	_MATRIX matrix3;
	for (size_t i = 0; i < M; i++)
		matrix3.push_back(r);
	matrix3[1][1] = 0;
	matrix3[3][0] = 0;	
	printMatrix2(matrix3);

	setZero3(matrix3);
	std::cout << "after setting to zeror" << std::endl;
	printMatrix2(matrix3);


	return 0;
}

// how to dynamically allocate matrix and delete matrix (memory)
// not need boolean matrix, space O(MN), but two vector for rows & columns， space O(M+N)

// bit matrix

// vector of vectors for matrix
// two bit vector for hash of rows or columns

// when built bit vector/matrix, might need to use ceil (cast to double first and then cast back to size_t)

// don't compare int with size_t