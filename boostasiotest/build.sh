set -e
if [ ! -d "build" ]; then
	mkdir build
fi

cd build

cmake ..
make
./runtests

cd ..
