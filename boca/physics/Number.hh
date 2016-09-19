#pragma once

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

private:

    Value_ number_ = Value_(0);

    Value_ error_ = Value_(0);

};
