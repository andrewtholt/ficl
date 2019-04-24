
: >string 
    >r dup >r abs s>d <# #s r> sign #>
    r@ char+ swap dup >r move r> r> c! 
;

16 chars allocate abort" alloc failed" value count-buff

variable counter
0 counter !

-1 value mqtt

\ 
\ Add one to counter and return string
: inc
    1 counter +!
    counter @ count-buff >string

    count-buff count
;

new-mqtt to mqtt

s" FICL" mqtt client-id!

\ s" 192.168.0.65" mqtt mqtt-host!

s" /test/start" mqtt mqtt-sub

mqtt mqtt-connect abort" mqtt-connect failed"

\ mqtt set-default-callback
mqtt set-ficl-callback

mqtt mqtt-dump

: tst
    1 mqtt mqtt-go
    inc  s" /test/counter" mqtt mqtt-pub
;

0 value START
defer logic

-1 constant ON
0 constant OFF


: /test/start
    ." START" cr 
    evaluate to START
;


: tst2
    begin
        msg-count@ 0>
    while
        ." Message" cr
        msg@ 

        evaluate

        logic
    repeat
;

: tst3
    begin
        1 mqtt mqtt-go

        tst2

        1000 ms
    again

;

