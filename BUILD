load("@rules_cc//cc:defs.bzl", "cc_library")
load("//:variables.bzl", "COPTS")
load("//:variables.bzl", "LOPTS")

cc_library(
    name = "standart",
    srcs = [
        "array.hpp",
        "reverse_iterator.hpp",
        "type_traits.hpp",
        "value_traits.hpp",
        "iterator_traits.hpp",
        "optional.hpp",
        "tuple.hpp"
    ],
    visibility = ["//visibility:public"],
    copts = COPTS,
    linkopts = LOPTS,
)