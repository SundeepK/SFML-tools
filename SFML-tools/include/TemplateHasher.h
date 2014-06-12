#ifndef TEMPLATEHASHER_H
#define TEMPLATEHASHER_H


template <typename Key_type>
struct TemplateHasher : public std::unary_function<Key_type, std::size_t>
{
public:
    std::size_t operator()(const Key_type & t) const
    {
        size_t seed = 0;
        hash_combine(seed, t);
        return seed;
    }

    void hash_combine(std::size_t & seed, const Key_type & v) const
    {
        std::hash<Key_type> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};

#endif // TEMPLATEHASHER_H
