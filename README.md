# meminfo

[![Security Status](https://github.com/mrabine/meminfo/workflows/security/badge.svg)](https://github.com/mrabine/meminfo/security/code-scanning)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/974e0cb906354e6e85ad57dd2915c3da)](https://app.codacy.com/gh/mrabine/meminfo/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
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
