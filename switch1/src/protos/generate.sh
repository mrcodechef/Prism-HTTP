#!/bin/bash

protoc -I . --grpc_out=../cpp --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./prism_switch.proto
protoc -I . --cpp_out=../cpp ./prism_switch.proto
