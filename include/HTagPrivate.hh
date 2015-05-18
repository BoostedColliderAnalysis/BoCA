# ifndef HTagPrivate_hh
# define HTagPrivate_hh

# include "Object.hh"
# include "Identification.hh"

// namespace hanalysis{
//   class HTagPrivate;
// }

class analysis::HTagPrivate : public Object
{

public:

    HTagPrivate();

    HTagPrivate(analysis::Identification *NewTag) : QTag(NewTag) {}

    ~HTagPrivate();

    analysis::Identification *QTag;

    float Bdt;

    int Tag;

    int InitialValue;

};

#endif
