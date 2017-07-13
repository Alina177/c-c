/**
* brief - method Danilevsky
* author - Gritsay Alina
* university - KPI
*/
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <cmath>
#define H 0.01

using namespace std;


double d2f(double x, int n, double* Koef){
 double h, x0, x1, x2,y0, y1, y2;
     h = 0.01;
     x0 = x;
     x1 = x + h;
     x2 = x + 2 * h;
//     y0 = f(x0, n, Koef);
//     y1 = f(x1, n, Koef);
//     y2 = f(x2, n, Koef);
//   d2f = (y2 - 2 * y1 + y0)/(h*h);
     return 0;
}

double df(double,int n, double* Koef){
	double h;
     h = 0.01;
 //    df = (f(x+h, n, Koef) - f(x, n, Koef))/h;
}

double f(double x, double n, double* Koef){
	double S;
	int j=1,i;
	S = pow(x,n);
	for ( i = n-1; i >0; i--){
		S = S - (pow(x,i)*Koef[j]);
		j = j + 1;
	}
	S = S - Koef[j];
	return S;
}

double pow(double x, double y){
	double res;
	if (x = 0){res = 0;}
	else if( (x<0) && ((ceil(y))*2 == 0) ){ res = exp(y*log(x));}
	else if( x > 0) { res = exp(y*log(x));}
	else{ res = exp(y*log(x));}
	return res;
}

double** multiply_matrix(double** A, double** B,int n){
	double S, C[n][n];
	for( int i = 0; i < n; i++){
		for( int j = 0; j< n; j++){
			S = 0.0;
			for (int k = 0; k < n; k++){
				S = S+A[i][k]*B[k][j];
				C[i][j] = S;
			}
		}
	}
		
		double** R = new double*[n];
				for(int i = 0; i < n; i++) {
					R[i] = new double[n];
					for(int j = 0; j < n; j++) {
						R[i][j] = C[i][j];
					}
				}		
		return R;
}

double* get_koef(double** A, int N) {
	double M[N][N], rM[N][N],r,koef_1=0.0;
	int i, j, k, w, q,index;
	double** C;
	index = N-2;
	if( A[N-1][N-2] == 0){
		while( A[N-1][index] == 0 && index>=0){
				index--;
		}
			if( index < 0){
			koef_1 = A[N-1][N-1];
				N--;
				//get_koef(A,N-1);
				//return;
				//cout << "N=" << N << endl;
			}
			else{
			for( i =0; i< N; i++){
				r = A[i][N-2];
				A[i][N-2] = A[i][index];
				A[i][index] = r;
			}
			for( j =0; j< N; j++){
				r = A[N-2][j];
				A[N-2][j] = A[index][j];
				A[index][j] = r;
			}
			}
			
	}

						for( i = 0; i < N; i++){
							for( j =0; j< N; j++){
								cout << A[i][j] << ' ';
								}
								cout << endl;
						} 	
	
	
	
	for(int k = N-2; k >=0; k--) {	
	
			for( int q = 0; q < N; q++){
				for(int w = 0; w < N; w++){
					if( q == w){M[q][w] = 1;} else{M[q][w] = 0;}
				}
			}
			for( int q = 0; q < N; q++){
				for(int w = 0; w < N; w++){
					if( q == w){rM[q][w] = 1;} else{rM[q][w] = 0;}
				}
			}			
		for(int j = 0; j < N; j++) {
			if( j == k){			
				M[k][j] = 1/A[k+1][k];
				rM[k][j] = A[k+1][j];
				
			} else{
				M[k][j] = -A[k+1][j]/A[k+1][k]; 
				rM[k][j] = A[k+1][j];
			}
			
			for( int q = 0; q < N; q++){
			for(int w = 0; w < N; w++){
			}
		}
			double** z = new double*[N];
				for(int i = 0; i < N; i++) {
					z[i] = new double[N];
					for(int j = 0; j < N; j++) {
						z[i][j] = rM[i][j];
					}
				}	
			double** f = new double*[N];
				for(int i = 0; i < N; i++) {
					f[i] = new double[N];
					for(int j = 0; j < N; j++) {
						f[i][j] = A[i][j];
					}
				}	
			double** h = new double*[N];
				for(int i = 0; i < N; i++) {
					h[i] = new double[N];
					for(int j = 0; j < N; j++) {
						h[i][j] = A[i][j];
					}
				}
			if( j ==N-1){
			
				C = multiply_matrix(z,f,N);	
				double** C1 = new double*[N];
					for(int i = 0; i < N; i++) {
						C1[i] = new double[N];
						for(int j = 0; j < N; j++) {
							C1[i][j] = M[i][j];
						}
					}
				A = multiply_matrix(C,C1,N);
						cout << "C[N][N] = " << endl;
							for( int q = 0; q < N; q++){
								for(int w = 0; w < N; w++){
									cout << A[q][w] << ' ';
								}
							cout<< endl;
							}
			}
		}	
	}
	double* Koef = new double[N+1];
	if(koef_1 == 0.0){
	for( int i = 0; i < N; i++){
		Koef[i] = A[0][i];
	}
	}else{
	for( int i = 0; i < N+1; i++){
		Koef[i] = A[0][i];
		Koef[N] = koef_1;
	}
	}
	return Koef;
}

int main() {
	int N,k;
	double* B;
	double* X;
	double x1,x0,f1,f2,a0,xn,b0;
	bool b;
	double** p = new double*[N];
	cout << "Enter N: ";
	cin >> N;
	cout << "Enter A[N][N]: " << endl;
	
		for(int i = 0; i < N; i++) {
			p[i] = new double[N];
			for(int j = 0; j < N; j++) {
				cin >> p[i][j];
			}
		}	
	double Koef[N];
	B = get_koef(p,N);
	for( int i = 0; i <N; i++){
		cout << "B[i] = " << B[i] << ' ';
	}
	
	x1 = x0;
	a0 = x0;
	b = false;
	k = 1;
	while(x1 <= xn){
		f1 = f(x1,N,B);
		x1 = x1 + 0.1;
		f2 = f(x1,N,B);
		if( f1*f2 < 0){
		     b0 = x1;
		     b = true;
		 }
		 if (b == true){
		  // X[k] := method_hord(x1-0.1{a0}, x1+0.1{b0}, n, Koef);
		     b = false;
	          a0 = X[k] + 0.1;
	           x1 = X[k] + 0.1;
		     k = k + 1;
		  }
          }

	for(int i = 0; i < N; i++) delete[] p[i];
	delete[] p;
}

