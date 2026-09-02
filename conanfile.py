from conan import ConanFile
from conan.tools import cmake


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("glfw/3.4")

    def generate(self):
        cm = cmake.CMakeDeps(self)
        cm.generate()
