#!/bin/bash
OLD_DIR=`pwd`
cd /home/user/workspace/openpdp/
ant -f make-package.xml
mv trustfhh-xacml-pdp-*.tar.gz /home/user/Dropbox/tnac-exchange/
cd $OLD_DIR

