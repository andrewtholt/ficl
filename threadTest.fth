1 set-sched .

0 value counter

/mutex allocate abort" Allocate failed" value lock
lock mutex-init

/task allocate abort" Allocate failed" value bill-vm
bill-vm /task erase

bill-vm construct 

/task allocate abort" Allocate failed" value ted-vm
ted-vm /task erase

ted-vm construct 

: bill
    begin 
        ." Around ...." counter . cr
        1500 ms 
        lock get
        counter 1+ to counter
        lock release
    again
;

: ted
    begin 
        ." And ...." counter . cr 
        1500 ms 
        lock get
        counter 1- to counter
        lock release
    again
;

' bill bill-vm activate
' ted ted-vm activate

