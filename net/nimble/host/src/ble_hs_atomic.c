/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "ble_hs_priv.h"

int
ble_hs_atomic_conn_delete(uint16_t conn_handle)
{
    struct ble_hs_conn *conn;

    ble_hs_lock();
    conn = ble_hs_conn_find(conn_handle);
    if (conn != NULL) {
        ble_hs_conn_remove(conn);
        ble_hs_conn_free(conn);

    }
    ble_hs_unlock();

    return conn != NULL ? 0 : BLE_HS_ENOTCONN;
}

void
ble_hs_atomic_conn_insert(struct ble_hs_conn *conn)
{
    ble_hs_lock();
    ble_hs_conn_insert(conn);
    ble_hs_unlock();
}

int
ble_hs_atomic_conn_flags(uint16_t conn_handle, ble_hs_conn_flags_t *out_flags)
{
    struct ble_hs_conn *conn;
    int rc;

    ble_hs_lock();

    conn = ble_hs_conn_find(conn_handle);
    if (conn == NULL) {
        rc = BLE_HS_ENOTCONN;
    } else {
        rc = 0;
        *out_flags = conn->bhc_flags;
    }

    ble_hs_unlock();

    return rc;
}
