#!/bin/bash

for r in `find -name "*_out.txt" | sort`; do
    grep -v "Average" $r > log
    mv log $r
done

