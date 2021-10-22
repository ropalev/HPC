#!/bin/bash
for i in {100..1000}
do
        rem=$(($i % 2))
        if [ "$rem" -ne "1" ]; then
                echo $i
        fi
done
