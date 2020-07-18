set_global_assignment -entity "xga60_pll" -library "lib_xga60_pll" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "xga60_pll" -library "lib_xga60_pll" -name IP_TOOL_VERSION "19.1"
set_global_assignment -entity "xga60_pll" -library "lib_xga60_pll" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_xga60_pll" -name SPD_FILE [file join $::quartus(sip_path) "xga60_pll.spd"]

set_global_assignment -library "lib_xga60_pll" -name MISC_FILE [file join $::quartus(sip_path) "xga60_pll_sim/xga60_pll.vo"]
