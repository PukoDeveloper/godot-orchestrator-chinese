// This file is part of the Godot Orchestrator project.
//
// Copyright (c) 2023-present Crater Crash Studios LLC and its contributors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//Modifications Copyright (c) 2026 PukoDeveloper.
//This file has been modified by PukoDeveloper on 2026-8-30.
//
#pragma once

#include <godot_cpp/classes/translation_domain.hpp>

#include "common/version.h"
#include <godot_cpp/classes/translation_server.hpp>

#define OACCEL_KEY(mask,key) (Key(static_cast<int>(mask) | static_cast<int>(key)))

#define OCONNECT(obj, signal, method)               \
        if (!obj->is_connected(signal, method)) {   \
            obj->connect(signal, method);           \
        }

#define ODISCONNECT(obj, signal, method)            \
        if (obj->is_connected(signal, method)) {    \
            obj->disconnect(signal, method);        \
        }

#define BEGIN_NOTIFICATION_HANDLER(x)               \
    switch(x) {

#define NOTIFICATION_HANDLER(code, method)          \
    case code: method(); break;

#define END_NOTIFICATION_HANDLER                    \
    default: break;                                 \
    }

#define BEGIN_NOTIFICATION_HANDLER_WITH_PARENT(x)   \
    GDE_NOTIFICATION(x)                             \
    BEGIN_NOTIFICATION_HANDLER

#define CAST_INT_TO_ENUM(t, x) static_cast<t>(static_cast<int>(x))

#define EI godot::EditorInterface::get_singleton()
#define EDSCALE EI->get_editor_scale()
#define EditorNode get_tree()->get_root()->get_child(0)
#define EDITOR_GET(x) EI->get_editor_settings()->get(x)
#define PROJECT_GET(x,y,z) EI->get_editor_settings()->get_project_metadata(x,y,z)
#define PROJECT_SET(x,y,z) EI->get_editor_settings()->set_project_metadata(x,y,z)
#define EDITOR_GET_ENUM(t, x) static_cast<t>(static_cast<int>(EDITOR_GET(x)))

// Taken from control.h
#define SET_DRAG_FORWARDING_GCD(from, to)                                           \
    from->set_drag_forwarding(callable_mp(this, &to::get_drag_data_fw).bind(from),  \
    callable_mp(this, &to::can_drop_data_fw).bind(from),                            \
    callable_mp(this, &to::drop_data_fw).bind(from));

#define GUARD_NULL(x) if (!(x)) return;

#define SAFE_MEMDELETE(obj) { memdelete(obj); obj = nullptr; }

#define SAFE_REMOVE_CHILDREN(obj)                                       \
    for (int i = obj->get_child_count() - 1; i >= 0; i--) {             \
        Node* child = obj->get_child(i);                                \
        obj->remove_child(child);                                       \
        child->queue_free();                                            \
    }

#define callable_mp_parent(method) callable_mp(static_cast<parent_type*>(this), &parent_type::method)
#define callable_mp_this(method) callable_mp(this, &self_type::method)
#define callable_mp_this_parent(method) callable_mp(this, &parent_type::method)
#define callable_mp_cast(obj, type, method) callable_mp(static_cast<type*>(obj), &type::method)

// Takes the {@code evt} and propagates the event from {@code source} to {@code target}.
#define push_and_accept_event(evt, source, target)  \
    (target)->grab_focus();                         \
    (target)->get_viewport()->push_input(evt);      \
    (source)->accept_event();                       \
    (source)->grab_focus();

#define push_event(evt, source, target)             \
    (target)->grab_focus();                         \
    (target)->get_viewport()->push_input(evt);      \
    (source)->grab_focus();

#define SNAME(x) StringName((x))


/*inline godot::String orchestrator_tr(const godot::String &p_message, const godot::StringName &p_context = "") {
    godot::TranslationServer *ts = godot::TranslationServer::get_singleton();
    if (!ts) {
        return p_message;
    }
    // 指定外掛的 Domain 進行翻譯
    Ref<TranslationDomain> domain = ts->get_or_add_domain("godot_orchestrator");
    if (domain.is_valid()) {
        return domain->translate(p_message, p_context);
    }
    return ts->translate(p_message, p_context);
}

// 供 C++ 原始碼呼叫的巨集
#define OTR(m_text) orchestrator_tr(m_text)
*/

namespace orchestrator {

inline godot::String orchestrator_tr(const godot::String &p_message, const godot::StringName &p_context = "") {
    godot::TranslationServer *ts = godot::TranslationServer::get_singleton();
    if (!ts) {
        return p_message;
    }

    // 取得插件專屬的 TranslationDomain
    godot::Ref<godot::TranslationDomain> domain = ts->get_or_add_domain("godot_orchestrator");
    if (domain.is_valid()) {
        return domain->translate(p_message, p_context);
    }

    return ts->translate(p_message, p_context);
}

inline godot::String orchestrator_tr_n(const godot::String &p_message, const godot::String &p_message_plural, int p_n, const godot::StringName &p_context = "") {
    godot::TranslationServer *ts = godot::TranslationServer::get_singleton();
    if (!ts) {
        return p_n == 1 ? p_message : p_message_plural;
    }

    godot::Ref<godot::TranslationDomain> domain = ts->get_or_add_domain("godot_orchestrator");
    if (domain.is_valid()) {
        return domain->translate_plural(p_message, p_message_plural, p_n, p_context);
    }

    return ts->translate_plural(p_message, p_message_plural, p_n, p_context);
}

} // namespace orchestrator

// 全域巨集定義（方便在所有 C++ 原始碼中直接呼叫）
#define OTR(m_text) orchestrator::orchestrator_tr(m_text)
#define OTRC(m_text, m_context) orchestrator::orchestrator_tr(m_text, m_context)
#define OTRN(m_singular, m_plural, m_count) orchestrator::orchestrator_tr_n(m_singular, m_plural, m_count)
