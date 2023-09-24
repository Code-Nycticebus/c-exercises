#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#if !defined(T) 
#warning "Why the fuck is 'T' not defined? did you not read the docs?"
#define T int
#endif

#define UNUSED __attribute__((unused)) 

#define _CONCAT(A, B) A##B
#define CONCAT(A,B) _CONCAT(A, B)

#define _STR(A) #A
#define STR(A) _STR(A)


#define Option(T) CONCAT(Option_, T)
#define OptionPtr(T) CONCAT(OptionPtr_, T)

typedef struct { T _value; bool some;} Option(T);
typedef struct { T* _value; } OptionPtr(T);

#define Some(T, value) ((Option(T)){._value=value, .some=true})
#define SomePtr(T, value) ((OptionPtr(T)){._value=value})
#define None(T) ((Option(T)){.some=false})
#define NonePtr(T) ((OptionPtr(T)){._value=NULL})

#define Unwrap(T, O) CONCAT(Option(T), _unwrap(O, __FILE__, __LINE__))
#define UnwrapPtr(T, O) CONCAT(OptionPtr(T), _unwrap(O, __FILE__, __LINE__))

#define Expect(T, O, MSG) CONCAT(Option(T), _expect(O, MSG, __FILE__, __LINE__))
#define ExpectPtr(T, O, MSG) CONCAT(OptionPtr(T), _expect(O, MSG, __FILE__, __LINE__))

UNUSED static T CONCAT(Option(T), _unwrap)(Option(T) o, const char* file, int line) {
    if (o.some) {
        return o._value;
    }
    fprintf(stderr, "Unwrap of 'Option(%s%s)' failed on line: %s:%d\n", STR(T), STR(PTR), file, line);
    abort();
    return (T ){0};
}

UNUSED static T* CONCAT(OptionPtr(T), _unwrap)(OptionPtr(T) o, const char* file, int line) {
    if (o._value != NULL) {
        return o._value;
    }
    fprintf(stderr, "Unwrap of 'Option(%s%s)' failed on line: %s:%d\n", STR(T), STR(PTR), file, line);
    abort();
    return (T*){0};
}

UNUSED static T CONCAT(Option(T), _expect)(Option(T) o, const char* msg, const char* file, int line)  {
    if (o.some) {
        return o._value;
    }
    fprintf(stderr, "Unwrap of 'Option(%s%s)' failed on line: %s:%d: %s\n", STR(T), STR(PTR), file, line, msg);
    abort();
    return (T){0};
}

UNUSED static T* CONCAT(OptionPtr(T), _expect)(OptionPtr(T) o, const char* msg, const char* file, int line)  {
    if (o._value != NULL) {
        return o._value;
    }
    fprintf(stderr, "Unwrap of 'Option(%s%s)' failed on line: %s:%d: %s\n", STR(T), STR(PTR), file, line, msg);
    abort();
    return (T*){0};
}


#undef T


