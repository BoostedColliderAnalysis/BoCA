#pragma once

#include "Analysis.hh"

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
    H0, Hbb, Htb, tt, tt2
};

enum class Collider
{
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
class AnalysisHeavyHiggs : public Analysis<Tagger>
{

public:

  AnalysisHeavyHiggs() {
    this->tagger().set_analysis_name(ProjectName());
  }

    std::string ProjectName() const {
        //        return  ProcessName() + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV-Eta2.5";
        return  this->ProcessName() + "-" + Name(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV";
    };

    int Mass() const {
        //     return 300;
        //     return 400;
        //         return 500;
        //     return 600;
        //     return 700;
        //             return 800;
        //     return 900;
        //         return 1000;
        return 2000;
        //            return 3000;
        //         return 4000;
        //                 return 5000;
        //                return 6000;
        //             return 7000;
        //         return 8000;
        //             return 9000;
        //                 return 10000;
        //                 return 12000;
        //                 return 15000;
        //                return 20000;
    };

    int PreCut() const {
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

    int EventNumberMax() const {
        //            return 10000000;
        //                   return 1000000;
        //         return 100000;
        return 10000;
        //                 return 1000;
        //                         return 500;
        //                         return 10;
    };;

    Collider collider_type() const {
        return Collider::LHC;
        //       return FHC;
        //        return LE;
    };

    float MissingEt() {
        switch (collider_type()) {
        case Collider::LHC :
            return 30;
        case Collider::LE :
            return 60;
        default :
            return 0;
        }
    };

    float LeptonPt() {
        switch (collider_type()) {
        case Collider::LHC :
            return 50;
        case Collider::LE :
            return 100;
        default :
            return 0;
        }
    };

    float BackgroundCrosssection(const Process process) const {
        switch (collider_type()) {
        case Collider::LHC :
            switch (PreCut()) {
            case 0 :
                return 97.54 * 2 * 1000;
            case 250 :
                return 5.698 * 2 * 1000;
            default :
                std::cout << "unhandled case" << std::endl;
                return 1;
            }
        case Collider::LE:
            switch (PreCut()) {
            case 0 :
              return 3564 * 2 * 1000;
            case 300 :
              return 178.1 * 2 * 1000;
            case 1000 :
                return 1.532 * 2 * 1000;
            case 1500 :
                return 0.2447 * 2 * 1000;
            case 2000 :
                return 0.09014 * 2 * 1000;
            case 2500 :
              return 0.0222 * 2 * 1000;
            default:
                std::cout << "unhandled case" << std::endl;
                return 1;
            }
        }
    }

    int BackgroundFileNumber() const
    {
      switch (collider_type()) {
        case Collider::LHC :
          switch (PreCut()) {
            case  0 :
              return 127;
            case  250 :
              return 41;
              //                 return 1; // < this must be removed !!
            default :
              return 1;
          }
            case Collider::LE :
              switch (PreCut()) {
                case  0 :
                  return 118;
                  //                 return 1; // < this must be removed !!
                case  100 :
                  return 15;
                case  250 :
                  return 15;
                case  300 :
                  return 110;
                  //                 return 1; // < this must be removed !!
                case  1000 :
                  return 32;
                case  1500 :
                  return 34;
                case  2000 :
                  return 26;
                case  2500 :
                  return 11;
                default :
                  return 1;
              }
                default :
                  return 1;
      }
    }

    virtual void NewFile(const Tag tag, const Process process) {
      analysis::AnalysisBase::NewFile(tag, FileName(process), NiceName(process));
    }

    virtual std::string FileName(const Process process) const {
      return Name(process) + "_" + std::to_string(PreCut()) + "GeV";
    }

private:

};

}

}
