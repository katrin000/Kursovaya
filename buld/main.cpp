#include <iostream>
#include <fstream>
using namespace std;
double Function(double previous, double current, double next, double dx, double sigma, double dt ) {
  double temp=0.0;
 
  temp = next - 2 * current + previous;
  //return ((sigma * dt) / (dx *dx) * temp + current);
  return ((sigma * dt) / (dx * dx) * temp + current);

}
void Fille(double* mas, int size, std::fstream& out)
{
  if (out.is_open()) {

    for (int i = 0; i < size; i++) {
      out << mas[i] << ' ';
    }
    out << '\n';
    cout << 'a' << endl;
  }
}
int main() {
  double tMax = 0.0;
  double sigma = 0.0;
  double xMax = 0.0;
  double deltaX = 0.0;
  double deltaT = 0.0;
  double time = 0.0;
  double pi = 3.141592653589793;
  double t = 0.0;
  size_t i = 0;

  string path = "file.txt";
  ifstream fin;
  fin.open(path);
  std::fstream f;
  f.open("output.txt", std::fstream::in | std::fstream::out);
  if (!fin.is_open())
  {
    cout << "file not found";

  }
  else {
    fin >> xMax;
    fin >> deltaX;
    fin >> tMax;
    fin >> deltaT;
    fin >> sigma;
    //cout << tMax;
  }
  fin.close();
  
  
  int count = static_cast<int>((xMax / deltaX) + 1);

  double* temporary = new double[count]; 
  double* current= new double[count];

  
  for (size_t i = 0; i < count; i++) {
    double x = i * deltaX;
    temporary[i] = sin(x * pi / xMax);
    current[i] = 0.0;
  }
  temporary[count-1] = 0.0;
  current[count-1] = 0.0;
  Fille(temporary, count, f);
  while ( t < tMax) {
    t=i*deltaT;
    for (size_t i = 1; i < count - 1; i++)
      current[i] = Function(temporary[i - 1], temporary[i], temporary[i + 1], deltaX, sigma, deltaT);
    current[count - 1] = 0.0;
    current[0] = 0.0;
    for (size_t i = 0; i < count; i++)
      temporary[i] = current[i];
    i++;
  }
  Fille(current, count, f);
  
  f.close();
  
  
  delete[] temporary;
  delete[] current;
}
