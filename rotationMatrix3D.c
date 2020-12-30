/* FileName: jamesMoncurReport1.c */
/* */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* define T and R as 0 and 1, signifing Translation and Rotation*/
enum operation {
	T , R
};

/* Function prototypes*/
/* used for translation: */
void translate( double *inputPtr, double *outputPtr, 
				int rowsIn, int colsIn, int rowsOut, int colsOut );

void matrixAdd( double **matrixSumPtr, double **matrix1Ptr, double **matrix2Ptr, int rows1, 
				int cols1, int rows2, int cols2, int rowsOut, int colsOut );
				
/* used for rotation: */
void rotate( double *inputPtr, double *outputPtr, int rows, int cols );

void matrixMultiply( double **matrixProductPtr, double array1[], double **matrix2Ptr, 
				int rows1, int cols1, int rows2, int cols2, int rowsOut, int colsOut );

unsigned int compareForCompatablity( int rows1, int cols1, int rows2, int cols2 );

/* used throughout program: */
unsigned int compareForAdditionCompatablity( int rows1, int cols1, int rows2, int cols2 );

void printMatrix(double *arr, int r, int c);


int main()
{
	char choice;
	/* initialise input and output coordinates*/
	/* memory allocation */
	int inOutRow = 3; /*no rows in both arrays inCoord and outCoord*/ 
	int inOutCol = 1; /*no columns in both arrays inCoord and outCoord*/ 
	double hold;
	double *inCoord = (double *)malloc(inOutRow * inOutCol * sizeof(double)); /* double scripted pointed to 1d array*/
	double *outCoord = (double *)malloc(inOutRow * inOutCol * sizeof(double));
	puts("*** 3D Translation/Rotation Algorithm ***");
	/* Input x1, y1, z1 from the user */
	printf("\nx-axis current value:  ");
	scanf( "%lf" , &hold );
	*(inCoord + 0 + 0) = hold;
	
	printf("y-axis current value:  ");
	scanf( "%lf" , &hold );
	*(inCoord + 0 + 1) = hold;
	
	printf("z-axis current value:  ");
	scanf( "%lf" , &hold );
	*(inCoord + 0 + 2) = hold;
	
	/* Input from user if transation or rotation operation is required */ 
	printf("\n\nEnter T or R for 3D translation / rotation: ");
    do
    {
        scanf(" %c", &choice);
        if (!(choice == 'T' || choice == 'R' ))
        {
            printf("%c is not a valid input, please enter either T or R." , choice);
            printf("\nEnter T or R for 3D translation / rotation:   ");
        }
    } while (!(choice == 'T' || choice == 'R'));
    
	switch ( choice ) { 
		case 'T':
			
		    translate( inCoord, outCoord, inOutRow, inOutCol, inOutRow, inOutCol);
		    
		    /* print input coordinates before translation*/
			puts("\n\n(x,y,z) coordinates before translation:");
			printMatrix(inCoord, inOutRow, inOutCol);
			/* print input coordinates before translation*/
			puts("\n\n(x,y,z) coordinates after translation:");
		    printMatrix(outCoord, inOutRow, inOutCol);
			break;
		case 'R':
			
			rotate( inCoord, outCoord, inOutRow, inOutCol);
	
			/* print input coordinates before translation*/
			puts("\n\n(x,y,z) coordinates before rotation:");
			printMatrix(inCoord, inOutRow, inOutCol);
			/* print input coordinates before translation*/
			puts("\n\n(x,y,z) coordinates after rotation:");
		    printMatrix(outCoord, inOutRow, inOutCol); 
			
			break;
		default:
			puts( "Invalid choice, please select either T or R.\n" );
		    break;
      } /* end switch */
      
      /* give back memory */
    free(inCoord);
    free(outCoord);
    
    return 0;
} /* end function main */


/* ******************* */
/* ******************* */

/* Function definitions */

