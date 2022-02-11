#!/bin/bash

export ZZIDUO_DIR=$(pwd)

log_file=${ZZIDUO_DIR}/$(date "+%H:%M:%S@%Y-%m-%d").log

set -e

main(){
	[ ! -d ${ZZIDUO_DIR}/output ] || rm -rf ${ZZIDUO_DIR}/output
	[ ! -d ${ZZIDUO_DIR}/build ] || rm -rf ${ZZIDUO_DIR}/build

	mkdir ${ZZIDUO_DIR}/output
	mkdir ${ZZIDUO_DIR}/build

	cd ${ZZIDUO_DIR}/build
	cmake ${ZZIDUO_DIR}
	make
}

main $* 2>&1 | tee ${log_file}