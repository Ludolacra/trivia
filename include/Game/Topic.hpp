#ifndef TOPIC_HPP_
#define TOPIC_HPP_

enum class Topic
{
    Pop = 0,
    Science,
    Sports,
    Rock
};

inline std::string to_string( const Topic topic )
{
#define CASE( X ) \
    case Topic::X: return #X
    switch( topic )
    {
        CASE( Pop );
        CASE( Science );
        CASE( Sports );
        CASE( Rock );
        default: throw std::runtime_error( "Unknown topic received!" );
    }
#undef CASE
};

#endif // TOPIC_HPP_
