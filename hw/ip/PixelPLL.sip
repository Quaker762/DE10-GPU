set_global_assignment -entity "PixelPLL" -library "lib_PixelPLL" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "PixelPLL" -library "lib_PixelPLL" -name IP_TOOL_VERSION "19.1"
set_global_assignment -entity "PixelPLL" -library "lib_PixelPLL" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_PixelPLL" -name SPD_FILE [file join $::quartus(sip_path) "PixelPLL.spd"]

set_global_assignment -library "lib_PixelPLL" -name MISC_FILE [file join $::quartus(sip_path) "PixelPLL_sim/PixelPLL.vo"]
