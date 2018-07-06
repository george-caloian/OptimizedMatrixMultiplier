#include "utils.h"
#include <fstream>
#include <sys/time.h>
#include <iostream>
#include <iomanip>

using namespace std;

int minim(int a, int b)
{
    if(a>=b)
   		return b;
   	else
   		return a;
}

int main(int argc, char **argv)
{
    struct test **tests;
    struct timeval begin, end;
    tests = (struct test **)malloc(sizeof(struct test*));
    (*tests) = (struct test *)calloc(MAXTESTS, sizeof(struct test));
    
    if (argc != 2)
        error("Usage: tema2 <cfg_file>");
    
    parse_config(argv[1], tests);
    print_tests(*tests);

    gettimeofday(&begin, NULL);
    
    for(int i = 0; i < 8; i++)
    {

        int size_A = tests[0][i].M * tests[0][i].K;
        int size_B = tests[0][i].K * tests[0][i].N;
        int size_C = tests[0][i].M * tests[0][i].N;
        string aux = tests[0][i].name;
        string aux_in = "input/";
	string aux_out = "out/";
        string aux_a = "_A";
        string aux_b = "_B";
        string aux_c = "_C";

        

        tests[0][i].A = new double[size_A];
        tests[0][i].B = new double[size_B];  
        tests[0][i].C = new double[size_C];

        
        FILE *fA, *fB, *fC;

        //deschiderea fisierelor de input
        string file_A = aux_in + aux  + aux_a + ".in";
        const char * filA = file_A.c_str();      
        fA = fopen(filA, "r");


        string file_B = aux_in + aux  + aux_b + ".in";
        const char * filB = file_B.c_str();
        fB = fopen(filB, "r");


        
        //citire A si B in functie de forma TT TN NT NN
        if (tests[0][i].transa == 'T' && tests[0][i].transb == 'T')
        {
        	//ajustare numar linii si coloane in functie de forma
            int lacb=tests[0][i].K;
            int ca=tests[0][i].M;
            
            
            for( int j = 0; j < lacb ; j=j+1)
                for ( int k = 0; k < ca; k=k+1)
                    fscanf(fA, "%lf", &tests[0][i].A[k * lacb + j]);

            int lb=tests[0][i].N;

            
            for( int j = 0; j < lb; j=j+1)
                for ( int k = 0; k < lacb; k=k+1)
                    fscanf(fB, "%lf", &tests[0][i].B[k + j * lacb]);

        }
        else if (tests[0][i].transa == 'T' && tests[0][i].transb == 'N')
        {
            int lalb=tests[0][i].K;
            int ca=tests[0][i].M;

            for( int j = 0; j < lalb; j=j+1)
                for ( int k = 0; k < ca; k=k+1)
                    fscanf(fA, "%lf", &tests[0][i].A[k * lalb + j]);

            int cb=tests[0][i].N;

            for( int j = 0; j < lalb; j=j+1)
                for ( int k = 0; k < cb; k=k+1)
                    fscanf(fB, "%lf", &tests[0][i].B[k * lalb + j]);

        }
        else if (tests[0][i].transa == 'N' && tests[0][i].transb == 'T')
        {
            int cacb=tests[0][i].K;
            int la=tests[0][i].M;

            for( int j = 0; j < la; j=j+1)
                for ( int k = 0; k < cacb; k=k+1)
                    fscanf(fA, "%lf", &tests[0][i].A[k + j * cacb]);

            int lb=tests[0][i].N;

            for( int j = 0; j < lb; j=j+1)
                for ( int k = 0; k < cacb; k=k+1)
                    fscanf(fB, "%lf", &tests[0][i].B[k + j * cacb]);                       
        }
        else if (tests[0][i].transa == 'N' && tests[0][i].transb == 'N')
        {
            int calb=tests[0][i].K;
            int la=tests[0][i].M;

            for( int j = 0; j < la; j=j+1)
                for ( int k = 0; k < calb; k=k+1)
                    fscanf(fA, "%lf", &tests[0][i].A[k + j * calb]);

            int cb=tests[0][i].N;

            for( int j = 0; j < calb; j=j+1)
                for ( int k = 0; k < cb; k=k+1)
                    fscanf(fB, "%lf", &tests[0][i].B[k * calb + j]);                       
        }

        
        fclose(fA);
        fclose(fB);

        string file_C = aux_in + aux  + aux_c + ".in";
        const char * filC = file_C.c_str();
        fC = fopen(filC, "r");

        // citire C
        for( int j = 0; j < tests[0][i].M; j=j+1)
            for ( int k = 0; k < tests[0][i].N; k=k+1)
                fscanf(fC, "%lf", &tests[0][i].C[k + j*tests[0][i].N]);
        fclose(fC);

        //etapa de calcul
        int block = 64;
        double *aux_n = new double[tests[0][i].M * tests[0][i].N];
        double *res = new double[tests[0][i].M * tests[0][i].N];

        //utilizarea metodei de spargere a matricilor in blocuri (lab 5)
        //inmultirea A*B
        for (int p = 0; p < tests[0][i].M ; p = p+block)
            for (int q = 0; q< tests[0][i].N ; q = q+block )
                for (int r = 0; r < tests[0][i].K ; r = r+block)
                    for (int pp = p; pp < minim(p + block, tests[0][i].M) ; pp++)
                        for (int qq = q; qq < minim(q + block, tests[0][i].N) ; qq++)
                        {
                            register double reg = 0;
                            for(int rr = r; rr < minim (r+ block, tests[0][i].K); rr++)
                            {
                                reg = tests[0][i].A[pp * tests[0][i].K + rr] * tests[0][i].B[qq * tests[0][i].K + rr];
                                aux_n [pp * tests[0][i].N + qq] += reg;
                            }
                        }

        // adunari cu alfa beta
        for(int g = 0;g < tests[0][i].M; g=g+1)
            for(int j = 0;j < tests[0][i].N; j=j+1)
                res [g * tests[0][i].N + j] = tests[0][i].alpha * aux_n [g * tests[0][i].N + j] + tests[0][i].beta * tests[0][i].C[g * tests[0][i].N+ j];

        string file_out = aux_out + aux  + ".out";


        FILE *fo;
        fo = fopen(file_out.c_str(),"w");

        //scriere in fisier
        for(int j = 0; j < tests[0][i].M; j=j+1)
        {
            for(int k=0; k< tests[0][i].N ; k=k+1)
                fprintf(fo,"%lf ",res[j * tests[0][i].N + k]);
            fprintf(fo,"\n");
           
        }
        fclose(fo);        
    }

    gettimeofday(&end, NULL);

    

    printf("%f \n", ((end.tv_sec - begin.tv_sec)*1000000.0f + end.tv_usec - begin.tv_usec)/1000000.0f);

    return 0;
}
