##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

#!/bin/sh

start_tdk() {

TDK_EXECUTION_PATH=`cat /var/TDK/tdk_platform.properties|grep TDK_EXECUTION_PATH|cut -d '=' -f 2`
echo $TDK_EXECUTION_PATH
    if [ -d $TDK_EXECUTION_PATH ];then
         echo "path exists"
         cp -r /var/TDK $TDK_EXECUTION_PATH/TDK/
         sh -c $TDK_EXECUTION_PATH/TDK/StartTDK.sh
     else
         echo "path not exists"
    fi

}

start_tdk
