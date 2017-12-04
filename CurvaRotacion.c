#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double likelihood(double* v_obs,double* v_model);
double *my_model(double * r_obs,double mb, double md, double mh);
double gaussrand();   
int main()
{
int N2=300;
double * r=malloc(300*sizeof(double));
double * v=malloc(300*sizeof(double));
FILE *file1 = fopen("RadialVelocities.dat", "r");
for (int i = 0; i < 300; i++)
{
  		if (feof(file1))
        		break;
		
    		fscanf(file1, " %lf %lf", &r[i], &v[i]);
		//printf(" %f %f", r[i], v[i]);
			
//	printf(" \n");
}
fclose(file1);
double * mb_walk=malloc(2000*sizeof(double));
double * md_walk=malloc(2000*sizeof(double));
double * mh_walk=malloc(2000*sizeof(double));
double * l_walk=malloc(2000*sizeof(double));
double mb_prime;
double md_prime;
double mh_prime;
double * v_init=malloc(300*sizeof(double));
double * v_prime=malloc(300*sizeof(double));
double l_prime;
double l_init;
double alpha;
double beta;

mb_walk[0]=gaussrand()*100+3500;
md_walk[0]=gaussrand()*100+3500;
mh_walk[0]=gaussrand()*100+3500;

//printf("%f %f %f",mb_walk[0],mb_walk[0],mb_walk[0]);// posdata siempre me botan ceros y no se por que;


v_init= my_model(r,mb_walk[0],md_walk[0],mh_walk[0]);
l_walk[0]=likelihood(v,v_init);
for (int i = 1; i < 2000; i++)
{
	mb_prime=gaussrand()*100+3500;
	md_prime=gaussrand()*100+3500;
	mh_prime=gaussrand()*100+3500;

	v_init=my_model(r,mb_walk[i-1],md_walk[i-1],mh_walk[i-1]);
	v_prime= my_model(r,mb_prime,md_prime,mh_prime);

	l_prime=likelihood(v,v_prime);
	l_init=likelihood(v,v_init);

	alpha=l_prime/l_init;
	if(alpha>=1.0){
		mb_walk[i]=mb_prime;
		md_walk[i]=md_prime;
		mh_walk[i]=mh_prime;
		l_walk[i]=l_prime;
			}
	else{
		beta=drand48()*(1.0-0.0) + 0.0;
		//printf("%f", beta);
		if(beta<=alpha){
			mb_walk[i]=mb_prime;
			md_walk[i]=md_prime;
			mh_walk[i]=mh_prime;
			l_walk[i]=l_prime;
				}
		else{
			mb_walk[i]=mb_walk[i-1];
			md_walk[i]=md_walk[i-1];
			mh_walk[i]=mh_walk[i-1];
			l_walk[i]=l_init;
	
			}
	
	}
	//printf("%f %f %f\n",mb_walk[i],md_walk[i],mh_walk[i]);
}
int max_likelihood_id;
double best_mb;
double best_md;
double best_mh;
double * best_v=malloc(300*sizeof(double));
double lmayor=0;

for (int i=1;i<2000;i++){
	if(l_walk[i-1]>l_walk[i] && l_walk[i-1]>lmayor){
		max_likelihood_id = i-1;
		lmayor=l_walk[i-1];
				}
			}

best_mb = mb_walk[max_likelihood_id];

best_mh = mh_walk[max_likelihood_id];
best_md=md_walk[max_likelihood_id];

best_v = my_model(r, best_mb, best_mh, best_md);

for (int i=0;i<300;i++){
printf(" %f\n", best_v[i]);

}
return 0;
}
//chi
double likelihood(double* v_obs,double* v_model)
{
double chi;
double sum=0;
for (int i=0;i<300;i++)
{
	sum=sum+(v_obs[i]-v_model[i]);
}
chi = (1.0/2.0)*pow(sum,2);
return chi;
}
//my model
double *my_model(double * r_obs,double mb, double md, double mh)
{
double bb=0.2497;
double bd=5.16;
double ad=0.3105;
double ah=64.3;
double* v_model=malloc(300*sizeof(double));;
for (int i=0;i<300;i++){
	v_model[i]=(sqrt(mb)*r_obs[i]/pow(sqrt(sqrt(pow(r_obs[i],2)+pow(bb,2))),3))+(sqrt(md)*r_obs[i]/pow(sqrt(sqrt(pow(r_obs[i],2)+pow(bd+ad,2))),3))+((sqrt(mh)/sqrt(sqrt(pow(r_obs[i],2)+pow(ah,2)))));
}
return v_model;
}
//gauss http://c-faq.com/lib/gaussian.html
double gaussrand()
{
	static double U, V;
	static int phase = 0;
	double Z;
	double PI=3.1416;

	if(phase == 0) {
		U = (rand() + 1.) / (RAND_MAX + 2.);
		V = rand() / (RAND_MAX + 1.);
		Z = sqrt(-2 * log(U)) * sin(2 * PI * V);
	} else
		Z = sqrt(-2 * log(U)) * cos(2 * PI * V);

	phase = 1 - phase;

	return Z;
}




