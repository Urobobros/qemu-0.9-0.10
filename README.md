# qemu-0.9-0.10

This repository contains QEMU versions 0.9.1 and 0.10.0.

A `Dockerfile` is included for building QEMU 0.9.1 with SDL support in a 32‑bit
Debian environment. Use the following commands:

```bash
docker build -t qemu-0.9.1 .
```

The build uses an out-of-tree directory to keep the source clean. To run an
interactive shell and store the build results on the host, mount a volume:

```bash
docker run -it --rm -v "$PWD/output:/usr/local" qemu-0.9.1
```

The compiled binaries will appear in the `output` directory on the host.
