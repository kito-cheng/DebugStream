#include "DebugStream.hpp"
#include   <iomanip> 
int main(){
  DebugStream ds(10);
  ds[3] << "abc\n";
  ds[11] << "XD\n";
  ds[8] << 123 << std::endl;
  ds.precision(2);
  ds[5] << 0.54321 << std::endl;
  ds[5] << std::setprecision(4) << 0.12354 << std::endl;
  ds[3].printf("%08d\n", 123);
  return 0;
}

