1 set-sched .

/task allocate abort" Allocate failed" value bill-vm
bill-vm /task erase

bill-vm construct 

/task allocate abort" Allocate failed" value ted-vm
ted-vm /task erase

ted-vm construct 

: bill
    begin 
        ." Around ...." cr 
        1500 ms 
    again
;

: ted
    begin 
        ." And ...." cr 
        1500 ms 
    again
;

' bill bill-vm activate
' ted ted-vm activate

