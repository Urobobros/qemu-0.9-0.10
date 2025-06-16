FROM i386/debian:stable-slim

RUN apt-get update && apt-get install -y \
    build-essential \
    libsdl1.2-dev \
    libasound2-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

COPY qemu-0.9.1 /src/qemu-0.9.1

WORKDIR /build

RUN mkdir qemu-build && cd qemu-build && \
    /src/qemu-0.9.1/configure --prefix=/usr/local --disable-gcc-check --target-list=i386-softmmu --enable-sdl && \
    make -j$(nproc) && \
    make install

CMD ["/bin/bash"]
