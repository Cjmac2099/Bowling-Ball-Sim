#ifndef URETHANE_HPP
#define URETHANE_HPP

#include "performance.hpp"
using namespace std;


class urethane : public performance {
 private:
  const float URETHANE_BASE_RATE = 0.8f;

 public:
  float oil = performance::compute_oil_absorption_rate();
  urethane(string, float, int, density);

  float compute_oil_absorption_rate() const;
  void print() const;
  ~urethane(){};
};

urethane::urethane(string name, float mass, int grit, density hardness)
    : performance(name, mass, grit, hardness) {
  // ???
}

float urethane::compute_oil_absorption_rate() const{
  // COMPUTE OIL ABSORPTION RATE
  return (URETHANE_BASE_RATE * oil / get_grit());
}

void urethane::print() const {
  cout << "Urethane Coverstock statistics" << endl
       << "\tName: "                << this->get_name() << endl 
       << "\tCoverstock Type:     " << this->hardness_to_string() << endl
       << "\tCoverstock Grit:     " << this->get_grit() << " grit" << endl
       << "\tOil absorption Rate: " << this->get_oil_absorption_rate() << endl;
}

#endif // URETHANE_HPP
