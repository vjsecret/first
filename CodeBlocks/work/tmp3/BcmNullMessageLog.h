#ifndef BCMNULLMESSAGELOG_INCLUDED
class BcmNullMessageLog
{
public:
        BcmNullMessageLog(void);
        virtual ~BcmNullMessageLog();
        bool IsFeatureEnabled(int a);
        typedef enum
        {
            kRsvp       = 0x00000001, // US/DS; IP 46
            kFtp        = 0x00000002, // US/DS; TCP 21
        }NatAlgMask;
};

BcmNullMessageLog::BcmNullMessageLog()
{
    printf("========START======\n");
    //<< "========START======\n"<< endl;
}
BcmNullMessageLog::~BcmNullMessageLog()
{
    printf("========END======\n");
    //<< "========END======\n"<< endl;
}

bool BcmNullMessageLog::IsFeatureEnabled(int)
{
    return 2;
}

#endif // BcmNullMessageLog_INCLUDED
