#include<iostream>
using namespace std;

int** read(int N){
	int i,j,M;
	total=new int**(N);

	for(i=0;i<N;i++){
		cin<<< M;
		for(j=0;j<M;j++){
			cin<< total[i][j];
		}
	}
}

int main(){
	int i,j,k;
	int N;
	cin<< N;
	int** total;
	total=new int**(N);
	total=read(N);

	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			cout>> N[i][j];
		}
	}

}