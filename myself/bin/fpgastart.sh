#!/bin/sh

BASEADDR=/myself/etc

IPADDR=192.168.10.6
NETMASK=255.255.255.0
GATEWAY=192.168.10.1

STRVAL=`/myself/bin/clvgetdial`
DIALVAL=`echo $STRVAL | awk -F ':' '{print $2}' `
echo $DIALVAL
if [ "$DIALVAL" == "0xf" ]; then
	echo "dialval is $DIALVAL, use default ip and mask"
else
	if [ -f $BASEADDR/mgtip.cfg ]; then
		. $BASEADDR/mgtip.cfg
	fi
	IPADDR=$MGT_IPADDRESS
	NETMASK=$MGT_NETMASK
	GATEWAY=$MGT_GATEWAY
fi

echo $IPADDR
echo $NETMASK

ifconfig eth0 down
ifconfig eth0 $IPADDR netmask $NETMASK up
#route add -net 192.168.10.0 netmask 255.255.255.0 gw $GATEWAY
route add default gw $GATEWAY

val=`echo $IPADDR | awk -F '.' '{print $4}'`
echo $val
macval=`printf "%02x\n" $val`
echo $macval

/myself/bin/cfgfpgaaddr x86 --mac 10:10:10:04:05:$macval --ip $IPADDR --mask $NETMASK

/myself/quaggav231/sbin/zebra -d
/myself/quaggav231/sbin/ospfd -d
