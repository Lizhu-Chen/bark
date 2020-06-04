# Copyright (c) 2020 Julian Bernhard, Klemens Esterle, Patrick Hart and
# Tobias Kessler
#
# This work is licensed under the terms of the MIT license.
# For a copy, see <https://opensource.org/licenses/MIT>.

import unittest
import os
import ray

import matplotlib.pyplot as plt

from load.benchmark_database import BenchmarkDatabase
from serialization.database_serializer import DatabaseSerializer
from modules.benchmark.benchmark_runner import BenchmarkRunner, BenchmarkConfig, BenchmarkResult
from modules.benchmark.benchmark_runner_mp import BenchmarkRunnerMP
from modules.benchmark.benchmark_analyzer import BenchmarkAnalyzer

from modules.runtime.viewer.matplotlib_viewer import MPViewer

from bark.world.evaluation import *
from modules.runtime.commons.parameters import ParameterServer
from bark.models.behavior import BehaviorIDMClassic, BehaviorConstantVelocity
from modules.runtime.viewer.video_renderer import VideoRenderer

# to find database files
os.chdir("../benchmark_database/")

class DatabaseRunnerTests(unittest.TestCase):
    def test_database_run_and_analyze(self):
        dbs = DatabaseSerializer(test_scenarios=1, test_world_steps=2, num_serialize_scenarios=5)
        dbs.process("data/database1")
        local_release_filename = dbs.release(version="test")

        db = BenchmarkDatabase(database_root=local_release_filename)

        evaluators = {"success" : "EvaluatorGoalReached", "collision" : "EvaluatorCollisionEgoAgent",
                      "max_steps": "EvaluatorStepCount"}
        terminal_when = {"collision" :lambda x: x, "max_steps": lambda x : x>2, "success" : lambda x: x}
        #params = ParameterServer() # only for evaluated agents not passed to scenario!

        try:
            from bark.models.behavior.uct import BehaviorUCTSingleAgentMacroActions
        except:
            print("Rerun with --define planner_uct=true")
            return
        
        scenario_param_file ="macro_actions_test.json" # must be within examples params folder
        params1 = ParameterServer(filename= os.path.join("modules/benchmark/tests/params/",scenario_param_file))
        params2 = ParameterServer(filename= os.path.join("modules/benchmark/tests/params/",scenario_param_file))
        params2["BehaviorUctSingleAgent"]["UseRandomHeuristic"]=False
        behaviors_tested = {"RandomHeuristic": BehaviorUCTSingleAgentMacroActions(params1), "DomainHeuristic" : BehaviorUCTSingleAgentMacroActions(params2)}

        benchmark_runner = BenchmarkRunnerMP(benchmark_database=db,
                                           evaluators=evaluators,
                                           terminal_when=terminal_when,
                                           behaviors=behaviors_tested,
                                           log_eval_avg_every=1)#log_eval_avg_every=10

        result = benchmark_runner.run(maintain_history=True)

        result.dump(os.path.join("./benchmark_results.pickle"))
        result_loaded = BenchmarkResult.load(os.path.join("./benchmark_results.pickle"))

       

        analyzer = BenchmarkAnalyzer(benchmark_result=result_loaded)
        configs_random = analyzer.find_configs(criteria={"behavior": lambda x: x=="RandomHeuristic", "success": lambda x : not x})
        configs_domain = analyzer.find_configs(criteria={"behavior": lambda x: x=="DomainHeuristic", "success": lambda x : not x})

        fig1 = plt.figure(figsize=[10, 10])
        viewer1 = MPViewer(
              params=params1,
              center=[5112, 5165],
              y_length = 120,
              enforce_y_length=True,
              axis = fig2.gca())

        analyzer.visualize(configs_idx_list = configs_random,
                         viewer = viewer1, real_time_factor=10, fontsize=12)
        plt.close(fig1)

        fig2 = plt.figure(figsize=[10, 10])
        viewer2 = MPViewer(
              params=params2,
              center=[5112, 5165],
              y_length = 120,
              enforce_y_length=True,
              axis = fig2.gca())

        analyzer.visualize(configs_idx_list = configs_domain,
                         viewer = viewer2, real_time_factor=10, fontsize=12)
        plt.close(fig2)


        
        fig, (ax1, ax2) = plt.subplots(1, 2)
        viewer1 = MPViewer(
              params=params1,
              center=[5112, 5165],
              y_length = 120,
              enforce_y_length=True,
              axis = ax1)
        viewer2 = MPViewer(
              params=params2,
              center=[5112, 5165],
              y_length = 120,
              enforce_y_length=True,
              axis = ax2)
        #analyzer.visualize(configs_idx_list = [configs_random[1:3], configs_domain[1:3]],
                          #viewer = [viewer1, viewer2], viewer_names=["RandomHeuristic", "DomainHeuristic"], real_time_factor=10, fontsize=12)



if __name__ == '__main__':
    unittest.main()


