#!/bin/bash

# Get the installation path from the user
read -p "Enter the installation path: " install_path

# Clone the Git repository
git clone git clone https://github.com/microsoft/vcpkg $install_path/vcpkg

# Change to the installation directory
cd $install_path

# Bootstapping vcpkg
./bootstrap-vcpkg.sh

# Add the installation directory to the user's PATH
echo "export PATH=\$PATH:$install_path" >> ~/.bashrc
echo "export VCPKG_ROOT=$install_path" >> ~/.bashrc

source ~/.bashrc

echo "Installation complete."