#include "cell_list.hpp"
#include <cmath>
#include <execution>
#include <iostream>
#include <vector>

void CellList::rebuild(const std::vector<Particle> &particle_pool) {
  for (std::size_t i = 0; const auto &p : particle_pool) {
    add_particle_to_cell(p, i++);
  }
}

void CellList::add_particle_to_cell(const Particle &p,
                                    const std::size_t p_index) {
  const auto x = p.coords.x;
  const auto y = p.coords.y;

  // std::cout << "X: " << x << "Y: " << y;
  auto cell = &cells.at(get_index(x, y));
  cell->particleIndices.push_back(p_index);
}

float CellList::get_index(const float x, const float y) const {
  const std::size_t max_index = CELL_AMOUNT - 1;
  const auto col_amount = static_cast<std::size_t>(std::sqrt(CELL_AMOUNT));
  const auto column = static_cast<std::size_t>(std::floor(x / cell_width));
  const auto row = static_cast<std::size_t>(std::floor(y / cell_height));

  // Flattens column and row into one index
  // Current hack for particles that might go oob, i need to fix underlaying
  // issue of particles going oob.
  const auto index = row * col_amount + column;
  return std::min(index, max_index);
}
