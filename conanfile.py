from conans import ConanFile, CMake
import os

class ThreadpoolConan(ConanFile):
    name = "ThreadPool"
    version = "0.1"
    license = "MIT"
    url = "https://github.com/jabaa/ThreadPool"
    description = "A C++11 library implementing a thread pool."
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "build_examples": [True, False]}
    default_options = "shared=True", "build_examples=True"
    generators = "cmake"
    exports_sources = "include{}*".format(os.sep), "src{}*".format(os.sep), "examples{}*".format(os.sep), "CMakeLists.txt"

    def build(self):
        cmake = CMake(self)
        build_shared_libs = "-DBUILD_SHARED_LIBS:BOOL=" + ("ON" if self.options.shared else "OFF")
        build_examples = "-DBUILD_EXAMPLES:BOOL=" + ("ON" if self.options.build_examples else "OFF")
        cmake.configure(source_folder=".", args=[build_shared_libs, build_examples])
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["ThreadPool"]
 
