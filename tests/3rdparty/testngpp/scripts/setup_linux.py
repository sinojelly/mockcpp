from cx_Freeze import setup, Executable

setup(
        name = "testngppgen",
        version = "1.1",
        description = "testngpp generator script",
        executables = [Executable("testngppgen.py")])
