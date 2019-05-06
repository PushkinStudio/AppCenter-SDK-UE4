#!/usr/bin/env bash
# Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.
set -e

printUsageExit()
{
    SCRIPT_NAME=`basename "$0"`
    SCRIPT_NAME="Tools/Build/$SCRIPT_NAME"
    echo -e "ERROR: $1\n"																			2>&1
    echo "Usage: $SCRIPT_NAME [ validateIncludeGuards|packEmbeddedFrameworks ]"						2>&1
    exit 1
}

validateIncludeGuards()
{
	THIRDPARTY_DIR="Plugins/AppCenter/ThirdParty"
	pushd $THIRDPARTY_DIR

	# @todo Use $2 instead
	SDK_ZIP="AppCenter-SDK-Apple-2.0.1.zip"
	SDK_DIR="AppCenter-SDK-Apple"

	rm -rd $SDK_DIR

	# extract SDK source
	unzip -o $SDK_ZIP

	SDK_IOS_DIR="AppCenter-SDK-Apple/iOS"
	pushd $SDK_IOS_DIR

	# process all headers first
	find . -name '*.h' | while read h_file; do
		echo "Processing file '$h_file'"

		h_name=$(basename $h_file)
		h_name=${h_name/./_}
		h_name=${h_name/+/_}	# MSConstants+Flags.h
		h_name=${h_name^^}
		GUARD_LINE_FIRST="#ifndef "$h_name
		GUARD_LINE_SECOND="#define "$h_name
		GUARD_LINE_LAST="#endif // "$h_name

		read -r firstline < $h_file

		if [[ $firstline != $GUARD_LINE_FIRST ]]; then 
			sed -i "1s/^/$GUARD_LINE_SECOND\n/" $h_file
			sed -i "1s/^/$GUARD_LINE_FIRST\n/" $h_file
			sed -i -e "\$a$GUARD_LINE_LAST" $h_file
		fi
	done

	# pack each library then
	find . -path '*.framework' -type d | while read framework_dir; do
		echo "Processing " $framework_dir
		framework_name=$(basename $framework_dir .framework)

		echo "Auto-packing is not implemented yet! ::" $framework_name

		# @TODO Pack embedded archives
		# 1. prepare embedded dir
		# 2. copy framework files
		# 3. check for bundle and copy it too 
		# 4. pack into zip with right name 

	done

	popd # SDK_IOS_DIR
	popd # THIRDPARTY_DIR
}

packEmbeddedFrameworks()
{
	echo "Auto-packing is not implemented yet!"
}

if [[ $# -eq 0 ]]; then
    printUsageExit "Parameters not found"
else
	if [ "$1" == "validateIncludeGuards" ]; then validateIncludeGuards
	elif [ "$1" == "packEmbeddedFrameworks" ]; then packEmbeddedFrameworks
    else printUsageExit "Unknown 1st parameter: $1"
    fi
fi

echo "--- END $0 $1 ---"
