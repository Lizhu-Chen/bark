cc_test(
    name = "dynamic_tests",
    srcs = [
        "dynamic_test.cc",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "//modules/geometry",
        "//modules/models/dynamic:dynamic",
        "//modules/commons/transformation:frenet",
        "@gtest//:gtest_main",
        "@boost//:geometry",
    ],
)

cc_test(
    name = "execution_test",
    srcs = [
        "execution_test.cc",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "//modules/geometry",
        "//modules/models/dynamic:dynamic",
        "//modules/commons/transformation:frenet",
        #"//modules/models/execution/mpc:mpc",
        "//modules/models/execution/interpolation:interpolation",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "behavior_motion_primitive_test",
    srcs = [
        "behavior_motion_primitive_test.cc",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "//modules/geometry",
        "//modules/models/dynamic:dynamic",
        "//modules/models/behavior/motion_primitives:motion_primitives",
        "//modules/models/behavior/idm:idm_lane_tracking",
        "//modules/world:world",
        "//modules/world/tests:make_test_world",
        "@gtest//:gtest_main",
        "@com_github_eigen_eigen//:eigen",
    ],
)

cc_test(
    name = "behavior_idm_classic_test",
    srcs = [
        "behavior_idm_classic_test.cc",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "//modules/geometry",
        "//modules/models/behavior/idm:idm_classic",
        "//modules/models/behavior/constant_velocity:constant_velocity",
        "//modules/models/execution/interpolation:interpolation",
        "@gtest//:gtest_main",
        "@com_github_eigen_eigen//:eigen",
        "//modules/world/tests:make_test_world",
    ],
)

# cc_test(
#     name = "behavior_mobil_test",
#     srcs = [
#         "behavior_mobil_test.cc",
#     ],
#     copts = ["-Iexternal/gtest/include"],
#     deps = [        
#         "//modules/geometry",
#         "//modules/models/behavior/rule_based:mobil",
#         "//modules/models/execution/interpolation:interpolation",
#         "//modules/world/tests:make_test_xodr_map",
#         "@gtest//:gtest_main",
#     ],
# )

py_test(
  name = "py_behavior_model_test",
  srcs = ["py_behavior_model_test.py"],
  data = ['//python:bark.so',
          '//modules/runtime/tests:xodr_data'],
  imports = ['../../../python/'],
  deps = ["//modules/runtime/commons:parameters",
          "//modules/runtime/commons:xodr_parser",
          "//modules/runtime:runtime",
          "//modules/runtime/scenario/scenario_generation:scenario_generation"],
)

cc_test(
    name = "behavior_static_trajectory_test",
    srcs = [
        "behavior_static_trajectory_test.cc",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "//modules/geometry",
        "//modules/models/behavior/static_trajectory",
        "@com_github_eigen_eigen//:eigen",
        "@gtest//:gtest_main",
    ],
)
