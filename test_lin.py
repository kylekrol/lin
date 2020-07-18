"""Simple collection of unit tests for the lin library.

These functions are written somewhat sparesely as the module is written using
an autocoder. The goal is to test all functions on only a handful of lin types.
"""

import lin

import numpy as np
import pytest


def test_constructor():
    """Tests constructs for the generic lin types. We ensure lin objects are
    zero initialized and can be generated from arrays of one and two dimensions.
    """
    m = lin.Matrix3x3()
    for i in range(len(m)):
        assert m[i] == 0.0

    v = lin.Vector3()
    for i in range(len(v)):
        assert v[i] == 0.0

    m = lin.Matrix3x3([
        [0.0, 1.0, 2.0],
        [3.0, 4.0, 5.0],
        [6.0, 7.0, 8.0]
    ])
    for i in range(len(m)):
        assert m[i] == float(i)

    m = lin.Matrix2x2([
        0.0, 1.0,
        2.0, 3.0
    ])
    for i in range(len(m)):
        assert m[i] == float(i)


def test_dimensions():
    """Tests the dimensions reported by lin objects are accurate.
    """
    m = lin.Matrix4x3()
    assert m.rows() == 4
    assert m.cols() == 3
    assert m.size() == 12

    v = lin.RowVector2()
    assert v.rows() == 1
    assert v.cols() == 2
    assert v.size() == 2


def test_get_item():
    """Tests element access from lin objects. This includes tests for negative
    indexing and expected exceptions.
    """
    n = lin.Matrix3x2([
        0.0, 1.0,
        2.0, 3.0,
        4.0, 5.0
    ])

    assert (n[0] == 0.0) and (n[1] == 1.0) and (n[-1] == 5.0) and (n[-2] == 4.0)

    assert (n[0, 1] == 1.0) and (n[1, 1] == 3.0) and (n[-1,  0] == 4.0) and \
            (n[-2, -1] == 3.0) and (n[-3,  1] == 1.0)

    with pytest.raises(IndexError):
        n[3, 0]
    with pytest.raises(IndexError):
        n[-4, 0]

    with pytest.raises(IndexError):
        n[0, 2]
    with pytest.raises(IndexError):
        n[0, -3]

    with pytest.raises(IndexError):
        n[6]
    with pytest.raises(IndexError):
        n[-7]


def test_set_item():
    """Tests element written to lin objects. This includes tests for negative
    indexing and expected exceptions.
    """
    m = lin.Matrix2x3()

    def set_and_check(x, *args):
        if len(args) == 1:
            args = args[0]
        assert m[args] != x
        m[args] = x
        assert m[args] == x

    set_and_check(1.0,  0,  2)
    set_and_check(2.0,  0, -1)
    set_and_check(3.0,  1,  0)
    set_and_check(4.0, -1,  0)

    set_and_check(5.0,  3)
    set_and_check(6.0, -2)

    with pytest.raises(IndexError):
        m[2, 0]

    with pytest.raises(IndexError):
        m[-3, 0]

    with pytest.raises(IndexError):
        m[6]

    with pytest.raises(IndexError):
        m[-7]


def test_numpy_compatability():
    """Tests compatbility with NumPy and Python's buffer protocol system.

    Here, we're checking for the following functionality:
     * Constructs NumPy arrays from lin objects.
     * Construct lin objects from NumPy arrays.
     * Casting lin objects to NumPy arrays without copying.
    """
    m = np.array([
        [0.0, 1.0, 2.0, 3.0],
        [4.0, 5.0, 6.0, 7.0]
    ])

    n = lin.Matrix2x4(m)
    assert np.all(np.array(n) == m)

    m = lin.Vector2([0.0, 1.0])
    n = np.array(m, copy=False)
    
    n[0] = 3.0
    assert np.all(np.array(m) == n)


@pytest.mark.skip(reason='Not implemented yet!')
def test_pickle():
    """Tests pickling support.
    """
    pass # TODO : Implement this


def test_generators():
    """Tests the zeros, ones, and nans generator functions.
    """
    m = lin.Matrix2x2.ones()
    for i in range(m.size()):
        assert m[i] == 1.0

    m = lin.Matrix2x2.nans()
    for i in range(m.size()):
        assert m[i] != m[i]

    m = lin.Matrix2x2.zeros()
    for i in range(m.size()):
        assert m[i] == 0.0


