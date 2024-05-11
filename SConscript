from building import *

cwd = GetCurrentDir()
src = Split('''
    test_main.c
    test_gpio.c
    test_timer.c
''')

if GetDepend('BSP_USING_PWM'):
    src += ['test_pwm.c']

if GetDepend('BSP_USING_WDT'):
    src += ['test_wdt.c']

CPPPATH = [cwd]

group = DefineGroup('Test', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
