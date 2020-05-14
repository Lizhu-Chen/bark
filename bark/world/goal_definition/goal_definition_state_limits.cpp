// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "bark/world/goal_definition/goal_definition_state_limits.hpp"
#include "bark/world/objects/agent.hpp"

namespace modules {
namespace world {
namespace goal_definition {


bool GoalDefinitionStateLimits::AtGoal(
  const modules::world::objects::Agent& agent) {
  const auto agent_state = agent.GetCurrentState();
  auto agent_angle = modules::geometry::Norm0To2PI(
    agent_state[modules::models::dynamic::StateDefinition::THETA_POSITION]);
  const modules::geometry::Point2d agent_pos = agent.GetCurrentPosition();
  return (modules::geometry::Within(agent_pos, xy_limits_) &&
          agent_angle >= angle_limits_.first &&
          agent_angle <= angle_limits_.second);
}


}  // namespace objects
}  // namespace world
}  // namespace modules