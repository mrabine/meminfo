# meminfo
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
