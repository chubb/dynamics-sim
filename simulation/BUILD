load("//bazel:cc.bzl", "project_cc_binary", "project_cc_library")

project_cc_binary(
    name = "sim",
    srcs = ["sim.cc", "sim.h"],
    deps = ["full-system"],
)

project_cc_library(
    name = "full-system",
    srcs = ["full-system.cc"],
    hdrs = ["full-system.h"],
    deps = ["propeller", "motor", "six-dof", "parameters"],
)

project_cc_library(
    name = "propeller",
    srcs = ["propeller.cc"],
    hdrs = ["propeller.h"],
    deps = ["sim-lib", "parameters"],
)

project_cc_library(
    name = "motor",
    srcs = ["motor.cc"],
    hdrs = ["motor.h", "map-util.h"],
    deps = ["sim-lib", "parameters"],
)

project_cc_library(
    name = "six-dof",
    srcs = ["six-dof.cc"],
    hdrs = ["six-dof.h", "map-util.h"],
    deps = ["sim-lib", "parameters"],
)

project_cc_library(
    name = "parameters",
    srcs = ["parameters.cc"],
    hdrs = ["parameters.h"],
    deps = ["lin-alg"],
)

project_cc_library(
    name = "sim-lib",
    srcs = ["sim-lib.cc"],
    hdrs = ["sim-lib.h"],
    deps = ["lin-alg"],
)

project_cc_library(
    name = "lin-alg",
    srcs = ["lin-alg.cc"],
    hdrs = ["lin-alg.h"],
    deps = ["@eigen//:eigen"],
)

project_cc_binary(
    name = "odeint-play",
    srcs = ["odeint-play.cc"],
    deps = ["@boost//:boost"],
)

project_cc_binary(
    name = "struct-play",
    srcs = ["struct-play.cc"],
    deps = ["lin-alg"]
)

project_cc_binary(
    name = "lambda-play",
    srcs = ["lambda-play.cc"],
)