#ifndef SYMMETRIC_HPP
#define SYMMETRIC_HPP

#include <iostream>

#include "core_type.hpp"

using namespace std;

enum symmetric_geometry { sphere, lightbulb, oval, other };

class symmetric_core : public core_type {
 private:
  bool axis;
  symmetric_geometry shape;

 public:
  symmetric_core(std::string, float, float, float, bool, symmetric_geometry);

  string axis_to_string() const;

  ~symmetric_core();

  /*3 function redeclarations */
  void compute_differential(const float*);
  string geometry_to_string() const;
  void print() const;
};

string symmetric_core::axis_to_string() const {
  if (axis) return "Ball is axisymmetric ";
  return "Ball is non-axisymmetric";
}

/* 2 more function definitions (6 total) */
// PARAMETERIZED CONSTRUCTOR
symmetric_core::symmetric_core(string name, float pan_mass, float core_mass, 
                              float rg, bool axis, symmetric_geometry shape)
  : core_type(name, pan_mass, core_mass, rg){
  differential = 0;
  this->axis = axis;
  this->shape = shape;
}

// DESTRUCTOR
symmetric_core::~symmetric_core(){ }

void symmetric_core::compute_differential(const float* drill_layout) {
  const float PTVR = 0.3f,  // Pin to VAL ratio
      OFFSET_MAX = 6,       // Maximum length from PaP
      DIFF_MAX = 0.6f;      // Maximum differential of a symmetric ball

  float PTP = DIFF_MAX - (DIFF_MAX * PTVR);        // Pin to PaP value
  float PTV = DIFF_MAX - (DIFF_MAX * (1 - PTVR));  // Pin to VAL value

  PTP = (drill_layout[0] * PTP) / OFFSET_MAX; // PTP CALCULATIONS

  if (*(drill_layout + 2) != 0) {
    PTV = PTV * (1 - (*(drill_layout + 2) / OFFSET_MAX));
  }

  differential = PTP + PTV;
}

/**
 * @brief
 *  Provides a description of a symmetric bowling ball
 */
void symmetric_core::print() const {
  cout << "Symmetric bowling ball statistics" << endl
       << "\tName: " << get_name() << endl
       << "\tPancake weight: " << get_pancake_mass() << endl
       << "\tCore shape:  " << geometry_to_string() << endl
       << "\tCore weight: " << get_mass() << " lbs" << endl
       << "\tSymmetry: " << axis_to_string() << endl
       << "\tRadius of Gyration: " << rg << endl
       << "\tDifferential: " << differential << endl;
}

// OUTPUT THE GEOMETRY SHAPE INTO A STRING
string symmetric_core::geometry_to_string() const {
  switch(shape){
    case sphere: // case of sphere
      return "sphere";
      break;
    case lightbulb: // case of lightbulb
      return "lightbulb";
      break;
    case oval: // case of oval
      return "oval";
      break;
    default: // any other case
      return "other";
      break;
  };
}

#endif  // SYMMETRIC_HPP