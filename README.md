# qemu-0.9-0.10

This repository contains QEMU versions 0.9.1 and 0.10.0.

A `Dockerfile` is included for building QEMU 0.9.1 with SDL support in a 32‑bit
Debian environment. `libsdl1.2-dev` must be installed when building outside the container. Use the following commands:

```bash
docker build -t qemu-0.9.1 .
```

To run an interactive shell inside the container:

```bash
docker run -it --rm qemu-0.9.1
```

The build outputs are installed under `/usr/local` inside the container.
