First, intall qemu:
```bash
sudo apt install qemu-system
```

Next, prepare the image
```bash
$ tar -xf Debian\ 12.ova
$ mkdir debian-ovf-extracted
$ mv "Debian 12-disk001.vmdk" "Debian 12.mf" "Debian 12.ovf" debian-ovf-extracted/

# verify the hashsum
$ cat Debian\ 12.mf
SHA256 (Debian 12.ovf) = 51b8bf672d43d21be9289bbebecabd669a88a07507d47f103876a55eec4df592
SHA256 (Debian 12-disk001.vmdk) = 771a442469a8af8de82d1cd680ee1057643ac73dd2df0c7ebf4c288d2a5408dd
$ sha256sum "Debian 12.ovf"
51b8bf672d43d21be9289bbebecabd669a88a07507d47f103876a55eec4df592  Debian 12.ovf
$ sha256sum "Debian 12-disk001.vmdk"
771a442469a8af8de82d1cd680ee1057643ac73dd2df0c7ebf4c288d2a5408dd  Debian 12-disk001.vmdk

# convert image to qcow2 format
qemu-img convert -f vmdk -O qcow2 -p Debian\ 12-disk001.vmdk debian-12.qcow2
```

Now, the file `Debian 12.ovf` contains the VM configuration which only
virtualbox understands, let's translate it to human-readable info:
- network: NAT, Ethernet adapter on 'NAT' E1000
- users: `root` & `myuser`, both have the same password `jango123#`
- various image characteristics that I cannot understand: `ovf:capacity="21474836480" ovf:diskId="vmdisk1" ovf:fileRef="file1"`
- 1 vcpu
- 1024 MiB RAM
- not yet understood: separate controllers, audio adapters, storage controllers
  (DVD, HardDisk)

TODO: watch the tutorials
- https://www.youtube.com/playlist?list=PLqKkf220xDDbW9G0a4XXO50yvHWFq2uOD
- https://www.youtube.com/watch?v=AAfFewePE7c
- https://www.youtube.com/watch?v=oAbNY-QuPx4
- https://www.youtube.com/watch?v=773PhMgEOFw
- firmware reversing: https://www.youtube.com/watch?v=50lFwNvHbDs

# Launching the vm
The most straightforward way:
```
qemu-system-x86_64 \
  -m 2048 \
  -cpu host \
  -smp 2 \
  -drive file=./debian-ovf-extracted/debian-12.qcow2,format=qcow2 \
  -enable-kvm
```
*Note*: -nographic won't work at all! The boot will hang

The changes in VM image are persistent!
