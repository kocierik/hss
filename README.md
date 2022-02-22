## HSS
ssh terminal interface 



create a .ps file inside your .ssh folder to store passwords and hostname separated by a comma
#### example:
```
PASSWORD,NAME@HOSTNAME
```
---
### Build:
Add to your path or create a <b>symlink</b> binary
```sh
# clone repo and run make
  make

# symlink binary to somewhere in your path 
# replace the second argument below with some directory in your path
  ln -s $PWD/hss  /usr/local/bin/hss
```

