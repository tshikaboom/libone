#!/bin/sh

# Script to create the BUILDNUMBER used by compile-resource. This script
# needs the script createBuildNumber.pl to be in the same directory.

{ perl ./createBuildNumber.pl \
	src/lib/libone-build.stamp \
        %outputfiles_buildnumber%
#Success
exit 0
}
#unsucessful
exit 1