/* ******************* */
/* functions used for translation */
void translate( double *inputPtr, double *outputPtr, int rowsIn, int colsIn, int rowsOut, int colsOut){
	/* initialise translation array representing the change in x,y,z*/
	double *transDelta = (double *)malloc(3 * 1 * sizeof(double)); /* double scripted pointed to 1d array*/
	int transRow = rowsIn; /*no rows in transDelta*/ 
	int transCol = colsIn; /*no columns in transDelta*/
	double hold;
	
	/* Input deltaX, deltaY, deltaZ from the user */
	printf("\nx-axis translation value: ");
	scanf( "%lf" , &hold );
	*(transDelta + 0 + 0) = hold;
	
	printf("y-axis translation value: ");
	scanf( "%lf" , &hold );
	*(transDelta + 0 + 1) = hold;
	
	printf("z-axis translation value: ");
	scanf( "%lf" , &hold );
	*(transDelta + 0 + 2) = hold;
	/*calculate value after translation*/
	matrixAdd( &outputPtr, &inputPtr, &transDelta, 
				rowsIn, colsIn, transRow, transCol, rowsIn, colsIn );
				/* rows/column of output array are same as rows/columns of input */
	
	free(transDelta);/* return memory to operating system*/
} /* end function translate */

void matrixAdd( double **matrixSumPtr, double **matrix1Ptr, double **matrix2Ptr, 
				int rows1, int cols1, int rows2, int cols2, int rowsOut, int colsOut ){
	/* initalise counters for rows and columns*/
	int i , j; /* i and j corresponds to columns and rows in the loop respectively*/
	unsigned int checkInput = compareForAdditionCompatablity( rows1, cols1, rows2, cols2 );
	unsigned int checkOutput = compareForAdditionCompatablity( rows1, cols1, rowsOut, colsOut );
	
	if ( checkInput == 1 ){ /* if matrices to be added have compatable dimensions */
		if ( checkInput == 1 ){ /* if output matrices has compatable dimensions with the input matrices */
			for ( i = 0; i < cols1; i++) {
	      		for (j = 0 ; j < rows1; j++) {
	         		*( *(matrixSumPtr + i*(colsOut-1)) + j ) = *( *(matrix1Ptr + i*(cols1-1) ) + j ) + *( *(matrix2Ptr + i*(cols2-1) ) + j ); 
	      		}/* end for */
	   		}/* end for */
		}/* end inner if */	
	}/* outer if */
	else{
		puts("Matrix dimesions are not compatable for addtion, please input valid matrices");
	}
} /* end function matrixAdd */

/* ******************* */
/* functions used for rotation */

