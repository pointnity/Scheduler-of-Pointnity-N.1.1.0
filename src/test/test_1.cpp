#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6)  
  #include<iostream>
  #include<map>
#endif

//////////////////#define G 2
using std::map;

int main(){
   map<int, int> test_map;
   test_map[1] = 2;
