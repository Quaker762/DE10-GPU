set_global_assignment -entity "pixel" -library "lib_pixel" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "pixel" -library "lib_pixel" -name IP_TOOL_VERSION "18.1"
set_global_assignment -entity "pixel" -library "lib_pixel" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_pixel" -name SPD_FILE [file join $::quartus(sip_path) "pixel.spd"]

set_global_assignment -library "lib_pixel" -name MISC_FILE [file join $::quartus(sip_path) "pixel_sim/pixel.vo"]
