# Copyright (c) 2020 Robert M. Vunabandi
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

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
