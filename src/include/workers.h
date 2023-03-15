/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright (C) 2023 Perry Werneck <perry.werneck@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

 #pragma once
 #include <py3270.h>
 #include <lib3270/ipc/session.h>
 #include <lib3270/ipc/action.h>
 #include <string>

 DLL_PRIVATE PyObject * py3270_call(PyObject *self, const std::function<std::string (TN3270::Session &session)> &worker) noexcept;
 DLL_PRIVATE PyObject * py3270_call(PyObject *self, const std::function<int (TN3270::Session &session)> &worker) noexcept;
 DLL_PRIVATE PyObject * py3270_call(PyObject *self, const std::function<PyObject * (TN3270::Session &session)> &worker) noexcept;

 DLL_PRIVATE PyObject * py3270_call(PyObject *self, const std::function<PyObject * (TN3270::Action &action)> &worker) noexcept;


