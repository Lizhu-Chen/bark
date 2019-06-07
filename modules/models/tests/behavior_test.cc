// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.


#include <Eigen/Core>
#include "gtest/gtest.h"

#include "modules/geometry/polygon.hpp"
#include "modules/geometry/line.hpp"
#include "modules/geometry/commons.hpp"
#include "modules/models/dynamic/single_track.hpp"
#include "modules/models/behavior/motion_primitives/motion_primitives.hpp"
#include "modules/commons/params/default_params.hpp"

using namespace modules::models::dynamic;
using namespace modules::models::execution;
using namespace modules::commons;
using namespace modules::models::behavior;
using namespace modules::models::dynamic;


TEST(behavior_motion_primitives, behavior_test) {

  DefaultParams params;
  DynamicModelPtr dynamics(new SingleTrackModel());
  BehaviorMotionPrimitives behavior(dynamics, &params);
  Input u(2);
  u << 0, 0;
  behavior.AddMotionPrimitive(u, 0.5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}