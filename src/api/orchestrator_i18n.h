#pragma once
#include <godot_cpp/classes/translation_server.hpp>

inline godot::String orchestrator_tr(const godot::String &p_message, const godot::StringName &p_context = "") {
    godot::TranslationServer *ts = godot::TranslationServer::get_singleton();
    if (!ts) {
        return p_message;
    }
    // 指定外掛的 Domain 進行翻譯
    return ts->translate(p_message, p_context, "godot_orchestrator");
}

// 供 C++ 原始碼呼叫的巨集
#define OTR(m_text) orchestrator_tr(m_text)