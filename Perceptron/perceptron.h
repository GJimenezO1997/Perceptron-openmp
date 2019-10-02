
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#define RANDOM(A, B) (rand() % ((B) - (A) + 1) + (A))     

using namespace std;

int condition = 0;
int sumatoria;
int contador = 0;
int n, i;
int tam = 529;
string str;


void entrenamiento(int x1[], int x2[], int x3[], int x4[], int x5[], int x6[], int x7[], float error, float w[], float alpha, int result[]){

	while(condition == 0){
		n++;
		
		//#pragma omp parallel for reduction (+:sumatoria)
		for(i=0;i<14;i++){

			sumatoria = ((x1[i] * w[0]) + (x2[i] * w[1])+(x3[i] * w[2]) + (x4[i] * w[3]) + (x5[i] * w[4]) + (x6[i] * w[5])+ (x7[i] * w[6]));
			
			if(sumatoria > 0){

				sumatoria = 1;
			}
			else{

				sumatoria = -1;
			}

			error = result[i] - sumatoria;
			
			if((error)!= 0){

				w[0] = w[0] + (0.5 * alpha) * (x1[i] * error);
				w[1] = w[1] + (0.5 * alpha) * (x2[i] * error);
				w[2] = w[2] + (0.5 * alpha) * (x3[i] * error);
				w[3] = w[3] + (0.5 * alpha) * (x4[i] * error);
				w[4] = w[4] + (0.5 * alpha) * (x5[i] * error);
				w[5] = w[5] + (0.5 * alpha) * (x6[i] * error);
				w[6] = w[6] + (0.5 * alpha) * (x7[i] * error);
			}
		}

		//#pragma omp parallel for reduction (+:sumatoria)
		for(i=0;i<14;i++){

			sumatoria = ((x1[i] * w[0]) + (x2[i] * w[1]) + (x3[i] * w[2]) + (x4[i] * w[3])+ (x5[i] * w[4])+ (x6[i] * w[5])+ (x7[i] * w[6]));
			if(error == 0){

				contador++;
			}
			if(contador == 14){

				condition = 1;
			}
		}
		if(n > 999999){

			cout<<"\n\t ---Numero de itraciones maximas---";
			exit(1);
		}
	}

}
void manual(int x8[], float w[], float alpha, int result[]){
	//#pragma omp parallel for reduction (+:sumatoria)
	int cont1 = 0;
	int cont2 = 0;

	for(i=0;i<7;i++){

		sumatoria = ((x8[i] * w[0]) + (x8[i] * w[1]) + (x8[i] * w[2]) + (x8[i] * w[3])+ (x8[i] * w[4])+ (x8[i] * w[5])+ (x8[i] * w[6]));

		if(sumatoria > 0){

			sumatoria = 1;
		}

		else{

			sumatoria = -1;
		}

		printf("\tEntradas: %2i | \n",x8[i]);

		if (x8[i] == -1){
			cont2 = cont2+ 1;
			if (cont2 == 4)
			{
				str = "Terrestre   ";
			}
		} else {
			cont1 = cont1+1;
			if (cont1 == 4)
			{
				str = "Acuatico    ";
			}
		}	
	}
	cout<<"\n\tResultado: "<<str;
	
}

void verificacion(int x1[], int x2[], int x3[], int x4[], int x5[], int x6[], int x7[], float error, float w[], float alpha, int result[]){
	
	//#pragma omp parallel for reduction (+:sumatoria)

	for(i=0;i<14;i++){

		sumatoria = ((x1[i] * w[0]) + (x2[i] * w[1]) + (x3[i] * w[2]) + (x4[i] * w[3])+ (x5[i] * w[4])+ (x6[i] * w[5])+ (x7[i] * w[6]));

		if(sumatoria > 0){

			sumatoria = 1;
		}

		else{

			sumatoria = -1;
		}

		if (sumatoria == 1){
			
			str = "Acuaticos    ";
		}

		else if (sumatoria == -1){
			str = "Terrestres   ";
		}

		//cout<<"\tEntradas: "<<x1[i]<<" , "<<x2[i]<<" , "<< x3[i]<<" , "<<x4[i]<<"    ------- Salida: "<<sumatoria<<" --- "<<str<<endl;
		printf("\tEntradas: %2i, %2i, %2i, %2i, %2i, %2i, %2i -- Salida: %2i -- %s  | \n",x1[i],x2[i], x3[i], x4[i], x5[i], x6[i], x7[i], sumatoria, str.c_str());

		if(sumatoria != result[i]){

			system("clear");
			cout<<"\n\t ---Numero de itraciones maximas---";
			exit(1);
			
		}
	}

}

