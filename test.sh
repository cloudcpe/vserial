#!/bin/bash

serials="serials.txt"

echo > ${serials}

for dev in v107 v110 ; do
    for b1 in `seq 0 255` ; do
        b1="$(printf "%02X" "$b1")"
        for b2 in `seq 0 255` ; do
            b2="$(printf "%02X" "$b2")"
            for b3 in `seq 0 255` ; do
                b3="$(printf "%02X" "$b3")"

                serial="$(./build/vserial encode $dev 01:02:03:$b1:$b2:$b3)"
                echo $serial >> ${serials}
            done
        done
    done
done
