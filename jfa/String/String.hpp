#ifndef STRING_HPP
#define STRING_HPP

namespace JFA
{
    class String
    {
    private:
        char *str;

    public:
        String();
        String(const char *str);
        String(const String &str);
        ~String();
        String substring(int start, int end);
        String replace(const char *search, const char *replace);
        String replaceAll(const char *search, const char *replace);
        String operator+(String str);
        String operator+(char character);
        String &operator=(const String &other);
        char operator[](int index);
        char operator[](int index) const;
        char operator==(const char *str);
        char operator==(String str);
        const char *toCharArray();
        int length();
        int length() const;
        int indexOf(const char *search);
        bool equals(String str);
        void print();
    };
}

#endif // STRING_HPP