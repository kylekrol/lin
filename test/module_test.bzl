
def lin_module_test(name, deps=[]):
    native.cc_test(
        name = name,
        srcs = native.glob([name + "/**/*.cpp"]),
        deps = ["@com_google_googletest//:gtest_main", "//lin:" + name] + deps,
        visibility = ["//visibility:private"],
    )
