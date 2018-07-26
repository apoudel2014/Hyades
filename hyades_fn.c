//Function used in hyades.c
// Conversion of RA in degrees
double radeg(double hr, double min, double sec){
  return ((hr*15.0)+((min*15.0)/60.0)+((sec*15.0)/3600.0));
  }
  
// Conversion of DEC in degrees  
double decdeg(double deg, double min, double sec){
  return (deg+(min*15./60.)+(sec*15./3600.));
  }

// Calculating mean:
double mean(double x, int n){
  return x/n;
  }
  
// Standard Deviation:
double SD(double sumofdev, int n){
  return (sqrt(sumofdev/(n-1)));
  }

// Standard Error:
double SD_err(double SD, double n){
  return (SD/sqrt(n));
  }

// Conversion of RA in Decimal hours:
double raDEhr(double hr, double min, double sec){
  return (hr+(min/60.0)+(sec/3600.0));
  }  
// Distance in parsec(given parallax in milli-arcsec) and error in distance:

double dist(double par){
  return (1000/par);
  }  
// Propagation of error in Distance:
double err_dis(double par, double err_par){
  return (err_par*1000/(par*par));
  }  
// Differenciating equation of photometric parallax:
double Dm(double distance)
{
  int SD_distance = 11.7035;
  return (5*2*SD_distance/distance);
}    
// Absolute magnitude and its error:
double absolute_mag(double app_mag, double distance)
{
  return (app_mag - (5*log10(distance)) + 5);
}

double err_absolute_mag(double err_app_mag, double distance, double err_distance)
{
  return sqrt((err_app_mag*err_app_mag)+(25*err_distance*err_distance/(distance*distance)));
}  
  


  
  