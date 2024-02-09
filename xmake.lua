set_toolchains("gcc-13@/opt/homebrew/bin/g++-13")

target("jar")
    set_kind("binary")
    set_languages("c17", "c++20")
    add_files("src/*.cpp")
