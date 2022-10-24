#!/bin/sh
make -j11 all
commander flash conn_interval_central_AM.s37 -s 440169493 -d efr32mg21

