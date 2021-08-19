thds=$(cat /proc/cpuinfo | grep "processor" | wc -l)
echo "Will compile with ${thds} thread(s)"
echo "Internet Connection & Super User Permission is Required!"
echo "This Installer is Design for Ubuntu & Tested on Ubuntu 20.04 LTS"
echo "Now Insatlling Pre-Requisite..."
sudo apt update
sudo apt install g++ cmake nodejs
echo "Pre-Requisite Installation Complete"
echo ""
echo ""
echo "Now Installing Easy Contact..."
git submodule update --init --recursive
cmake .
cmake --build . -j $thds
cd Web
npm install
cd ..
cd DataBase && ./ecdb &
cd Web && node server.js
