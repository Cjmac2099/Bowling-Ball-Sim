#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include "coverstock_type.hpp"
using namespace std;

enum density { soft, medium, hard };

class performance : public coverstock_type {
 private:
  density hardness;

 protected:
  /* 1 virtual function declaration */
  virtual float compute_oil_absorption_rate();

 public:
  performance(string, float, int, density);   

  string hardness_to_string() const; 

  virtual ~performance(){};
};

performance::performance(string name, float mass, int grit, density hardness)
    : coverstock_type(name, mass, grit) {
  
  //PARAMETERIZED CONSTRUCTOR
  this->hardness = hardness;
}

string performance::hardness_to_string() const {
  
  switch(hardness){
    case soft: // case of soft
      cout << "soft" << endl;
      break;
    case medium: // case of medium
      cout << "medium" << endl;
      break;
    case hard: // case of hard 
      cout << "hard" << endl;
      break;
    default: // default case
      break;
  }
  return "";
}

float performance::compute_oil_absorption_rate() {
  
  switch(hardness){
    case soft: // case for soft
      return 1.5;
      break;
    case medium: // case for medium
      return 1;
      break;
    case hard: // case for hard 
      return 0.8;
      break;
    default: // default case
      break;
  }
  return 0;
}

#endif // PERFORMANCE_HPP