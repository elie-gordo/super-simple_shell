#!/bin/sh
# Print Linux PID upper limit from the kernel procfs interface.
# Useful to answer exercise 1 quickly with an authoritative source.
cat /proc/sys/kernel/pid_max
