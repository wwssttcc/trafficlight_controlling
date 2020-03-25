#!/bin/bash
sudo cp /mnt/hgfs/share/trafficlight_controlling/hc595_drv/* ./
make clean
make
sudo cp hc595_drv.ko ~/nfs/myir_hostapd/home/root/driver
