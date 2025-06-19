#pragma once

enum class StatusCode {
    SUCCESS = 0,
    GENERIC_ERROR,
    WINAPI_ERROR,
    UNKOWN

};

#define NO_DISCARD [[nodiscard]]

#define UNUSED(x) x [[maybe_unused]]

#define CATCH_ALL() catch (WinApiException& exception) { \
        DebugHelper::show_debug_message(exception.get_message());\
        \
        return static_cast<int>(StatusCode::WINAPI_ERROR);\
    }\
    catch (GenericException& exception) { \
        DebugHelper::show_debug_message(exception.get_message());\
        \
        return static_cast<int>(StatusCode::GENERIC_ERROR);\
    }\
    catch (...) {\
        DebugHelper::show_debug_message(L"UNKWON EXCEPTION!");\
        \
        return static_cast<int>(StatusCode::UNKOWN);\
    }

