FROM alpine

RUN apk add clang boost-iostreams boost-dev libstdc++ cmake make build-base libc-dev gtest gtest-dev bash

RUN mkdir /routeplanning

WORKDIR /routeplanning

COPY CMakeLists.txt ./
COPY src ./src/
RUN mkdir tests
COPY tests/* ./tests/

RUN sh -c "cmake -DCMAKE_BUILD_TYPE=Debug . && make && ./bin/tests"
