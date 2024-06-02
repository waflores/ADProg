# ADProg WORKSPACE
workspace(name = "active_directory_user_creation_utility")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "rules_qt",
    branch = "main",
    remote = "https://github.com/Vertexwahn/rules_qt6.git",
)

load("@rules_qt//:fetch_qt.bzl", "fetch_qt6")

fetch_qt6()

load("@rules_qt//tools:qt_toolchain.bzl", "register_qt_toolchains")

register_qt_toolchains()
