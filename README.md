# meminfo
[![Build Status](https://github.com/mrabine/meminfo/workflows/build/badge.svg)](https://github.com/mrabine/meminfo/actions?query=workflow%3Abuild)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/mrabine/meminfo.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/mrabine/meminfo/context:cpp)
[![GitHub Releases](https://img.shields.io/github/release/mrabine/meminfo.svg)](https://github.com/mrabine/meminfo/releases/latest)
[![GitHub License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/mrabine/meminfo/blob/main/LICENSE)

Monitor process VmRSS usage

## Download

To download the latest source do this:
```bash
git clone https://github.com/mrabine/meminfo.git
```

## Configuration

To configure meminfo do this:
```bash
cd meminfo
mkdir build && cd build
cmake ..
```

## Installation

To install meminfo do this:
```bash
make && sudo make install
```

## Usage

**meminfo** [options] [name]

**-d delay**\
&emsp;delay between updates (default: 5 seconds)\
**-h**\
&emsp;show available options\
**-n number**\
&emsp;number of iterations\
**-v**\
&emsp;print version

## License

[MIT](https://choosealicense.com/licenses/mit/)
