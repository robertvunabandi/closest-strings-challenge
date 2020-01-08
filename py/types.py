import enum


class IntEnum(enum.Enum):
    """
    An enumeration of integers.
    """
    def __str__(self):
        return str(self.value)
    
    def __repr__(self):
        return f"<{self.__class__.__name__}.{self.name}>"
