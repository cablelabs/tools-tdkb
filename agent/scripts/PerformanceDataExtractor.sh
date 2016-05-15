#!/bin/sh
# ============================================================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ============================================================================

# This file and its contents are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.

# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================

export PATH=$PATH:/usr/local/bin:/usr/local/lib:/usr/local/lib/sa

cd $TDK_PATH

ITERATION=`cat sysStatAvg.log | awk ' /ITERATION/ { print $0 }' | wc -l`
TOTAL_LINES=`cat sysStatAvg.log | wc -l`
LINE_COUNT=$(($TOTAL_LINES / $ITERATION))


while read line
do

    sed -e '/ITERATION/,$d' sysStatAvg.log > performance.temp

    cat performance.temp | awk 'BEGIN { RS="" ; FS="\n" } { print $2 }' | awk '{print $8}' >> cpu.log

    cat performance.temp  | awk 'BEGIN { RS="" ; FS="\n" } { print $4 }' | awk '{print$2,$3,$4}' >> memused.log

    sed -e '1,'$LINE_COUNT'd' < sysStatAvg.log > temp

    mv temp sysStatAvg.log

done < sysStatAvg.log

echo "Performance data Extracted"
