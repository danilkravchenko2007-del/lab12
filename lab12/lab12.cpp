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

void printBoard4Arrays(int* P, int K) {
	if (K <= 10) {
		cout << "----------------\n";
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				if (P[j] == i) {
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


void solve4Arrays(int col, int K, int* P, int* H, int* R, int* L, int& count) {
	if (col == K) {
		count++;
		printBoard4Arrays(P, K);
		return;
	}

	for (int row = 0; row < K; row++) {
		if (H[row] == 0 && R[row - col + K - 1] == 0 && L[row + col] == 0) {

			P[col] = row;

			H[row] = 1;
			R[row - col + K - 1] = 1;
			L[row + col] = 1;

			solve4Arrays(col + 1, K, P, H, R, L, count); // рекурсия

			// откат
			H[row] = 0;
			R[row - col + K - 1] = 0;
			L[row + col] = 0;
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

	cout << "\nРЕШЕНИЕ ИЗ ЛЕКЦИЙ (4 МАССИВА)" << endl;

	// выделяем память под 4 массива
	int* P = new int[K] { 0 };         // позиции ферзей
	int* H = new int[K] { 0 };         // занятые строки
	int* R = new int[2 * K - 1] { 0 }; // занятые главные диагонали (их всегда 2*K - 1)
	int* L = new int[2 * K - 1] { 0 }; // занятые побочные диагонали (их всегда 2*K - 1)

	int numSolutions4 = 0;

	if (K <= 10)
		cout << "\nВсе возможные расстановки:" << endl;

	solve4Arrays(0, K, P, H, R, L, numSolutions4);

	cout << "Количество перестановок: " << numSolutions4 << endl;

	// Очистка памяти
	delete[] P;
	delete[] H;
	delete[] R;
	delete[] L;

	return 0;
}







