#ifndef LANE_TYPE_H
#define LANE_TYPE_H

#include "bowling_ball.hpp"
#include "oil_pattern.hpp"
#include <iomanip>
#include <iostream>

class lane_type {
 private:
  oil_pattern* pattern;

 public:
  lane_type(layout_ids);

  float compute_board_track(bowling_ball*, bool) const;
  void transition_oil(bowling_ball*, bool);

  void print() const;

  ~lane_type();
};

lane_type::lane_type(layout_ids layout) { pattern = new oil_pattern(layout); }

void lane_type::print() const { pattern->print(); }

lane_type::~lane_type() { delete pattern; pattern = nullptr;}

float lane_type::compute_board_track(bowling_ball* ball, bool debug) const {
  cout << fixed << setprecision(2);

  const float OIL_BOARDS_PER_SEGMENT = -2.f;
  const float HOOK_BOARDS_PER_SEGMENT = 2.5f;

  float hook_potential = ball->get_hook_potential(); // get balls hook potential
  float* oil_volume_segments = pattern->get_oil_volume_segments(); // shallow copy of current oil_volume_segments

  float current_board = 20.f;  

  float glide_transition, hook_transition;

  for (int i = 0; i < BOARD_SEGMENTS; i++) {
    if (debug) cout << "Current Board: " << current_board << endl;
      // get glide transition
      glide_transition = *oil_volume_segments * OIL_BOARDS_PER_SEGMENT;
      float oil_on_board = 1.0f - *oil_volume_segments;
      // get hook transition
      hook_transition = oil_on_board * HOOK_BOARDS_PER_SEGMENT * hook_potential;
      // get current board
      current_board += hook_transition + glide_transition;
      // update segments
      oil_volume_segments++;
  }
  if (debug) cout << "Final Board:   " << current_board << endl << endl;

  return current_board;
}

void lane_type::transition_oil(bowling_ball* ball, bool debug) {
  const float MAX_OIL_ABSORBED = 0.03f;
  const float MAX_OIL_DISSIPATED = 0.01f;

  float oil_volume = 0.f;
  float oil_absorbed = 0.f;

  // CALCULATE OIL ABSORPTION RATE
  float oil_absorption_rate = ball->get_coverstock_type()->get_oil_absorption_rate();
  // CALCULATE OIL VOLUME
  float* oil_volume_segments = pattern->get_oil_volume_segments();

  cout << fixed << setprecision(3);
  for (int i = 0; i < BOARD_SEGMENTS; i++) {
    if (oil_volume_segments[i] > 0.0f) {
      // Calculate the volume of oil to be absorbed
      oil_volume = oil_volume_segments[i] * MAX_OIL_ABSORBED * oil_absorption_rate;

      // Update lane segment and ball's absorbed oil
      oil_volume_segments[i] -= oil_volume;
      oil_absorbed += oil_volume;
    }

    // Check if the ball has oil to be dissipated
    if (oil_absorbed > 0.0f) {
      // Calculate the volume of oil to be dissipated
      oil_volume = oil_absorbed * MAX_OIL_DISSIPATED;

      // Update ball's absorbed oil and lane segment
      oil_absorbed -= oil_volume;
      oil_volume_segments[i] += oil_volume;
    }
  }
  if (debug) pattern->print();
}
#endif  // LANE_TYPE_H
