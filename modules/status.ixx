/// @file status.ixx
/// @author Danylo Marchenko (cdanymar)
/// @brief Logging journal message statuses.
/// @version 1.0
/// @date 2024-08-17
/// @copyright Copyright (c) 2024
export module journal:status;

import std;
import ansi;

/// @brief Makes a new status.
/// @param Name C++ status name.
/// @param Text Status text in a report.
/// @param Level Importance level.
/// @param Style ANSI style.
#define MAKE_STATUS(Name, Text, Level, Style)                               \
struct Name final                                                           \
{                                                                           \
    Name() = delete;                                                        \
    static consteval auto getLabel() -> std::string_view { return Text; }   \
    static consteval auto getRequiredLevel() -> level { return Level; }     \
    static consteval auto getColor() -> decltype(Style) { return Style; }   \
}

/// @brief Logging journal utilities.
export namespace journal
{
    /// @brief Message statuses.
    inline namespace status
    {
        /// @brief Importance level.
        enum level
        {
            /// @brief Unimportant at all.
            none,

            /// @brief Critical importance, error reports.
            critical,

            /// @brief Essential system unexpectancies reports.
            essential,

            /// @brief Descriptive system status reports.
            descriptive,

            /// @brief Verbose system information reports.
            verbose,

            /// @brief Every single possible message.
            all,

            /// @brief No messages at all.
            min = none,

            /// @brief All possible messages.
            max = all
        };


        MAKE_STATUS(Text, "    ", all, ansi::manipulators::fg::regular);

        MAKE_STATUS(Info, "INFO", verbose, ansi::manipulators::fg::indigo);

        MAKE_STATUS(Good, "GOOD", descriptive, ansi::manipulators::fg::green);

        MAKE_STATUS(Warn, "WARN", essential, ansi::manipulators::fg::yellow);

        MAKE_STATUS(Fail, "FAIL", critical, ansi::manipulators::fg::red);

        MAKE_STATUS(Test, "TEST", all, ansi::manipulators::fg::magenta);

#ifdef _DEBUG
        MAKE_STATUS(Debug, "TEST", max, ansi::manipulators::bg::red);
#endif
    }


    /// @brief Journal status concept.
    /// @tparam T Static class.
    template <class T>
    concept journal_status = requires
    {
        { T::getLabel() } -> std::same_as<std::string_view>;
        { T::getRequiredLevel() } -> std::same_as<level>;
        { T::getColor() } -> std::same_as<const ansi::sgr>;
    };
}
