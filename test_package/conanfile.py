from conans import ConanFile, CMake
import os

class ThreadPoolTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "build_examples": [True, False]}
    default_options = "shared=True", "build_examples=True"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package_info(self):
        self.cpp_info.libs = ["ThreadPool"]

    def test(self):
        self.run("bin{}example1".format(os.sep))
        
