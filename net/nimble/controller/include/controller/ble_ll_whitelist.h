/**
 * Copyright (c) 2015 Stack Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef H_BLE_LL_WHITELIST_
#define H_BLE_LL_WHITELIST_

#define BLE_LL_CFG_WHITELIST_SIZE   (8)

/* Clear the whitelist */
int ble_ll_whitelist_clear(void);

/* Read the size of the whitelist */
int ble_ll_whitelist_read_size(uint8_t *rspbuf);

/* Add a device to the whitelist */
int ble_ll_whitelist_add(uint8_t *addr, uint8_t addr_type);

/* Remove a device fromthe whitelist */
int ble_ll_whitelist_rmv(uint8_t *addr, uint8_t addr_type);

/* Enable whitelisting */
void ble_ll_whitelist_enable(void);

/* Disable whitelisting */
void ble_ll_whitelist_disable(void);

/* Boolean function returning true if address matches a whitelist entry */
int ble_ll_whitelist_match(uint8_t *addr, uint8_t addr_type);

#endif /* H_BLE_LL_WHITELIST_ */