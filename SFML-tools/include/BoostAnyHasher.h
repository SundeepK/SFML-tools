#ifndef BOOSTANYHASHER_H_
#define BOOSTANYHASHER_H_

#include <boost/any.hpp>

struct BoostAnyHasher : public std::unary_function<boost::any, std::size_t>
{
public:
    std::size_t operator()(const boost::any & t) const
    {
        size_t seed = 0;
        hash_combine(seed, t);
        return seed;
    }

    void hash_combine(std::size_t & seed, const boost::any & v) const
    {
        seed ^= (size_t(&v)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};


#endif /* BOOSTANYHASHER_H_ */
