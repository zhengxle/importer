#!/bin/bash

# set workspace
BASE_PATH=$(cd "$(dirname "$0")"; pwd)
cd $BASE_PATH

cd $BASE_PATH/..
make release=yes

cd $BASE_PATH
/usr/local/bin/rpm_create -p /home/a -v $3 -r $4 $2.spec -k
