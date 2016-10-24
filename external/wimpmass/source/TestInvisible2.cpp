
#include <fstream>
#include <gtest/gtest.h>

#include "boca/generic/Vector.hh"
#include "external/wimpmass/wimpmass/Invisible2.hh"

namespace wimpmass
{

using namespace boca::units;

class TestInvisible22 :  public Invisible22
{

public :

    TestInvisible22() : Invisible22(massless,  massless,  massless) {};

    struct event22 {
        double p3[4], p4[4], p5[4], p6[4];
        double pmiss[4];
    };

    inline void solve22(event22 &evt, double mn, double mx, double my, int &nsols, double p1[][4], double p2[][4]);

    inline void Momentum(double momentum[4], boca::LorentzVector<boca::Momentum> const &vector);

    inline boca::LorentzVector<boca::Momentum> Vector(double momentum[4]);

};

void TestInvisible22::solve22(event22 &evt, double mn, double mx, double my, int &nsols, double p1[][4], double p2[][4])
{
    SetFirstChain(Vector(evt.p3), Vector(evt.p5));
    SetSecondChain(Vector(evt.p4), Vector(evt.p6));
    SetMissingMomentum(Vector(evt.pmiss));
    SetMasses(my * GeV, mx * GeV, mn * GeV);
    auto sols = Solve();
    nsols = sols.size();
    for (auto sol : boca::IntegerRange(sols.size())) {
        Momentum(p1[sol], sols[sol].first);
        Momentum(p2[sol], sols[sol].second);
    }
}

boca::LorentzVector<boca::Momentum> TestInvisible22::Vector(double momentum[4])
{
    boca::LorentzVector<boca::Momentum> vector;
    vector.E() = momentum[0] * GeV;
    vector.Px() = momentum[1] * GeV;
    vector.Py() = momentum[2] * GeV;
    vector.Pz() = momentum[3] * GeV;
    return vector;
}

void TestInvisible22::Momentum(double momentum[4], const boca::LorentzVector<boca::Momentum> &vector)
{
    momentum[0] = vector.E() / GeV;
    momentum[1] = vector.Px() / GeV;
    momentum[2] = vector.Py() / GeV;
    momentum[3] = vector.Pz() / GeV;
}

}

auto ReadDataFile()
{
    std::ifstream datafile("sqsq_pythia_events.lhe");
    std::array<wimpmass::TestInvisible22::event22, 3> events;
    for (auto &event : events) {
        //find the line containing <event>
        bool found = false;
        std::string line;
        while (found == false) {
            std::getline(datafile, line);
            if (datafile.eof()) break;
            if (line.find("<event>") != std::string::npos) found = true;
        }
        if (datafile.eof()) break;

        //read the first line of an event
        int npar, itemp;
        double dtemp1, dtemp2, dtemp3, dtemp4;
        datafile >> npar >> itemp >> dtemp1 >> dtemp2 >> dtemp3 >> dtemp4;

        //read npar lines
        int nlep = 0;
        for (auto j :  boca::IntegerRange(npar)) {
            int ic1, ic2, ic3, ic4, ic5, ic6;
            double ic7;
            std::array<double, 6> p;
            datafile >> ic1 >> ic6 >> ic2 >> ic3 >> ic4 >> ic5 >> p[1] >> p[2] >> p[3] >> p[0] >> p[4] >> p[5] >> ic7;
            p[0] = sqrt(p[1] * p[1] + p[2] * p[2] + p[3] * p[3] + p[4] * p[4]);
            //read the momenta of the four leptons
            if (std::abs(ic1) == 11 || std::abs(ic1) == 13) {
                switch (nlep) {
                case 0 :
                    for (auto i : boca::IntegerRange(4)) event.p5[i] = p[i];
                    break;
                case 1 :
                    for (auto i : boca::IntegerRange(4)) event.p3[i] = p[i];
                    break;
                case 2 :
                    for (auto i : boca::IntegerRange(4)) event.p6[i] = p[i];
                    break;
                case 3 :
                    for (auto i : boca::IntegerRange(4)) event.p4[i] = p[i];
                    break;
                default :
                    break;
                }
                ++nlep;
            }
            //read missing momentum
            if (std::abs(ic1) == 12) for (auto i : boca::IntegerRange(4)) event.pmiss[i] = p[i];
        }
    }
    datafile.close();
    return events;
}

TEST(Wimpmass, Invisible2)
{
    auto events = ReadDataFile();

    using Momentum = std::array<float, 4>;
    using Momenta = std::array<Momentum, 2>;
    using Solutions = std::array<Momenta, 2>;
    std::array<Solutions, 3> results;

    Solutions solutions;
    {
        {
            auto momentum1 = Momentum {{134.70704, -32.048583, 9.6606075, -83.309111}};
            auto momentum2 = Momentum {{622.30009, -110.44245, -207.11309, -567.51995}};
            Momenta momenta {{momentum1, momentum2}};
            solutions.at(0) = momenta;
        }
        {
            auto momentum1 = Momentum {{134.30854, -36.861854, 8.4747212, -80.76526}};
            auto momentum2 = Momentum {{696.21101, -105.62918, -205.9272, -648.8922}};
            Momenta momenta {{momentum1, momentum2}};
            solutions.at(1) = momenta;
        }
        results.at(0) = solutions;
        {
            auto momentum1 = Momentum {{194.13307, 129.51206, 9.2983923, 103.64688}};
            auto momentum2 = Momentum {{1730.5181, -429.40022, 108.68985, 1669.8532}};
            Momenta momenta {{momentum1, momentum2}};
            solutions.at(0) = momenta;
        }
        {
            auto momentum1 = Momentum {{195.69957, 130.37358, 9.5577866, 105.47303}};
            auto momentum2 = Momentum {{1743.9175, -430.26174, 108.43045, 1683.5322}};
            Momenta momenta {{momentum1, momentum2}};
            solutions.at(1) = momenta;
        }
        results.at(1) = solutions;
        {
            auto momentum1 = Momentum {{309.9882, 124.83235, -259.05223, -57.587915}};
            auto momentum2 = Momentum {{180.95836, 39.251808, 137.57608, -46.828469}};
            Momenta momenta {{momentum1, momentum2}};
            solutions.at(0) = momenta;
        }
        {
            auto momentum1 = Momentum {{320.71777, 123.6285, -271.53291, -61.323945}};
            auto momentum2 = Momentum {{189.80549, 40.455662, 150.05676, -42.276429}};
            Momenta momenta {{momentum1, momentum2}};
            solutions.at(1) = momenta;
        }
        results.at(2) = solutions;
    }

    for (auto &event :  events) {
        auto pos = boca::Position(events,  event);
        wimpmass::TestInvisible22 inv;
        int nsols;
        double p1[4][4], p2[4][4];
        inv.solve22(event, 100.42479, 143.70998, 181.23681, nsols, p1, p2);
        ASSERT_EQ(nsols,  2);
        for (auto isol : boca::IntegerRange(nsols)) {
            for (auto i : boca::IntegerRange(4)) {
                ASSERT_FLOAT_EQ(p1[isol][i], results[pos][isol][0][i]);
                ASSERT_FLOAT_EQ(p2[isol][i], results[pos][isol][1][i]);
            }
        }
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
