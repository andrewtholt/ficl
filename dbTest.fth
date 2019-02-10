-1 value plc
-1 value db
0 0 2value hostname
-1 value io

s" /tmp/plc.db" plc-new to plc

s" 192.168.0.65" plc plc-set-hostname
8123 plc plc-set-port

1 plc plc-setup
1 plc plc-verbose

plc plc-getdb to db

plc plc-get-hostname to hostname

db hostname s" HA_REST" plc-mkio dup 0= abort" Failed to create io." to io

s" IN1" s" switch.relay_1" s" IN" s" HA_REST" plc plc-add-io
s" IN2" s" switch.relay_2" s" IN" s" HA_REST" plc plc-add-io

s" OUT1" s" switch.relay_3" s" OUT" s" HA_REST" plc plc-add-io
s" OUT2" s" switch.relay_4" s" OUT" s" HA_REST" plc plc-add-io

cr
plc plc-dump
