from conans import ConanFile, CMake, tools

class Terradecerpea(ConanFile):
    name = 'terradecerpea'
    version = '2.0.0'
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'cmake_find_package_multi'
    requires = [ 'spdlog/1.6.1'
               , 'fmt/6.2.1'
               , 'range-v3/0.10.0'
               ]

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
