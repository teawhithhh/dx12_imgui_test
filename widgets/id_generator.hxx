#ifndef ID_GENERATOR
#define ID_GENERATOR
class IdGenerator {
public:
    static int GenerateId();
private:
    static int g_idCounter_;
};
#endif
