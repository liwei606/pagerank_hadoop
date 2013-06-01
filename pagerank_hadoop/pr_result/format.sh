#!/bin/bash

for r in `find -name "*_pr_result_*.txt" | sort`; do
    awk 'NR > 100' $r > log
    awk 'NR < 101' $r >> log
    mv log $r
done
