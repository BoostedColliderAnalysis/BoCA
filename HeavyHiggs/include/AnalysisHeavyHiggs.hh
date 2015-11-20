#pragma once

#include "Analysis.hh"
#include "Vector.hh"
// #define DEBUG

namespace analysis
{

/**
 * @brief Namespace for the heavy higgs analyses
 *
 */

namespace heavyhiggs
{


enum class Process
{
    H0, Hbb, Htt, Htb, tt, tt2, tttt, tttb, ttwbb, ttwcc, Htwb, ttwwbb

};

enum class Collider
{
    LHC, FHC, LE
};

std::string Name(Collider collider);

std::string Name(Process process);

std::string NiceName(Process process);

/**
 *
 * @brief Analysis for heavy higgs
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisHeavyHiggs : public Analysis<Tagger>
{

  public:
    
    AnalysisHeavyHiggs(){
//       Info();
      DetectorGeometry::set_detector_type(DetectorType::CMS);
    }

    int Mass() const {
//       Info();
        //     return 300;
        //     return 400;
//                 return 500;
        //     return 600;
//             return 700;
//                     return 800;
        //     return 900;
                return 1000;
//       return 1500;
//                 return 2000;
//                    return 3000;
//         return 4000;
//                         return 5000;
//       return 6000;
//         return 7000;
//                 return 8000;
//                         return 10000;
//                         return 12000;
//                         return 15000;
//                        return 20000;
    };

    int PreCut() const {
//       Info();
        switch (collider_type()) {
        case Collider::LHC :
            switch (Mass()) {
            case 500 :
                return 0;
            case 1000 :
//                 return 250;
                return 0;
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
    
    int PreCutUse() const {
      //       Info();
      switch (PreCut()) {
        case 0:
          return 200;
        default :
          return 0;
      }
    };

    long EventNumberMax() const override {
//       Info();
        //            return 10000000;
        //                   return 1000000;
        //         return 100000;
        return 10000;
        //                 return 1000;
        //                         return 500;
        //                         return 10;
    };
    
    long ReaderNumberMax() const override {
//       Info();
       return EventNumberMax();
//        return  40000;
    }

    Collider collider_type() const {
//       Info();
        switch(DetectorGeometry::detector_type()){
          case DetectorType::CMS : return Collider::LHC;
          case DetectorType::Spp : return Collider::LE;
        }
    };

    float MissingEt() const {
//       Info();
        switch (collider_type()) {
        case Collider::LHC :
            return 30;
        case Collider::LE :
            return 60;
        default :
            return 0;
        }
    };

    float LeptonPt() const {
//       Info();
        switch (collider_type()) {
        case Collider::LHC :
            return 15;
        case Collider::LE :
            return 100;
        default :
            return 0;
        }
    };


    float SecondLeptonPt() const {
//       Info();
        switch (collider_type()) {
        case Collider::LHC :
            return 15;
        case Collider::LE :
            return 50;
        default :
            return 0;
        }
    };
    
    float VetoLeptonPt() const {
//       Info();
      switch (collider_type()) {
        case Collider::LHC :
          return 10;
        case Collider::LE :
          return 50;
        default :
          return 0;
      }
    };

    float BottomPt() const {
//       Info();
        switch (collider_type()) {
        case Collider::LHC :
            return 20;
        case Collider::LE :
            return 40;
        default :
            return 0;
        }
    };



    int FileNumber(Process process) const {
//       Info();
        switch (collider_type()) {
        case Collider::LHC :
            switch (process) {
            case  Process::ttwwbb :
                return 1;
            case  Process::ttwbb :
                return 1;
            case Process::tt:
                switch (PreCut()) {
                case 0:
                    return 127;
                case 250:
                    return 41;
                default :
                    return 1;
                }
            default :
                return 1;
            }
        case Collider::LE :
            switch (process) {
            case  Process::ttwwbb:
                return 2;
            case  Process::ttwbb:
                return 1;
            case Process::tt:
                switch (PreCut()) {
                case 0:
                    return 118;
                case 100:
                    return 15;
                case 300:
                    return 110;
                case 1000:
                    return 32;
                case 1500:
                    return 33;
                case 2000:
                    return 26;
                case 2500:
                    return 11;
                default :
                    return 1;
                }
            default :
                return 1;
            }
        default :
            return 1;
        }
    }

    std::string Suffix(Process process) const {
//       Info();
        switch (process) {
        case Process::Htt:
            return "_" + std::to_string(Mass()) + "GeV";
        case Process::Htwb:
            return "_" + std::to_string(Mass()) + "GeV";
        case Process::Hbb:
            return "_" + std::to_string(Mass()) + "GeV";
        case Process::tt:
            return "-" + std::to_string(PreCut()) + "GeV";
        case Process::ttwwbb:
            return "";
        case Process::ttwbb:
            return "";
        default:
            return "";
        }
    }

    virtual void NewFile(Tag tag, Process process) {
//       Info();
        analysis::AnalysisBase::NewFile(tag, FileNames(process, tag), NiceName(process));
    }

    virtual void NewFile(Tag tag, float crosssection, Process process) {
//       Info();
        analysis::AnalysisBase::NewFile(tag, FileNames(process, tag), crosssection, NiceName(process), Mass());
    }

    Strings FileNames(Process process, Tag tag) const {
//       Info();
        if (FileNumber(process) == 1) return {FileName(process, tag)};
        Strings names;
        for (const auto & file_number  : Range(FileNumber(process))) {
            if (file_number == 0) names.emplace_back(FileName(process, tag));
            else names.emplace_back(FileName(process, tag) + "_" + std::to_string(file_number));   
        }
        return names;
    }

    virtual std::string FileName(Process process, Tag tag) const {
//       Info();
        switch (tag) {
        case Tag::signal:
            return Name(process) + "-" + Name(collider_type()) + Suffix(process);
//                return Name(process) + Suffix(process) + "_" + Name(collider_type());

        case Tag::background:
            return Name(process) + "-" + Name(collider_type()) + Suffix(process);
//           return Name(process) + Suffix(process) + "_" + Name(collider_type());

        }
    }

private:

};

}

}
