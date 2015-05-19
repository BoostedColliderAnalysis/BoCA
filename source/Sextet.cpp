# include "Sextet.hh"

void analysis::Sextet::Settriplet1(const Triplet &triplet) {
    triplet_1 = triplet;
}

void analysis::Sextet::Settriplet2(const Triplet &triplet) {
    triplet_2 = triplet;
}

analysis::Sextet::Sextet() {
  Print(kInformation, "Default Constructor");
}

analysis::Sextet::Sextet(const Triplet &triplet_1, const Triplet &triplet_2)
{
    Print(kInformation, "Constructor");
    Settriplet1(triplet_1);
    Settriplet2(triplet_2);
    SetBdt(triplet_1.Bdt(), triplet_2.Bdt());
    SetTag(triplet_1.Tag(), triplet_2.Tag());
}

analysis::Triplet analysis::Sextet::triplet1() const {
    return triplet_1;
}

analysis::Triplet analysis::Sextet::triplet2() const {
    return triplet_2;
}

