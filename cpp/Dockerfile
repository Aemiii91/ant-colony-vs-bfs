FROM alpine

RUN apk add boost-iostreams boost-dev libstdc++ cmake make build-base gcc libc-dev gtest gtest-dev bash python3 python3-dev

RUN mkdir /routeplanning


WORKDIR /routeplanning

COPY CMakeLists.txt /routeplanning/
COPY src /routeplanning/src/
COPY include /routeplanning/include
COPY apicaller /routeplanning/apicaller
RUN mkdir tests
COPY tests/* /routeplanning/tests/


RUN sh -c "cmake . && make && cd bin && ./tests"
