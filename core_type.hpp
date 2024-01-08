#ifndef CORE_TYPE_HPP
#define CORE_TYPE_HPP

#include <string>
using namespace std;

class core_type {
 private:
  string name;
  float pancake_mass;
  float core_mass;

 protected:
  // Radius of gyration (2.4 - 2.8, lower value -> earlier hook)
  float rg;
  // Track flare potential (0 - 0.8, higher value -> agressive hook)
  float differential;

 public:
  core_type(string, float, float, float);

  string get_name()         const { return name; } // get name
  float get_pancake_mass()  const { return pancake_mass; } // get pancake mass
  float get_core_mass()     const { return core_mass; } // get core mass
  float get_mass()          const { return pancake_mass + core_mass; } // get combination of pancake and core mass
  float get_rg()            const { return rg; } // get radius of gyration
  float get_differential()  const { return differential; } // get differential

  /* 1 virtual & 3 pure virtual function declarations */
  virtual void compute_differential(const float*) = 0; // pure virtual
  virtual string geometry_to_string() const = 0; // pure virtual
  virtual void print() const = 0; // pure virtual
  virtual ~core_type() { } // virtual

};

core_type::core_type(string name, float pancake_mass, float core_mass, float rg) {
  this->name = name;
  this->pancake_mass = pancake_mass;
  this->core_mass = core_mass;
  this->rg = rg;
}


#endif