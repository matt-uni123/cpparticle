#include "cell_list.hpp"
#include <cmath>
#include <iostream>
#include <vector>

void CellList::rebuild(const std::vector<Particle> &particle_pool) {
  for (std::size_t i = 0; i < particle_pool.size(); ++i) {
    add_particle_to_cell(particle_pool.at(i), i);
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
  // Find particle offset from nearest square, then subtract coordinate by
  // offset to find row/colum of correct cell

  const auto column = static_cast<int64_t>(std::floor(x / cell_width));
  const auto row = static_cast<int64_t>(std::floor(y / cell_height));
  std::cout << "X: " << x << " Y: " << y;
  std::cout << " Row: " << row << " Column: " << row << '\n';

  // Since we split into 16 cells, the column amount will be the square root of
  // that value.
  const auto col_amount = 4;

  // Flattens column and row into one index
  const auto index = row * col_amount + column;
  return index;
}
