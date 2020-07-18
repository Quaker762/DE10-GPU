set_global_assignment -entity "hsbridge_pll" -library "lib_hsbridge_pll" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "hsbridge_pll" -library "lib_hsbridge_pll" -name IP_TOOL_VERSION "19.1"
set_global_assignment -entity "hsbridge_pll" -library "lib_hsbridge_pll" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_hsbridge_pll" -name SPD_FILE [file join $::quartus(sip_path) "hsbridge_pll.spd"]

set_global_assignment -library "lib_hsbridge_pll" -name MISC_FILE [file join $::quartus(sip_path) "hsbridge_pll_sim/hsbridge_pll.vo"]
