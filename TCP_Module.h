 /* TCP IP transfer hedder file (using sys/socket driver)
 *
 * Copyright (c) 2018  Umbrella Irrigation Software, Inc.
 * Copyright (c) 2018  Sina Eradat <sina.eradat.540@my.csun.edu>
 */

int tcp_init(int port,char *ipadr);
int tcp_read(char *data);
int tcp_write(char *data);
int tcp_xfer(char *data_Tx, char *data_RX);