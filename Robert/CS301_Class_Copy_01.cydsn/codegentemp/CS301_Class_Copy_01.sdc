# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\schoo\302OffOnedrive\301 Project\12_Cypress_LineFollowingRobot\Robert\CS301_Class_Copy_01.cydsn\CS301_Class_Copy_01.cyprj
# Date: Tue, 08 Aug 2023 00:44:45 GMT
#set_units -time ns
create_clock -name {ADC_IntClock(routed)} -period 349.99999999999994 -waveform {0 175} [list [get_pins {ClockBlock/dclk_1}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 16.666666666666664 -waveform {0 8.33333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 16.666666666666664 -waveform {0 8.33333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {Clock_QENC} -source [get_pins {ClockBlock/clk_sync}] -edges {1 5 11} -nominal_period 83.333333333333314 [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {ADC_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 21 43} -nominal_period 349.99999999999994 [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {Clock_PWM} -source [get_pins {ClockBlock/clk_sync}] -edges {1 61 121} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {UART_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 131 261} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_generated_clock -name {Clock2} -source [get_pins {ClockBlock/clk_sync}] -edges {1 121 241} [list [get_pins {ClockBlock/dclk_glb_3}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\schoo\302OffOnedrive\301 Project\12_Cypress_LineFollowingRobot\Robert\CS301_Class_Copy_01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\schoo\302OffOnedrive\301 Project\12_Cypress_LineFollowingRobot\Robert\CS301_Class_Copy_01.cydsn\CS301_Class_Copy_01.cyprj
# Date: Tue, 08 Aug 2023 00:44:28 GMT
