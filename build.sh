#  cd 3dparty/taglib && mkdir build
#  cd build && cmake ..
#  make

  cmake . -Bbuild -Wdev -Werror=dev && cmake --build ./build
