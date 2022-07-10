load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

GTEST_VERSION = "1.12.1"
http_archive(
    name = "com_google_googletest",
    url = "https://github.com/google/googletest/archive/release-{}.zip".format(GTEST_VERSION),
    sha256 = "24564e3b712d3eb30ac9a85d92f7d720f60cc0173730ac166f27dda7fed76cb2",
    strip_prefix = "googletest-release-{}".format(GTEST_VERSION),
)
