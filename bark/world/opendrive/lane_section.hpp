// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick
// Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef MODULES_WORLD_OPENDRIVE_LANE_SECTION_HPP_
#define MODULES_WORLD_OPENDRIVE_LANE_SECTION_HPP_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "bark/models/dynamic/dynamic_model.hpp"
#include "bark/world/opendrive/lane.hpp"

namespace modules {
namespace world {
namespace opendrive {

class XodrLaneSection {
 public:
  explicit XodrLaneSection(float s) : s_(s) {}
  ~XodrLaneSection() {}

  XodrLanes GetLanes() const { return lanes_; }

  XodrLanePtr GetLaneByPosition(XodrLanePosition pos);

  XodrLanePtr GetNearestLaneOnN(double x, double y, double vx, double vy);
  XodrLanePtr GetLaneWithOffset(const models::dynamic::State& state,
                               double angle_offset);

  XodrLanePtr GetLeftLane(const models::dynamic::State& state) {
    return GetLaneWithOffset(state, 3.14 / 2);
  }
  XodrLanePtr GetRightLane(const models::dynamic::State& state) {
    return GetLaneWithOffset(state, -3.14 / 2);
  }

  //! setter functions
  void AddLane(const XodrLanePtr& l);

  //! getter functions
  float GetS() const { return s_; }

 private:
  float s_;
  XodrLanes lanes_;
};

inline std::string print(const XodrLaneSection& ls) {
  std::stringstream ss;
  ss << "s: " << ls.GetS() << std::endl;
  for (auto const& l : ls.GetLanes())
    ss << "XodrLane: " << print(*(l.second)) << std::endl;
  return ss.str();
}

using XodrLaneSectionPtr = std::shared_ptr<XodrLaneSection>;

}  // namespace opendrive
}  // namespace world
}  // namespace modules

#endif  // MODULES_WORLD_OPENDRIVE_LANE_SECTION_HPP_
