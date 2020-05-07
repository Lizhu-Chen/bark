// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick
// Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef MODULES_WORLD_EVALUATION_EVALUATOR_BEHAVIOR_EXPIRED_HPP_
#define MODULES_WORLD_EVALUATION_EVALUATOR_BEHAVIOR_EXPIRED_HPP_

#include <limits>
#include <memory>

#include "modules/models/behavior/behavior_model.hpp"
#include "modules/world/evaluation/base_evaluator.hpp"
#include "modules/world/objects/agent.hpp"
#include "modules/world/observed_world.hpp"

namespace modules {
namespace world {
class World;
class ObservedWorld;
namespace evaluation {

using modules::models::behavior::BehaviorStatus;

class EvaluatorBehaviorExpired : public BaseEvaluator {
 public:
  EvaluatorBehaviorExpired() : agent_id_(std::numeric_limits<AgentId>::max()) {}
  explicit EvaluatorBehaviorExpired(const AgentId& agent_id)
      : agent_id_(agent_id) {}
  virtual ~EvaluatorBehaviorExpired() {}

  virtual EvaluationReturn Evaluate(const world::World& world) {
    const auto agent_ptr = world.GetAgent(agent_id_);
    if (agent_ptr) {
      if (agent_ptr->GetBehaviorStatus() == BehaviorStatus::EXPIRED) {
        return true;
      } else {
        return false;
      }
    } else {
      return true;
    }
  }

  virtual EvaluationReturn Evaluate(
      const world::ObservedWorld& observed_world) {
    const auto agent_ptr = observed_world.GetEgoAgent();
    if (agent_ptr) {
      if (agent_ptr->GetBehaviorStatus() == BehaviorStatus::EXPIRED) {
        return true;
      } else {
        return false;
      }
    } else {
      return true;
    }
  }

 private:
  AgentId agent_id_;
};

}  // namespace evaluation
}  // namespace world
}  // namespace modules

#endif  // MODULES_WORLD_EVALUATION_EVALUATOR_BEHAVIOR_EXPIRED_HPP_