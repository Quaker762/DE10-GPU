set_global_assignment -entity "PLL500" -library "lib_PLL500" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "PLL500" -library "lib_PLL500" -name IP_TOOL_VERSION "18.1"
set_global_assignment -entity "PLL500" -library "lib_PLL500" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_PLL500" -name SPD_FILE [file join $::quartus(sip_path) "PLL500.spd"]

set_global_assignment -library "lib_PLL500" -name MISC_FILE [file join $::quartus(sip_path) "PLL500_sim/PLL500.vo"]
