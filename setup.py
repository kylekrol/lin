# Based off of https://github.com/pybind/python_example

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

import os
import setuptools
import sys

__version__ = '0.0.1'


class get_pybind_include(object):

    def __str__(self):
        import pybind11
        return pybind11.get_include()


ext_modules = [
    Extension(
        'lin',
        ['lin.cpp'],
        include_dirs=[
            get_pybind_include(),
            'include'
        ],
        language='c++'
    ),
]


def has_flag(compiler, flagname):
    import tempfile
    import os

    with tempfile.NamedTemporaryFile('w', suffix='.cpp', delete=False) as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        fname = f.name

    try:
        compiler.compile([fname], extra_postargs=[flagname])
    except setuptools.distutils.errors.CompileError:
        return False
    finally:
        try:
            os.remove(fname)
        except OSError:
            pass

    return True


def cpp_flag(compiler):
    for flag in ['-std=c++17', '-std=c++14']:
        if has_flag(compiler, flag):
            return flag

    raise RuntimeError('Unsupported compiler -- at least C++14 support is needed!')


class BuildExt(build_ext):
    c_opts = {
        'msvc': ['/EHsc'],
        'unix': [],
    }
    l_opts = {
        'msvc': [],
        'unix': [],
    }

    if sys.platform == 'darwin':
        darwin_opts = ['-stdlib=libc++', '-mmacosx-version-min=10.7']
        c_opts['unix'] += darwin_opts
        l_opts['unix'] += darwin_opts

    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = self.c_opts.get(ct, [])
        link_opts = self.l_opts.get(ct, [])
        if ct == 'unix':
            opts.append(cpp_flag(self.compiler))
            if has_flag(self.compiler, '-fvisibility=hidden'):
                opts.append('-fvisibility=hidden')
            if has_flag(self.compiler, '-Werror'):
                opts.append('-Werror')

        for ext in self.extensions:
            ext.define_macros = [('VERSION_INFO', '"{}"'.format(self.distribution.get_version()))]
            ext.extra_compile_args = opts
            ext.extra_link_args = link_opts
        build_ext.build_extensions(self)


_SQR = 6
_ALL = 4


