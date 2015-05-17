# ifndef HTagPrivate_hh
# define HTagPrivate_hh

# include "Object.hh"
# include "HTag.hh"

// namespace hanalysis{
//   class HTagPrivate;
// }

class analysis::HTagPrivate : public Object
{

public:

    HTagPrivate();

    HTagPrivate(analysis::HTag *NewTag) : QTag(NewTag) {}

    ~HTagPrivate();

    analysis::HTag *QTag;

    float Bdt;

    int Tag;

    int InitialValue;

};

#endif
