/*
* ============================================================================
* COMCAST C O N F I D E N T I A L AND PROPRIETARY
* ============================================================================
* This file and its contents are the intellectual property of Comcast.  It may
* not be used, copied, distributed or otherwise  disclosed in whole or in part
* without the express written permission of Comcast.
* ============================================================================
* Copyright (c) 2014 Comcast. All rights reserved.
* ============================================================================
*/


#ifndef __SSP_MBUS_LIB_H__
#define __SSP_MBUS_LIB_H__


#define CCSP_DBUS_PATH_TDK         "/com/cisco/spvtg/ccsp/TDK"

DBusHandlerResult tdk_path_message_func (DBusConnection  *conn,
                       DBusMessage     *message,
                       void            *user_data);

#endif

