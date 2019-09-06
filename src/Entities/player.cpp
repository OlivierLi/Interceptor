#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "player.h"

void Player::update(const World& world) {
  // Compute all the last know positions for the player
  last_known_positions.clear();
  for (sf::Event& event : *world.frame_events) {
    if (event.type == sf::Event::MouseMoved) {
      last_known_positions.push_back(std::pair<int, int>(
          event.mouseMove.x, SCREEN_RESOLUTION_Y - event.mouseMove.y));
    }
  }

  if (!last_known_positions.empty()) {
    // Move the player at the very last known position
    pos_x = last_known_positions.front().first;
    pos_y = last_known_positions.front().second;
  }
}

// This function returns shortest distance to one of the last know locations of
// the player
int Player::get_distance(int x, int y) const {
  int minimum_distance = INT_MAX;
  int distance = INT_MAX;

  for (const auto& position : last_known_positions) {
    distance =
        sqrt(pow((x - position.first), 2) + pow((y - position.second), 2));
    if (distance < minimum_distance) {
      minimum_distance = distance;
    }
  }

  return minimum_distance;
}

Player::~Player() {
  ;
}
