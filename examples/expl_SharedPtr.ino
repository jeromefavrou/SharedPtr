
#include <SharedPtr.hpp>

class Foo
{
    public:

        Foo(void)
        {
            Serial.println("foo constructor");
        }

        ~Foo(void)
        {
            Serial.println("foo destructor");
        }
};


class Bar
{
    private:
        SharedPtr<Foo> m_foo;
    public:
        Bar(SharedPtr<Foo> & _foo):m_foo(_foo)
        {
            Serial.println("bar constructor");
        }

        ~Bar(void)
        {
            Serial.println("bar destructor");
        }
};



void setup()
{
    Serial.begin(9600);

    SharedPtr<Foo> test = SharedPtr<Foo>(Foo());

    Serial.println(test.getCount());

    if(true)
    {
        Bar expl(test);

        Serial.println(test.getCount());
    }

    Serial.println(test.getCount());

}

void loop()
{

}