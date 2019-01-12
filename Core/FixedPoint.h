#ifndef FIXED_POINT_H_
#define FIXED_POINT_H_

#include <stdint.h>

template <typename InternalType, typename LargeType, unsigned int FRACTIONAL_BITS>
class FixedPoint
{
        static_assert(FRACTIONAL_BITS != 0,                      "FRACTIONAL_BITS must be non-zero");
        static_assert(FRACTIONAL_BITS <= sizeof(InternalType)*8, "InternalType not large enough for required FRACTIONAL_BITS");
        static_assert(sizeof(LargeType) >= sizeof(InternalType), "LargeType must be at least as large as InternalType!");

    public:
        FixedPoint() :
            value()
        {
        }

        FixedPoint(const int8_t  i8) : value(static_cast<InternalType>(i8) << FRACTIONAL_BITS) {}
        FixedPoint(const uint8_t u8) : value(static_cast<InternalType>(u8) << FRACTIONAL_BITS) {}

        FixedPoint(const int16_t  i16) : value(static_cast<InternalType>(i16) << FRACTIONAL_BITS) {}
        FixedPoint(const uint16_t u16) : value(static_cast<InternalType>(u16) << FRACTIONAL_BITS) {}

        FixedPoint(const int32_t  i32) : value(static_cast<InternalType>(i32) << FRACTIONAL_BITS) {}
        FixedPoint(const uint32_t u32) : value(static_cast<InternalType>(u32) << FRACTIONAL_BITS) {}

        FixedPoint(const int64_t  i64) : value(static_cast<InternalType>(i64) << FRACTIONAL_BITS) {}
        FixedPoint(const uint64_t u64) : value(static_cast<InternalType>(u64) << FRACTIONAL_BITS) {}

        constexpr static const InternalType FACTOR = 1 << FRACTIONAL_BITS;

        FixedPoint(const double d) : value(static_cast<InternalType>(d * FACTOR)) {}
        FixedPoint(const float  f) : value(static_cast<InternalType>(f * FACTOR)) {}

        ~FixedPoint() = default;

        FixedPoint(const FixedPoint&) = default;
        FixedPoint(FixedPoint&&)      = default;

        FixedPoint& operator=(const FixedPoint&) = default;
        FixedPoint& operator=(FixedPoint&&)      = default;

        FixedPoint& operator+=(const FixedPoint& rhs)
        {
            value += rhs.value;
            return *this;
        }

        FixedPoint& operator-=(const FixedPoint& rhs)
        {
            value -= rhs.value;
            return *this;
        }

        FixedPoint& operator*=(const FixedPoint& rhs)
        {
            value = static_cast<InternalType>((static_cast<LargeType>(value) *
                                               static_cast<LargeType>(rhs.value)) >> FRACTIONAL_BITS);
            return *this;
        }

        FixedPoint& operator/=(const FixedPoint& rhs)
        {
            value = static_cast<InternalType>((static_cast<LargeType>(value) << FRACTIONAL_BITS) /
                                               static_cast<LargeType>(rhs.value));

            return *this;
        }

        friend bool operator<(const FixedPoint& lhs, const FixedPoint& rhs)
        {
            return lhs.value < rhs.value;
        }

        friend FixedPoint operator+(const FixedPoint& lhs, const FixedPoint& rhs)
        {
            return FixedPoint(ForcedValueType(lhs.value + rhs.value));
        }

        friend FixedPoint operator-(const FixedPoint& lhs, const FixedPoint& rhs)
        {
            return FixedPoint(ForcedValueType(lhs.value - rhs.value));
        }

        friend FixedPoint operator*(const FixedPoint& lhs, const FixedPoint& rhs)
        {
            return FixedPoint
                (ForcedValueType
                 (static_cast<InternalType>((static_cast<LargeType>(lhs.value) *
                                             static_cast<LargeType>(rhs.value)) >> FRACTIONAL_BITS)));
        }

        friend FixedPoint operator/(const FixedPoint& lhs, const FixedPoint& rhs)
        {
            return FixedPoint
                (ForcedValueType
                 (static_cast<InternalType>((static_cast<LargeType>(lhs.value) << FRACTIONAL_BITS) /
                                             static_cast<LargeType>(rhs.value))));
        }

        InternalType GetRaw() const
        {
            return value;
        }

        template <typename UserType>
        void Round(UserType& o_integer) const
        {
            const InternalType POINT_FIVE = 1 << (FRACTIONAL_BITS - 1);
            o_integer = static_cast<UserType>((value + POINT_FIVE) >> FRACTIONAL_BITS);
        }

        explicit operator int8_t()  const { return static_cast<int8_t> (value >> FRACTIONAL_BITS); }
        explicit operator int16_t() const { return static_cast<int16_t>(value >> FRACTIONAL_BITS); }
        explicit operator int32_t() const { return static_cast<int32_t>(value >> FRACTIONAL_BITS); }

        explicit operator uint8_t()  const { return static_cast<uint8_t> (value >> FRACTIONAL_BITS); }
        explicit operator uint16_t() const { return static_cast<uint16_t>(value >> FRACTIONAL_BITS); }
        explicit operator uint32_t() const { return static_cast<uint32_t>(value >> FRACTIONAL_BITS); }

    private:
        struct ForcedValueType
        {
            ForcedValueType(const InternalType& i_value) :
                value(i_value)
            {
            }

            InternalType value;
        };

        FixedPoint(const ForcedValueType& forcedValue) : value(forcedValue.value) {}

        InternalType value;
};

#endif
