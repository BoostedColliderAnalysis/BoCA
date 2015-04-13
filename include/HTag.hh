# ifndef HTag_hh
# define HTag_hh

# include "HObject.hh"
// # include "d_ptr.h"

namespace hanalysis
{
class HTag;
class HTagPrivate;
}

class hanalysis::HTag : public HObject
{

public:

    HTag();

//     HTag(const HTag &NewTag);

//     HTag(HTag &&NewTag);

//     HTag& operator=(HTag NewTag); //note: pass by value and let compiler do the magics

    ~HTag();

    void SetBdt(const float NewBdt);

    void SetBdt(const float NewBdt1, const float NewBdt2);

    virtual float Bdt() const;

    void SetTag(const int NewTag);

    void SetTag(const int NewTag1, const int NewTag2);

    int Tag() const;

    void SetFlag(const bool NewFlag);

    void SetFlag(const bool NewFlag1, const bool NewFlag2);

    bool Flag() const;

    bool Degenerate() const {
        return degenerate_;
    }

    void SetDegenerate(const bool degenerate) {
        degenerate_ = degenerate;
    }

    void SetDegenerate() {
      degenerate_ = true;
    }

    void UnsetDegenerate() {
      degenerate_ = false;
    }

    int initial_value() const {
        return initial_value_;
    }

    template<typename HMultiplet>
    bool operator < (const HMultiplet &Multiplet) const {
        // largest bdt in front
        return (Bdt() > Multiplet.Bdt());
    }

protected:

    virtual inline std::string ClassName() const {
        return "HTag";
    };

//     HTag(HTagPrivate &NewTagPrivate);

//     class HTagPrivate;

//     HTagPrivate *TagPrivate;
//     d_ptr<HTagPrivate> d;
//     std::unique_ptr<HTagPrivate> TagPrivate;
//     std::shared_ptr<HTagPrivate> TagPrivate;

private:

    float bdt_;

    int tag_;

    int initial_value_;

    bool flag_;

    bool degenerate_;

};

#endif
