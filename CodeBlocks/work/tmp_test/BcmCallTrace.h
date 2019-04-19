#ifndef ???_H_INCLUDED
#define ???_H_INCLUDED

class BcmCallTrace
{
public:
    BcmCallTrace(const char *pModuleClassName, const char *pFunctionName)
    {
        // Store these for use in the destructor.
        pfModuleClassName = pModuleClassName;
        pfFunctionName = pFunctionName;
    }

private:
    // Storage for the pointers passed in to the constructor.  Used in the
    // destructor.
    const char *pfModuleClassName;
    const char *pfFunctionName;
}

#define CallTrace(pModuleClassName, pFunctionName) \
        BcmCallTrace __callTraceInstance(pModuleClassName, pFunctionName)

#endif // ???_H_INCLUDED
