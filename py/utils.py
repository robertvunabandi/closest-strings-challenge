_C_RED = "\033[1;31m"
_C_BLUE = "\033[1;34m"
_C_CYAN = "\033[1;36m"
_C_GREEN = "\033[0;32m"
_C_YELLOW = "\033[1;33m"
_C_RESET = "\033[0;0m"
_C_BOLD = "\033[;1m"
_C_REVERSE = "\033[;7m"

def _in_color(s: str, color: str) -> str:
    return "{}{}{}".format(color, str(s), _C_RESET)

def in_red(s: str) -> str: 
    return _in_color(s, _C_RED)
def in_green(s: str) -> str: 
    return _in_color(s, _C_GREEN)
def in_cyan(s: str) -> str: 
    return _in_color(s, _C_CYAN)
def in_blue(s: str) -> str: 
    return _in_color(s, _C_BLUE)
def in_bold(s: str) -> str: 
    return _in_color(s, _C_BOLD)
def in_yellow(s: str) -> str: 
    return _in_color(s, _C_YELLOW)
