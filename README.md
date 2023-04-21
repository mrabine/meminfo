# meminfo

[![Security Status](https://github.com/mrabine/meminfo/workflows/security/badge.svg)](https://github.com/mrabine/meminfo/security/code-scanning)
[![Codacy Grade](https://app.codacy.com/project/badge/Grade/aa8d30be1e104cdebdaf1861de8a8db1)](https://www.codacy.com/gh/mrabine/meminfo/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=mrabine/meminfo&amp;utm_campaign=Badge_Grade)
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
