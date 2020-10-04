#!/bin/bash

usage()
{
	echo "Usage: newproj <project_name>"
}

if [ $# -gt 0 ]; then
	cp -RP BlankProject-xcode $1
else
	usage
fi

