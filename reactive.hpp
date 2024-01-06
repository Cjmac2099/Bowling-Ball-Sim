/*Name: Christopher Johnson, 5007642687, 1001, Assignment 5
Description: a resin style coverstock
Input: user input and performance base class
Output: info and title of all inputted values*/

#include "performance.hpp"
using namespace std;

enum material { solid, pearl, hybrid };

class reactive : public performance {
 private:
  const float REACTIVE_BASE_RATE = 0.7f;
  material compound;

 public:
  reactive(string, float, int, density, material); 
  string material_to_string() const; 

  float compute_oil_absorption_rate(); 
  void print() const; 

  ~reactive(){ }; 
};

reactive::reactive(string name, float mass, int grit, density hardness,
                   material compound)
    : performance(name, mass, grit, hardness) {
  /* YOUR CODE HERE */
  this->compound = compound;
  set_oil_absorption_rate(compute_oil_absorption_rate());
}

string reactive::material_to_string() const {
  /* YOUR CODE HERE */
  switch (compound) {
    case solid: // case for solid
      return "solid";
      break;
    case pearl: // case for pearl
      return "pearl";
      break;
    case hybrid: // case for hybrid
      return "hybrid";
      break;
    default: // default case
      break;
  }
  return "";
}

float reactive::compute_oil_absorption_rate() {
  /* YOUR CODE HERE */
  float compoundRate = 0;
  switch(compound){
    case solid: // case for solid
      compoundRate =  0.65;
      break;
    case pearl: // case for pearl
      compoundRate =  0.9;
      break;
    case hybrid: // case for hybrid
      compoundRate =  0.7;
      break;
    default:
      break;
  }
  float scaledRate = compoundRate * REACTIVE_BASE_RATE;
  float finalRate = scaledRate * (performance::compute_oil_absorption_rate());
  return finalRate;
}

void reactive::print() const {
  cout << "Performance Coverstock statistics" << endl
       << "\tName: "                << this->get_name() << endl 
       << "\tCoverstock Type:     " << this->hardness_to_string() 
       << " "                       << this->material_to_string() << endl
       << "\tCoverstock Grit:     " << this->get_grit() << " grit" << endl
       << "\tOil absorption Rate: " << this->get_oil_absorption_rate() << endl;
}