void principal(int threads){

	int nth = threads;
	int x8[8];

	float aleatorios[tam];

	for(int i = 0; i < tam; i++){

		aleatorios[i]=(RANDOM(-5, 5) / 900.0);	
	}

	float factorfactorAprendizaje[] = { -0.52,-0.12,0.0143, 0.0234,0.232,0.2335,0.4674,0.675,0.7883, 0.752,0.823,0.9876};
	float error;
	int i;
	int x1[] = {-1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, 1, -1}; 	// | -1 |-1 | -1 | -1 |
 	int x2[] = {-1, 1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1};		// |  1 | 1 |  1 | -1 |
	int x3[] = {-1, 1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1};		// | -1 | 1 | -1 | -1 |
	int x4[] = {-1, 1, 1, 1, -1, -1, -1, -1, 1, -1, -1, 1, -1, -1};		// | -1 | 1 |  1 |  1 |
	int x5[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1};	// | -1 |-1 | -1 | -1 |
	int x6[] = {-1, 1, 1, -1, -1, -1, -1, 1, 1, 1, -1, 1, -1, -1};		// | -1 | 1 |  1 | -1 |
	int x7[] = {-1, 1, 1, -1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1};		// | -1 | 1 |  1 | -1 |
	int result[] = {-1, 1, 1, -1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}; //  | -1 | 1 |  1 | -1 |
	
	float alpha = 0.5*factorfactorAprendizaje[rand() % 12];
	float w[7] = {aleatorios[rand() % 528], aleatorios[rand() % 528], aleatorios[rand() % 528], aleatorios[rand() % 528], aleatorios[rand() % 528], aleatorios[rand() % 528], aleatorios[rand() % 528]};
	srand(time(NULL));

	omp_set_num_threads(nth);
	
	/*Dealracion de secciones paralelas*/ 
	#pragma omp sections
	{

		//Seccion utilizada para realizar el entrenamiento del perceptron
		#pragma omp section
		{
			entrenamiento(x1, x2, x3, x4, x5, x6, x7, error, w, alpha, result);
		}
		//Seccion utilizada para mostrar pesos
		#pragma omp section
		{
			//system("clear");
			cout<<"\n\t------------PERCEPTRON-----------------------------------------------|"<<endl;
			cout<<"\n\t------------PESOS OPTIMOS--------------------------------------------|\n"<<endl;
			cout<<"\tPeso w[1]:   "<<w[0]<<"\t\t\t\t\t\t     |"<<endl;
			cout<<"\tPeso w[2]:   "<<w[1]<<"\t\t\t\t\t\t     |"<<endl;
			cout<<"\tPeso w[3]:   "<<w[2]<<"\t\t\t\t\t\t     |"<<endl;
			cout<<"\tPeso w[4]:   "<<w[3]<<"\t\t\t\t\t\t     |"<<endl;		
			cout<<"\tPeso w[5]:   "<<w[4]<<"\t\t\t\t\t\t     |"<<endl;
			cout<<"\tPeso w[6]:   "<<w[5]<<"\t\t\t\t\t\t     |"<<endl;		
			cout<<"\tPeso w[7]:   "<<w[6]<<"\t\t\t\t\t\t     |"<<endl;
		}

		//Seccion para verificar el entrenamiento
		#pragma omp section
		{
			cout<<"\n\t------------VERIFICACION DE ENTRENAMIENTO----------------------------|\n\n";

			verificacion(x1, x2, x3, x4, x5, x6, x7, error, w, alpha, result);
			cout<<endl;

		}

		//Seccion para verificar el entrenamiento
		#pragma omp section
		{
			
			cout<<"\tIngresa el valor de la nueva entrada: "<<endl;
			cout<<"\tX8: "<<endl;
			for (int i = 0; i < 7; ++i){
				cout<<"\t";
				  cin>>x8[i];				   

			}
			manual( x8,  w,  alpha,  result);

		}


	}
}
