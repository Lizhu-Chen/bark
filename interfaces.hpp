

// ----- INTERFACES AND GROUPS -------------


// Wejdene and some other person -> tested output as in python
class ModelLoader {
  ModelLoader();
  LoadModel(std::string checkpoint, std::string model);
  std::vector<double> EvaluateModel(std::vector<double> neural_network_input) const;
}


// Sebastian and some other person -> some tests
class NNHeuristic : mcts::Heuristic<NNHeuristic> {

  NNHeuristic(standard from mcts) {
    model_loader.LoadModel();

    // Ensure parameters are same as in training use defaults
    observer_ ...
  };

  calculate_heuristic_values(standard from mcts) {
    observed_world = node->get_state()->GetObservedWorld(); //<- dp as we did with get nearest distance
    EigenVector output = observer_.Observe(observed_world);
    std::vector<double> model_output = model.EvaluateModel(output)

    // Calculate 
    //model_output: Q(s, a) -> V(s) = 1/N_a * sum_a Q(s,a)
    return V(s);
  }

  private:
    ModelLoader model_loader_;
    NNNearestObserver observer_;
}



// ------------ WHERE IS THE IMPLEMENTATION ------------------
- ModelLoader is in branch on bark-ml
- NNHeuristic is in branch on planner uct
-> add barkml to dep in branch (@bark_ml//:model_loader, @bark_ml//:observer)
-> Introduce new parameter for BehaviorUCT to set this as heuristic

- Where to do evaluation and training?
-> training in barkml, scenarios must be the same as in final benchmark
