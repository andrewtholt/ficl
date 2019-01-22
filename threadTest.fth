
/task allocate abort" Allocate failed" value bill-vm
bill-vm /task erase

bill-vm construct bill

: bill
    begin 
        ." Around ...." cr 
        1500 ms 
    again
;

' bill bill-vm activate

