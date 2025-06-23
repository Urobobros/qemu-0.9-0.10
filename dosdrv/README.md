# Cue/Bin DOS Driver (experimental)

This directory contains a very small prototype of a DOS driver that reads
CUE/BIN images. The code only parses the CUE sheet and reports the track
information. It does not yet implement the full MSCDEX interface, but it
serves as a starting point for a real driver.

## Building

The build relies on the `bcc` 16-bit compiler (package `bcc`). Run:

```sh
make
```

This will create `cuebin.sys`, which is a simple COM-like program printing
the parsed track information. It can be executed under DOS for testing
purposes.