void rotate( double *inputPtr, double *outputPtr, int rows, int cols){
	/*initialise varialbes*/
	char choice;
	int order;
	double xAng, yAng, zAng;
	int rotRow = 3; /*the rotational matrices have the same dimensions*/ 
	int rotCol = 3; 
	int i, j;
	double *holdInput1 = (double *)malloc(3 * sizeof(double)); /*  */
	double *holdInput2 = (double *)malloc(3 * sizeof(double));
	double *holdInput3 = (double *)malloc(3 * sizeof(double));
	
	/* initialise rotation matrices for x, y and z axes, which have dims 3x3*/
	char angleFormat;
	printf("\n\nChoose the unit (degrees/radians) for the 3D rotation angles [d/r]: ");
	    do
	    {
	        scanf( " %c" , &angleFormat );
	        if (!( angleFormat == 'd' || angleFormat == 'r' ))
	        {
	            printf("%c is not a valid input. Please enter a valid input\n", angleFormat);
	            printf("Choose the unit (degrees/radians) for the 3D rotation angles [d/r]: ");
	        }
	    } while (!( angleFormat == 'd' || angleFormat == 'r' ));
	printf("\nx-axis rotation angle: ");
	scanf("%lf" , &xAng);
	if ( angleFormat == 'd'){
		xAng = xAng * M_PI / 180; /* convert from degrees to radians */
	}
	double xRot[9] = { 1, 0, 0, 0, cos(xAng), -sin(xAng), 0, sin(xAng), cos(xAng) };

	
	printf("y-axis rotation angle: ");
	scanf("%lf" , &yAng);
	if ( angleFormat == 'd'){
		yAng = yAng * M_PI / 180; /* convert from degrees to radians */
	}
	double yRot[9] = { cos(yAng), 0, sin(yAng), 0, 1, 0, -sin(yAng), 0, cos(yAng) };
	
	printf("z-axis rotation angle: ");
	scanf("%lf" , &zAng);
	if ( angleFormat == 'd'){
		zAng = zAng * M_PI / 180; /* convert from degrees to radians */
	}
	double zRot[9] = { cos(zAng), -sin(zAng), 0, sin(zAng), cos(zAng), 0, 0, 0, 1 };
	
	/* determine order of rotation and perform calculation*/
	
	/* determine whether default order is required*/
	puts("\nDefault 3D axes order is x-axis, y-axis, z-axis");
	printf("Do you wish to use a different order of axes than default axes rotation order [y/n]: ");
    do
    {
        scanf( " %c" , &choice );
        if (!( choice == 'y' || choice == 'n' ))
        {
			printf("%c is not a valid input. Please enter a valid input\n", choice);
            printf("Do you wish to change default axes rotation order [y/n]: ");
        }
    } while (!( choice == 'y' || choice == 'n' ));	
    
    if ( choice == 'n' ){
      	puts("Chosen axes rotation order is x,y,z");
      	matrixMultiply( &outputPtr, xRot, &inputPtr, rows, cols, rotRow, rotCol,rows, cols );
		/* calculates the coords after x-axes rotation*/
		matrixMultiply( &outputPtr, yRot, &outputPtr, rows, cols, rotRow, rotCol,rows, cols );
		/* calculates the coords after y-axes rotation*/
		matrixMultiply( &outputPtr, zRot, &outputPtr, rows, cols, rotRow, rotCol,rows, cols );
		/* calculates the final coords after z-axes rotation*/
	}/* end if */
	else{
		/* select custom order*/
		puts("\n\nThere are six possible combinations that the input coordinates can be rotated by.");
		puts("The one combation is to rotate by the x-axes, then y-axes, then z-axes i.e. (x,y,z).\nSelect a combination number from 1-6");
		printf("   1: x,y,x  2: x,z,y  3: y,x,z  4: y,z,x  5: z,x,y  6: z,y,x  \n ");
	    do
	    {
	        scanf( " %d" , &order );
	        if (!( order == 1 || order == 2 || order == 3 || order == 4 || order == 5 || order == 6 ))
	        {
	            printf("%d is not a valid input. Please enter a valid input\n", order);
	            printf("   1: x,y,x  2: x,z,y  3: y,x,z  4: y,z,x  5: z,x,y  6: z,y,x  \n ");
	        }
	    } while (!( order == 1 || order == 2 || order == 3 || order == 4 || order == 5 || order == 6 ));
		/*assign order*/
		switch ( order ){
			case 1:
    			puts("Chosen axes rotation order is x,y,z");
    			matrixMultiply( &outputPtr, xRot, &inputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the coords after x-axes rotation*/
				matrixMultiply( &outputPtr, yRot, &outputPtr, rows, cols, rotRow, rotCol,rows, cols );
				/* calculates the coords after y-axes rotation*/
				matrixMultiply( &outputPtr, zRot, &outputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the final coords after z-axes rotation*/
				break;
				
			case 2:
    			puts("Chosen axes rotation order is x,z,y");
    			matrixMultiply( &outputPtr, xRot, &inputPtr, rows, cols,  rotRow, rotCol, rows, cols );
				/* calculates the coords after x-axes rotation*/
				matrixMultiply( &outputPtr, zRot, &outputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the coords after z-axes rotation*/
				matrixMultiply( &outputPtr, yRot, &outputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the final coords after y-axes rotation*/
				break;
				
			case 3:
    			puts("Chosen axes rotation order is y,x,z");
    			matrixMultiply( &outputPtr, yRot, &inputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the coords after y-axes rotation*/
				matrixMultiply( &outputPtr, xRot, &outputPtr,  rows, rotRow, rotCol, cols, rows, cols );
				/* calculates the coords after x-axes rotation*/
				matrixMultiply( &outputPtr, zRot, &outputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the final coords after z-axes rotation*/
				break;
				
			case 4:
    			puts("Chosen axes rotation order is y,z,x");
    			matrixMultiply( &outputPtr, yRot, &inputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the coords after y-axes rotation*/
				matrixMultiply( &outputPtr, zRot, &outputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the coords after z-axes rotation*/
				matrixMultiply( &outputPtr, xRot, &outputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the final coords after x-axes rotation*/	
				break;
				
			case 5:
    			puts("Chosen axes rotation order is z,x,y");
    			matrixMultiply( &outputPtr, zRot, &inputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the coords after x-axes rotation*/
				matrixMultiply( &outputPtr, xRot, &outputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the coords after y-axes rotation*/
				matrixMultiply( &outputPtr, yRot, &outputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the final coords after z-axes rotation*/
				break;
			case 6:
    			puts("Chosen axes rotation order is z,y,x");
    			matrixMultiply( &outputPtr, zRot, &inputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the coords after z-axes rotation*/
				matrixMultiply( &outputPtr, yRot, &outputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the coords after y-axes rotation*/
				matrixMultiply( &outputPtr, xRot, &outputPtr, rows, cols, rotRow, rotCol, rows, cols );
				/* calculates the final coords after x-axes rotation*/
				break;
		}/* end switch */
	}/* end else */
	
						        		
	/* return memory to operating system*/
	free(holdInput1);
	free(holdInput2);
	free(holdInput3);
} /* end function rotate */


void matrixMultiply( double **matrixProductPtr, double array1[], double **matrix2Ptr, 
						int rowsOut, int colsOut, int rows1, int cols1, int rows2, int cols2 ){
	/*this is a general matrix multipier function, however modified to accept the first matrix in array[3] form*/
	/* initialise variables */ 
	int r, c, k; /* c is a counter for columns in matrix1, r is rows for matrix1, k for columns of matrix2*/
	double sum = 0;
	double hold1, hold2;
	double nextInputHolder[3];
	
	
	unsigned int checkOutput = compareForAdditionCompatablity( rows2, cols2, rowsOut, colsOut ); /* ensure...*/  
	/*...init output array is of correct dimensions*/
	
	/*initialise inputHold*/
	
	/* processing phase */
	if ( rows2 == cols1 ){ /* first matrice no. of column must be equal to second matrice rows to be compatable for multiplication */
		if ( checkOutput == 1 ){ /* if output matrices has compatable dimensions with the input matrices */
			for (r = 0; r < rows1; r++) { /* loops through first matrix's rows (ie rotational matrix) */
		    	for (c = 0; c < cols2; c++) {/* loops thr second matrix's columns (ie rotational matrix) */
		        	for (k = 0; k < rows2; k++) {/* loops thr first matrix's column and second matrix's rows */
		        		hold1 =array1[ k+(r*rows2) ];
		        		hold2 = *( *(matrix2Ptr + c) + k );
		        		sum = sum + ( hold1 * hold2);/* multiplys first matrix's column in row r by second matrix's rows in column c*/	
		        	}
		 		nextInputHolder[r] = sum; /* assign sum to a holding array */
		        sum = 0; /*reset sum for next row in matrix*/
		    	}/* end inner for */
		    }/* end outer for */
		    
		}/* end inner if */
	}/* end outer if */
	else{
	puts("Matrix dimesions are not compatable for multiplication, please input valid matrices");
	}/* end outer else */
	
	/* assign the holding values to relevant output matrix elements*/
	/* the purpose of this is to avoid introducing the output elements as a input elements inappropriately in recursive use of this function */		
	*( *(matrixProductPtr + 0 ) + 0 ) = nextInputHolder[0];
	*( *(matrixProductPtr + 0 ) + 1 ) = nextInputHolder[1];
	*( *(matrixProductPtr + 0 ) + 2 ) = nextInputHolder[2];
}/* end function matrixMultiply */

/* ******************* */
/* functions used throughout program */

unsigned int compareForAdditionCompatablity( int rows1, int cols1, int rows2, int cols2 ){
	if ( rows1 == rows2 ){
		if ( cols1 == cols2){
			return 1;
		}
	}
	else{
		puts("Matrix dimensions are incompatable and therefore matrix operations cannot occur");
		return 0;
	}
} /* end function compareForCompatable */

void printMatrix(double *arr, int r, int c){
	int i,j;
	/* Display the matrix */
    for (i = 0; i <  r; i++){
      for (j = 0; j < c; j++) {
         printf( "%lf %c" , *(arr + i*c + j) , (j+1)% c == 0 ? '\n' : '\t'); 
    	}/*end inner for */
    }/* end outer for */
}/* end function printMatrix */
