#pragma once

#include "Analysis.hh"

namespace analysis {

/**
 * @brief Namespace for the heavy higgs analyses
 *
 */

namespace heavyhiggs {


enum class Process
{
    H0, Hbb, Htt, Htb, tt, tt2, tttt, tttb, ttwbb, ttwcc, Htwb, ttwwbb

};

enum class Collider {
    LHC, FHC, LE
};

std::string Name(const Collider collider);

std::string Name(const Process process);

std::string NiceName(const Process process);

/**
 *
 * @brief Analysis for heavy higgs
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisHeavyHiggs : public Analysis<Tagger> {

public:

    int Mass() const
    {
        //     return 300;
        //     return 400;
        //         return 500;
        //     return 600;
        //     return 700;
        //             return 800;
        //     return 900;
        //         return 1000;
//                 return 2000;
        //            return 3000;
        //         return 4000;
//                         return 5000;
                       return 7000;
        //         return 8000;
        //                 return 10000;
        //                 return 12000;
        //                 return 15000;
        //                return 20000;
    };

    int PreCut() const
    {
        switch (collider_type()) {
        case Collider::LHC :
            switch (Mass()) {
            case 500 :
                return 0;
            case 1000 :
                return 250;
            case 2000 :
                return 250;
            case 3000 :
                return 250;
            default :
                return 0;
            }
        case Collider::LE :
            switch (Mass()) {
            case 500 :
                return 0;
            case 1000 :
                return 300;
            case 2000 :
                return 300;
            case 4000 :
                return 1500;
            case 6000 :
                return 2500;
            case 10000 :
                return 2500;
            case 15000 :
                return 2500;
            case 20000 :
                return 2500;
            default :
                return 0;
            }
        default :
            return 0;
        }
    };

    long EventNumberMax() const override
    {
        //            return 10000000;
        //                   return 1000000;
        //         return 100000;
        return 10000;
        //                 return 1000;
        //                         return 500;
        //                         return 10;
    };

    Collider collider_type() const
    {
//         return Collider::LHC;
        //       return FHC;
        return Collider::LE;
    };

    float MissingEt() const
    {
        switch (collider_type()) {
        case Collider::LHC :
            return 30;
        case Collider::LE :
            return 60;
        default :
            return 0;
        }
    };

    float LeptonPt() const
    {
        switch (collider_type()) {
        case Collider::LHC :
            return 50;
        case Collider::LE :
            return 100;
        default :
            return 0;
        }
    };
    
    float BottomPt() const {
      switch (collider_type()) {
        case Collider::LHC :
          return 20;
        case Collider::LE :
          return 40;
        default :
          return 0;
      }
    };
    


    int FileNumber(const Process process) const
    {
        switch (collider_type()) {
        case Collider::LHC :
            switch (process) {
              case  Process::ttwwbb :
                return 1;
              case  Process::ttwbb :
                return 1;
            //                 return 1; // < this must be removed !!
            default :
                return 1;
            }
        case Collider::LE :
            switch (process) {
              case  Process::ttwwbb:
                return 2;
              case  Process::ttwbb:
                return 1;
            default :
                return 1;
            }
        default :
            return 1;
        }
    }
    
    std::string Suffix(const Process process) const{
      switch (process) {
        case Process::Htt:
          return "_" + std::to_string(Mass()) + "GeV";
        case Process::Htwb:
          return "_" + std::to_string(Mass()) + "GeV";
        case Process::ttwwbb:
          return "";
        case Process::ttwbb:
          return "";
        default:
          return "";
      }
    }

    virtual void NewFile(Tag tag, const Process process)
    {
        analysis::AnalysisBase::NewFile(tag, FileName(process, tag), NiceName(process));
    }

    virtual void NewFile(Tag tag, float crosssection, const Process process) {
      for(const auto& file_number : Range(FileNumber(process))) analysis::AnalysisBase::NewFile(tag, FileName(process, file_number, tag), crosssection, NiceName(process));      
    }

    virtual std::string FileName(const Process process, int file_number, Tag tag) const {
      switch(tag){
	case Tag::signal:
        return Name(process) + Suffix(process)+"_" + Name(collider_type());
        case Tag::background:
          if(file_number == 0) return Name(process) + Suffix(process)+"_" + Name(collider_type());
	  return Name(process) + Suffix(process)+"_" + Name(collider_type()) + "_" + std::to_string(file_number);
      }
    }
    
    virtual std::string FileName(const Process process, Tag tag) const {
      switch(tag){
        case Tag::signal:
          return Name(process) + Suffix(process)+"_" + Name(collider_type());
        case Tag::background:
          return Name(process) + Suffix(process)+"_" + Name(collider_type());

      }
    }

private:

};

}

}
