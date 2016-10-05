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
#
PORT=69
SRC="$(dirname $1)"
cd $SRC
CMND="$4/execution/uploadLogs?fileName=$2 -F logFile=@$(basename $1)"
curl -g --interface erouter0 $CMND