def test_add():
    """Tests all overloads of the addition operator and add function.

    We'll test all binary operator overloads of the add function here to fully
    test the autocoder's binary operator generation function. These overloads
    will then be skipped for other operators.
    """
    a = lin.Matrix2x2([
        0.0, 1.0,
        2.0, 3.0
    ])
    b = lin.Matrix2x2()

    c = a + b
    assert type(c) is lin.Matrix2x2
    assert (c[0, 0] == 0.0) and (c[0, 1] == 1.0) and (c[1, 0] == 2.0) and \
            (c[1, 1] == 3.0)

    c = a + 2.0
    assert type(c) is lin.Matrix2x2
    assert (c[0, 0] == 2.0) and (c[0, 1] == 3.0) and (c[1, 0] == 4.0) and \
            (c[1, 1] == 5.0)

    c = 1.0 + a
    assert type(c) is lin.Matrix2x2
    assert (c[0, 0] == 1.0) and (c[0, 1] == 2.0) and (c[1, 0] == 3.0) and \
            (c[1, 1] == 4.0)

    b += 2.0
    assert type(b) is lin.Matrix2x2
    assert (b[0, 0] == 2.0) and (b[0, 1] == 2.0) and (b[1, 0] == 2.0) and \
            (b[1, 1] == 2.0)

    a += b
    assert type(a) is lin.Matrix2x2
    assert (a[0, 0] == 2.0) and (a[0, 1] == 3.0) and (a[1, 0] == 4.0) and \
            (a[1, 1] == 5.0)

    # Do a full binary operator test for add.
    a = lin.Vector2()
    b = lin.Vector2([1.0, 2.0])

    c = lin.add(a, b)
    assert type(c) is lin.Vector2
    assert (c[0] == 1.0) and (c[1] == 2.0)

    a = lin.add(c, -1.0)
    assert type(a) is lin.Vector2
    assert (a[0] == 0.0) and (a[1] == 1.0)

    b = lin.add(5.0, a)
    assert type(b) is lin.Vector2
    assert (b[0] == 5.0) and (b[1] == 6.0)


def test_cross():
    """Tests all overloads of the cross product function.
    """
    u = lin.Vector3([1.0, 0.0, 0.0])
    v = lin.Vector3([0.0, 1.0, 0.0])

    w = lin.cross(u, v)
    assert type(w) is lin.Vector3
    assert (w[0] == 0.0) and (w[1] == 0.0) and (w[2] == 1.0)

    v = lin.RowVector3([0.0, 1.0, 0.0])

    w = lin.cross(u, v)
    assert type(w) is lin.Vector3
    assert (w[0] == 0.0) and (w[1] == 0.0) and (w[2] == 1.0)

    u = lin.RowVector3([1.0, 0.0, 0.0])

    w = lin.cross(u, v)
    assert type(w) is lin.RowVector3
    assert (w[0] == 0.0) and (w[1] == 0.0) and (w[2] == 1.0)

    v = lin.Vector3([0.0, 1.0, 0.0])

    w = lin.cross(u, v)
    assert type(w) is lin.RowVector3
    assert (w[0] == 0.0) and (w[1] == 0.0) and (w[2] == 1.0)


def test_divide():
    """Tests all overloads of the division operator and divide function.
    """
    a = lin.Vector2([ 1.0, 2.0])
    b = lin.Vector2([-1.0, 4.0])

    c = a / b
    assert type(c) is lin.Vector2
    assert (c[0] == -1.0) and (c[1] == 0.5)

    c = a / 2.0
    assert type(c) is lin.Vector2
    assert (c[0] == 0.5) and (c[1] == 1.0)

    c = 2.0 / a
    assert type(c) is lin.Vector2
    assert (c[0] == 2.0) and (c[1] == 1.0)

    c = lin.divide(a, 2.0)
    assert type(c) is lin.Vector2
    assert (c[0] == 0.5) and (c[1] == 1.0)


def test_dot():
    """Tests all overloads of the dot product function.
    """
    u = lin.RowVector3([0.0, 2.0, 1.0])
    v = lin.Vector3([1.0, -0.5, 2.0])

    assert lin.dot(u, u) == 5.0
    assert lin.dot(u, v) == 1.0
    assert lin.dot(v, u) == 1.0
    assert lin.dot(v, v) == 5.25


def test_fro():
    """Tests the frobenius norm function.
    """
    m = lin.Matrix2x3([
        0.0,  1.0, 2.0,
        3.0, -1.0, 0.0
    ])

    assert lin.fro(m) == 15.0


def test_isfinite():
    """Tests the isfinite function.
    """
    u = lin.Vector3([0.0, 0.0, float('nan')])
    v = lin.Vector2()

    assert not lin.isfinite(u)
    assert lin.isfinite(v)


