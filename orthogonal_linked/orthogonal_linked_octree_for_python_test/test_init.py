import pytest
import orthogonal_linked_octree_for_python


def test_init():
    with pytest.raises(ZeroDivisionError):
        1 / 0
