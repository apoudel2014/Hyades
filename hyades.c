#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "hyades.h"
#include "hyades_fn.c"
FILE *inptr, *outptr;

int main()
{
  int N;
  double sum_d_deg, sum_r_deg, sum_rINhr, sum_dis;
  char ch[1000], c0[10], c1[10], c2[10], c3[10],c4[10], c5[10], c6[10], c7[10], c8[10], c9[10], c10[10], c11[10];
  outptr = fopen("output/rdINdeg.dat", "w");
  fprintf(outptr, "#RAinDEG   DECinDEG  RAinHR   Dis(pc) Err_dis Dm        Mv      err_Mv    Mb\n");
  inptr = fopen("data/hyades.dat", "r");

  fgets (ch, 1000, inptr);
  while(fgets (ch, 1000, inptr)!=NULL)
  {   
    N += 1;
    sscanf(ch, "%s %s %s %s %s %s %s %s %s %s %s %s", c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11);
    // RA calculation:
    double r_hr, r_min, r_sec, r_deg, rINhr;
    r_hr = atof(c3);
    r_min = atof(c4);
    r_sec = atof(c5);
    r_deg = radeg(r_hr, r_min, r_sec);
    rINhr = raDEhr(r_hr, r_min, r_sec);
    sum_r_deg += r_deg;
    sum_rINhr += rINhr;
    // Declination calculation:
    double d_hr, d_min, d_sec, d_deg;
    d_hr = atof(c6);
    d_min = atof(c7);
    d_sec = atof(c8);
    d_deg = decdeg(d_hr, d_min, d_sec);
    sum_d_deg += d_deg;
    // Distance and error in distance:
    double par, err_par,distance, err_distance, Der_m;
    par = atof(c1);
    err_par = atof(c2);
    distance = dist(par);
    err_distance = err_dis(par, err_par);
    Der_m = Dm(distance); 
    sum_dis += distance;
    // Absolute V & B magnitude and V error:
    double app_mag, app_Bmag, err_app_mag, abs_mag, abs_Bmag, err_abs_mag;
    app_mag = atof(c9);
    err_app_mag = atof(c10);
    app_Bmag = atof(c11)+app_mag;
    abs_mag = absolute_mag(app_mag, distance);
    abs_Bmag = absolute_mag(app_Bmag, distance);
    err_abs_mag = err_absolute_mag(err_app_mag, distance, err_distance);      
    //printf("%g %g\n", d_deg, sum_d_deg);
    fprintf(outptr, "%.8g %.8g %.8g %.8g %.8g %.8g %.8g %.8g %.8g\n", r_deg, d_deg, rINhr, distance, err_distance, Der_m, abs_mag, err_abs_mag, abs_Bmag);   
  }
  fclose(inptr);   
  fclose(outptr);
  // Mean, standard deviation, and standard error calculation:
  //Mean:
  double mean_r_deg, mean_rINhr, mean_d_deg, mean_dis, diff_r_deg, diff_rINhr, diff_d_deg, diff_dis;
  mean_r_deg = mean(sum_r_deg, N); 
  mean_d_deg = mean(sum_d_deg, N);
  mean_rINhr = mean(sum_rINhr, N);
  mean_dis   = mean(sum_dis, N);
  char ch1[100], d0[20], d1[20], d2[20], d3[20];
  inptr = fopen("output/rdINdeg.dat", "r");

  fgets (ch1, 1000, inptr);
  while(fgets (ch1, 100, inptr)!=NULL)
  {    
    double temp1, temp2, temp3, temp4;
    sscanf(ch1, "%s %s %s %s", d0, d1, d2, d3);
    temp1 = atof(d0);
    temp2 = atof(d1);
    temp3 = atof(d2);
    temp4 = atof(d3);
    diff_r_deg += pow((temp1-mean_r_deg), 2);
    diff_d_deg += pow((temp2-mean_d_deg), 2);
    diff_rINhr += pow((temp3-mean_rINhr), 2);
    diff_dis   += pow((temp4-mean_dis), 2);

  }
  fclose(inptr);
  //Standard Deviation:
  double sd_r_deg, sd_rINhr, sd_d_deg, sd_dis;
  sd_r_deg = SD(diff_r_deg, N);
  sd_rINhr = SD(diff_rINhr, N);
  sd_d_deg = SD(diff_d_deg, N);
  sd_dis   = SD(diff_dis, N);
  //SD_error:
  double sdER_r_deg, sdER_rINhr, sdER_d_deg, sdER_dis;
  sdER_r_deg = SD_err(sd_r_deg, N);
  sdER_rINhr = SD_err(sd_rINhr, N);
  sdER_d_deg = SD_err(sd_d_deg, N);
  sdER_dis   = SD_err(sd_dis, N);
  outptr = fopen("output/mean_SD_err.dat", "w");
  fprintf(outptr, "Mean, SD, and SD_error of the mean of the RA in decimal degrees:\n");
  fprintf(outptr, "%g, %g, and %g\n", mean_r_deg, sd_r_deg, sdER_r_deg);
  fprintf(outptr, "Mean, SD, and SD_error of the mean of the DEC in decimal degrees:\n");
  fprintf(outptr, "%g, %g, and %g\n", mean_d_deg, sd_d_deg,sdER_d_deg);
  fprintf(outptr, "Mean, SD, and SD_error of the mean of the RA in decimal hrs:\n");
  fprintf(outptr, "%g, %g, and %g\n", mean_rINhr, sd_rINhr, sdER_rINhr);
  fprintf(outptr, "Mean, SD, and SD_error of the mean of the distance in parsec:\n");
  fprintf(outptr, "%g, %g, and %g\n", mean_dis, sd_dis, sdER_dis);
  fclose(outptr);
return 0;
}














