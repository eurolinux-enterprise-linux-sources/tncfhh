#!/bin/bash
USER=user
VERSION=0.8.3
BUILD=`date +%Y%m%d-%H%M`
make package_source
if test $# = 1
then
	if test $1 = y
	then
		mv tncfhh-$VERSION.tar.gz /home/$USER/Dropbox/tnac-exchange/tncfhh-$VERSION-$BUILD.tar.gz
		echo "Created tncfhh-$VERSION-$BUILD.tar.gz"
	else
		mv tncfhh-$VERSION.tar.gz /home/$USER/Dropbox/tnac-exchange/
		echo "Created tncfhh-$VERSION.tar.gz"
	fi
else
	mv tncfhh-$VERSION.tar.gz /home/$USER/Dropbox/tnac-exchange/
	echo "Created tncfhh-$VERSION.tar.gz"
fi
