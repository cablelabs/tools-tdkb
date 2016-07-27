#
# ============================================================================
# COMCAST C O N F I D E N T I A L AND PROPRIETARY
# ============================================================================
# This file (and its contents) are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.
# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================

#!/bin/sh

start_tdk() {
    if [ -d "/opt" ];then
        cp -r /var/TDK /opt
        sh -c /opt/TDK/StartTDK.sh
    else
        if [ -d "/nvram" ];then
            cp -r /var/TDK /nvram
            sh -c /nvram/TDK/StartTDK.sh
        fi
    fi
}

start_tdk
