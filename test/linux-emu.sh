#!/bin/sh
o="$1"
case "$o" in
  mount)
        { test -e /dev/loop0p3 || losetup -P -f /home/inc/moje/programy/odgałęzione/linux/disk.img; } \
        && mount /dev/loop0p3 /mnt/oth \
        && mount /dev/loop0p2 /mnt/oth/boot \
        && mount --types proc /proc /mnt/oth/proc \
        && mount --rbind /sys /mnt/oth/sys \
        && mount --make-rslave /mnt/oth/sys \
        && mount --rbind /dev /mnt/oth/dev \
        && mount --make-rslave /mnt/oth/dev \
        && mount --bind /run /mnt/oth/run \
        && mount --make-slave /mnt/oth/run \
        && chroot /mnt/oth /bin/bash
        ;;
  umount)
        mount | grep -Fe ' on /mnt/oth/' | cut -d \  -f 3 | tac | xargs -r umount \
        && umount /mnt/oth \
        && losetup -d /dev/loop0
        ;;
  qemu)
        exec qemu-system-x86_64 -s -S -machine q35 -cpu IvyBridge -smp cores=2,threads=2 -m 4096 -hda /home/inc/moje/programy/odgałęzione/linux/disk.img -boot order=c
        ;;
esac
