
def lin_module(name, deps=[]):
    native.cc_library(
        name = name,
        hdrs = [name + ".hpp"] + native.glob([name + "/**/*.hpp"]),
        deps = deps,
        include_prefix = "lin",
        visibility = ["//visibility:public"],
    )
