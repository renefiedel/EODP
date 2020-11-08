#ifndef COMMON_SRC_COMMON_HPP_
#define COMMON_SRC_COMMON_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <math.h>
#include <boost/multi_array.hpp>
#include <boost/filesystem.hpp>

using namespace std;

// Module names
#define GEOMETRY_MODULE_NAME             "GM"

// File extensions
#define XML_FILE_EXTENSION               ".xml"
#define TXT_FILE_EXTENSION               ".txt"
#define NC_FILE_EXTENSION               ".nc"

// Contants
static const double SECINDAY = 86400;

//! Convert angle in radians to angle in degrees.
//! @param radians Number of radians.
//! @return Number of degrees that correspond to input radians.
inline double radiansToDegrees(double radians)
{
  return (radians * 180. / M_PI);
}

inline void normalise(double v[3])
{
	double mod= sqrt(v[0]*v[0]+v[1]*v[1] + v[2]*v[2]);
	v[0] = v[0]/mod;
	v[1] = v[1]/mod;
	v[2] = v[2]/mod;
}

inline double angleDeg(double v1[3],double v2[3])
{
	// Calculate the angle between two unitary vectors

    // Get the unitary vectors
    normalise(v1);
    normalise(v2);

    // angles is the acos of the scalar product
    double scalarProd = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
    double outAngle = acos(scalarProd);

    // Precision issues
    if (std::isnan(outAngle))
    {
        if (scalarProd > 1)
            outAngle = acos(1.);
        else // cos < -1
            outAngle = acos(-1.);
    }

    return(radiansToDegrees(outAngle));
}

//! return a string of a vector for the log
template<typename T>
string printVector(std::vector<T> v)
{
  string out = "[";
  for (std::size_t ii = 0; ii < v.size(); ++ii)
  {
    out += to_string(v[ii]) + " ";
  }
  out += "]";
  return out;
}

// Auxiliary files for logging:

template<typename T>
void multiply3by3Matrix(const T letf[3][3], const T right[3][3], T out[3][3])
{
  double sum = 0.0;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      sum = 0.0;
      for (int k = 0; k < 3; k++)
        sum += letf[i][k] * right[k][j];
      out[i][j] = sum;
    }
  }
}

//! Make sure that the longitude in [-180, 180]
//! @param lon Longitude in degrees.
template <typename T>
inline void checkBoundsLongitude(T &lon)
{
  if (lon>180.0){
    lon -=360.0;
  }
}

// Check that file exists
inline bool fileExists(const std::string filename)
{
  ifstream in(filename);
  if (!in.good())
  {
    return false;
  }
  return true;
}

#endif /* COMMON_SRC_COMMON_HPP_ */

