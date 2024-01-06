/*Name: Christopher Johnson, 5007642687, 1001, Assignment 5
Description: the plastic coverstock
Input: user input and virtual functions from coverstock_type
Output: info and title of all inputted values*/

#ifndef PLASTIC_HPP
#define PLASTIC_HPP

#include "coverstock_type.hpp"
using namespace std;

class plastic : public coverstock_type {
 private:
  const float PLASTIC_BASE_RATE = 0.1f;

 public:
  plastic(string, float, int);

  float compute_oil_absorption_rate();
  void print() const; // redeclaration
  virtual ~plastic(){};
};

plastic::plastic(string name, float mass, int grit)
    : coverstock_type(name, mass, grit) {
  /* YOUR CODE HERE */
  set_oil_absorption_rate(compute_oil_absorption_rate());
  
}

float plastic::compute_oil_absorption_rate() {
  return PLASTIC_BASE_RATE * GRIT_BASE / get_grit();
}

void plastic::print() const {
  cout << "Plastic Coverstock statistics" << endl
       << "\tName: "                << this->get_name() << endl 
       << "\tCoverstock Grit:     " << this->get_grit() << " grit" << endl
       << "\tOil absorption Rate: " << this->get_oil_absorption_rate() << endl;
}

#endif // PLASTIC_HPP
