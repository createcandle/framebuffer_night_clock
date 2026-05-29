# framebuffer night clock

Simple framebuffer clock application for Linux. Shows centered 24h time in dark red color, using PNG files for the numbers.

The `fbclock` file is a pre-compiled ARM64 binary (for Raspberry Pi).

This is a modification of "df3120-fbclock":

https://github.com/rayner/df3120-fbclock


### Building it:

- clone this repository and enter its directory
- `make`

This will create the `fbclock` binary, which you can run as follows:

Normal display:
```
./fbclock
```

180 Degree rotated display:
```
./fbclock -r 1
```

