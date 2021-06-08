load("@rules_cc//cc:defs.bzl", "cc_test")
load("//:variables.bzl", "COPTS")
load("//:variables.bzl", "LOPTS")

cc_test(
    name = "test_array",
    srcs = [
        "test_array.cpp",
    ],
    deps = [
        "//:standart",
    ],
    copts = COPTS,
    linkopts = LOPTS,
)