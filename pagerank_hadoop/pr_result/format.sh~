#!/bin/bash

for r in `find -name "*_pr_result_10.txt" | sort`; do
    awk 'NR > 100' $r > log
    mv log $r
done
