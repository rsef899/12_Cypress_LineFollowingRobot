# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\Documents\UOA\2023\Semester 2\COMPSYS301\repos\12_Cypress_LineFollowingRobot\Janith\PSOC\lab3.cydsn\lab3.cyprj
# Date: Thu, 24 Aug 2023 03:03:39 GMT
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3001 6001} [list [get_pins {ClockBlock/dclk_glb_0}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for D:\Documents\UOA\2023\Semester 2\COMPSYS301\repos\12_Cypress_LineFollowingRobot\Janith\PSOC\lab3.cydsn\TopDesign\TopDesign.cysch
# Project: D:\Documents\UOA\2023\Semester 2\COMPSYS301\repos\12_Cypress_LineFollowingRobot\Janith\PSOC\lab3.cydsn\lab3.cyprj
# Date: Thu, 24 Aug 2023 03:03:37 GMT