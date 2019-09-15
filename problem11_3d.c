#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "coeff.h"

double **meshgrid(int len, int begin, int addX, int addY);
void saveMat(double** mat, char*str, int m, int n);

int main(){
	int len = 6;
	double c  = 0;
	double c1 = 0;
	double **x = meshgrid(len, -2, 1, 0);
	double **y = meshgrid(len, -2, 0, 1);
	saveMat(x, "meshX.dat", len, len);
	saveMat(y, "meshY.dat", len, len);
	
	//Direction vectors parallel to plane
	double ** n1 = createMat(3, 1);
	    n1[0][0] = 1 ; n1[1][0] = -2 ; n1[2][0] = 3 ;	      

	double ** n2 = createMat(3, 1);
	    n2[0][0] = 2 ; n2[1][0] = -1 ; n2[2][0] = -1 ;	 
	
	//Finding normal
	double ** n3 = createMat(3,3);
	    n3[0][0] = 0           ;   n3[1][0] = -(n1[2][0]) ;     n3[2][0] = n1[1][0]    ;
        n3[0][1] = n1[2][0]    ;   n3[1][1] = 0           ;     n3[2][1] = -(n1[0][0]) ;
        n3[0][2] = -(n1[1][0]) ;   n3[1][2] = n1[0][0]    ;     n3[2][2] = 0           ;
        
    double ** n = matmul(n3, n2, 3,3,1);   

    //Finding plane equation
	double ** P = createMat(3, 1);
	    P[0][0] = 1 ; P[1][0] = -1 ; P[2][0] = -1 ;
	c = **matmul(transpose(n,3,1), P, 1,3,1);
	
	//Generating points on a plane
	double **z = createMat(len,len);
	for (int i=0; i<len; i++)
		for (int j=0; j<len; j++)
	z[i][j] = (c- (n[0][0]*x[i][j]+n[1][0]*y[i][j])*1.0)/(n[2][0]);
	print(z,len,len);
	printf("\n\n\n\n");
	
	saveMat(z, "meshz.dat", len, len);
	print(n,3,1);
	printf("\n\n\n");	
	printf("%lf", c);
	printf("\n\n");
	
		//Finding distance between point and plane  
	double ** Q = createMat(3, 1);
	    Q[0][0] = 1 ; Q[1][0] = 3 ; Q[2][0] = -7 ;
	c1 =  **matmul(transpose(n,3,1), Q, 1,3,1);
	double Distance = abs(c-c1)/linalg_norm(n,3);
	printf("Distance = %lf", Distance);
	
	//Plotting lines
	double ** A = createMat(3, 1);
	    A[0][0] = 1 ; A[1][0] = -2 ; A[2][0] = 4 ;
	    double ** L1_y = createMat(len,len);
	    double ** L1_z = createMat(len,len);
	    for (int i=0; i<len; i++)
		for (int j=0; j<len; j++)
    L1_y[i][j] = (((x[i][j]-A[0][0])*n1[1][0])/n1[0][0])+A[1][0];
    	for (int i=0; i<len; i++)
		for (int j=0; j<len; j++)
	L1_z[i][j] = (((x[i][j]-A[0][0])*n1[2][0])/n1[0][0])+A[2][0];
        
	double ** B = createMat(3, 1);
	    B[0][0] = 2 ; B[1][0] = -1 ; B[2][0] = -7 ;
	    double ** L2_y = createMat(len,len);
	    double ** L2_z = createMat(len,len);
	    for (int i=0; i<len; i++)
		for (int j=0; j<len; j++)
    L2_y[i][j] = (((x[i][j]-B[0][0])*n2[1][0])/n2[0][0])+B[1][0];
    	for (int i=0; i<len; i++)
		for (int j=0; j<len; j++)
	L2_z[i][j] = (((x[i][j]-B[0][0])*n2[2][0])/n2[0][0])+B[2][0];	

	saveMat(L1_y, "meshL1_y.dat", len, len);
	saveMat(L1_z, "meshL1_z.dat", len, len);
	saveMat(L2_y, "meshL2_y.dat", len, len);
	saveMat(L2_z, "meshL2_z.dat", len, len);
	saveMat(P, "pointP.dat", 3, 1);
	saveMat(Q, "pointQ.dat", 3, 1);

	return 0;
}
																																											
double **meshgrid(int len, int begin, int addX, int addY)
{
	double ** ret = createMat(len, len);
	for (int i=0; i<len; i++)
		for (int j=0; j<len; j++){
			ret[i][j] = begin + i*addY + j*addX;
		}
	return ret;
}

void saveMat(double** mat, char *str, int m, int n){
	FILE *fp;
	fp = fopen(str,"w");
	for (int i=0; i < m; i++){
		for (int j=0; j < n; j++){
			fprintf(fp, "%lf ", mat[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}
