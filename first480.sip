set_global_assignment -entity "first480" -library "lib_first480" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "first480" -library "lib_first480" -name IP_TOOL_VERSION "18.1"
set_global_assignment -entity "first480" -library "lib_first480" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_first480" -name SPD_FILE [file join $::quartus(sip_path) "first480.spd"]

set_global_assignment -library "lib_first480" -name MISC_FILE [file join $::quartus(sip_path) "first480_sim/first480.vo"]
