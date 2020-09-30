install:
#  cd 3dparty/taglib && mkdir build
#  cd build && cmake ..
#  make

  export CMAKE_PREFIX_PATH="~/.brew/Cellar/qt/5.15.1/lib/cmake:$CMAKE_PREFIX_PATH"
  cmake . -Bbuild -Wdev -Werror=dev && cmake --build ./build

install