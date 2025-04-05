#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void mnozenie(int *A[], int *B[], int *C[], int N, int poczatek, int koniec)
{
	for(int i = poczatek; i < koniec; ++i) 
	{
	  	for(int j = 0; j < N; ++j) 
	  	{
			for(int k = 0; k < N; ++k) 
			{ 
       			C[i][j] += A[i][k] * B[k][j]; 
    		} 
    	}
    }
}

void mnozenieT(int *A[], int *B[], int *C[], int N, int poczatek, int koniec)
{
	for(int i = poczatek; i < koniec; ++i) 
	{
	  	for(int j = 0; j < N; ++j) 
	  	{
			for(int k = 0; k < N; ++k) 
			{ 
       			C[i][j] += A[i][k] * B[j][k]; 
    		} 
    	}
    }
}

void czysc(int *A[], int N)
{
    for(int i = 0; i < N; i++)
    {
    	for(int j = 0; j < N; j++)
    	{
    		A[i][j] = 0;
    	}
    }
}

int main()  
{
	srand (time(NULL));
	int i, j, k;
	int N, watki;
	cout << "Podaj rozmiar macierzy kwadratowej:";
    cin >> N;
    cout << "Podaj liczbe watkow:";
    cin >> watki;
    cout << "Rozmiar macierzy:"<<N<<"x"<<N<<"\n";
    
    int **A = new int*[N];
    for(i = 0; i < N; i++)
    	A[i] = new int[N];
    	
   	int **B = new int*[N];
    for(i = 0; i < N; i++)
    	B[i] = new int[N];
    	
   	int **C = new int*[N];
    for(i = 0; i < N; i++)
    	C[i] = new int[N];
    
    for(i = 0; i < N; i++)
    {
    	for(j = 0; j < N; j++)
    	{
    		A[i][j] = rand() % 100;
    		B[i][j] = rand() % 100;
    	}
    }
    
    // Macierz sekwencyjna A * B
    
    czysc(C, N);
    
  	auto start1 = std::chrono::steady_clock::now();
      
	mnozenie(A, B, C, N, 0, N);
    
   	auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end1-start1;
    std::cout << "Mnozenie sekwencyjne: " << elapsed_seconds1.count() << "s\n";
    
    // Macierz sekwencyjna A * B transponowana
    
    czysc(C, N);

   	auto start2 = std::chrono::steady_clock::now();
      
	mnozenieT(A, B, C, N, 0, N);
    
   	auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2-start2;
    std::cout << "Mnozenie sekwencyjne transponowane: " << elapsed_seconds2.count() << "s\n";
	
	int kolumny = N/watki;
	thread threadObj[watki];
	
	// Macierz na watkach A * B
	
	czysc(C, N);
	
	auto start3 = std::chrono::steady_clock::now();
	
	for(int i = 0; i < watki; i++)
	{
		int poczatek = kolumny * i;
		int koniec = kolumny + poczatek;
		threadObj[i] = thread(mnozenie, A, B, C, N, poczatek, koniec);
	}
	
	for(int i = 0; i < watki; i++)
	{
		threadObj[i].join();
	}
	
	auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds3 = end3-start3;
    std::cout << "Mnozenie na "<<watki<<" watkach: "<< elapsed_seconds3.count() << "s\n";
    
    // Macierz na watkach A * B transponowana
	
	czysc(C, N);
    
   	auto start4 = std::chrono::steady_clock::now();
	
	for(int i = 0; i < watki; i++)
	{
		int poczatek = kolumny * i;
		int koniec = kolumny + poczatek;
		threadObj[i] = thread(mnozenieT, A, B, C, N, poczatek, koniec);
	}
	
	for(int i = 0; i < watki; i++)
	{
		threadObj[i].join();
	}
	
	auto end4 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds4 = end4-start4;
    std::cout << "Mnozenie na "<<watki<<" watkach transponowane: "<< elapsed_seconds4.count() << "s\n";
    
    for(i = 0; i < N; i++)
    	delete[] A[i];
    delete[] A;
    
   	for(i = 0; i < N; i++)
    	delete[] B[i];
    delete[] B;
    
   	for(i = 0; i < N; i++)
    	delete[] C[i];
    delete[] C;

    return 0;
}
