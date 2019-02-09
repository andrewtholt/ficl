-1 value plc

s" /tmp/plc.db" plc-new to plc

1 plc plc-setup
1 plc plc-verbose

plc plc-dump

s" IN1" s" switch.relay_1" s" IN" s" HA_REST" plc plc-add-io
s" IN2" s" switch.relay_2" s" IN" s" HA_REST" plc plc-add-io

s" OUT1" s" switch.relay_3" s" OUT" s" HA_REST" plc plc-add-io
s" OUT2" s" switch.relay_4" s" OUT" s" HA_REST" plc plc-add-io


