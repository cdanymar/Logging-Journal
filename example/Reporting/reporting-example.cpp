import journal;

using namespace journal::status;

namespace foo
{
    void bar()
    {
        journal::log<Text>("rock-a-bye Billy");
        journal::log<Info>("please don't you cry");
        journal::log<Good>("it's not your fault you have that strange eye");
        journal::log<Warn>("stay safe with Mommy");
        journal::log<Fail>("you'll never fall");
        journal::log<Test>("and we'll always love you, sharp angles and all");
    }
}

int main()
{
    foo::bar();
    return 0;
}
