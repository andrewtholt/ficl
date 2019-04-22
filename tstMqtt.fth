
-1 value mqtt

new-mqtt to mqtt

s" FICL" mqtt client-id!

s" 192.168.0.65" mqtt mqtt-host!

s" /test/start" mqtt mqtt-sub

mqtt mqtt-connect abort" mqtt-connect failed"

mqtt set-default-callback

mqtt mqtt-dump

1 mqtt mqtt-go

s" fred" s" /test/counter" mqtt mqtt-pub

