#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double PI = 3.14159265359;
/* Goal : Calculate pi by calculating the integral from 0 to 1 of f using the trapezoid method */

// calculates f
double f(double x) {
    return 4 / ( 1 + x*x );
}


// calculates the trapezoids and sums them
double trapezoids(double a, double b, double n) {
    double total_area = 0.5*( f(b)-f(a) );
    double h = ( b-a )/n; // step
    for (int i = 1; i < n; i++) {
        total_area += f(a + i*h);
    }
    total_area *= h;

    return total_area;
}


int main(int argc, char *argv[]){
	double a = 0, b = 1;        // boundaries of the integral
	int n = 10000;              // number of trapezoids
	double h = ( b-a )/n;       // step
    double startTime, endTime;

    // you can specify an argument n else by default it is 10000
    if (argc > 1) {
        n = atoi(argv[1]);
    }

	int rank, size;
	MPI_Init (&argc, &argv);	            /* starts MPI */
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* get current process id */
    MPI_Comm_size (MPI_COMM_WORLD, &size);	/* get number of processes */

    if (rank == 0) {
        // time the process
        startTime = MPI_Wtime();

        // first process
        double pi, part_of_pi;

        // first fraction of pi
        pi = trapezoids(a, a + (b-a)/size, n/size);

        // add up the fractions of pi calculated by the other processes
        for (int i = 1; i < size; i++) {
            // printf("Waiting for process %d to compute...\n", i);
            MPI_Recv(&part_of_pi, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            pi += part_of_pi;
        }

        endTime = MPI_Wtime();
        // printf(" --- Time taken: %f --- \n", endTime - startTime);
        // printf(" --- Pi Estimate: %f --- \n", pi);
        // printf(" --- Error: %f --- \n", PI - pi);
        // printf(" --- Percentage Error: %f --- \n", 100*(PI - pi)/PI);
        printf("%f++", endTime - startTime);
        printf("%f++", pi);
        printf("%f\n", PI - pi);

    } else {
        // printf("process %d is computing ...\n", rank);
        double part_of_pi = trapezoids(a + rank*(b-a)/size, a + (rank+1)*(b-a)/size, n/size);
		MPI_Send(&part_of_pi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
}