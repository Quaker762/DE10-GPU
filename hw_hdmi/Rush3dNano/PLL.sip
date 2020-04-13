set_global_assignment -entity "PLL" -library "lib_PLL" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "PLL" -library "lib_PLL" -name IP_TOOL_VERSION "19.1"
set_global_assignment -entity "PLL" -library "lib_PLL" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_PLL" -name SPD_FILE [file join $::quartus(sip_path) "PLL.spd"]

set_global_assignment -library "lib_PLL" -name MISC_FILE [file join $::quartus(sip_path) "PLL_sim/PLL.vo"]
