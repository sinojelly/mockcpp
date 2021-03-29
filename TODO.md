# This is the todo list to improve mockcpp and testngpp

## Build System Optimize
### Refactor build scripts
#### Features
- One script to support many compilers on a platform.
- Move the build directory to source root, so we can use build_vc, build_mingw to store binaries generated by different compilers.
- Use subdirectories in build directory to store the build files for different project.
#### TODO
- Move build directory to source root.
  - [x] VS2019
  - [ ] MinGW
  - [ ] Linux

### Optimize the prebuilt mockcpp/testngpp tools
#### Features
- Reuse the prebuilt binary, so don't neet to waste time to build them each time built the tested project.
- Create a prebuilt binary repository and add a sample project to make it easy to use.
- Manage prebuilt binaries in different directories classified by platform and compiler.
#### TODO
- [ ] Create binary repository.
- [ ] Add a sample project.
- [ ] Manage prebuilt binaries in different directories.
  - [ ] win32-vs2019
  - [ ] win64-vs2019
  - [ ] win32-mingw
  - [ ] win64-mingw
  - [ ] linux-gcc4
  - [ ] linux-gcc5
  - [ ] termux-clang

### Little improvements
- [x] Update python scripts to support python3.
- [x] Update to support latest GCC,MINGW,VS2019 compilers.
- [x] Remove dependency on boost.(mainly use c++11 to support is_enum, typeof)
#### mockcpp
- [x] support catch2.
- [ ] Optimize the user interface of normal class method mock.
#### testngpp
- [x] Runner link to testngpp staticly, make the prebuilt binaries reusable.

### Mockcpp Bugfix
- [ ] Global function mock doesn't work on vs2019.

### Testngpp Bugfix
- [ ] Memory leak check doesn't work on MinGW.