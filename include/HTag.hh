# ifndef HTag_hh
# define HTag_hh

# include "HObject.hh"

// namespace hanalysis{
// class HTagPrivate;
// }
class hanalysis::HTag : public HObject
{

public:

    HTag();

    ~HTag();

    void SetBdt(const float NewBdt);

    virtual float Bdt() const;

    void SetTag(const int NewTag);

    int Tag() const;

    template<typename HMultiplet>
    bool operator < (const HMultiplet& Multiplet) const {
      // largest bdt in front
      return (Bdt() > Multiplet.Bdt());
    }

protected:

//     float Bdt;

//     int Tag;

//     static const int InitialValue = -10;

    virtual inline std::string ClassName() const {
        return "HTag";
    };

    HTag(HTagPrivate &NewTagPrivate);

    HTagPrivate * TagPrivate;

private:

};

#endif
