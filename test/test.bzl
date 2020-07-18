
def lin_test(name, tags=[]):
    native.cc_test(
        name = name,
        srcs = native.glob([name + "/*.cpp"]),
        deps = [
            "@gtest//:gtest_main",
            "//:lin"
        ],
        tags = tags,
        visibility = ["//visibility:private"],
    )
