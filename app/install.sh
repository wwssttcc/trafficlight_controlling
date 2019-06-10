#!/bin/bash
sudo cp /mnt/hgfs/share/trafficlight_controlling/app/* ./
make clean
make proto
make
sudo cp tl_running.out trafficlight.cfg ~/nfs/myir_hostapd/home/root/
sudo cp tl_running.out trafficlight.cfg /mnt/hgfs/share/trafficlight_controlling/bin/
