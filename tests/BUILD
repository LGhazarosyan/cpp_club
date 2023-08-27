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
        "@gtest//:gtest_main",
    ],
    copts = COPTS,
    linkopts = LOPTS,
)

cc_test(
    name = "test_tuple",
    srcs = [
        "test_tuple.cpp",
    ],
    deps = [
        "//:standart",
        "@gtest//:gtest_main",
    ],
    copts = COPTS,
    linkopts = LOPTS,
)

cc_test(
    name = "test_optional",
    srcs = [
        "test_optional.cpp",
    ],
    deps = [
        "//:standart",
        "@gtest//:gtest_main",
    ],
    copts = COPTS,
    linkopts = LOPTS,
)

cc_test(
    name = "test_reverse_iterator",
    srcs = [
        "test_reverse_iterator.cpp",
    ],
    deps = [
        "//:standart",
        "@gtest//:gtest_main",
    ],
    copts = COPTS,
    linkopts = LOPTS,
)

cc_test(
    name = "test_traits",
    srcs = [
        "test_traits.cpp",
    ],
    deps = [
        "//:standart",
        "@gtest//:gtest_main",
    ],
    copts = COPTS,
    linkopts = LOPTS,
)

cc_test(
    name = "test_unique",
    srcs = [
        "test_unique_ptr.cpp",
    ],
    deps = [
        "//:standart",
        "@gtest//:gtest_main",
    ],
    copts = COPTS,
    linkopts = LOPTS,
)

test_suite(
    name = "standart_tests",
    tests = [
    "test_array",
    "test_optional",
	"test_traits",
	"test_unique",
    ],
);
