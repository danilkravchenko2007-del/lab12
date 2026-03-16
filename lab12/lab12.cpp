/*#include <iostream>
using namespace std;

void permutations(int* arr, int l, int r) {
	if (l == r) {
		cout << arr[0] << arr[1] << arr[2] << endl;
	}

	else {
		for (int i = l; i <= r; i++) {
			int temp = arr[l];
			arr[l] = arr[i];
			arr[i] = temp;

			permutations(arr, l + 1, r);

			temp = arr[l];
			arr[l] = arr[i];
			arr[i] = temp;
		}
	}
}

int main() {
	int arr[3] = { 1, 2, 3 };
	permutations(arr, 0, 2);

	return 0;
}*/


#include <iostream>
#include <cmath>
using namespace std;

#define MAX_K	16

void printBoard(int** board, int K) {
	if (K <= 10) {
		cout << "----------------\n";
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				if (board[i][j] == 1) {
					cout << "Q ";
				}
				else {
					cout << ". ";
				}
			}
			cout << endl;
		}
	
		cout << "----------------\n";
	}
}

bool permuteIsOk(int** board, int row, int col, int K) {
	// проверяем есть ли ферзь, стоящий выше нашего в одном столбце
	for (int i = 0; i < row; i++) {
		if (board[i][col] == 1) 
			return false;
	}

	// проверяем первую диагональ (двигаемся вверх и влево)
	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == 1)
			return false;
	}

	// проверяем вторую диагональ (двигаемся вверх и вправо)
	for (int i = row, j = col; i >= 0 && j < K; i--, j++) {
		if (board[i][j] == 1)
			return false;
	}
	return true;
}

void solve(int** board, int row, int K, int& count) {
	if (row == K) {
		count++;
		printBoard(board, K);
		return;
	}

	for (int col = 0; col < K; col++) {
		if (permuteIsOk(board, row, col, K)) {
			board[row][col] = 1; // ставим ферзя
			
			solve(board, row + 1, K, count); // переходим на следующую строку

			board[row][col] = 0; // откат

		}
	}
}

void printBoard1D(int* board, int K) {
	if (K <= 10) {
		cout << "----------------\n";
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				if (board[i] == j) {
					cout << "Q ";
				}
				else {
					cout << ". ";
				}
			}
			cout << endl;
		}
		cout << "----------------\n";
	}

}
bool permuteIsOk1D(int* board, int row, int col, int K) {
	for (int i = 0; i < row; i++) {
		if (board[i] == col) // проверка столбца
			return false;

		if (abs(board[i] - col) == abs(row - i)) // проверка диагоналей
			return false;
	}
	return true;
}

void solve1D(int* board, int row, int K, int& count) {
	if (row == K) {
		count++;
		printBoard1D(board, K);
		return;
	}
	for (int col = 0; col < K; col++) {
		if (permuteIsOk1D(board, row, col, K)) {
			board[row] = col;

			solve1D(board, row + 1, K, count);
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Введите размер поля К (не более 16 и не менее 1)" << endl;
	int K;
	cin >> K;


	while (K > MAX_K || K < 1) {
		cout << "Ошибка! Введите K еще раз" << endl;
		cin >> K;
	}

	cout << "\nРЕШЕНИЕ С ИСПОЛЬЗОВАНИЕМ МАТРИЦЫ" << endl;

	int** board = new int* [K];

	for (int i = 0; i < K; i++) {
		board[i] = new int [K] { 0 };
	}

	int numSolutions = 0;
	if (K <= 10)
		cout << "\nВсе возможные перестановки:" << endl;

	solve(board, 0, K, numSolutions);

	cout << "Количество перестановок: " << numSolutions << endl;

	for (int i = 0; i < K; i++) {
		delete[] board[i];
	}

	delete[] board;

	cout << "\nРЕШЕНИЕ С ИСПОЛЬЗОВАНИЕМ ОДНОМЕРНОГО МАССИВА" << endl;

	int* board1D = new int[K] { 0 };

	int numSolutions1D = 0;

	if (K <= 10)
		cout << "\nВсе возможные перестановки:" << endl;

	solve1D(board1D, 0, K, numSolutions1D);

	cout << "Количество перестановок: " << numSolutions1D << endl;

	delete[] board1D;

}