def autocode():

    # Helper functions for cxx type names
    def __cxx_vector(rows):
        return f'lin::Vectord<{rows}>'
    def __cxx_row_vector(columns):
        return f'lin::RowVectord<{columns}>'
    def __cxx_matrix(rows, columns):
        return f'lin::Matrixd<{rows}, {columns}>'

    # Helper functions for python names
    def __py_vector(rows):
        return f'Vector{rows}'
    def __py_row_vector(columns):
        return f'RowVector{columns}'
    def __py_matrix(rows, columns):
        return f'Matrix{rows}x{columns}'

    # Helper functions to autogenerate code
    def __gen_class(cxx_class, py_class):
        return \
            f'py::class_<{cxx_class}> {py_class}(m, "{py_class}", py::buffer_protocol());\n' + \
            f'{py_class}.def(py::init<>());\n' + \
            f'{py_class}.def("__init__", []({cxx_class} &self, py::array_t<double> arr) -> void ' + '{\n' + \
            '  py::buffer_info info = arr.request();\n' + \
            '  if (info.format != py::format_descriptor<double>::format()) throw std::runtime_error("Incompatible format - expected a double array!");\n' + \
            '  if (info.ndim == 2) {\n' + \
            '    if (info.shape[0] != (long) self.rows()) throw std::runtime_error("Invalid buffer shape - wrong row count!");\n' + \
            '    if (info.shape[1] != (long) self.cols()) throw std::runtime_error("Invalid buffer shape - wrong column count!");\n' + \
            '    for (lin::size_t i = 0; i < self.rows(); i++)\n' + \
            '      for (lin::size_t j = 0; j < self.cols(); j++)\n' + \
            '        self(i, j) = *((double *)(((char *) info.ptr) + i * info.strides[0] + j * info.strides[1]));\n' + \
            '  } else if (info.ndim == 1) {\n' + \
            '    if (info.shape[0] != (long) self.size()) throw std::runtime_error("Invalid buffer shape - wrong size count!");\n' + \
            '    for (lin::size_t i = 0; i < self.size(); i++)\n' + \
            '      self(i) = *((double *)(((char *) info.ptr) + i * info.strides[0]));\n' + \
            '  } else { throw std::runtime_error("Incompatible buffer dimensions - expected one or two dimensions!"); }\n' + \
            '});\n' + \
            f'{py_class}.def_static("nans", []() -> {cxx_class} * ' + '{ ' + f'return new {cxx_class}(lin::nans<{cxx_class}>());' +' });\n' + \
            f'{py_class}.def_static("ones", []() -> {cxx_class} * ' + '{ ' + f'return new {cxx_class}(lin::ones<{cxx_class}>());' +' });\n' + \
            f'{py_class}.def_static("zeros", []() -> {cxx_class} * ' + '{ ' + f'return new {cxx_class}(lin::zeros<{cxx_class}>());' +' });\n' + \
            f'{py_class}.def_buffer([]({cxx_class} &self) -> py::buffer_info ' + '{\n' + \
            f'  if (lin::internal::is_col_vector<{cxx_class}>())\n' + \
            '    return py::buffer_info{ self.data(), sizeof(double), py::format_descriptor<double>::format(), 1, {self.rows()}, {sizeof(double)} };\n' + \
            '  else\n' + \
            '    return py::buffer_info{ self.data(), sizeof(double), py::format_descriptor<double>::format(), 2, {self.rows(), self.cols()}, {self.cols() * sizeof(double), sizeof(double)} };\n' + \
            '});\n' + \
            f'{py_class}.def("__repr__", []({cxx_class} const &self) -> std::string ' + '{\n' + \
            f'  std::stringstream ss; ss << "{py_class}";\n' + \
            '  for (lin::size_t i = 0; i < self.rows(); i++) {\n' + \
            '    ss << "\\n";\n' + \
            '    for (lin::size_t j = 0; j < self.cols() - 1; j++)\n' + \
            '      ss << self(i, j) << ", ";\n' + \
            '    ss << self(i, self.cols() - 1);\n' + \
            '  }\n' + \
            '  return std::string(ss.str());\n' + \
            '});\n' + \
            f'{py_class}.def(py::pickle(\n' + \
            f'  []({cxx_class} const &self) -> std::array<double, {cxx_class}::Traits::max_size> * ' + '{\n' + \
            f'    std::array<double, {cxx_class}::Traits::max_size> *arr = new std::array<double, {cxx_class}::Traits::max_size>();\n' + \
            f'    memcpy(arr->data(), self.data(), {cxx_class}::Traits::max_size * sizeof(double));\n' + \
            '    return arr;' + \
            '    },\n' + \
            f'  [](std::array<double, {cxx_class}::Traits::max_size> const &arr) -> {cxx_class} * ' + '{\n' + \
            f'    {cxx_class} *other = new {cxx_class}();\n' + \
            f'    memcpy(other->data(), arr.data(), {cxx_class}::Traits::max_size * sizeof(double));\n' + \
            '    return other;' + \
            '}\n' + \
            '));\n' + \
            f'{py_class}.def("rows",     &{cxx_class}::rows);\n' + \
            f'{py_class}.def("cols",     &{cxx_class}::cols);\n' + \
            f'{py_class}.def("size",     &{cxx_class}::size);\n' + \
            f'{py_class}.def("__len__",  &{cxx_class}::size);\n' + \
            f'{py_class}.def("__getitem__", []({cxx_class} const &self, long i) -> double ' + '{\n' +\
            '  if (i < 0) i = self.size() + i;\n' + \
            '  if (i < 0 || ((lin::size_t) i) >= self.size()) throw py::index_error("Invalid indexing - index out of bounds!");\n' +\
            '  return self(i);\n' + \
            '});\n' + \
            f'{py_class}.def("__getitem__", []({cxx_class} const &self, std::tuple<long, long> t) -> double ' + '{\n' + \
            '  long i = (std::get<0>(t) < 0 ? self.rows() + std::get<0>(t) : std::get<0>(t));\n' + \
            '  long j = (std::get<1>(t) < 0 ? self.cols() + std::get<1>(t) : std::get<1>(t));\n' + \
            '  if (i < 0 || ((lin::size_t) i) >= self.rows()) throw py::index_error("Invalid indexing - row index out of bounds!");\n' + \
            '  if (j < 0 || ((lin::size_t) j) >= self.cols()) throw py::index_error("Invalid indexing - column index out of bounds!");\n' + \
            '  return self(i, j);\n' + \
            '});\n' + \
            f'{py_class}.def("__setitem__", []({cxx_class} &self, long i, double x) -> void ' + '{\n' + \
            '  if (i < 0) i = self.size() + i;\n' + \
            '  if (i < 0 || ((lin::size_t) i) >= self.size()) throw py::index_error("Invalid indexing - index out of bounds!");\n' +\
            '  self(i) = x;\n' + \
            '});\n' + \
            f'{py_class}.def("__setitem__", []({cxx_class} &self, std::tuple<long, long> t, double x) -> void ' + '{\n' +\
            '  long i = (std::get<0>(t) < 0 ? self.rows() + std::get<0>(t) : std::get<0>(t));\n' + \
            '  long j = (std::get<1>(t) < 0 ? self.cols() + std::get<1>(t) : std::get<1>(t));\n' + \
            '  if (i < 0 || ((lin::size_t) i) >= self.rows()) throw py::index_error("Invalid indexing - row index out of bounds!");\n' + \
            '  if (j < 0 || ((lin::size_t) j) >= self.cols()) throw py::index_error("Invalid indexing - column index out of bounds!");\n' + \
            '  self(i, j) = x;\n' + \
            '});\n' + \
            f'{py_class}.def("__neg__", []({cxx_class} const &self) -> {cxx_class} * ' + '{\n' + \
            f'  return new {cxx_class}(-self);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__pos__", []({cxx_class} const &self) -> {cxx_class} * ' + '{\n' + \
            f'  return new {cxx_class}(self);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__iadd__", []({cxx_class} &self, {cxx_class} const &other) -> {cxx_class} & ' + '{\n' \
            '  return (self = self + other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__iadd__", []({cxx_class} &self, double other) -> {cxx_class} & ' + '{\n' \
            '  return (self = self + other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__add__", []({cxx_class} const &self, {cxx_class} const &other) -> {cxx_class} * ' + '{\n' \
            f'  return new {cxx_class}(self + other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__add__", []({cxx_class} const &self, double other) -> {cxx_class} * ' + '{\n' \
            f'  return new {cxx_class}(self + other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__radd__", []({cxx_class} const &self, double other) -> {cxx_class} * ' + '{\n' \
            f'  return new {cxx_class}(other + self);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__itruediv____", []({cxx_class} &self, {cxx_class} const &other) -> {cxx_class} & ' + '{\n' \
            '  return (self = self / other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__itruediv____", []({cxx_class} &self, double other) -> {cxx_class} & ' + '{\n' \
            '  return (self = self / other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__truediv__", []({cxx_class} const &self, {cxx_class} const &other) -> {cxx_class} * ' + '{\n' \
            f'  return new {cxx_class}(self / other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__truediv__", []({cxx_class} const &self, double other) -> {cxx_class} * ' + '{\n' \
            f'  return new {cxx_class}(self / other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__rtruediv__", []({cxx_class} const &self, double other) -> {cxx_class} * ' + '{\n' \
            f'  return new {cxx_class}(other / self);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__isub__", []({cxx_class} &self, {cxx_class} const &other) -> {cxx_class} & ' + '{\n' \
            '  return (self = self - other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__isub__", []({cxx_class} &self, double other) -> {cxx_class} & ' + '{\n' \
            '  return (self = self - other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__sub__", []({cxx_class} const &self, {cxx_class} const &other) -> {cxx_class} * ' + '{\n' \
            f'  return new {cxx_class}(self - other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__sub__", []({cxx_class} const &self, double other) -> {cxx_class} * ' + '{\n' \
            f'  return new {cxx_class}(self - other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__rsub__", []({cxx_class} const &self, double other) -> {cxx_class} * ' + '{\n' \
            f'  return new {cxx_class}(other - self);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__imul__", []({cxx_class} &self, double other) -> {cxx_class} & ' + '{\n' + \
            f'  return (self = other * self);' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__mul__", []({cxx_class} const &self, double other) -> {cxx_class} * ' + '{\n' + \
            f'  return new {cxx_class}(self * other);\n' + \
            '}, py::is_operator());\n' + \
            f'{py_class}.def("__rmul__", []({cxx_class} const &self, double other) -> {cxx_class} * ' + '{\n' + \
            f'  return new {cxx_class}(other * self);\n' + \
            '}, py::is_operator());\n' + \
            '\n'
    def __gen_uop(cxx_class, op):
        return \
            f'm.def("{op}", []({cxx_class} const &c) -> decltype(lin::{op}(c).eval()) * ' + '{ ' + f'return new decltype(lin::{op}(c).eval())(lin::{op}(c));' + ' });\n'
    def __gen_bop(cxx_class, op):
        return \
            f'm.def("{op}", []({cxx_class} const &u, {cxx_class} const &v) -> {cxx_class} * ' + '{ ' + f'return new {cxx_class}(lin::{op}(u,v));' + ' });\n' + \
            f'm.def("{op}", []({cxx_class} const &u, double v) -> {cxx_class} * ' + '{ ' + f'return new {cxx_class}(lin::{op}(u,v));' + ' });\n' + \
            f'm.def("{op}", [](double u, {cxx_class} const &v) -> {cxx_class} * ' + '{ ' + f'return new {cxx_class}(lin::{op}(u,v));' + ' });\n'
    def __gen_uops(cxx_class):
        return \
            f'm.def("fro", []({cxx_class} const &c) -> double' + ' { return lin::fro(c); });\n' + \
            __gen_uop(cxx_class, 'negate') + \
            __gen_uop(cxx_class, 'sign') + \
            __gen_uop(cxx_class, 'square') + \
            f'm.def("sum", []({cxx_class} const &c) -> double' + ' { return lin::sum(c); });\n' + \
            __gen_uop(cxx_class, 'transpose') + \
            f'm.def("isfinite", []({cxx_class} const &c) -> bool' + ' { return lin::all(lin::isfinite(c)); });\n' + \
            '\n'
    def __gen_bops(cxx_class):
        return \
            __gen_bop(cxx_class, 'add') + \
            __gen_bop(cxx_class, 'divide') + \
            __gen_bop(cxx_class, 'multiply') + \
            __gen_bop(cxx_class, 'subtract')


    # Generating module source code
    with open(os.path.join(os.path.abspath(os.path.dirname(__file__)), 'lin.cpp'), 'w') as ostream:

        # Header
        ostream.write(r'''
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <lin/core.hpp>
#include <lin/generators.hpp>
#include <lin/math.hpp>
#include <lin/queries.hpp>

#include <array>
#include <cstring>
#include <exception>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>

PYBIND11_MODULE(lin, m) {

'''
        )

        # Column vector types
        ostream.write(r'''// -----
// Vector type definitions
//

'''
        )
        for i in range(2, _SQR + 1):
            ostream.write(__gen_class(__cxx_vector(i), __py_vector(i)))
        ostream.write(r'''// -----

'''
        )

        # Column vector types
        ostream.write(r'''// -----
// Row vector type definitions
//

'''
        )
        for i in range(2, _SQR + 1):
            ostream.write(__gen_class(__cxx_row_vector(i), __py_row_vector(i)))
        ostream.write(r'''// -----

'''
        )

        # Matrix types
        ostream.write(r'''// -----
// Matrix type definitions
//

'''
        )
        for i in range(2, _ALL + 1):
            for j in range(2, _ALL + 1):
                ostream.write(__gen_class(__cxx_matrix(i, j), __py_matrix(i, j)))
        for i in range(_ALL + 1, _SQR + 1):
            ostream.write(__gen_class(__cxx_matrix(i, i), __py_matrix(i, i)))
        ostream.write(r'''// -----

'''
        )

        # Matrix multiplication operators
        ostream.write(r'''// -----
// Matrix multiplication operators
//

'''
        )
        for i in range(2, _ALL + 1):
            for j in range(2, _ALL + 1):
                ostream.write(
                    f'{__py_vector(i)}.def("__mul__", []({__cxx_vector(i)} const &self, {__cxx_row_vector(j)} const &other) -> decltype((self * other).eval()) * ' +
                    '{ return new decltype((self * other).eval())(self * other); }, py::is_operator());\n'
                )
        for i in range(_ALL + 1, _SQR + 1):
            ostream.write(
                f'{__py_vector(i)}.def("__mul__", []({__cxx_vector(i)} const &self, {__cxx_row_vector(i)} const &other) -> decltype((self * other).eval()) * ' +
                '{ return new decltype((self * other).eval())(self * other); }, py::is_operator());\n'
            )
        ostream.write('\n')

        for i in range(2, _ALL + 1):
            for j in range(2, _ALL + 1):
                for k in range(1, _ALL + 1):
                    if k == 1:
                        other = __cxx_vector(j)
                    else:
                        other = __cxx_matrix(j, k)
                    ostream.write(
                        f'{__py_matrix(i, j)}.def("__mul__", []({__cxx_matrix(i, j)} const &self, {other} const &other) -> decltype((self * other).eval()) * ' +
                        '{ return new decltype((self * other).eval())(self * other); }, py::is_operator());\n'
                    )
        for i in range(_ALL + 1, _SQR + 1):
            ostream.write(
                f'{__py_matrix(i, i)}.def("__mul__", []({__cxx_matrix(i, i)} const &self, {__cxx_matrix(i, i)} const &other) -> decltype((self * other).eval()) * ' +
                '{ return new decltype((self * other).eval())(self * other); }, py::is_operator());\n'
            )
            ostream.write(
                f'{__py_matrix(i, i)}.def("__mul__", []({__cxx_matrix(i, i)} const &self, {__cxx_vector(i)} const &other) -> decltype((self * other).eval()) * ' +
                '{ return new decltype((self * other).eval())(self * other); }, py::is_operator());\n'
            )
        ostream.write('\n')

        for i in range(2, _ALL + 1):
            for k in range(2, _ALL + 1):
                ostream.write(
                    f'{__py_row_vector(i)}.def("__mul__", []({__cxx_row_vector(i)} const &self, {__cxx_matrix(i, k)} const &other) -> decltype((self * other).eval()) * ' +
                    '{ return new decltype((self * other).eval())(self * other); }, py::is_operator());\n'
                )
        for i in range(_ALL + 1, _SQR + 1):
            ostream.write(
                f'{__py_row_vector(i)}.def("__mul__", []({__cxx_row_vector(i)} const &self, {__cxx_matrix(i, i)} const &other) -> decltype((self * other).eval()) * ' +
                '{ return new decltype((self * other).eval())(self * other); }, py::is_operator());\n'
            )

        # Operators
        ostream.write(r'''// -----
// Operators
//

'''
        )
        for i in range(2, _SQR + 1):
            ostream.write(f'm.def("dot", []({__cxx_vector(i)} const &u, {__cxx_vector(i)} const &v) -> double' + ' { return lin::dot(u, v); });\n')
            ostream.write(f'm.def("dot", []({__cxx_vector(i)} const &u, {__cxx_row_vector(i)} const &v) -> double' + ' { return lin::dot(u, v); });\n')
            ostream.write(f'm.def("norm", []({__cxx_vector(i)} const &u) -> double' + ' { return lin::norm(u); });\n')
            ostream.write(__gen_uops(__cxx_vector(i)))
            ostream.write(__gen_bops(__cxx_vector(i)))
        for i in range(2, _SQR + 1):
            ostream.write(f'm.def("dot", []({__cxx_row_vector(i)} const &u, {__cxx_row_vector(i)} const &v) -> double' + ' { return lin::dot(u, v); });\n')
            ostream.write(f'm.def("dot", []({__cxx_row_vector(i)} const &u, {__cxx_vector(i)} const &v) -> double' + ' { return lin::dot(u, v); });\n')
            ostream.write(f'm.def("norm", []({__cxx_row_vector(i)} const &c) -> double' + ' { return lin::norm(c); });\n')
            ostream.write(__gen_uops(__cxx_row_vector(i)))
            ostream.write(__gen_bops(__cxx_row_vector(i)))
        for i in range(2, _ALL + 1):
            for j in range(2, _ALL + 1):
                if i == j:
                    ostream.write(f'm.def("trace", []({__cxx_matrix(i, j)} const &m) -> double' + ' { return lin::trace(m); });\n')
                ostream.write(__gen_uops(__cxx_matrix(i, j)))
                ostream.write(__gen_bops(__cxx_matrix(i, j)))
        for i in range(_ALL + 1, _SQR + 1):
            ostream.write(f'm.def("trace", []({__cxx_matrix(i, i)} const &m) -> double' + ' { return lin::trace(m); });\n')
            ostream.write(__gen_uops(__cxx_matrix(i, i)))
            ostream.write(__gen_bops(__cxx_matrix(i, i)))
        if _SQR >= 3:
            ostream.write(r'''
m.def("cross", [](lin::Vector3d const &u, lin::Vector3d const &v) -> lin::Vector3d { return lin::cross(u, v); });
m.def("cross", [](lin::Vector3d const &u, lin::RowVector3d const &v) -> lin::Vector3d { return lin::cross(u, v); });
m.def("cross", [](lin::RowVector3d const &u, lin::Vector3d const &v) -> lin::RowVector3d { return lin::cross(u, v); });
m.def("cross", [](lin::RowVector3d const &u, lin::RowVector3d const &v) -> lin::RowVector3d { return lin::cross(u, v); });'''
            )
        ostream.write(r'''

// -----

'''
        )

        # Footer
        ostream.write(r'''}
'''
        )


autocode()
setup(
    name='lin',
    version=__version__,
    author='Kyle Krol',
    author_email='kyle.krol.27@gmail.com',
    url='https://github.com/kkrol27/lin',
    description='Simple python wrapper for lin matrix and vector types.',
    long_description='',
    ext_modules=ext_modules,
    setup_requires=['pybind11>=2.5.0'],
    install_requires=['numpy'],
    cmdclass={'build_ext': BuildExt},
    zip_safe=False,
)
