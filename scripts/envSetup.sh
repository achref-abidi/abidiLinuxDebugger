#!/bin/bash

apt-get update
apt-get cmake make 

cd ..
git submodule update --init --recursive