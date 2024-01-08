#ifndef ASYMMETRIC_HPP
#define ASYMMETRIC_HPP

#include <iostream>

#include "core_type.hpp"

using namespace std;

enum asymmetric_geometry { triangle, rectangle, polygon };

class asymmetric_core : public core_type {
 private:
  asymmetric_geometry shape;
  float intermediate_differential;

 public:
  asymmetric_core(string, float, float, float, asymmetric_geometry);

  void compute_intermediate_differential();

  ~asymmetric_core();

  void compute_differential(const float*);
  string geometry_to_string() const;
  void print() const;
};

// PARAMETERIZED CONSTRUCTOR
asymmetric_core::asymmetric_core(string name, float pan_mass, float core_mass, float rg, asymmetric_geometry shape) 
  : core_type(name, pan_mass, core_mass, rg){
  differential = 0;
  intermediate_differential = 0;
  this->shape = shape;
  compute_intermediate_differential();
}

// CALCULATE INTERMEDIATE DIFFERENTIAL
void asymmetric_core::compute_intermediate_differential(){
  switch(shape){
    case triangle:
      intermediate_differential = intermediate_differential + 0.05;
      break;
    case rectangle:
      intermediate_differential = intermediate_differential + 0.1;
      break;
    case polygon:
      intermediate_differential = intermediate_differential + 0.2;
      break;
    default:
      intermediate_differential = intermediate_differential;
      break;
  };
}

// DESTRUCTOR
asymmetric_core::~asymmetric_core(){ };
/**
 * @brief
 *  Provides a description of a symmetric bowling ball
 */
void asymmetric_core::print() const {
  cout << "Asymmetric bowling ball statistics" << endl
       << "\tName: " << get_name() << endl
       << "\tPancake weight: " << get_pancake_mass() << endl
       << "\tCore shape:  " << geometry_to_string() << endl
       << "\tCore weight: " << get_mass() << " lbs" << endl
       << "\tRadius of Gyration: " << rg << endl
       << "\tDifferential: " << differential << endl
       << "\tIntermediate Differential: " << intermediate_differential << endl;
}

// OUTPUT THE GEOMETRY SHAPE INTO A STRINGS
string asymmetric_core::geometry_to_string() const {
  switch(shape){
    case triangle: // case of triangle
      return "triangle";
      break;
    case rectangle: // case of rectangle
      return "rectangle";
      break;
    case polygon: // case of polygon
      return "polygon";
      break;
    default: // any other case
      break;
  };
  return "";
}


void asymmetric_core::compute_differential(const float* drill_layout) {
  const float PTVR = 0.3f,  // Pin to VAL ratio
      OFFSET_MAX = 6,       // Maximum length from PaP
      DIFF_MAX = 0.6f;      // Maximum differential of a symmetric ball

  float PTP = DIFF_MAX - (DIFF_MAX * PTVR);        // Pin to PaP value
  float PTV = DIFF_MAX - (DIFF_MAX * (1 - PTVR));  // Pin to VAL value

  PTP = (drill_layout[0] * PTP) / OFFSET_MAX; // PTP CALCULATIONS

  if (*(drill_layout + 2) != 0) {
    PTV = PTV * (1 - (*(drill_layout + 2) / OFFSET_MAX));
  }

  differential = (PTP + PTV) + intermediate_differential;;
}

#endif  // ASYMMETRIC_HPP