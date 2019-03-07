
#ifndef _OSPF_FPGA_H_
#define _OSPF_FPGA_H_

int ip4int2str(unsigned int ip, char *p);
int  ospf_fpga_route_tbl_upd (void);
void ospf_fpga_configip_dump (struct vty *vty);
void ospf_fpga_route_tbl_dump (struct vty *vty, int flag);
void ospf_fpga_route_tbl_read_dump (struct vty *vty);
void poscfg_init (void);
int poscfg_set (int port, int val);
int poscfg_get (int port);
void fpga_pos_port_cfg_write (struct vty *vty);
int  ospf_fpga_route_tbl_reset (void);
int  ospf_fpga_thread_create (void);
void ospf_fpga_thread_exit(void);
void ospf_fpga_route_tbl_init (void);
void ospf_fpga_route_tbl_exit (void);

#endif