def test_multiply():
    """Tests all the overloads of the multiplication operator and multiply
    function.
    """
    a = lin.Matrix3x3([
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    ])

    b = lin.Vector3([1.0, 2.0, 3.0])
    c = a * b
    assert type(c) is lin.Vector3
    assert (c[0] == 1.0) and (c[1] == 2.0) and (c[2] == 3.0)

    b = lin.Matrix3x2([
        1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0
    ])
    c = a * b
    assert type(c) is lin.Matrix3x2
    for i in range(len(c)):
        assert c[i] == b[i]

    c = a * a
    assert type(c) is lin.Matrix3x3
    for i in range(len(c)):
        assert c[i] == a[i]

    a = lin.Vector2([1.0, 3.0])
    b = lin.RowVector2([1.0, 2.0])

    c = a * b
    assert type(c) is lin.Matrix2x2
    assert (c[0, 0] == 1.0) and (c[0, 1] == 2.0) and (c[1, 0] == 3.0) and \
            (c[1, 1] == 6.0)

    a *= 2.0
    assert (a[0] == 2.0) and (a[1] == 6.0)

    c = a * 0.5
    assert type(c) is lin.Vector2
    assert (c[0] == 1.0) and (c[1] == 3.0)

    c = 2.0 * b
    assert type(c) is lin.RowVector2
    assert (c[0] == 2.0) and (c[1] == 4.0)

    a = lin.RowVector2([2.0, 2.0])

    c = lin.multiply(a, b)
    assert type(c) is lin.RowVector2
    assert (c[0] == 2.0) and (c[1] == 4.0)


def test_negate():
    """Tests the unary negative operator and negate function.
    """
    u = lin.Vector2([1.0, -2.0])

    v = -u
    assert type(v) is lin.Vector2
    assert (v[0] == -1.0) and (v[1] == 2.0)

    u = lin.negate(v)
    assert type(u) is lin.Vector2
    assert (u[0] == 1.0) and (u[1] == -2.0)


def test_norm():
    """Tests all the overloads of the vector two norm function.
    """
    u = lin.Vector2([3.0, 4.0])
    v = lin.RowVector3([3.0, 0.0, 4.0])

    assert lin.norm(u) == 5.0
    assert lin.norm(v) == 5.0


def test_positive():
    """Tests the unary plus operator.
    """
    u = lin.Vector2([1.0, -2.0])

    v = +u
    assert type(v) is lin.Vector2
    assert (v[0] == 1.0) and (v[1] == -2.0)


def test_sign():
    """Tests the sign function.
    """
    u = lin.Vector3([-1.0, 0.0, 5.0])

    v = lin.sign(u)
    assert type(v) is lin.Vector3
    assert (v[0] == -1.0) and (v[1] == 0.0) and (v[2] == 1.0)


def test_square():
    """Tests the square function.
    """
    u = lin.Vector3([1.0, -3.0, 2.0])

    v = lin.square(u)
    assert type(v) is lin.Vector3
    assert (v[0] == 1.0) and (v[1] == 9.0) and (v[2] == 4.0)


def test_subtract():
    """Tests all overloads of the subtraction operator and subtract function.
    """
    a = lin.Matrix2x2([
        0.0, 1.0,
        2.0, 3.0
    ])
    b = lin.Matrix2x2()

    c = b - a
    assert type(c) is lin.Matrix2x2
    assert (c[0, 0] == 0.0) and (c[0, 1] == -1.0) and (c[1, 0] == -2.0) and \
            (c[1, 1] == -3.0)

    c = a - 2.0
    assert type(c) is lin.Matrix2x2
    assert (c[0, 0] == -2.0) and (c[0, 1] == -1.0) and (c[1, 0] == 0.0) and \
            (c[1, 1] == 1.0)

    c = 1.0 - a
    assert type(c) is lin.Matrix2x2
    assert (c[0, 0] == 1.0) and (c[0, 1] == 0.0) and (c[1, 0] == -1.0) and \
        (c[1, 1] == -2.0)

    a -= 2.0
    assert type(a) is lin.Matrix2x2
    assert (a[0, 0] == -2.0) and (a[0, 1] == -1.0) and (a[1, 0] == 0.0) and \
            (a[1, 1] == 1.0)

    b -= a
    assert type(b) is lin.Matrix2x2
    assert (b[0, 0] == 2.0) and (b[0, 1] == 1.0) and (b[1, 0] == 0.0) and \
            (b[1, 1] == -1.0)

    c = lin.subtract(a, 1.0)
    assert type(a) is lin.Matrix2x2
    assert (c[0, 0] == -3.0) and (c[0, 1] == -2.0) and (c[1, 0] == -1.0) and \
            (c[1, 1] == 0.0)


def test_trace():
    """Tests the trace function on for square matrices.
    """
    m = lin.Matrix3x3([
        0.0, 1.0, 2.0,
        3.0, 4.0, 5.0,
        6.0, 7.0, 8.0
    ])

    assert lin.trace(m) == 12.0


def test_transpose():
    """Tests the transpose function and ensures the proper type is returned.
    """
    m = lin.Matrix2x3([
        0.0, 1.0, 2.0,
        3.0, 4.0, 5.0
    ])

    n = lin.transpose(m)
    assert type(n) is lin.Matrix3x2
    assert (n[0, 0] == 0.0) and (n[1, 0] == 1.0) and (n[2, 0] == 2.0) and \
        (n[0, 1] == 3.0) and (n[1, 1] == 4.0) and (n[2, 1] == 5.0)
    
    u = lin.Vector2([0.0, 1.0])

    v = lin.transpose(u)
    assert type(v) is lin.RowVector2
    assert (v[0] == 0.0) and (v[1] == 1.0)
