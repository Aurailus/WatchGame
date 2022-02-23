class EnsureException : public std::exception {
public:
    EnsureException(const string& message = ""): message(message) {}

    const char* what() const throw() {
        return message.data();
    }

private:
    string message;
};

template <typename E = EnsureException, typename C, std::enable_if_t<std::is_base_of_v<std::exception, E>, bool> = true>
void ensure(C condition, const string& message) {
    if (!condition) throw E(message);
}