# ifndef HTagPrivate_hh
# define HTagPrivate_hh

# include "HObject.hh"
# include "HTag.hh"

// namespace hanalysis{
//   class HTagPrivate;
// }

class hanalysis::HTagPrivate : public HObject
{

public:

    HTagPrivate();

    HTagPrivate(hanalysis::HTag *NewTag) : QTag(NewTag) {}

    ~HTagPrivate();

    hanalysis::HTag *QTag;

    float Bdt;

    int Tag;

    int InitialValue;

};

#endif
