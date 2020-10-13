FROM alpine

RUN apk add boost-iostreams boost-dev libstdc++ cmake make build-base gcc libc-dev gtest gtest-dev bash

RUN mkdir /routeplanning

WORKDIR /routeplanning

COPY CMakeLists.txt /routeplanning/
COPY src /routeplanning/src/
RUN mkdir tests
COPY tests/* /routeplanning/tests/

RUN sh -c "cmake -DCMAKE_BUILD_TYPE=Debug . && make && cd bin && ./tests"
