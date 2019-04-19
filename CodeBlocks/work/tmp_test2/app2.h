#ifndef APP2_H_INCLUDED
#define gInfoMsg(x, y) cout
#define U(x,y) cout

#endif // APP2_H_INCLUDED

const char *gNullMessageLog = " Null ";
const char *pfModuleClassName= " Null ";
const char *pfFunctionName= " Null ";

class BcmMessageLogSettings // : public BcmMessageLogSettings
{
public:

    // These are the severity levels associated with a message.
    typedef enum
    {
        // Need text describing when to use each of these.

        // Common severities for most purposes.
        kFatalErrorMessages =           0x00000001,
        kErrorMessages =                0x00000002,
        kWarningMessages =              0x00000004,
        kInitializationMessages =       0x00000008,
        kFunctionEntryExitMessages =    0x00000010,
        kInformationalMessages =        0x00000020,
    } SeverityBits;


};
