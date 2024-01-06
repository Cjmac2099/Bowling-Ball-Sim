/*Name: Christopher Johnson, 5007642687, 1001, Assignment 5
Description:the volume of oil per segment on a lane
Input: user input
Output: info and title of all inputted values */

#ifndef OIL_PATTERN_H
#define OIL_PATTERN_H

#include <iomanip>
#include <iostream>
#include <iomanip>

using std::setw, std::setprecision, std::fixed;
using namespace std;

enum layout_ids { cheetah, scorpion, shark };

/* Possible oil layouts */
const int BOARD_SEGMENTS = 12;
const float CHEETAH_PATTERN[BOARD_SEGMENTS] = 
  {1, .95f, .9f, .85f, .8f, .7f, 0.5f, 0, 0, 0, 0 , 0};
const float SCORPION_PATTERN[BOARD_SEGMENTS] = 
  {1, 1, .9f, .8f, .8f, .7f, 0.6f, .5f, .3f, 0, 0, 0};
const float SHARK_PATTERN[BOARD_SEGMENTS] = 
  {1, 1, .8f, .7f, .68f, .65f, 0.6f, .52f, .5f, .4f, 0, 0};

class oil_pattern {
 private:
  string name;
  layout_ids layout; 
  float* oil_volume_segments;

 public:
  oil_pattern(layout_ids);

  float* get_oil_volume_segments() { return oil_volume_segments; }

  void copy_oil_volume_segments();
  string layout_to_string();

  void print();

  ~oil_pattern();
};

oil_pattern::oil_pattern(layout_ids layout) {
  this->layout = layout;
  name = layout_to_string();

  oil_volume_segments = new float[BOARD_SEGMENTS];
  copy_oil_volume_segments();
}

string oil_pattern::layout_to_string() { 
  switch(layout){
    case cheetah : return "Cheetah"; break; // CHEETAH CASE
    case scorpion: return "Scorpion"; break; // SCORPION CASE
    case shark: return "Shark"; break; // SHARK CASE
    default: break; // DEFAULT CASE
  }
  // function return
  return "";
}

void oil_pattern::copy_oil_volume_segments() {
  switch(layout){
    case cheetah: // CASE FOR CHEETAH
      for(int i = 0; i < BOARD_SEGMENTS; i++){
        // copy cheetah pattern
        oil_volume_segments[i] = CHEETAH_PATTERN[i];
      }
      break;
    case scorpion: // CASE FOR SCORPION
      for(int i = 0; i < BOARD_SEGMENTS; i++){
        // copy scorpion pattern
        oil_volume_segments[i] = SCORPION_PATTERN[i];
      }
      break;
    case shark: // CASE FOR SHARK
       for(int i = 0; i < BOARD_SEGMENTS; i++){
        // copy shark pattern
        oil_volume_segments[i] = SHARK_PATTERN[i];
      }
      break;
    default: // DEFAULT CASE
      break;
  }
}

void oil_pattern::print() {
  cout << setprecision(4) << setw(8) << "Current pattern: ";
  for (int i = 0; i < BOARD_SEGMENTS; i++)
    if(i < 11) {
      // output pattern
        cout << setw(5) << *(oil_volume_segments + i) << ",";
    }
    else {
      // output pattern
        cout << setw(5) << *(oil_volume_segments + i);
    }
  cout << "\n";
}

// destructor
oil_pattern::~oil_pattern() { delete oil_volume_segments; oil_volume_segments = nullptr; }

#endif // OIL_PATTERN_H
