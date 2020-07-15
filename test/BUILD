cc_test(
    name = "all",
    srcs = glob(["**/*.cpp"]),
    copts = ["-Iexternal/gtest/include -Iinclude/"],
    deps = [
        "@gtest//:gtest_main",
        "//:lin"
    ],
)
