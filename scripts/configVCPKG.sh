#!/bin/bash

# Set the installation path
install_path=~/vcpkg

# Clone the Git repository
git clone git clone https://github.com/microsoft/vcpkg $install_path

# Bootstapping vcpkg
$install_path/bootstrap-vcpkg.sh

# Add the installation directory to the user's PATH
echo "export PATH=\$PATH:$install_path" >> ~/.bashrc
echo "export VCPKG_ROOT=$install_path" >> ~/.bashrc

source ~/.bashrc

echo "Installation complete."