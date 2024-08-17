/// @file journal.ixx
/// @author Danylo Marchenko (cdanymar)
/// @brief Logging journal utilities.
/// @version 1.0
/// @date 2024-08-17
/// @copyright Copyright (c) 2024
export module journal;

export import :status;

/// @brief Logging journal utilities.
export namespace journal
{
    /// @brief Global level of status messages importance.
    level importance = all;


    /// @brief Wrapper for journal entry with function signature.
    class journal_entry final
    {
        /// @brief Logs a journal entry.
        /// @tparam Args Format string arguments.
        template <journal_status, typename... Args>
        friend constexpr auto log(journal_entry, Args&&...) -> void;

    public:
        /// @brief Initializes new journal entry.
        /// @param message Logging message.
        /// @param location Call location.
        [[nodiscard]] constexpr journal_entry(const char* const message, const std::string_view location = nameof(__builtin_FUNCSIG()))
            : m_message(message), m_location(location)
        {
        }

        /// @brief Initializes new journal entry.
        /// @param message Logging message.
        /// @param location Call location.
        [[nodiscard]] constexpr journal_entry(const std::string& message, const std::string_view location = nameof(__builtin_FUNCSIG()))
            : m_message(message), m_location(location)
        {
        }

        /// @brief Initializes new journal entry.
        /// @param message Logging message.
        /// @param location Call location.
        [[nodiscard]] constexpr journal_entry(std::string_view&& message, const std::string_view location = nameof(__builtin_FUNCSIG()))
            : m_message(std::forward<std::string_view>(message)), m_location(location)
        {
        }

    private:
        /// Journal entry data.
        std::string_view m_message, m_location;


        /// @brief Strips function signature from the name.
        /// @param signature @c __builtin_FUNCSIG() return value to transform.
        /// @return Name of the function/method.
        [[nodiscard]] static constexpr auto nameof(std::string_view signature) -> std::string_view
        {
            std::size_t pos = signature.find('(');

            signature = signature.substr(0, pos);
            pos = signature.rfind(' ');

            return signature.substr(pos + 1);
        }
    };


    /// @brief Logs a journal entry.
    /// @tparam Status Message status (importance).
    /// @tparam Args Format string arguments.
    /// @param message Message to log.
    /// @param args Format string values.
    template <journal_status Status = Text, typename... Args>
    constexpr auto log(const journal_entry message, Args&&... args) -> void
    {
        using namespace ansi::manipulators;
        using namespace std::chrono;

        static std::ofstream file(std::format(R"(logs\{:%Y-%m-%d}.log)", system_clock::now()), std::ios_base::app);

        if (Status::getRequiredLevel() > importance)
            return;

        const time_point now = floor<seconds>(current_zone()->to_local(system_clock::now()));

        ansi::print<fg::bright::black>("{:%Y-%m-%d %H:%M:%S} ", now);
        ansi::print<Status::getColor(), text::bold>(Status::getLabel());
        ansi::print<fg::bright::white>(" {:.<32}: ", message.m_location);
        ansi::println(message.m_message, std::forward<Args>(args)...);

        ansi::print(file, "{:%Y-%m-%d %H:%M:%S} ", now);
        ansi::print(file, Status::getLabel());
        ansi::print(file, " {:.<32}: ", message.m_location);
        ansi::println(file, message.m_message, std::forward<Args>(args)...);
    }
}
