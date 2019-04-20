1 set-sched .

variable counter
0 counter !

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
        lock get
        ." Around ...." counter @ dup . cr
        1+ counter !
        lock release
        500 ms 
    again
;

: ted
    begin 
        lock get
        ." And ...." counter @ dup . cr 
        1- counter !
        lock release
        1500 ms 
    again
;

' bill bill-vm activate
' ted ted-vm activate

