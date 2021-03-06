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

/* This whole file is conditionally compiled based on whether the 
 * SHELL_PRESENT identity is provided.
 */

#ifdef SHELL_PRESENT

#include <os/os.h>

#include <string.h>

#include <util/cbmem.h>

#include "log/log.h"

#include <stdio.h>

#include <shell/shell.h>
#include <console/console.h> 

static int 
shell_log_dump_entry(struct log *log, void *arg, void *dptr, uint16_t len) 
{
    struct log_entry_hdr ueh;
    char data[128];
    int dlen;
    int rc;

    rc = log_read(log, dptr, &ueh, 0, sizeof(ueh)); 
    if (rc != sizeof(ueh)) {
        goto err;
    }

    dlen = min(len-sizeof(ueh), 128);

    rc = log_read(log, dptr, data, sizeof(ueh), dlen);
    if (rc < 0) {
        goto err;
    }
    data[rc] = 0;

    /* XXX: This is evil.  newlib printf does not like 64-bit 
     * values, and this causes memory to be overwritten.  Cast to a 
     * unsigned 32-bit value for now.
     */
    console_printf("[%lu] %s\n", (unsigned long) ueh.ue_ts, data);

    return (0);
err:
    return (rc);
}

int 
shell_log_dump_all_cmd(int argc, char **argv)
{
    struct log *log;
    int rc;

    log = NULL;
    while (1) {
        log = log_list_get_next(log);
        if (log == NULL) {
            break;
        }

        if (log->l_log->log_type == LOG_TYPE_STREAM) {
            continue;
        }

        console_printf("Dumping log %s\n", log->l_name);

        rc = log_walk(log, shell_log_dump_entry, NULL);
        if (rc != 0) {
            goto err;
        }
    }

    return (0);
err:
    return (rc);
}

#endif 


