
#ifndef _FPGA_OPT_H_
#define _FPGA_OPT_H_

#define FPGA_POS_IF_COUNT        4
#define FPGA_IF_NAME_LEN         16
#define FPGA_IF_COUNT            8
#define FPGA_IF_MAX_COUNT        9   /* 4:pos 4:eth 1:x86 */

#define FPGA_ROUTE_MAX_CNT       2048

#define FPGA_ADD_ROUTE           1
#define FPGA_DEL_ROUTE           2
#define FPGA_RESET_ROUTE         3

/* pos info bit define */
#define OPTIC_RX_LOSS        0x01
#define OPTIC_TX_FAULT       0x02
#define OPTIC_TX_DISABLE     0x04
#define SDH_SYNC             0x08
#define AU_PTR               0x10
#define SOH_PARITY           0x20
#define POS_DESCRAMBLE       0x40

#define CFG_POS_SCRAMBLE     1
#define CFG_POS_DESCRAMBLE   0

#define CFG_DEFAULT_IP       0x00000000
#define CFG_DEFAULT_MASK     0xffffffff

struct fpga_interface {
		int ifindex;
		char ifname[FPGA_IF_NAME_LEN];
		unsigned char mac[6];
		unsigned int ip;
		unsigned int mask;
};

struct fpga_route {
	unsigned int ip;      /* destination ip address */
	unsigned int mask;    /* destination ip mask */
	unsigned int via;     /* via ip */
};

struct fpga_port_bdwinfo {
		int port;
		unsigned int rxbdw;
		unsigned int txbdw;
};

extern struct fpga_interface fpgaif[FPGA_IF_MAX_COUNT];

int fpga_write_route_opt (struct fpga_route *frt, int raddr);
int fpga_read_route_opt (struct fpga_route *frt, int raddr);
int fpga_write_route_complete (int complete);
int fpga_check_cfgip_repeat (struct fpga_interface *fif);
int fpga_check_cfgip_same_port (struct fpga_interface *fif);
int fpga_write_confip (struct fpga_interface *fif);
int fpga_check_del_cfgip (unsigned int ip, unsigned int mask);
int fpga_read_confip (void);
int fpga_read_pos_info (int port, int *pinfo);
int fpga_write_pos_cfg (int port, int pval);
int fpga_read_port_bandwidth (struct fpga_port_bdwinfo *bdwinfo);
int fpga_dev_init (void);
void fpga_dev_exit (void);

int getqid(void);
int fpga_cfgip_init_msgq(void);
int fpga_cfgip_get_ifindex (unsigned int ip, unsigned int mask);
int fpga_cfgip_send_msgq(struct fpga_interface *fif);
#endif

