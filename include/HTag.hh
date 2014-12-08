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

    void SetTag(const int NewTag) {
        Tag = NewTag;
    }

    int GetTag() const {
        return Tag;
    }

protected:

    float Bdt;

    int Tag;

    virtual inline std::string ClassName() const {
        return "HTag";
    };

private:

};

#endif
