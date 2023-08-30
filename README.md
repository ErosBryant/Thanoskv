## NVM_Leveldb

### Dependencies
- https://pmem.io/blog/2016/02/how-to-emulate-persistent-memory
```
E.g. memmap=4G!12G reserves 4GB of memory between 12th and 16th GB. Configuration is done within GRUB, and varies between Linux distributions. Here are two examples of GRUB configuration.

Ubuntu Server 15.04

# sudo vi /etc/default/grub

GRUB_CMDLINE_LINUX="memmap=nn[KMG]!ss[KMG]"

# sudo update-grub2

```

- NUMA
```bash
sudo apt update
sudo apt install numactl
sudo apt-get install libnuma-dev

sudo numactl --show
```




## Download
```bash
git clone --recurse-submodules https://github.com/ErosBryant/Thanoskv.git

```

```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
```


## Set nvm version

```
source scripts/setvars.sh
scripts/mount_dax.sh
```

- ### git
```
git log
git restore .
git checkout ___


- branch
git checkout __
```


