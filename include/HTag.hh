# ifndef HTag_hh
# define HTag_hh

# include "HObject.hh"

class hanalysis::HTag : public HObject
{

public:

    HTag();

    ~HTag();

    void SetBdt(const float NewBdt) {
        Bdt = NewBdt;
    }

    virtual float GetBdt() const {
        return Bdt;
    }

    void SetTag(const bool NewTag) {
        Tag = NewTag;
    }

    bool GetTag() const {
        return Tag;
    }

protected:

    float Bdt;

    float Tag;

    virtual inline std::string ClassName() const {
        return "HTag";
    };

private:

};

#endif
