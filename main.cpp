#include <iostream>
#include <fstream>
#include<string>
using namespace std;
void Fille(double* arr, size_t size, string name, double c)
{
  fstream out;
  out.open(name, std::fstream::in | std::fstream::out);
  if (out.is_open()) {

    for (size_t i = 0; i < size; i++) {
      out << arr[i] << ' ';
      out << '\n';
      out << c;
    }
  }
  else
    throw "file not found";
  out.close();
}

size_t ReturnSize(string nameFile)
{
  ifstream file_in;
  size_t size = 0;
  double tmp = 0.0;

  file_in.open(nameFile);
  if (file_in.is_open())
  {
    while (!file_in.eof())
    {
      file_in >> tmp;
      size++;
    }
  }
  else
    throw "file not found";
  file_in.close();
  size--;
  return size;
}



int main()
{
  string Good_Result = "GoodFile.txt";
  string Current_Result = "CompareWithGoodFile.txt";
 
  size_t size_GR = 0;
  size_t size_CR = 0;

  
  double max = 0.0;
  double temp_buff = 0.0;
  size_t i = 0;
  size_t conversion_factor = 0;

  size_GR = ReturnSize(Good_Result);
  size_CR = ReturnSize(Current_Result);

  double* array_GR = new double[size_GR];
  double* array_CR = new double[size_CR];
  double* array_ABS = new double[size_CR];
  double* array_REL = new double[size_CR];


  ifstream file_in;
 
   file_in.open(Good_Result, ifstream::in | std::ifstream::out);
  
   

  if (file_in.is_open())
  {
    i = 0;
    while (!file_in.eof())
    {
      file_in >> temp_buff;
      array_GR[i] = temp_buff;
      i++;
    }
  }
  else
    throw "file not found";
  file_in.close();



  file_in.open(Current_Result, ifstream::in | std::ifstream::out);

  

if (file_in.is_open())
{
  i = 0;
  temp_buff = 0.0;
  while (!file_in.eof())
  {
    file_in >> temp_buff;
    array_CR[i] = temp_buff;
    i++;
  }
}
else
throw "file not found";
file_in.close();

 conversion_factor = (size_GR - 1) / (size_CR - 1);

for (size_t i = 0; i < size_CR; i++)
{
  array_ABS[i] = abs(array_GR[i * conversion_factor] - array_CR[i]);
 }

for (size_t j = 0; j < size_CR; j++)
{
  if (array_ABS[j] > max) 
    max = array_ABS[j];
}
Fille(array_ABS, size_CR, "ABS_file.txt", max);





for (size_t p = 0; p < size_CR; p++)
{
  double tmp = 0.0;
  if (array_GR[p * conversion_factor] > array_CR[p]) tmp = array_GR[p * conversion_factor];
  else
    tmp =  array_CR[p];
  array_REL[p] = (abs(array_GR[p * conversion_factor] - array_CR[p]) / tmp);
}

for (size_t i = 0; i < size_CR; i++)
{
  if (array_REL[i] > max) max = array_REL[i];
}
Fille(array_REL, size_CR, "REL_file.txt", max);
delete[] array_GR;
delete[] array_CR;
delete[] array_ABS;
delete[]array_REL;
return 0;
}


