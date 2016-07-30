#ifndef XI_DEBUG_MACROS
#define XI_DEBUG_MACROS

  #define XI_SERIAL Serial

  #if XI_DEBUG_LEVEL >= 1
    #define XI_DEBUG_PRINT(x)         { XI_SERIAL.print(F(x));   }
    #define XI_DEBUG_PRINTLN(x)       { XI_SERIAL.println(F(x)); }
    #define XI_DEBUG_PRINT_VARLN(x)   { XI_SERIAL.println(x);   }
    #define XI_DEBUG_VALUELN(x, y)    { XI_SERIAL.print(F(x)); Serial.print(y); }
  #else // #if DEBUG_LEVEL >= 1
    #define XI_DEBUG_PRINT(x)
    #define XI_DEBUG_PRINTLN(x)
    #define XI_DEBUG_PRINT_VARLN(x)   
    #define XI_DEBUG_VALUELN(x, y)
    // #define DEBUG_ENDLN()

  #endif // #if DEBUG_LEVEL >= 1

#endif