-1 value plc
-1 value db
0 0 2value hostname
-1 value io

s" /tmp/plc.db" plc-new to plc
\ s" :memory:" plc-new to plc

s" 192.168.0.65" plc plc-set-hostname
8123 plc plc-set-port

0 plc plc-setup
0 plc plc-verbose

plc plc-getdb to db
plc plc-get-hostname to hostname

db hostname s" HA_REST" plc-mkio dup 0= abort" Failed to create io." to io

s" START" s" switch.relay_1" s" IN" s" HA_REST" plc plc-add-io
s" STOP" s" switch.relay_2" s" IN" s" HA_REST" plc plc-add-io

s" MOTOR" s" switch.back_floodlights" s" OUT" s" HA_REST" plc plc-add-io
\ s" MOTOR" s" switch.relay_3" s" OUT" s" HA_REST" plc plc-add-io
\ s" OUT2" s" switch.relay_4" s" OUT" s" HA_REST" plc plc-add-io

cr
plc plc-dump


: logic
    io plc-input-scan

    s" START"  plc plc-ld
    s" MOTOR"  plc plc-or
    s" STOP"   plc plc-andn
    
    s" MOTOR" plc plc-out
    
    io plc-output-update
    
    plc plc-end
;

\ plc plc@

\ logic

1000 value minTime
0 value maxTime
: stats ( value --- )
    dup minTime min to minTime
    dup maxTime max to maxTime

    ." Max  :" maxTime . cr
    ." Value:" . cr
    ." Min  :" minTime . cr
;

mktimer value timer
: main
\    begin
    100 0 do
        timer start-timer
        logic 
        timer read-timer dup stats

        500 swap - 
        dup 0> if
            ms
        else
            drop
        then
    loop
\    again
    timer read-timer . cr
;


