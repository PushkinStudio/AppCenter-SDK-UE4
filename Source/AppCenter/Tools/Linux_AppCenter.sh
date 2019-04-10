#!/usr/bin/env bash
# Copyright 2015-2019 Mail.Ru Group. All Rights Reserved.
set -e

printUsageExit()
{
    SCRIPT_NAME=`basename "$0"`
    SCRIPT_NAME="Tools/Build/$SCRIPT_NAME"
    echo -e "ERROR: $1\n"																			2>&1
    echo "Usage: $SCRIPT_NAME [ packSharedObjects|dumpBreakpadSymbols armeabi-v7a|arm64-v8a ]"		2>&1
    exit 1
}

packSharedObjects()
{
	if [ -z $1 ]; then
        printUsageExit "Platform arcitecture not set"
    fi

	ARCH=$2

	# Prepare directory to store symbols
	ANDROID_DIR="Intermediate/Android"
	pushd $ANDROID_DIR

	SO_DIR="libs"
	SO_ZIP="libs.zip"
	rm -rf $SO_DIR
	mkdir -p $SO_DIR

	echo "Dump the symbols using the Breakpad toolchain as described in the https://chromium.googlesource.com/breakpad/breakpad/+/master/README.ANDROID#93"

	# There two paths we need to process
	JNI_DIR=APK/jni/$ARCH
	LIBS_DIR=APK/libs/$ARCH

	find $JNI_DIR $LIBS_DIR -name '*.so' | while read so_file; do
		echo "Processing file '$so_file'"

		cp -v $so_file $SO_DIR/$(basename $so_file)
	done

	# cleanup if we have some junk
	rm -f $SO_ZIP

	# zip symbol files into archive
	zip -r -v $SO_ZIP $SO_DIR

	# ANDROID_DIR
	popd
}

dumpBreakpadSymbols()
{
	if [ -z $1 ]; then
        printUsageExit "Platform arcitecture not set"
    fi

	# Prepare directory to store symbols
	ANDROID_DIR="Intermediate/Android"
	pushd $ANDROID_DIR

	ARCH=$2

	SO_DIR="libs"
	SO_ZIP="libs.zip"
	rm -rf $SO_DIR
	mkdir -p $SO_DIR

	SYMBOLS_DIR="symbols"
	SYMBOLS_ZIP="symbols.zip"
	rm -rf $SYMBOLS_DIR
	mkdir -p $SYMBOLS_DIR

	echo "Dump the symbols using the Breakpad toolchain as described in the https://chromium.googlesource.com/breakpad/breakpad/+/master/README.ANDROID#93"

	# unzip .so files from zip
	unzip -u $SO_ZIP

	# Create a symbols.zip file with the following structure:
	# $ unzip -l symbols.zip 
	# Archive:  symbols.zip
	#   Length     Date   Time    Name
	#  --------    ----   ----    ----
	#         0  07-22-13 15:07   symbols/
	#         0  07-22-13 15:07   symbols/libnative.so/
	#         0  07-22-13 15:07   symbols/libnative.so/EAC901FB6DDCCE8AED89E1A8E4A58360/
	#     12468  07-22-13 15:07   symbols/libnative.so/EAC901FB6DDCCE8AED89E1A8E4A58360/libnative.so.sym
	#         0  07-22-13 15:07   symbols/libnative.so/FDC5C9E715C4F16408C0B78F95855BF0/
	#     12467  07-22-13 15:07   symbols/libnative.so/FDC5C9E715C4F16408C0B78F95855BF0/libnative.so.sym
	#  --------                   -------
	#     24935                   6 files
	
	find $SO_DIR -name '*.so' | while read so_file; do
		echo "Processing file '$so_file'"

		sym_file=$so_file'.sym'
		dump_syms $so_file > $sym_file

		read -r -a firstline < $sym_file

		# MODULE Linux arm D51B4A5504974FA6ECC1869CAEE3603B0 test_google_breakpad
		version_number=${firstline[3]}

		symfile_dir="$SYMBOLS_DIR/$(basename $so_file)/$version_number"
		mkdir -p $symfile_dir

		mv -v $sym_file $symfile_dir/$(basename $sym_file)
	done

	# cleanup if we have some junk
	rm -f $SYMBOLS_ZIP

	# zip symbol files into archive
	zip -r -v $SYMBOLS_ZIP $SYMBOLS_DIR

	# ANDROID_DIR
	popd
}

if [[ $# -eq 0 ]]; then
    printUsageExit "Parameters not found"
else
	if [[ $# -eq 2 ]]; then
		if [ "$2" == "armeabi-v7a" ]; then :;
		elif [ "$2" == "arm64-v8a" ]; then :;
		else printUsageExit "Unknown 2nd parameter: $2"
		fi
	fi

	if [ "$1" == "packSharedObjects" ]; then packSharedObjects $2
	elif [ "$1" == "dumpBreakpadSymbols" ]; then dumpBreakpadSymbols $2
    else printUsageExit "Unknown 1st parameter: $1"
    fi
fi

echo "--- END $0 $1 ---"
