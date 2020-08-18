set_global_assignment -entity "vga60_svga60_pll" -library "lib_vga60_svga60_pll" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "vga60_svga60_pll" -library "lib_vga60_svga60_pll" -name IP_TOOL_VERSION "20.1"
set_global_assignment -entity "vga60_svga60_pll" -library "lib_vga60_svga60_pll" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_vga60_svga60_pll" -name SPD_FILE [file join $::quartus(sip_path) "vga60_svga60_pll.spd"]

set_global_assignment -library "lib_vga60_svga60_pll" -name MISC_FILE [file join $::quartus(sip_path) "vga60_svga60_pll_sim/vga60_svga60_pll.vo"]
