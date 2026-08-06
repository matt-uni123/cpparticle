#ifndef CELL_LIST_HPP
#define CELL_LIST_HPP
#include "CommonTypes.hpp"
#include <array>
#include <vector>

inline constexpr int CELL_AMOUNT = 16;

struct Cell {
  std::vector<std::size_t> particleIndices;
};

struct CellList {
  CellList(const float width, const float height)
      : cell_width(width), cell_height(height) {}

  void rebuild(const std::vector<Particle> &particle_pool);
  void reset_cells();

  void add_particle_to_cell(const Particle &p, const std::size_t index);
  float get_index(const float x, const float y) const;

  float cell_width;
  float cell_height;
  std::array<Cell, CELL_AMOUNT> cells;
  std::array<Cell, CELL_AMOUNT> &get_cell_arry() const;
  Cell &get_cell();
};
#endif // !CELL_LIST_HPP
