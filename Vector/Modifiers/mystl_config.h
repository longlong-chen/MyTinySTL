#define MYSTL_TRY try
#define MYSTL_UNWIND(action) catch(...) {action; throw; }