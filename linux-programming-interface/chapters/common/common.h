#define CHECK(x) if (!(x)) { \
    char[] error_buf = __FILE__ ":" __LINE__ " failure in " #x; \
    write(2, error_buf, sizeof(error_buf));                     \
    fsync(2);                                                   \
}
