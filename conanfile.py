import os

from conan import ConanFile

class CWsppRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        if self.settings.os == "Windows":
            self.requires("zlib/[>1.3.0 <1.4]")
            self.requires("openssl/[>3.5.0 <3.6]")

    def layout(self):
        # We make the assumption that if the compiler is msvc the
        # CMake generator is multi-config
        multi = True if self.settings.get_safe("compiler") == "msvc" else False
        if multi:
            self.folders.generators = "generators"
        else:
            self.folders.generators = os.path.join(str(self.settings.build_type), "generators")
