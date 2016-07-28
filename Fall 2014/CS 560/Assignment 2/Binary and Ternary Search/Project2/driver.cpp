/*	Trevor Cargile
	813542789
	CS560 - Terary Search	*/

#include <iostream>
#include <ctime>

int bisearch(int array);
int tsearch(int array);

using namespace std;

int A[8000];

int main(int argc, char* argv[]){

	srand(time(0));
	rand();

	for (int i = 0; i < 8000; i++){
		A[i] = 2 * i;
	}

	int bcompares, tcompares;
	for (int i = 0; i < 5; i++){
		bcompares = 0;
		tcompares = 0;
		for (int j = 0; j < 10; j++){
			bcompares += bisearch(i);
			tcompares += tsearch(i);
		}
		cout << "Average compares for array " << i << " doing binary search is: " << bcompares / 10 << endl;
		cout << "Average compares for array " << i << " doing ternary search is: " << tcompares / 10 << endl;
	}

	tcompares = tsearch(0);

	// Keep command prompt open.. stupid.
	while (1){}
	return 0;
}

int bisearch(int array){
	int compares = 0;
	int size = 0;
	int found = 0;

	if (array == 0)
		size = 500;
	else if (array == 1)
		size = 1000;
	else if (array == 2)
		size = 2000;
	else if (array == 3)
		size = 4000;
	else if (array == 4)
		size = 8000;

	int number = rand() % (2 * size + 1);

	int right, left, current;
	right = size - 1;
	left = 0;


	while (right > (left+1)){
		current = (left + right) / 2;
		if (A[current] == number){
			compares++;
			//cout << " found. ";
			break;
		}
		else if (A[current] > number)
			right = current;
		else
			left = current;
		compares++;
		}

	if (A[right] == number){
		compares++;
		//cout << " At end. ";
	}
	else if (A[left] == number){
		compares++;
		//cout << " At end. ";
	}

	//cout << number << " " << A[number / 2] << " " << compares << endl;

	return compares;
}

int tsearch(int array){
	int compares = 0;
	int size = 0;
	int found = 0;

	if (array == 0)
		size = 500;
	else if (array == 1)
		size = 1000;
	else if (array == 2)
		size = 2000;
	else if (array == 3)
		size = 4000;
	else if (array == 4)
		size = 8000;

	int chunk = size / 3;
	int leftovers = size - chunk;
	//int number = rand() % (2 * size + 1);
	int number = 501;
	int left = 0;
	int right = size - 1;

	while ((right - left) >= 1){

		//cout << left + chunk << " , " << left + leftovers / 2 + chunk << " , " << right << endl;

		//Check the terms for equality.
		if (A[left + chunk] == number || A[left + leftovers / 2 + chunk] == number || A[right] == number){
			compares++;
			//cout << " found. " << endl;
			break;
		}

		if (A[left + chunk] > number)
			right = left + chunk;
		else if (A[left + leftovers / 2 + chunk] > number){
			right = left + leftovers / 2 + chunk;
			left = left + chunk + 1;
		}
		else if (A[right] > number)
			left = left + leftovers / 2 + chunk + 1;

		chunk = (right - left) / 3;
		leftovers = (right - left) - chunk;
		compares++;
	}

	return compares;
}
