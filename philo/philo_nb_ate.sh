#!/bin/bash

philos=("1" "2" "3" "4" "5")

for x in "${philos[@]}"; do
    count=$(./philo 5 800 200 200 7 | grep -c "$x is eating")
    echo "Philo $x : $count"
done

