// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "bark/world/prediction/prediction_settings.hpp"
#include "bark/world/observed_world.hpp"


namespace modules {
namespace world {
namespace prediction {

using modules::models::behavior::BehaviorModelPtr;

PredictionSettings::PredictionSettings(const BehaviorModelPtr& ego_prediction, const BehaviorModelPtr& others_prediction) : 
  ego_prediction_model_(ego_prediction),
  others_prediction_model_(others_prediction) {}

void PredictionSettings::ApplySettings(modules::world::ObservedWorld& observed_world) const {
  observed_world.SetEgoBehaviorModel(BehaviorModelPtr(ego_prediction_model_->Clone()));
  for (const auto &agent : observed_world.GetOtherAgents()) {
      observed_world.SetBehaviorModel(agent.first, BehaviorModelPtr(others_prediction_model_->Clone()));
  }
}


}  // namespace prediction
}  // namespace world
}  // namespace modules







