FROM alpine

RUN apk add --no-cache gcc cmake make musl-dev linux-headers

COPY . /c_test_repo

WORKDIR /c_test_repo/build

RUN cmake -DCMAKE_BUILD_TYPE="Debug" .. && \
    cmake --build .

CMD ctest .
