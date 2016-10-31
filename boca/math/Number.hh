#pragma once

#include "boca/math/Math.hh"

template <typename Value_>
class Number
{

public:

    Number()
    {}

    Number(Value_ const &number) :
        number_(number)
    {}

    Number(Value_ const &number,  Value_ const &error) :
        number_(number),
        error_(error)
    {}

    Value_ &Value()
    {
        return number_;
    }

    Value_ &Error()
    {
        return error_;
    }

    Value_ Value() const
    {
        return number_;
    }

    Value_ Error() const
    {
        return error_;
    }

    Number &Round() {
        if(Error() > Value(0)) {
            Error() = RoundError(Error());
            Value() = RoundToError(Value(), Error());
        } else {
            Value() = RoundToDigits(Value());
        }
        return *this;
    }

    /**
     * @brief Output stream operator
     */
    friend auto &operator<<(std::ostream &stream, Number const &number)
    {
        stream << Stream(number.number_) << Stream(number.error_);
        return stream;
    }

private:

    Value_ number_ = Value_(0);

    Value_ error_ = Value_(0);

};
