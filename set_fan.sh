#!/bin/bash

PERCENTAGE=0

usage(){
        echo "Usage: $0 [-s value] [-r]"
}

exit_abnormal(){
        usage
        exit 1
}

set_value(){
        bash -c "echo $PERCENTAGE > /sys/devices/pwm-fan/target_pwm"
}

read_value(){
        bash -c "head /sys/devices/pwm-fan/target_pwm"
}

while getopts "s:r" options; do
        case "${options}" in
                s)
                        PERCENTAGE=${OPTARG}
                        echo "PERCENTAGE=$PERCENTAGE"
                        set_value
                        ;;
                r)
                        read_value
                        ;;
                :)
                        echo "Error: -${OPTARG} requires an argument."
                        exit_abnormal
                        ;;
                *)
                        exit_abnormal
                        ;;
        esac
done
exit 0
