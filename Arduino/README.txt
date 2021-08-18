The arduino code is rewritten to 1 sketch where you can define which kind of EEPROM you want to use. This can be done in the "useEEPROM" variable.
This variable has 3 states:
    -0: This state uses no EEPROM, the setup variables will be reset to default when the arduino gets powered off and on again. This is the best option
        If you don't want to buy an EEPROM module, or don't want anything to break or act weird.     
    -1: This state uses an external EEPROM module, these modules are pretty cheap (around €5-€10). I recommend using this option, it doens't use the arduino's
        EEPROM so it doesn't break down, or starts acting weird. This module can behave the same after enough write cycles but you can replace them.
    -2: This state uses the internal EEPROM from the arduino, this is the least recommended option since when the arduino's EEPROM write cycles are reached it can
        start acting weird or just do nothing and the internal EEPROM can't be replaced, but the arduino works just fine when EEPROM isn't working correctly anymore.