set_global_assignment -entity "pixel2" -library "lib_pixel2" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "pixel2" -library "lib_pixel2" -name IP_TOOL_VERSION "18.1"
set_global_assignment -entity "pixel2" -library "lib_pixel2" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_pixel2" -name SPD_FILE [file join $::quartus(sip_path) "pixel2.spd"]

set_global_assignment -library "lib_pixel2" -name MISC_FILE [file join $::quartus(sip_path) "pixel2_sim/pixel2.vo"]
