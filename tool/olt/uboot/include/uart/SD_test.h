//extern void usdelay();
void etn_verify_scan_all_phy();


extern void inline rtl8139cp_verify_mac_reset();
extern void rtl8139cp_verify_SetEthAddr();
extern void inline rtl8139cp_verify_phy_auto_negotiation(UINT8 phyID);
extern void rtl8139cp_verify_phy_loopback_test();
extern void rtl8139cp_verify_mac_loopback_test();
extern void rtl8139cp_verify_normal_reg_setup();
extern void rtl8139cp_verify_scan_all_phy();
extern void rtl8139cp_verify_RxTx();
extern void rtl8139cp_verify_Address();
extern void rtl8139cp_verify_only_rx();
extern void rtl8139cp_verify_only_tx();
extern void rtl8139cp_verify_RxTx_workaround();
extern void mass_loopback();
extern void rtl8139cp_verify_dump_phy_reg();


UINT32 rtl8139cp_verify_mdio_read(UINT8 ,UINT8 );
void rtl8139cp_verify_mdio_write(UINT8 , UINT8 , UINT16);
//static UINT32 ioaddr=RL8139CP_LAN_BASE;

